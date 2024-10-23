// -- Window.cpp --
#include "Window.h"

//default libraries for general c++ functions and stuff
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

//Window and graphics stuff
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <cstddef>
#include <cstdlib>



Window::Window() {
    // Constructor body
}


int Window::create_window(int win_width, int win_height) {
    /* Initialises data */
    SDL_Window *window = NULL;

    /*
    * Initialises the SDL video subsystem (as well as the events subsystem).
    * Returns 0 on success or a negative error code on failure using SDL_GetError().
    */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
    return 1;
    }

    /* Creates a SDL window */
    window = SDL_CreateWindow("SDL Example", /* Title of the SDL window */
                SDL_WINDOWPOS_UNDEFINED, /* Position x of the window */
                SDL_WINDOWPOS_UNDEFINED, /* Position y of the window */
                win_width, /* Width of the window in pixels */
                win_height, /* Height of the window in pixels */
                0);     /* Additional flag(s) */

    /* Checks if window has been created; if not, exits program */
    if (window == NULL) {
        fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
        return 1;
    }

    bool isrunning = true;
    while(isrunning) {
        SDL_Event event;

        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT)
                isrunning = false;
        }
    }

    /* Pauses all SDL subsystems for a variable amount of milliseconds */
    //SDL_Delay(100);

    /* Frees memory */
    SDL_DestroyWindow(window);

    /* Shuts down all SDL subsystems */
    SDL_Quit(); 

    return 0;
}
