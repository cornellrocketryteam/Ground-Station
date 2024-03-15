# Ground Station

IMAGE PLACEHOLDER

## Description

The Ground Station GUI used to display rocket data and telemetry.

## Depenendencies Required

- git
- cmake
 On the PI:
- ```sudo apt install libwayland-dev```
- ```sudo apt install libxkbcommon-x11-dev```

## Compiling

1. Run ```git clone --recursive git@github.com:cornellrocketryteam/Ground-Station.git```
2. Run ```cmake -B build && cmake --build build```
3. ```cmake .. -DGRAPHICS=GRAPHICS_API_OPENGL_21```
4. Run the executable by running ```./build/GroundStation```

