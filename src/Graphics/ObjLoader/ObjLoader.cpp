#include <Headers/ObjLoader.hpp>

//default libraries for general c++ functions and stuff
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <tiny_obj_loader.h>

//This is essentially a data type that loads up an .obj and keeps the output


//For generating much later
GLuint VAO, VBO, EBO;

// Variables that LoadObj will fill, and we can therefore use
//for attributes like vertices, indices, materials, e.t.c
tinyobj::attrib_t attrib; 

//if an obj file has more than 1 shape, then this list will be bigger than one
std::vector<tinyobj::shape_t> shapes; 
std::vector<tinyobj::material_t> materials;
std::string warn, err;
bool bTriangulate = true;

// Function to load OBJ and store data for OpenGL usage
// This function is specifically used for loading stuff up
ObjLoader::ObjLoader(const std::string& obj_path) {
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, obj_path.c_str(), nullptr, bTriangulate);
    if (!warn.empty()) 
        std::cout << "Warning: " << warn << std::endl;
    if (!err.empty()) 
        std::cerr << "Error: " << err << std::endl;
    if (!ret) 
        std::cerr << "Error: something is wrong with ret in Obj_loader" << std::endl;
        return;
}





/*
int blend_weights(const std::string& base_obj_path, const std::string& weights_path, tinyobj::attrib_t& blended_attrib, std::vector<tinyobj::shape_t>& shapes) {
    //tinyobj::shape_t shape = shapes[0];
    tinyobj::attrib_t base_attrib;
    load_obj(base_obj_path, base_attrib, shapes);

    std::vector<tinyobj::attrib_t> targets_attribs(35);
    std::vector<std::vector<tinyobj::shape_t>> targets_shapes(35);
    std::string filePath;
    for (size_t i = 0; i < 35; i++) {
        filePath = "data/faces/" + std::to_string(i) + ".obj";
        load_obj(filePath, targets_attribs[i], targets_shapes[i]);
    }
    blended_attrib = base_attrib;

    // Load weights
    std::ifstream weights_file(weights_path);
    std::vector<float> weights;
    float w;
    while (weights_file >> w)
        weights.push_back(w);


    // Apply blended weights formula
    // Blend the vertex position
    //std::cout << base_indices.size() << std::endl;
    for (size_t i = 0; i < weights.size(); i++) {
        assert(base_attrib.vertices.size() == targets_attribs[i].vertices.size());
        for (size_t k = 0; k < base_attrib.vertices.size(); k++) {
            blended_attrib.vertices[k] += weights[i] * (targets_attribs[i].vertices[k] - base_attrib.vertices[k]);
        }
    }

    return 0;
}
*/
