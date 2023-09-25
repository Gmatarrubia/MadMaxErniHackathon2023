#!/bin/bash

echo "launching python services"

python ./CommunicationModule/CommunicationModule.py &
python ./RobotServices/moveService.py &
python ./RobotServices/progress.py &
python ./RbotoServices/collisionService.py &

echo "robot up and runnning"
