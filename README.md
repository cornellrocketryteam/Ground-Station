# Ground Station

IMAGE PLACEHOLDER

## Description

The Ground Station GUI used to display rocket data and telemetry.

## Depenendencies Required

- git
- cmake
<br>
 On the PI:
  ```sudo apt install libwayland-dev```
  ```sudo apt install libxkbcommon-x11-dev```

<br> 
Make sure to git clone wiringPi and raylib on the Pi

## Compiling

1. Run ```git clone --recursive git@github.com:cornellrocketryteam/Ground-Station.git```
2. Run ```cmake -B build && cmake --build build```
3. ```cmake .. -DGRAPHICS=GRAPHICS_API_OPENGL_21```
4. Run the executable by running ```./build/GroundStation```

