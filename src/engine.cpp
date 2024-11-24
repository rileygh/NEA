#include "engine.h"
#include "vec3f.h"
#include "ray.h"
#include "utils.h"

#include <glfw/glfw3.h>

#include <map>
#include <cmath>
#include <tuple>

void Engine::allocate_image_buffer() {
    image_buffer = new GLubyte[width * height * 3];
}

Vec3f Engine::trace(Ray ray) { return Vec3f(1, 1, 1); } // return white for now

Vec3f Engine::get_pixel_coords(Vec3f camera_pos, int row, int col) {
    #define ASPECT_RATIO width / height

    float x = (2 * ((row + 0.5f) / width) - 1) * tan(radians(fov / 2)) * ASPECT_RATIO;
    float y = (1 - 2 * (col + 0.5f) / height) * tan(radians(fov / 2));
    return Vec3f(x, y, -1); // camera starts being aligned with -z axis
}

GLubyte* Engine::get_render_data() {
    int c = 0;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            // TODO: make the correct ray
            // then trace it
            // and add RGB triplet to image_buffer
            int i = (row * width + col) * 3;
            image_buffer[i] = 255;
            image_buffer[i + 1] = 255;
            image_buffer[i + 2] = 255;
            c += 1;
        }
        std::cerr<<c<<'\n';
    }
    return image_buffer;
}

float Engine::get_fov() { return fov; }

void Engine::set_fov(float _fov) { fov = _fov; }
void Engine::set_width(int _width) { width = _width; }
void Engine::set_height(int _height) { height = _height; }