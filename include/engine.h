#ifndef ENGINE_H
#define ENGINE_H

#include "vec3f.h"
#include "ray.h"

#include <glfw/glfw3.h>

#include <map>

class Engine {
    public:
    void allocate_image_buffer();
    Vec3f get_pixel_coords(Vec3f camera_pos, int row, int col);
    Vec3f trace(Ray ray);

    GLubyte* get_render_data();

    float get_fov();

    void set_fov(float _fov);
    void set_width(int _width);
    void set_height(int _height);

    private:
    float fov;
    int width, height;

    GLubyte* image_buffer = nullptr; // multiply by 3 as RGB triplets used

    std::map<Ray, std::tuple<int, int>> primary_rays;
};

#endif