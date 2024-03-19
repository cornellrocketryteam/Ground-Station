# Ground Station

IMAGE PLACEHOLDER

## Description

The Ground Station GUI used to display rocket data and telemetry.

## Depenendencies Required

- git
- cmake

 ## On the PI:
  ```sudo apt install libwayland-dev```
  ```sudo apt install libxkbcommon-x11-dev```

## Reminders 
- Make sure to git clone wiringPi and raylib on the Pi
-  The serial port on the RPI4 that the Pico uses is /dev/ttyACM0
## Compiling
1. Run ```git clone --recursive git@github.com:cornellrocketryteam/Ground-Station.git``` in the lib folder, and git clone pigpio 
2. Run ```cmake .. -DGRAPHICS=GRAPHICS_API_OPENGL_21``` in the build folder, then ```make -j4 ``` 
3. Run the executable by running ```./build/GroundStation```

