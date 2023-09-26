#!/usr/bin/python

import zmq
import time
import random

# Initialize incoming comms
context = zmq.Context()

#initialize outcoming comms
pubSocket = context.socket(zmq.PUB)
pubSocket.bind("ipc:///tmp/toWebCom")

#Global status
SPEED = 0

def main():
    global SPEED
    try:
        while True:
            SPEED = random.randint(5, 30)
            pubSocket.send_string(f"speed {SPEED}")
            print(f"Sent speed: {SPEED}")
            time.sleep(10)

    except KeyboardInterrupt:
        # Manually stop all active listener threads if you press Ctrl+C
        print("Program stopped.")

if __name__ == "__main__":
    main()
