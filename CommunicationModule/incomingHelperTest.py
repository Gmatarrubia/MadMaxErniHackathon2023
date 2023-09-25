import zmq
import time

context = zmq.Context()
socket = context.socket(zmq.SUB)
socket.connect("ipc:///tmp/fromWebCom")
socket.setsockopt_string(zmq.SUBSCRIBE, "control_mode")
socket.setsockopt_string(zmq.SUBSCRIBE, "automatic_move")
socket.setsockopt_string(zmq.SUBSCRIBE, "manual_move")
while True:
    message = socket.recv_string()
    topic , value = message.split(' ')
    print(f"{topic} {value}")

