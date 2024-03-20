# Ground Station

## Description

The Ground Station GUI used to display rocket data and telemetry.

## Depenendencies Required

- git
- cmake

## On the PI:
- ```sudo apt install libwayland-dev```
- ```sudo apt install libxkbcommon-x11-dev```

## Reminders 
- Make sure to git clone pigpio and raylib on the Pi
- The serial port on the RPI4 that the Pico uses is /dev/ttyACM0
- Make sure to enable the serial ports on the RPI by navigating to ```sudo raspi-config```
## Compiling
1. Run ```git clone --recursive git@github.com:cornellrocketryteam/Ground-Station.git``` and in the lib folder ```git clone git@github.com:joan2937/pigpio.git```
2. Run ```cmake .. -DGRAPHICS=GRAPHICS_API_OPENGL_21``` in the build folder, then ```make -j4 ``` 
3. Run the executable by running ```sudo ./build/GroundStation```

