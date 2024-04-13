# Ground Station

## Description

The Ground Station GUI used to display rocket data and telemetry.

## Depenendencies Required

- git
- cmake

## On the PI:
- ```sudo apt install libwayland-dev libxrandr-dev libxkbcommon-x11-dev libxinerama-dev libxcursor-dev libxi-dev```

## Reminders 
- Make sure to git clone pigpio and raylib on the Pi
- The serial port on the RPI4 that the Pico uses is /dev/ttyACM0
- Make sure to enable the serial ports on the RPI by navigating to ```sudo raspi-config```
## Compiling
1. Run ```git clone --recursive git@github.com:cornellrocketryteam/Ground-Station.git```
2. Run ```cmake .. -DGRAPHICS=GRAPHICS_API_OPENGL_21``` in the build folder, then ```sudo make -j4``` 
3. Run the executable by running ```sudo ./build/GroundStation```

Byte 0: 00100100
Byte 1: 00101000
Byte 2: 10111101
Byte 3: 01110110
Byte 4: 00110011
Byte 5: 00000000
Byte 6: 00000000
Byte 7: 00000000
Byte 8: 00000000
Byte 9: 10111010
Byte 10: 10010111
Byte 11: 11100100
Byte 12: 10111111
Byte 13: 00101100
Byte 14: 00001111
Byte 15: 00000001
Byte 16: 00000000
Byte 17: 00101100
Byte 18: 00001111
Byte 19: 00000001
Byte 20: 00000000
Byte 21: 01000101
Byte 22: 11010101
Byte 23: 01111000
Byte 24: 01101001
Byte 25: 00111111
Byte 26: 10100110
Byte 27: 10011011
Byte 28: 11000100
Byte 29: 00111101
Byte 30: 10100110
Byte 31: 10011011
Byte 32: 01000100
Byte 33: 10111110
Byte 34: 00000000
Byte 35: 00000000
Byte 36: 10000000
Byte 37: 10111111
Byte 38: 00000000
Byte 39: 00000000
Byte 40: 10000000
Byte 41: 10111111
Byte 42: 00000000
Byte 43: 00000000
Byte 44: 10000000
Byte 45: 10111111
Byte 46: 00000000
Byte 47: 00000000
Byte 48: 10000000
Byte 49: 10111111
Byte 50: 00000000
Byte 51: 00000000
Byte 52: 10000000
Byte 53: 10111111
Byte 54: 00000000
Byte 55: 00000000
Byte 56: 10000000
Byte 57: 10111111
Byte 58: 00000000
Byte 59: 00000000
Byte 60: 10000000
Byte 61: 10111111
Byte 62: 00000000
Byte 63: 00000000
Byte 64: 10000000
Byte 65: 10111111
Byte 66: 00000000
Byte 67: 00000000
Byte 68: 10000000
Byte 69: 10111111
Byte 70: 00000000
Byte 71: 00000000
Byte 72: 10000000
Byte 73: 10111111
Byte 74: 00000000
Byte 75: 00000000
Byte 76: 10000000
Byte 77: 10111111
Byte 78: 00000000
Byte 79: 00000000
Byte 80: 10000000
Byte 81: 10111111
Byte 82: 00000000
Byte 83: 00000000
Byte 84: 10000000
Byte 85: 10111111
