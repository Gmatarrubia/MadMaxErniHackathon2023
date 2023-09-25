# PICAR-CPP

This is an attempt to do some funny stuff with [sunfounder's picar-x smart video car kit](https://www.sunfounder.com/products/picar-x). Some ideas include:

- [x] Rewrite controllers of motors and servos in cpp and move the car successfully with code.
- [x] Connect the car with a wireless joystick and turn it into a remote-control car.
- [ ] Refactor controllers and sensor drivers into nodes inside a DCPS system like opendds (ROS is enough but why not DDS)
  - [ ] A web-based UI to control the car and display sensor outputs.
- [ ] Perception stuff (human face detection/edge detection/freespace detection) with the sensors, especially the camera.
  - [ ] Hook the raspberry pi with an edge TPU or other acceleration hardware to achive usable performance.
- [ ] A simple planner that helps the car to achive self-driving in limited environment.

## SMBUS and I2C

For clarification of smbus concepts, check the following:

- https://www.totalphase.com/blog/2020/09/overview-of-smbus-functions/
- https://raspberry-projects.com/pi/programming-in-python/i2c-programming-in-python/using-the-i2c-interface-2

C source code of smbus and initialization code come from

- https://github.com/leon-anavi/rpi-examples/tree/master/BMP180/c

## PWM: Pulse Width Modulation

Check [wikipedia](https://en.wikipedia.org/wiki/Pulse-width_modulation) or the following:

- https://www.allaboutcircuits.com/technical-articles/introduction-to-microcontroller-timers-pwm-timers/

## Timer Registers

Check 2.2 of the following for clarification of prescaler, arr, period, frequency, etc:

- https://www.st.com/content/ccc/resource/technical/document/application_note/54/0f/67/eb/47/34/45/40/DM00042534.pdf/files/DM00042534.pdf/jcr:content/translations/en.DM00042534.pdf

The main takeaway is the following:

<a href="https://www.codecogs.com/eqnedit.php?latex=freq=\frac{CLOCK}{(PSC&plus;1)*(ARR&plus;1)}" target="_blank"><img src="https://latex.codecogs.com/svg.latex?freq=\frac{CLOCK}{(PSC&plus;1)*(ARR&plus;1)}" title="freq=\frac{CLOCK}{(PSC+1)*(ARR+1)}" /></a>

## GPIO Pin Access

GPIO Pin access is completed with the [wiringPi](http://wiringpi.com/) library. Its default pin numbering is different from that of Raspberry Pi. For details see [here](http://wiringpi.com/pins/).

Pin numbering, pin mode and pin value can be checked with command `gpio readall`.

## Joystick

Install deps:

```bash
sudo apt-get install joystick
```

For usage, check:

- https://www.kernel.org/doc/Documentation/input/joystick-api.txt
