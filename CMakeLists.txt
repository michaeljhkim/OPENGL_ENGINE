cmake_minimum_required(VERSION 3.5.0)
project(opengl_engine)
set(CMAKE_CXX_STANDARD 17)

# Include the 'include' directory for headers
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(opengl_engine
    src/main.cpp
    #src/glad.c

    src/Graphics/glad.c
    src/Graphics/Shaders/Shaders.cpp
    src/Graphics/ObjLoader/ObjLoader.cpp
    src/Graphics/Renderer/Renderer.cpp

    src/UI/UserInput/UserInput.cpp
    src/UI/window/Window.cpp
    src/UI/Camera/Camera.cpp
)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})

# Link SDL2 library
target_link_libraries(opengl_engine ${SDL2_LIBRARIES} tinyobjloader)