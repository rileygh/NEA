#include <iostream>

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "input_handler.hpp"

#define WIDTH 500
#define HEIGHT 500

int main(int argc, char **argv) {
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
        std::cout << "error initialising: %s\n", SDL_GetError();
        return 0;
    }

    SDL_Window *window = SDL_CreateWindow("meow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    bool mainloop = true;
    InputHandler handler;

    while (mainloop) {
        handler.handle();
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}