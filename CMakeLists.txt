cmake_minimum_required(VERSION 3.15)
project(GroundStation)

# Set C/C++ standards
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

# Build raylib
add_subdirectory(lib/raylib)

# Add fmt
add_subdirectory(lib/fmt)

# Create the executable
add_executable(${PROJECT_NAME} src/main.cpp
        src/gui.cpp
        src/statusbar.cpp
        src/datagrid.cpp
        src/graph.cpp
        src/rocket.cpp
        src/serialread.cpp
        src/sfr.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} raylib fmt)


# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework CoreVideo")
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework GLUT")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
