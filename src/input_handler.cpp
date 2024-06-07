#include <iostream>

#include <SDL2/SDL.h>
#include "input_handler.hpp"

InputHandler::InputHandler() {
    key_states.clear();
};

void InputHandler::handle() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                SDL_Quit();
                exit(0);
            case SDL_KEYDOWN:
                key_states[event.key.keysym.sym] = true;
                break;
            case SDL_KEYUP:
                key_states[event.key.keysym.sym] = false;
                break;
            default:
                break;
        }
    }
}

bool InputHandler::key_pressed(SDL_Keycode key) {
    return key_states[key];
}
