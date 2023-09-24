import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
from enum import Enum
import time
import threading
import socket
import os

STATE = Enum('STATE', ['RUN', 'PAUSED'])
MODE = Enum('MODE', ['AUTOMATIC', 'MANUAL'])

progress = 0
status = "paused"
speed = 1

services_sock = ""
firebase_sock = ""
SERVICES_SOCK = "/tmp/robot_services_sock"
FIREBASE_SOCK = "/tmp/firebase_sock"

current_mode = MODE.AUTOMATIC  # Initialize with 0 (automatic)
active_listener_threads = [] # keep track of active listener threads

# Create a listen socket
def create_sock(sock_file):
    with socket.socket(socket.AF_UNIX, socket.SOCK_DGRAM) as s:
        try:
            s.bind(sock_file)
            s.listen(1)
            return(s)
        except FileExistsError:
            pass
        except socket.error:
            return(s)

def close_sock(sock_file):
    with socket.socket(socket.AF_UNIX, socket.SOCK_DGRAM) as s:
        s.close()
        os.remove(sock_file)

# Read from a socket
def write_sock(sock_file, value):
    with socket.socket(socket.AF_UNIX, socket.SOCK_DGRAM) as s:
        try:
            s.sendall(str(value).encode('utf-8'))
        finally:
            s.close()

# Initialice sockets
def create_sockets():
    global services_sock
    global firebase_sock
    services_sock = create_sock(SERVICES_SOCK)
    firebase_sock = create_sock(FIREBASE_SOCK)

def stop_sockets():
    close_sock(SERVICES_SOCK)
    close_sock(FIREBASE_SOCK)

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
        if initial_control_data.get('type, 0') == 0:
            current_mode = MODE.AUTOMATIC
        else:
            current_mode = MODE.MANUAL

# Function to set initial values
def set_initial_values():
    ref = db.reference('automatic')
    ref.update({'move': 0})

# Function to start a listener thread
def start_listener(collection_name, callback):
    ref = db.reference(collection_name)

    def listener_callback(event):
        print(f"{collection_name} changed: {event.event_type}, New value: {event.data}")
        callback(event)

    listener_thread = threading.Thread(target=lambda: ref.listen(listener_callback))
    listener_thread.start()
    active_listener_threads.append(listener_thread)
    return listener_thread

# ControlType listener callback
def control_listener_callback(event):
    global current_mode
    control_data = event.data
    value = control_data.get('type', 0)
    if value == 0:
        current_mode = MODE.AUTOMATIC
    else:
        current_mode = MODE.MANUAL


# Automatic listener callback
def automatic_listener_callback(event):
    global firebase_sock
    data = event.data

    if data.get('type', 0) == 1:
        current_mode = STATE.RUN
    else:
        current_mode = STATE.PAUSED
    client_socket, _ = firebase_sock.accept()
    write_sock(client_socket, current_mode)

# Manual listener callback
def manual_listener_callback(event):
    pass

def stop_listeners():
    for listener_thread in active_listener_threads:
        listener_thread.stop()
        listener_thread.join()

def update_status(status_data):
    # Update status db
    ref = db.reference('status')
    ref.update(status_data)

def service_stop():
        # Manually stop all active listener threads if you press Ctrl+C
        stop_listeners()
        stop_sockets()
        print("Program stopped.")

def main():
    initialize_firebase()
    set_initial_values()
    create_sockets()

    # Start all listeners
    start_listener('controlType', control_listener_callback)
    start_listener('automatic', automatic_listener_callback)
    start_listener('manual', manual_listener_callback)

    try:
        while True:
            status_data = {
                 "progress": progress,
                 "speed": speed,
                 "status": status,
                 }
            update_status(status_data)

            time.sleep(1)

    except KeyboardInterrupt:
            service_stop()
    finally:
            service_stop()

if __name__ == "__main__":
    main()
