#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <SDL2/SDL.h>
#include <map>

class InputHandler {
    public:
    InputHandler();

    void handle();
    bool key_pressed(SDL_Keycode key);

    private:
    std::map<SDL_Keycode, bool> key_states;
};

#endif