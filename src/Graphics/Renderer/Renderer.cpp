#include <Headers/Renderer.hpp>
#include <Headers/ObjLoader.hpp>

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

// Function to load OBJ and store data for OpenGL usage
// This function is specifically used for loading stuff up
Renderer::Renderer() {
    
}

void Renderer::Generate_VAO_VBO_EBO(ObjLoader& loaded_Obj) {
    std::vector<float> vertices_buffer;
    std::vector<GLuint> indices;

    // Generate vertices buffer with interleaved position, normal, color, and texture coordinates
    for (const auto& index : loaded_Obj.shapes[0].mesh.indices) {
        int vid = index.vertex_index;
        int nid = index.normal_index;
        int tid = index.texcoord_index;
        //int cid = index.color_index;

        // Position (3 floats)
        vertices_buffer.push_back(loaded_Obj.attrib.vertices[3 * vid + 0]);
        vertices_buffer.push_back(loaded_Obj.attrib.vertices[3 * vid + 1]);
        vertices_buffer.push_back(loaded_Obj.attrib.vertices[3 * vid + 2]);

        // Normal (3 floats)
        if (nid >= 0) {  // Only add if normal index exists
            vertices_buffer.push_back(loaded_Obj.attrib.normals[3 * nid + 0]);
            vertices_buffer.push_back(loaded_Obj.attrib.normals[3 * nid + 1]);
            vertices_buffer.push_back(loaded_Obj.attrib.normals[3 * nid + 2]);
        }

        // Texture Coordinates (2 floats)
        if (tid >= 0) {  // Only add if texcoord index exists
            vertices_buffer.push_back(loaded_Obj.attrib.texcoords[2 * tid + 0]);
            vertices_buffer.push_back(loaded_Obj.attrib.texcoords[2 * tid + 1]);
        }
        // Color (3 floats)
        // Extract vertex color if available
        if (!loaded_Obj.attrib.colors.empty()) {
            vertices_buffer.push_back(loaded_Obj.attrib.colors[3 * vid + 0]);
            vertices_buffer.push_back(loaded_Obj.attrib.colors[3 * vid + 1]);
            vertices_buffer.push_back(loaded_Obj.attrib.colors[3 * vid + 2]);
        }

        // Index
        indices.push_back(vid);
    }
    
    // Generate and bind VAO, VBO, and EBO
    glGenVertexArrays(1, &loaded_Obj.VAO);
    glGenBuffers(1, &loaded_Obj.VBO);
    glGenBuffers(1, &loaded_Obj.EBO);

    glBindVertexArray(loaded_Obj.VAO);

    // Upload interleaved vertex data to VBO
    glBindBuffer(GL_ARRAY_BUFFER, loaded_Obj.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_buffer.size() * sizeof(float), vertices_buffer.data(), GL_STATIC_DRAW);

    // Upload index data to EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, loaded_Obj.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Define vertex attributes layout
    int stride = (3 + 3 + 3 + 2) * sizeof(float); // Update based on the attribute count and sizes

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Color attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Texcoord attribute
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, stride, (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(3);

    //glBindVertexArray(0);  // Unbind VAO

    return;
}
