#!/bin/bash

python3 /home/madmax/ErniHackathon2023/python/picar-x/example/configure.py

if [ $? -eq 0 ]; then
    ./build/madmaxRobot
else
    echo "Error during HW configuration"
fi
