// Shaders.h
#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <glad/glad.h>
#include <string>
#include <tiny_obj_loader.h>

class Obj_loader {
public:
    GLuint VAO, VBO, EBO;

    tinyobj::attrib_t attrib; 
    std::vector<tinyobj::shape_t> shapes; 
    std::vector<tinyobj::material_t> materials;

    Obj_loader(const std::string& obj_path);
    int blend_weights(const std::string& base_obj_path, const std::string& weights_path, tinyobj::attrib_t& attrib, std::vector<tinyobj::shape_t>& shapes);
};

#endif