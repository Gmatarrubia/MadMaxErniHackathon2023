import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import time
import threading
import socket
import os
import zmq

CONTROL_MODE = 0  # Initialize with 0 (automatic)
AUTOMATIC_MOVE = 0
MANUAL_MOVE = 0
PROGRESS = 0
SPEED = 0
STATUS = "paused"
active_listener_threads = [] # keep track of active listener threads

context = zmq.Context()

# Firebase initialization
def initialize_firebase():
    cred = credentials.Certificate("./CommunicationModule/credentials.json")
    firebase_admin.initialize_app(cred, {
        'databaseURL': 'https://mad-max-erni-default-rtdb.firebaseio.com'
    })

    # Fetch the initial value of 'controlType' from the database
    ref = db.reference('controlType')
    initial_control_data = ref.get()
    
    if initial_control_data is not None:
        global CONTROL_MODE
        CONTROL_MODE = initial_control_data.get('type', 0)  # Default to 0 if 'type' is not found

# Function to set initial values
def set_initial_values():
    ref = db.reference('automatic')
    ref.update({'move': 0})

def update_status(status_data):
    # Update status db
    ref = db.reference('status')
    ref.update(status_data)

# Function to start a listener thread
def start_listener(collection_name, pubsock, callback):
    ref = db.reference(collection_name)

    def listener_callback(event):
        print(f"{collection_name} changed: {event.event_type}, New value: {event.data}")
        callback(event, pubsock)

    listener_thread = threading.Thread(target=lambda: ref.listen(listener_callback))
    listener_thread.start()
    active_listener_threads.append(listener_thread)
    return listener_thread

# Socket callback
def start_socket_read(socket):
    def listener_function():
        global SPEED
        global STATUS
        global PROGRESS
        while True:
            message = socket.recv_string()
            topic , value = message.split(' ')
            if topic == "speed":
                SPEED = int(value)
            elif topic == "progress":
                PROGRESS = int(value)
            elif topic == "status":
                STATUS = str(value)
            status_data = {"progress": PROGRESS, "speed": SPEED, "status": STATUS}
            print("status: ", status_data)
            update_status(status_data)

    subscriber_thread = threading.Thread(target=listener_function)
    subscriber_thread.daemon = True  # Set the thread as a daemon so it exits when the main program exits
    subscriber_thread.start()

# ControlType listener callback
def control_listener_callback(event, pubSock):
    global CONTROL_MODE
    control_data = event.data
    CONTROL_MODE = control_data.get('type', 0) # Update CONTROL_MODE with the control_type
    pubSock.send_string(f"control_mode {CONTROL_MODE}")

# Automatic listener callback
def automatic_listener_callback(event, pubSock):
    global AUTOMATIC_MOVE
    automatic_data = event.data
    AUTOMATIC_MOVE = automatic_data.get('move', 0) # Update CONTROL_MODE with the control_type
    if CONTROL_MODE == 0:
        pubSock.send_string(f"automatic_move {AUTOMATIC_MOVE}")

# Manual listener callback
def manual_listener_callback(event, pubSock):
    global MANUAL_MOVE
    manual_data = event.data
    if manual_data.get('down', 0) == True:
        MANUAL_MOVE = "back"
    elif manual_data.get('up', 0) == True:
        MANUAL_MOVE = "fordward"
    elif manual_data.get('left', 0) == True:
        MANUAL_MOVE = "left"
    elif manual_data.get("right", 0) == True:
        MANUAL_MOVE = "right"
    else:
        MANUAL_MOVE = "stop"
    if CONTROL_MODE == 1:
        pubSock.send_string(f"manual_move {MANUAL_MOVE}")

def stop_listeners():
    for listener_thread in active_listener_threads:
        listener_thread.stop()
        listener_thread.join()

def main():
    #Socket creation
    toWebSock = context.socket(zmq.SUB)
    toWebSock.connect("ipc:///tmp/toWebCom")
    toWebSock.setsockopt_string(zmq.SUBSCRIBE, "progress")
    toWebSock.setsockopt_string(zmq.SUBSCRIBE, "speed")
    toWebSock.setsockopt_string(zmq.SUBSCRIBE, "status")
    fromWebSock = context.socket(zmq.PUB)
    fromWebSock.bind("ipc:///tmp/fromWebCom")

    start_socket_read(toWebSock)
    initialize_firebase()
    set_initial_values()

    # Start all listeners
    start_listener('controlType', fromWebSock, control_listener_callback)
    start_listener('automatic', fromWebSock, automatic_listener_callback)
    start_listener('manual', fromWebSock, manual_listener_callback)

    try:
        while True:
            time.sleep(10)

    except KeyboardInterrupt:
        # Manually stop all active listener threads if you press Ctrl+C
        stop_listeners()
        print("Program stopped.")

if __name__ == "__main__":
    main()
