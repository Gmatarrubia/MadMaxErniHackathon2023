from picarx import Picarx
import zmq
import time

px = Picarx()

# Initialize incoming comms
context = zmq.Context()
subSocket = context.socket(zmq.SUB)
subSocket.connect("ipc:///tmp/fromWebCom")
subSocket.setsockopt_string(zmq.SUBSCRIBE, "control_mode")
subSocket.setsockopt_string(zmq.SUBSCRIBE, "automatic_move")
subSocket.setsockopt_string(zmq.SUBSCRIBE, "manual_move")

#initialize outcoming comms
pubSocket = context.socket(zmq.PUB)
pubSocket.bind("ipc:///tmp/toWebCom")

#Global status
CONTROL_MODE = 0
SPEED = 0
STATUS = "initial"
def move(operate:str, speed):
    global SPEED
    global STATUS
    if operate == 'stop':
        px.stop()
        SPEED = 0
        STATUS = "stop"
    else:
        if operate == 'forward':
            px.set_dir_servo_angle(0)
            px.forward(speed)
        elif operate == 'backward':
            px.set_dir_servo_angle(0)
            px.backward(speed)
        elif operate == 'left':
            px.set_dir_servo_angle(-30)
            px.forward(speed)
        elif operate == 'right':
            px.set_dir_servo_angle(30)
            px.forward(speed)
        STATUS = "run"
    # Update state
    pubSocket.send_string(f"speed {SPEED}")
    pubSocket.send_string(f"status {STATUS}")

def main():
    global CONTROL_MODE
    global SPEED
    try:
        while True:
            message = subSocket.recv_string()
            topic , value = message.split(' ')

            if str(topic) == "control_mode":
                CONTROL_MODE = int(value)
            if str(topic) == "manual_move":
                SPEED = 10  # Default speed for manual mode
                move(value, SPEED)
    except KeyboardInterrupt:
        # Manually stop all active listener threads if you press Ctrl+C
        stop_listeners()
        print("Program stopped.")

if __name__ == "__main__":
    main()
