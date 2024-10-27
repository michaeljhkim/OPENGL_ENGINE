// Shaders.h
#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <glad/glad.h>
#include <string>

class Obj_loader {
public:
    Obj_loader(const std::string& obj_path, GLuint &VAO, GLuint &VBO, GLuint &EBO, size_t &index_count);       // Constructor
};

#endif