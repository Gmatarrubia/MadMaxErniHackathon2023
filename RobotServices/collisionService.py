#!/usr/bin/python

from picarx import Picarx
import zmq
import time

px = Picarx()

# Initialize incoming comms
context = zmq.Context()

#initialize outcoming comms
pubSocket = context.socket(zmq.PUB)
pubSocket.bind("ipc:///tmp/fromWebCom")

#Global status
PROGRESS = 0

def main():
    global PROGRESS
    try:
        while True:
                distance = px.ultrasonic.read()
                if distance < 300:
                    OBJECT_DETECTED = 1
                else:
                    OBJECT_DETECTED = 0
                pubSocket.send_string(f"object_detected {OBJECT_DETECTED}")
                time.sleep(0.1)

    except KeyboardInterrupt:
        # Manually stop all active listener threads if you press Ctrl+C
        print("Program stopped.")

if __name__ == "__main__":
    main()
