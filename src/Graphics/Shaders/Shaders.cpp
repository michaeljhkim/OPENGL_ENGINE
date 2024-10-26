#include <Headers/Shaders.h>

//default libraries for general c++ functions and stuff
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tiny_obj_loader.h>

#include <vector>
#include <cstddef>
#include <cstdlib>


Shaders::Shaders() {
    // Constructor body
}

//Constructor or whatever, where it establishes the function exists
void file_load(std::string shader_file, std::string &src);

//Load shaders into the program with this
int Shaders::load_shaders(GLint &shaderProgram) {
    char infoLog[512];
    GLint success;
    std::string v_src, f_src;
    file_load("vertex_core.glsl", v_src);
    file_load("fragment_core.glsl", f_src);

    GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertSrc = v_src.c_str(); 
    glShaderSource(vertexShader, 1, &vertSrc, nullptr);
    glCompileShader(vertexShader);
    
    // fragment shader
    GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragSrc = f_src.c_str(); 
    glShaderSource(fragmentShader, 1, &fragSrc, nullptr);
    glCompileShader(fragmentShader);
    
    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return 0;
}



//we transfer the shader data to a string
void file_load(std::string shader_file, std::string &src) {  // Use std::string here
    std::string temp;
    std::ifstream in_file;

    in_file.open(shader_file);
    if (in_file.is_open()) {
        while (std::getline(in_file, temp))
            src += temp + "\n";
    }
    else printf("ERROR: SHADER FILE COULD NOT LOAD\n");
    in_file.close();
}
