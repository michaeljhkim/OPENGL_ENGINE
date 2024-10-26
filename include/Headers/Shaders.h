// Shaders.h
#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>

class Shaders {
public:
    Shaders();       // Constructor
    int load_shaders(GLint &program);      // Member function
};

#endif