cmake_minimum_required(VERSION 3.12)
project(GroundStation)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)


# Set the path to the Raylib directory (modify this accordingly)
set(RAYLIB_DIR ${RAYLIB_DIR})

# Add the Raylib library
find_library(RAYLIB NAMES raylib HINTS ${RAYLIB_DIR}/lib)

# Find the Protobuf library
find_package(Protobuf REQUIRED)

# Add the Raylib include directory
include_directories(${RAYLIB_DIR}/include)

# Include directories for generated protobuf code
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROTOBUF_INCLUDE_DIRS})

# Set the source files for your project
set(SOURCE_FILES src/main.cpp
                src/dataprocessing.cpp
                src/gui.cpp
                src/rocket3d.cpp
                src/sensorDisplay.cpp)

# Create the executable
add_executable(GroundStation ${SOURCE_FILES})

# Link the Raylib library
target_link_libraries(GroundStation ${RAYLIB})

#link the Protobuf library
target_link_libraries(GroundStation ${PROTOBUF_LIBRARIES})
