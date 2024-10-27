#include <Headers/Obj_loader.h>

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
#include <tiny_obj_loader.h>


// Struct to hold a single vertex's attributes
struct Vertex {
    float position[3];
    float normal[3];
    float texcoord[2];
    float color[3];  // Add this line to store color
};
void render(GLuint vao, size_t vertex_count);


//Most of the code is from tiny_obj_loader github
//Only changes is storing the position, normal, texcoord, and color in a struct
Obj_loader::Obj_loader(const std::string& obj_path, GLuint &VAO, GLuint &VBO, GLuint &EBO, size_t &index_count) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, obj_path.c_str());
    if (!warn.empty()) 
        std::cout << "Warning: " << warn << std::endl;
    if (!err.empty()) 
        std::cerr << "Error: " << err << std::endl;
    if (!ret) 
        return;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Loop over shapes
    for (const auto& shape : shapes) {
        size_t index_offset = 0;
        for (const auto& num_vertices : shape.mesh.num_face_vertices) {
            for (size_t v = 0; v < num_vertices; v++) {
                tinyobj::index_t idx = shape.mesh.indices[index_offset + v];

                Vertex vertex = {};
                vertex.position[0] = attrib.vertices[3 * idx.vertex_index + 0];
                vertex.position[1] = attrib.vertices[3 * idx.vertex_index + 1];
                vertex.position[2] = attrib.vertices[3 * idx.vertex_index + 2];

                if (idx.normal_index >= 0) {
                    vertex.normal[0] = attrib.normals[3 * idx.normal_index + 0];
                    vertex.normal[1] = attrib.normals[3 * idx.normal_index + 1];
                    vertex.normal[2] = attrib.normals[3 * idx.normal_index + 2];
                }

                if (idx.texcoord_index >= 0) {
                    vertex.texcoord[0] = attrib.texcoords[2 * idx.texcoord_index + 0];
                    vertex.texcoord[1] = attrib.texcoords[2 * idx.texcoord_index + 1];
                }
                
                // Extract vertex color if available
                if (!attrib.colors.empty()) {
                    vertex.color[0] = attrib.colors[3 * idx.vertex_index + 0];
                    vertex.color[1] = attrib.colors[3 * idx.vertex_index + 1];
                    vertex.color[2] = attrib.colors[3 * idx.vertex_index + 2];
                } 
                else {
                    // Default color if no color information is available
                    vertex.color[0] = 1.0f;  // Default to white
                    vertex.color[1] = 1.0f;  
                    vertex.color[2] = 1.0f;  
                }


                // Store vertex and index
                vertices.push_back(vertex);
                indices.push_back(index_offset + v);
            }
            index_offset += num_vertices;
        }
    }

    index_count = indices.size();

    // Generate and bind VAO, VBO, and EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Upload vertex data to VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // Upload index data to EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Define vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
    glEnableVertexAttribArray(2);

    // Add color attribute
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);  // Unbind VAO
}





// Render function using glDrawElements
// not sure if I need this function
void render(GLuint VAO, size_t index_count) {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
