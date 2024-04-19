# Ground Station

## Description

The Ground Station GUI used to display rocket data and telemetry.

## Depenendencies Required

- git
- cmake

## On the PI:

- `sudo apt install libwayland-dev libxrandr-dev libxkbcommon-x11-dev libxinerama-dev libxcursor-dev libxi-dev`

## On your laptop: 

- Make sure to change the serial port path on line 33 of serialread.cpp to the port that RATS is using.

## Compiling

1. Run `git clone --recursive git@github.com:cornellrocketryteam/Ground-Station.git`
2. Run `cmake .. -DGRAPHICS=GRAPHICS_API_OPENGL_21` in the build folder, then `
3. Run the executable by running `./build/GroundStation`
