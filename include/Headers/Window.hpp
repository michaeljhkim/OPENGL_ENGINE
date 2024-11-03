// Window.h
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>

class Window {
    public:
        SDL_Window* gGraphicsApplicationWindow;

        Window();       // Constructor
        void CreateWindow(int win_width, int win_height);      // Member function
        void Window_CleanUp();
        int get_gScreenWidth();
        int get_gScreenHeight();

    private:
        int gScreenWidth;
        int gScreenHeight;
};

#endif