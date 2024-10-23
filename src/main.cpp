#include <stdio.h> /* printf and fprintf */
#include <iostream>
#include <fstream>
#include <string>


#include "window/Window.h"





int main () {
    Window main_window;

    //16:9 1280x720 window
    main_window.create_window(1280, 720);

    return 0;
}
