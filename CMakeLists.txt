cmake_minimum_required(VERSION 3.15)
project(GroundStation)

# Set C/C++ standards
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

# Build raylib
add_subdirectory(lib/raylib)

# Create the executable
add_executable(${PROJECT_NAME} src/main.cpp
                src/dataprocessing.cpp
                src/gui.cpp
                src/rocket3d.cpp
                src/sensorDisplay.cpp
        src/components/button.cpp
        src/components/button.h
        src/components/textDisplay.cpp
        src/components/textDisplay.h
        src/components/graph.cpp
        src/components/graph.h)

target_link_libraries(${PROJECT_NAME} raylib)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework CoreVideo")
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework GLUT")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

