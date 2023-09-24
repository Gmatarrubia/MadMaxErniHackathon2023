import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import time
import threading

def initialize_firebase():
    # Initialize Firebase with your service account key
    cred = credentials.Certificate("./credentials.json")
    firebase_admin.initialize_app(cred, {
        'databaseURL': 'https://mad-max-erni-default-rtdb.firebaseio.com'
    })

def set_initial_move():
    ref = db.reference('automatic')
    ref.update({'move': 0})

def move_listener():
    ref = db.reference('automatic')

    def move_callback(event):
        print(f"Move changed: {event.event_type}, New value: {event.data}")

    ref.listen(move_callback)

def main():
    initialize_firebase()
    set_initial_move()

    # Start listener.
    move_listener_thread = threading.Thread(target=move_listener)
    move_listener_thread.start()

    try:
        while True:
            status_data = {"progress": 3, "speed": 1, "status": "paused"}
            print("status: ", status_data)
            update_status(status_data)
            
            time.sleep(10)

    except KeyboardInterrupt:
        # Stop the listener if you press Ctrl+C
        move_listener_thread.join()  # Wait for the move_listener_thread to complete
        print("Listener stopped.")

def update_status(status_data):
    # Update status db
    ref = db.reference('status')
    ref.update(status_data)

if __name__ == "__main__":
    main()

