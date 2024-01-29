cmake_minimum_required(VERSION 3.15)
project(GroundStation)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0

# Create the executable
add_executable(${PROJECT_NAME} src/main.cpp
                src/dataprocessing.cpp
                src/gui.cpp
                src/rocket3d.cpp
                src/sensorDisplay.cpp)

target_link_libraries(${PROJECT_NAME} raylib)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
<<<<<<< HEAD
endif()
=======
endif()

>>>>>>> eaa79b56007b3856001b751e24c79410ec173bec
