#include <Headers/UserInput.hpp>

//default libraries for general c++ functions and stuff
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float User_unit = 10.0f;
float User_x = 0.0f;
float User_y = 0.0f;
float User_z = 0.0f;

glm::vec3 direction = glm::vec3(0.0f, 110.0f, 0.0f);
float yaw = 0.0f; // Horizontal rotation
float pitch = 0.0f; // Vertical rotation
float sensitivity = 0.01f; // Mouse sensitivity


UserInput::UserInput() {
}

void UserInput::User_Movement(SDL_Event& user_event) {

    if (user_event.type == SDL_KEYDOWN) {
        if (user_event.key.keysym.sym == SDLK_d) {
            User_x += User_unit;
            std::cout << User_x << std::endl;
        }
        else if (user_event.key.keysym.sym == SDLK_a)
            User_x -= User_unit;

        if (user_event.key.keysym.sym == SDLK_w)
            User_y += User_unit;
        else if (user_event.key.keysym.sym == SDLK_s) 
            User_y -= User_unit;

        if (user_event.key.keysym.sym == SDLK_SPACE)
            User_z += User_unit;
        else if (user_event.key.keysym.sym == SDLK_LCTRL)
            User_z -= User_unit;
    }

    return;
}



void UserInput::User_MLook(SDL_Event& user_event) {
    // Get the current mouse state
    int xrel, yrel;
    //SDL_GetRelativeMouseState(&xrel, &yrel);
    xrel = user_event.motion.xrel;
    yrel = user_event.motion.yrel;
    std::cout << xrel << yrel << std::endl;
    
    // Update yaw and pitch
    yaw += static_cast<float>(xrel) * sensitivity;  // Multiply by sensitivity
    pitch -= static_cast<float>(yrel) * sensitivity; // Invert the pitch for intuitive movement

    // Clamp pitch to avoid gimbal lock
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    // Convert angles to radians for glm
    float yawRad = glm::radians(yaw);
    float pitchRad = glm::radians(pitch);

    // Calculate the direction vector
    direction.x = cos(yawRad) * cos(pitchRad);
    direction.y = sin(pitchRad);
    direction.z = sin(yawRad) * cos(pitchRad);
    direction = glm::normalize(direction);

    return;
}