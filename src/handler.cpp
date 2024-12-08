#include <GLFW/glfw3.h>

#include <cmath>

#include "handler.h"
#include "utils.h"
#include "engine.h"
#include "vec3f.h"

void Handler::update_camera_pos() {
    Vec3f camera_pos = m_engine.get_camera_pos();
    Vec3f camera_dir = m_engine.get_camera_dir();
    float movement_speed = m_engine.get_movement_speed();

    Vec3f world_up(0, 1, 0);

    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) {
        m_engine.set_camera_pos(camera_pos - camera_dir * movement_speed);
    }
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS) {
        m_engine.set_camera_pos(camera_pos + camera_dir * movement_speed);
    }
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS) {
        m_engine.set_camera_pos(camera_pos + camera_dir.cross(world_up).norm() * movement_speed);
    }
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS) {
        m_engine.set_camera_pos(camera_pos - camera_dir.cross(world_up).norm() * movement_speed);
    }
    if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        m_engine.set_camera_pos(camera_pos + world_up * movement_speed);
    }
    if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        m_engine.set_camera_pos(camera_pos - world_up * movement_speed);
    }
}

void Handler::update_camera_dir() {
    float sensitivity = m_engine.get_sensitivity();
    float yaw = m_engine.get_yaw(); // horizontal
    float pitch = m_engine.get_pitch(); // vertical

    double x, y;
    static double last_x, last_y; // static as need to persist between calls
    glfwGetCursorPos(m_window, &x, &y);

    double x_offset = (x - last_x) * sensitivity;
    double y_offset = (y - last_y) * sensitivity;

    yaw += static_cast<float>(x_offset);
    pitch += static_cast<float>(y_offset);

    // vertical flipping can still occur at this point
    // so clamp pitch
    if (pitch > 89) { pitch = 89; }
    if (pitch < -89) { pitch = -89; }

    m_engine.set_yaw(yaw);
    m_engine.set_pitch(pitch);

    Vec3f new_dir = Vec3f(
        cos(radians(yaw) * cos(radians(pitch))),
        sin(radians(pitch)),
        sin(radians(yaw)) * cos(radians(pitch))
    ).norm();

    last_x = x;
    last_y = y;

    m_engine.set_camera_dir(new_dir);
}
