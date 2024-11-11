#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include "vec3f.h"

class Camera {
    public:
    Camera(GLFWwindow* window, Vec3f pos, Vec3f rot);

    void move();
    void rotate();

    // getters
    Vec3f pos() const;
    Vec3f rot() const;

    // setters
    void set_pos(Vec3f position);
    void set_rot(Vec3f rotation);

    private:
    Vec3f position;
    Vec3f rotation;
};

#endif