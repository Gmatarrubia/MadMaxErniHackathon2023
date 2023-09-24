import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import time
import threading

current_mode = 0  # Initialize with 0 (automatic)
active_listener_threads = [] # keep track of active listener threads

# Firebase initialization
def initialize_firebase():
    cred = credentials.Certificate("/home/madmax/Desktop/firebase-test/credentials.json")
    firebase_admin.initialize_app(cred, {
        'databaseURL': 'https://mad-max-erni-default-rtdb.firebaseio.com'
    })

    # Fetch the initial value of 'controlType' from the database
    ref = db.reference('controlType')
    initial_control_data = ref.get()
    
    if initial_control_data is not None:
        global current_mode
        current_mode = initial_control_data.get('type', 0)  # Default to 0 if 'type' is not found

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
    current_mode = control_data.get('type', 0) # Update current_mode with the control_type
    pass


# Automatic listener callback
def automatic_listener_callback(event):
    pass

# Manual listener callback
def manual_listener_callback(event):
    pass

def stop_listeners():
    for listener_thread in active_listener_threads:
        listener_thread.stop()
        listener_thread.join()

def main():
    initialize_firebase()
    set_initial_values()
    
    # Start all listeners
    start_listener('controlType', control_listener_callback)
    start_listener('automatic', automatic_listener_callback)
    start_listener('manual', manual_listener_callback)

    try:
        while True:
            status_data = {"progress": 3, "speed": 1, "status": "paused"}
            print("status: ", status_data)
            update_status(status_data)
            
            time.sleep(10)

    except KeyboardInterrupt:
        # Manually stop all active listener threads if you press Ctrl+C
        stop_listeners()
        print("Program stopped.")

def update_status(status_data):
    # Update status db
    ref = db.reference('status')
    ref.update(status_data)

if __name__ == "__main__":
    main()
