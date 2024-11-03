// ObjLoader.h
#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <glad/glad.h>
#include <string>
#include <tiny_obj_loader.h>

class ObjLoader {
public:
    GLuint VAO, VBO, EBO;

    tinyobj::attrib_t attrib; 
    std::vector<tinyobj::shape_t> shapes; 
    std::vector<tinyobj::material_t> materials;

    ObjLoader(const std::string& obj_path);
    int blend_weights(const std::string& base_obj_path, const std::string& weights_path, tinyobj::attrib_t& attrib, std::vector<tinyobj::shape_t>& shapes);
};

#endif