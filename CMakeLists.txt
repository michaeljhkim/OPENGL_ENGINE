cmake_minimum_required(VERSION 3.5.0)
project(opengl_engine)
set(CMAKE_CXX_STANDARD 17)

add_executable(opengl_engine
    src/main.cpp
    src/glad.c
)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})

# Link SDL2 library
target_link_libraries(opengl_engine ${SDL2_LIBRARIES})