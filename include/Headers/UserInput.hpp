// UserInput.h
#ifndef USERINPUT_HPP
#define USERINPUT_HPP

#include <glad/glad.h>
#include <string>
#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class UserInput {
public:
    float User_x = 0.0f;
    float User_y = 0.0f;
    float User_z = 0.0f;

    glm::vec3 direction = glm::vec3(0.0f, 110.0f, 0.0f);
    float mouseX;
    float mouseY; 
    float deltaX; 
    float deltaY; 

    UserInput();
    void User_Movement(SDL_Event& user_event);
    void User_MLook(SDL_Event& user_event);
};

#endif