#!/usr/bin/python

from picarx import Picarx
import zmq
import time

px = Picarx()

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
            value = px.get_grayscale_data()
            linea = px.get_line_status(value)
            if linea != "stop" :
                PROGRESS = PROGRESS + 1
                pubSocket.send_string(f"progress {PROGRESS}")
                time.sleep(5)

    except KeyboardInterrupt:
        # Manually stop all active listener threads if you press Ctrl+C
        stop_listeners()
        print("Program stopped.")

if __name__ == "__main__":
    main()
