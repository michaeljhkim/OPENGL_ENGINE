// -- Window.cpp --
#include <Headers/Window.h>

//default libraries for general c++ functions and stuff
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

//Window and graphics stuff
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <Headers/Shaders.h>


int quit_check();
void render_loop();
void framebuffer_size_callback(SDL_Window* window);




Window::Window(int win_width, int win_height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL failed to initialize: " << SDL_GetError() << std::endl;
        return;
    }

    // Set OpenGL version and profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


    // Create SDL window with OpenGL context
    SDL_Window* window = SDL_CreateWindow("SDL Example",    /* Title of the SDL window */
                SDL_WINDOWPOS_UNDEFINED,    /* Position x of the window */
                SDL_WINDOWPOS_UNDEFINED,    /* Position y of the window */
                win_width,      /* Width of the window in pixels */
                win_height,     /* Height of the window in pixels */
                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);     /* Additional flag(s) */

    if (!window) {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    // Create an OpenGL context
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // Set the context to be current
    SDL_GL_MakeCurrent(window, gl_context);

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // Set initial viewport size
    framebuffer_size_callback(window);



    //Function for the loop
    render_loop();

    // Frees memory and Shuts down all SDL subsystems
    SDL_DestroyWindow(window);
    SDL_Quit(); 
}






//We seperate so child classes can have an easier time editing code
//This is where the stuff we need to render and run happens
void render_loop() {
    //additional GL flags (study them later)
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);

    /*
    //load shaders
    GLint core_program;
    Shaders gl_shader;
    gl_shader.load_shaders(core_program);
    */

    //Actual render loop
    while(!quit_check()) {
        //std::cout << "TESTING";
        //RENDER STUFF HERE
    }
}


// Callback function to handle window resize
void framebuffer_size_callback(SDL_Window* window) {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);
}


//Function to check if window should continue to render and run
int quit_check() { 
    SDL_Event event;
    SDL_PollEvent(&event);
    return (event.type == SDL_QUIT);
}





