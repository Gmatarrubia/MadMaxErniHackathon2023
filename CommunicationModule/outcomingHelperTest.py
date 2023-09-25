import zmq
import time

context = zmq.Context()
socket = context.socket(zmq.PUB)
socket.bind("ipc:///tmp/toWebCom")
progress = 0
speed = 200
status = "run"

while True:
    topic = "speed"
    socket.send_string(f"{topic} {speed}")

    topic = "progress"
    socket.send_string(f"{topic} {progress}")

    topic = "status"
    socket.send_string(f"{topic} {status}")
    time.sleep(1)
    progress = progress + 1
