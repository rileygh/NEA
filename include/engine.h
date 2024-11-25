#ifndef ENGINE_H
#define ENGINE_H

#include "vec3f.h"
#include "vec2f.h"
#include "ray.h"

#include <glfw/glfw3.h>

#include <map>
#include <tuple>

struct Camera {
    Vec3f position;
    Vec3f direction;
};

class Engine {
    public:
    void allocate_image_buffer();
    Vec2f get_pixel_coords(Vec3f camera_pos, int row, int col);
    Vec3f trace(Ray ray);
    GLubyte* get_render_data();

    float get_fov();

    void set_fov(float fov);
    void set_width(int width);
    void set_height(int height);
    void set_camera_pos(Vec3f position);
    void set_camera_dir(Vec3f direction);

    void set_defaults();

    private:
    float m_fov;
    int m_width, m_height;
    Camera m_camera;

    GLubyte* m_image_buffer = nullptr; // multiply by 3 as RGB triplets used

    std::map<Ray, std::tuple<int, int>> m_primary_rays;
};

#endif