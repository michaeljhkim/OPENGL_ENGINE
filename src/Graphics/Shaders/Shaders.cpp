//alot of this is still temporary. Just default code from graphics class. Need to learn how to create dynamic lighting and shaders 

#include <Headers/Shaders.hpp>

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
Shaders::Shaders(GLint& shaderProgram) {
    int success;
    char error_msg[512];
    std::string v_src, f_src;

    //temporary place to put the shaders, until I figure something better out
    file_load("temp_asset_folder/vertex_core.glsl", v_src);
    file_load("temp_asset_folder/fragment_core.glsl", f_src);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertSrc = v_src.c_str(); 
    glShaderSource(vs, 1, &vertSrc, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vs, 512, NULL, error_msg);
        std::cout << "Vertex Shader Failed: " << error_msg << std::endl;
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragSrc = f_src.c_str(); 
    glShaderSource(fs, 1, &fragSrc, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fs, 512, NULL, error_msg);
        std::cout << "Fragment Shader Failed: " << error_msg << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, error_msg);
        std::cout << "Program Link Error: " << error_msg << std::endl;
    }
    glDeleteShader(vs);
    glDeleteShader(fs);
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
