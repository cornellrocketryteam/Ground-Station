cmake_minimum_required(VERSION 3.15)
project(GroundStation)

message(PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

# Set C/C++ standards
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

# Build raylib
add_subdirectory(lib/raylib)

if (NOT APPLE)
    add_library(WiringPi SHARED lib/WiringPi/src/wiringPi.c
    lib/WiringPi/src/byteswap.h lib/WiringPi/src/ads1115.c lib/WiringPi/src/ads1115.h lib/WiringPi/src/bmp180.c lib/WiringPi/src/bmp180.h lib/WiringPi/src/CMakeLists.txt lib/WiringPi/src/COPYING.LESSER lib/WiringPi/src/drcNet.c lib/WiringPi/src/drcNet.h lib/WiringPi/src/drcSerial.c lib/WiringPi/src/drcSerial.h lib/WiringPi/src/ds18b20.c lib/WiringPi/src/ds18b20.h lib/WiringPi/src/htu21d.c lib/WiringPi/src/htu21d.h lib/WiringPi/src/Makefile lib/WiringPi/src/max5322.c lib/WiringPi/src/max5322.h lib/WiringPi/src/max31855.c lib/WiringPi/src/max31855.h lib/WiringPi/src/mcp23s08.c lib/WiringPi/src/mcp23s08.h lib/WiringPi/src/mcp23s17.c lib/WiringPi/src/mcp23s17.h lib/WiringPi/src/mcp23x08.h lib/WiringPi/src/mcp23x0817.h lib/WiringPi/src/mcp3002.c lib/WiringPi/src/mcp3002.h lib/WiringPi/src/mcp3004.c lib/WiringPi/src/mcp3004.h lib/WiringPi/src/mcp3422.c lib/WiringPi/src/mcp3422.h lib/WiringPi/src/mcp4802.c lib/WiringPi/src/mcp4802.h lib/WiringPi/src/mcp23008.c lib/WiringPi/src/mcp23008.h lib/WiringPi/src/mcp23016.c lib/WiringPi/src/mcp23016.h lib/WiringPi/src/mcp23016reg.h lib/WiringPi/src/mcp23017.c lib/WiringPi/src/mcp23017.h lib/WiringPi/src/noMoreStatic lib/WiringPi/src/pcf8574.c lib/WiringPi/src/pcf8574.h lib/WiringPi/src/pcf8591.c lib/WiringPi/src/pcf8591.h lib/WiringPi/src/piHiPri.c lib/WiringPi/src/piThread.c lib/WiringPi/src/pseudoPins.c lib/WiringPi/src/pseudoPins.h lib/WiringPi/src/rht03.c lib/WiringPi/src/rht03.h lib/WiringPi/src/sn3218.c lib/WiringPi/src/sn3218.h lib/WiringPi/src/softPwm.c lib/WiringPi/src/softPwm.h lib/WiringPi/src/softServo.c lib/WiringPi/src/softServo.h lib/WiringPi/src/softTone.c lib/WiringPi/src/softTone.h lib/WiringPi/src/sr595.c lib/WiringPi/src/sr595.h lib/WiringPi/src/wiringPi.c lib/WiringPi/src/wiringPi.h lib/WiringPi/src/wiringPiI2C.c lib/WiringPi/src/wiringPiI2C.h lib/WiringPi/src/wiringPiSPI.c lib/WiringPi/src/wiringPiSPI.h lib/WiringPi/src/wiringSerial.c lib/WiringPi/src/wiringSerial.h lib/WiringPi/src/wiringShift.c lib/WiringPi/src/wiringShift.h lib/WiringPi/src/wpiExtensions.c lib/WiringPi/src/wpiExtensions.h
    )
    include_directories(lib/WiringPi/src)
    target_include_directories(WiringPi PUBLIC lib/WiringPi/src)
endif()

# Create the executable
add_executable(${PROJECT_NAME} src/main.cpp
        src/gui.cpp
        src/statusbar.cpp
        src/datagrid.cpp
        src/graph.cpp
        src/rocket.cpp
        src/gps.cpp
        src/dataprocessing.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE src)

if (NOT APPLE)
    target_link_libraries(${PROJECT_NAME} raylib WiringPi)
else()
    target_link_libraries(${PROJECT_NAME} raylib)
endif() 


# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework CoreVideo")
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework GLUT")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

