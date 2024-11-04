#include <Headers/Window.hpp>
#include <Headers/ObjLoader.hpp>
#include <Headers/Renderer.hpp>
#include <Headers/Shaders.hpp>
#include <Headers/UserInput.hpp>
#include <Headers/Camera.hpp>

#include <stdio.h> /* printf and fprintf */
#include <iostream>
#include <fstream>
#include <string>

//Window and graphics stuff
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


//ABSTRACT MORE OF THIS CODE IN THE FUTURE!!!

//SDL window where all the magic happens
Window main_window;

//determines if program continues or quits
bool gQuit = false;

//for holding shaders
GLint core_program;

//for holding all shapes being loaded
std::vector<ObjLoader> shape_dictionary;

/*
glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;
glm::mat4 mvp;
*/

//Camera Object for moving cameran in first person
Camera gCamera;


void InitializeProgram() {
    //16:9 1280x720 window
    main_window.CreateWindow(1440, 1440);
}   

//load the OBJ file, then generating the vertex buffers
void VertexSpecification() {
    //Load OBJ file
    std::string obj_path = "temp_asset_folder/data/faces/0.obj";
    ObjLoader test_obj(obj_path);
    shape_dictionary.push_back(test_obj);

    //generate vertex buffers
    //Most likely a function will be created elsewhere, and called in main loop in order to add more shapes down the line!
    Renderer temp_rend; //for testing
    temp_rend.Generate_VAO_VBO_EBO(shape_dictionary[0]);
}

//Graphics pipeline. So far, just loading shaders
void CreateGraphicsPipeline() {
    //load shaders
    Shaders gl_shader(core_program);
}

//Gets user input, and handles them
void Input() {
    //for getting every single input user can make in SDL
    SDL_Event event;

    //defines default values for x and y mouse movement
    static int mouseX = main_window.get_gScreenWidth()/2; 
    static int mouseY = main_window.get_gScreenHeight()/2;
    
    //Goes through every single input, and handles them before exiting
    while( SDL_PollEvent(&event) != 0 ) {
        //if the input is quit, we quit the whole program
        if(event.type == SDL_QUIT) {
            gQuit = true;
            break;
        }
        //if the mouse is moved at all, RELATIVE x and y values are passed into the camera MouseLook function
        if(event.type == SDL_MOUSEMOTION) {
            mouseX += event.motion.xrel;
            mouseY += event.motion.yrel;
            gCamera.MouseLook(mouseX, mouseY);
        }
    }

    //Determines if user pressed WASD, and moves camera accordingly
    //Does so by getting a list of all keys, and checking if they have been pressed
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

//we load up the rendering parameters, the camera, and the shaders here
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
    glm::mat4 projection = glm::perspective(glm::radians(30.0f), 1.0f, 0.1f, 10000.0f);
    glm::mat4 mvp = projection * view;

    // Draw shaders
    GLuint MatrixID = glGetUniformLocation(core_program, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
    glUseProgram(core_program);
}

//here's where the actual models gets rendered
void Draw() {
    glBindVertexArray(shape_dictionary[0].VAO);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    glDrawArrays(GL_TRIANGLES, 0, shape_dictionary[0].shapes[0].mesh.indices.size());
}

//We trap the mouse, and then loop the game logic
//Input, PreDraw, Draw, and swap_window for updating SDL logics 
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

//deletes windows, VAO, VBO, and EBO from &shape_diectory
void CleanUp() {
    main_window.Window_CleanUp();
    for(int i = 0; i < shape_dictionary.size(); i++ ) {
        glDeleteVertexArrays(1, &shape_dictionary[0].VAO);
        glDeleteBuffers(1, &shape_dictionary[0].VBO);
        glDeleteBuffers(1, &shape_dictionary[0].EBO);
    }
    glDeleteProgram(core_program);
}



//This is where everything begins.
int main () {
    InitializeProgram();
    VertexSpecification();
    CreateGraphicsPipeline();
    MainLoop();
    CleanUp();

    return 0;
}
