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
            PROGRESS = PROGRESS + 1
            pubSocket.send_string(f"progress {PROGRESS}")
            print(f"Sent progress: {PROGRESS}")
            time.sleep(10)

    except KeyboardInterrupt:
        # Manually stop all active listener threads if you press Ctrl+C
        print("Program stopped.")

if __name__ == "__main__":
    main()
