// Renderer.h
#ifndef RENDERER_H
#define RENDERER_H

#include <Headers/Obj_loader.h>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tiny_obj_loader.h>

class Renderer {
public:
    //Obj_loader(const std::string& obj_path, GLuint &VAO, GLuint &VBO, GLuint &EBO, size_t &index_count);       // Constructor
    Renderer();
    void init();
    void loadModel(const std::string& objPath);
    void render(const glm::mat4& mvp);
    void cleanup();
    void Generate_VAO_VBO_EBO(Obj_loader& loaded_Obj);
};

#endif