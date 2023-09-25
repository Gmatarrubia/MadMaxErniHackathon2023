# ErniHackathon2023
Repository to be used on ERNI Hackaton 2023 by the team in Madrid.

## Overview
The project consists of the development of a Remote Robot Control System based on a PIcarx, an IoT robot platform. This system leverages Firebase, a cloud-based real-time database, to enable remote control and management of the robot's operations.

## Repo Structure
This repository includes all the piece of code developed to achieve the Erni hackathon goal.
1. In the folder `CommunicationModule` is located the Python controller logic which talk with the Web App.
2. `MadMaxWeb` contains the web app code. It is written using Angular.
3. `RobotServices` include all the robot microservices that are the interface with the real world.

## Architecture

Several microservices are running in the raspi in both, C++ and Python. These microservices read from the sersors and write the values to UNIX sockets. These UNIX sockets are read from the controller which contain the logic of the system. The controller is paired with the web interface throw a real-time database of firebase.

||Communication Method||
|---------------------------------|-----------------------------------|-----------------------|
| Microservices  (Python and C++) | <--UNIX Sockets-->                | Controller Python app |
| Controller PYthon app           | <--Firebase real-time database--> | Firebase Web App      |

## About PiCar-X:
PiCar-X is a versatile robotic car platform built around the Raspberry Pi. It is equipped with a wide range of sensors and features that enable diverse functionalities, making it a highly adaptable and interactive robotics platform.

## Download
Download this repository to your Raspberry Pi:

```shell
git clone https://github.com/FernandoAnegon/ErniHackathon2023.git
```
## Installation
`MadMaxWeb` is the web app which allows the user to control the robot remotely. It is a SPA (Single Page Application) built using the Angular framework. The web app allows two types of control over the robot:
1. Automatic Mode: No user interaction required for the robot to move through the obstacle course as fast as possible.
2. Manual Mode: The user makes use of the direction buttons displayed on screen OR the arrow keys from their keyboard to control the robot´s movement.


## About the Team
https://web.yammer.com/main/threads/eyJfdHlwZSI6IlRocmVhZCIsImlkIjoiMjQ1NDYzNzQ4MjU5ODQwMCJ9
