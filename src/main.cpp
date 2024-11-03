#include <stdio.h> /* printf and fprintf */
#include <iostream>
#include <fstream>
#include <string>

#include <Headers/Window.hpp>
#include <Headers/ObjLoader.hpp>
#include <Headers/Renderer.hpp>
#include <Headers/Shaders.hpp>
#include <Headers/UserInput.hpp>
#include <Headers/Camera.hpp>

//Window and graphics stuff
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Window main_window;
bool gQuit = false;
GLint core_program;
std::vector<ObjLoader> shape_dictionary;

//TEMPORARY
/*
glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;
glm::mat4 mvp;
*/

float g_uOffset = 0.0f;
Camera gCamera;


void InitializeProgram() {
    //16:9 1280x720 window
    main_window.CreateWindow(1440, 1440);
}   

void VertexSpecification() {
    std::string obj_path = "temp_asset_folder/data/faces/0.obj";
    ObjLoader test_obj(obj_path);
    Renderer temp_rend; //for testing

    shape_dictionary.push_back(test_obj);
    temp_rend.Generate_VAO_VBO_EBO(shape_dictionary[0]);
}

void CreateGraphicsPipeline() {
    //load shaders
    Shaders gl_shader(core_program);
}

void Input() {
    SDL_Event event;
    static int mouseX = main_window.get_gScreenWidth()/2; 
    static int mouseY = main_window.get_gScreenHeight()/2;
    
    while( SDL_PollEvent(&event) != 0 ) {
        if(event.type == SDL_QUIT) {
            gQuit = true;
            break;
        }
        if(event.type == SDL_MOUSEMOTION) {
            mouseX += event.motion.xrel;
            mouseY += event.motion.yrel;
            gCamera.MouseLook(mouseX, mouseY);
        }
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    float speed = 0.1f;
    if(state[SDL_SCANCODE_W]) {
        gCamera.MoveForward(speed);
    }
    if(state[SDL_SCANCODE_S]) {
        gCamera.MoveBack(speed);
    }
    if(state[SDL_SCANCODE_A]) {
        gCamera.MoveLeft(speed);
    }
    if(state[SDL_SCANCODE_D]) {
        gCamera.MoveRight(speed);
    }
}

void PreDraw() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.4f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Control render mode: solid or wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //transformations of the camera
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = gCamera.GetViewMatrix();
    //glm::mat4 projection = glm::perspective(glm::radians(30.0f), 1.0f, 0.1f, 1000.0f);
    glm::mat4 projection = glm::perspective(glm::radians(30.0f), 1.0f, 0.1f, 1000.0f);
    glm::mat4 mvp = projection * view;

    // Draw shaders
    GLuint MatrixID = glGetUniformLocation(core_program, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
    glUseProgram(core_program);
}

//here's where the actual models gets rendered
void Draw() {
    glBindVertexArray(shape_dictionary[0].VAO);
    //glm::mat4 model = glm::mat4(1.0f);
    /*
    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    */
    glDrawArrays(GL_TRIANGLES, 0, shape_dictionary[0].shapes[0].mesh.indices.size());
}

void MainLoop() {
    SDL_WarpMouseInWindow(main_window.gGraphicsApplicationWindow, main_window.get_gScreenWidth()/2, main_window.get_gScreenHeight()/2);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    while(!gQuit) {
        Input();
        PreDraw();
        Draw();
        SDL_GL_SwapWindow(main_window.gGraphicsApplicationWindow);
    }
}

void CleanUp() {
    main_window.Window_CleanUp();
}



int main () {
    InitializeProgram();
    VertexSpecification();
    CreateGraphicsPipeline();
    MainLoop();
    CleanUp();

    return 0;
}
