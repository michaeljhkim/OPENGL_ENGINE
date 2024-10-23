#include <stdio.h> /* printf and fprintf */
#include <iostream>
#include <fstream>
#include <string>


#include "window/Window.h"





int main (int argc, char **argv) {
    Window test;

    //16:9 1280x720 window
    test.create_window(1280, 720);

    return 0;
}
