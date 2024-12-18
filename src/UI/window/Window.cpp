// -- Window.cpp --
#include <Headers/Window.hpp>
#include <Headers/ObjLoader.hpp>
#include <Headers/Renderer.hpp>
#include <Headers/Shaders.hpp>
#include <Headers/UserInput.hpp>

//default libraries for general c++ functions and stuff
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

//Window and graphics stuff
#include <SDL2/SDL.h>
#include <glad/glad.h>


void render_loop(SDL_Window* gGraphicsApplicationWindow);
void framebuffer_size_callback(SDL_Window* gGraphicsApplicationWindow);
SDL_Window* gGraphicsApplicationWindow;
int gScreenWidth;
int gScreenHeight;


Window::Window() {
}

int Window::get_gScreenWidth() { return gScreenWidth; }
int Window::get_gScreenHeight() { return gScreenHeight; }

void Window::CreateWindow(int win_width, int win_height) {
    gScreenWidth = win_width;
    gScreenHeight = win_height;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL failed to initialize: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Set OpenGL version and profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 1);

    // Create SDL window with OpenGL context
    gGraphicsApplicationWindow = SDL_CreateWindow("SDL Example",    /* Title of the SDL window */
                SDL_WINDOWPOS_UNDEFINED,    /* Position x of the window */
                SDL_WINDOWPOS_UNDEFINED,    /* Position y of the window */
                win_width, win_height,     /* Width and Height of the window in pixels */
                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);     /* Additional flag(s) */

    if (!gGraphicsApplicationWindow) {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    // Create an OpenGL context
    SDL_GLContext gl_context = SDL_GL_CreateContext(gGraphicsApplicationWindow);
    if (!gl_context) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(gGraphicsApplicationWindow);
        SDL_Quit();
        return;
    }

    // Set the context to be current
    SDL_GL_MakeCurrent(gGraphicsApplicationWindow, gl_context);

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(gGraphicsApplicationWindow);
        SDL_Quit();
        return;
    }

    // Set initial viewport size
    framebuffer_size_callback(gGraphicsApplicationWindow);
}      

void Window::Window_CleanUp() {
    SDL_DestroyWindow(gGraphicsApplicationWindow);
    SDL_Quit(); 
}


// Callback function to handle window resize
void framebuffer_size_callback(SDL_Window* gGraphicsApplicationWindow) {
    int width, height;
    SDL_GetWindowSize(gGraphicsApplicationWindow, &width, &height);
    glViewport(0, 0, width, height);
}

/*


//We seperate so child classes can have an easier time editing code
//This is where the stuff we need to render and run happens
//may have to change where certain pieces of code should reside 
void render_loop(SDL_Window* window) {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.4f, 0.5f, 1.0f);

    // Control render mode: solid or wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    //load shaders
    GLint core_program;
    Shaders gl_shader(core_program);


    //system("pwd");    // for seeing where the executable is being run

    // TEMPORARY THING, JUST FOR TESTING
    // STILL NEED TO WORK ON MAKING A DYNAMIC SHAPE LOADER
    std::string obj_path = "temp_asset_folder/data/faces/0.obj";
    std::vector<ObjLoader> shape_dictionary;
    ObjLoader test_obj(obj_path);
    shape_dictionary.push_back(test_obj);
    Renderer temp_rend; //for testing


    //for handling user input
    SDL_Event event;
    UserInput test_uin; 

    //setup up stuff
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(20.0f, 100.0f, 200.0f), glm::vec3(0.0f, 110.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(30.0f), 1.0f, 0.1f, 1000.0f);
    glm::mat4 mvp = projection * view;

    SDL_SetRelativeMouseMode(SDL_TRUE); 

    //Actual render loop
    //while the user input event type is not quit, keep looping
    while( !(event.type == SDL_QUIT) ) {
        SDL_PollEvent(&event);
        test_uin.User_Movement(event);
        if (event.type == SDL_MOUSEMOTION) 
            test_uin.User_MLook(event);

        glm::mat4 model = glm::mat4(1.0f);
        glm::vec3 cameraPosition = glm::vec3(20.0f + test_uin.User_x, 100.0f + test_uin.User_y, 200.0f + test_uin.User_z);
        glm::vec3 targetPosition = cameraPosition + test_uin.direction; // Look in the direction the camera is facing
        glm::mat4 view = glm::lookAt(cameraPosition, test_uin.direction, glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 projection = glm::perspective(glm::radians(30.0f), 1.0f, 0.1f, 1000.0f);
        glm::mat4 mvp = projection * view;


        // input
        //temp_input_func();
        temp_rend.Generate_VAO_VBO_EBO(shape_dictionary[0]);

        //render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw shaders
        GLuint MatrixID = glGetUniformLocation(core_program, "MVP");
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
        glUseProgram(core_program);
        
        //here's where the actual model stuff and translations happens
        glBindVertexArray(shape_dictionary[0].VAO);
        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        glDrawArrays(GL_TRIANGLES, 0, shape_dictionary[0].shapes[0].mesh.indices.size());

        SDL_GL_SwapWindow(window);
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &shape_dictionary[0].VAO);
    glDeleteBuffers(1, &shape_dictionary[0].VBO);
    glDeleteBuffers(1, &shape_dictionary[0].EBO);
    glDeleteProgram(core_program);
}

*/








