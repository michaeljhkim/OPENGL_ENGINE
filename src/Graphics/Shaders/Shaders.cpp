#include <Headers/Shaders.h>

//default libraries for general c++ functions and stuff
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


//Constructor or whatever, where it establishes the function exists
void file_load(std::string shader_file, std::string &src);


//Load shaders into the program with this
Shaders::Shaders(GLint &shaderProgram) {
    char infoLog[512];
    GLint success;
    std::string v_src, f_src;

    //temporary place to put the shaders, until I figure something better out
    file_load("temp_asset_folder/vertex_core.glsl", v_src);
    file_load("temp_asset_folder/fragment_core.glsl", f_src);

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
