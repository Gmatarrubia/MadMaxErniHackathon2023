#!/usr/bin/python
import zmq
import time

# Initialize incoming comms
context = zmq.Context()

#initialize outcoming comms
pubSocket = context.socket(zmq.PUB)
pubSocket.bind("ipc:///tmp/toWebCom")

#Global status
PROGRESS = 0

def main():
    global PROGRESS
    try:
        while True:
            # No object detection for 20 secs
            OBJECT_DETECTED = 0
            print("No object detected!")
            pubSocket.send_string(f"object_detected {OBJECT_DETECTED}")
            time.sleep(20)

            # Fake object detection for 3 secs
            OBJECT_DETECTED = 1
            print("Object detected! Stop!")
            pubSocket.send_string(f"object_detected {OBJECT_DETECTED}")
            time.sleep(3)

    except KeyboardInterrupt:
        # Manually stop all active listener threads if you press Ctrl+C
        print("Program stopped.")

if __name__ == "__main__":
    main()
