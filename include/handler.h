#ifndef HANDLER_H
#define HANDLER_H

#include "engine.h"
#include <GLFW/glfw3.h>

struct Handler {
    Handler(GLFWwindow* window, Engine& engine) : m_window(window), m_engine(engine) {}

    void update_camera_pos();
    void update_camera_dir();

    GLFWwindow* m_window;
    Engine& m_engine;
};

#endif