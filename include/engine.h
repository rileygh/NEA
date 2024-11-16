#ifndef ENGINE_H
#define ENGINE_H

#include "vec3f.h"
#include "ray.h"

#include <map>

class Engine {
    public:
    Vec3f get_pixel_coords(Vec3f camera_pos, float fov, int row, int col);
    void render();

    private:
    float fov;
};

#endif