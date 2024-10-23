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


/* Sets constants */
#define WIDTH 1280
#define HEIGHT 720
#define DELAY 3000



Window::Window() {
    // Constructor body
}


int Window::create_window() {
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
                WIDTH, /* Width of the window in pixels */
                HEIGHT, /* Height of the window in pixels */
                0); /* Additional flag(s) */

    /* Checks if window has been created; if not, exits program */
    if (window == NULL) {
    fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
    return 1;
    }

    /* Pauses all SDL subsystems for a variable amount of milliseconds */
    SDL_Delay(DELAY);

    /* Frees memory */
    SDL_DestroyWindow(window);

    /* Shuts down all SDL subsystems */
    SDL_Quit(); 

    return 0;
}
