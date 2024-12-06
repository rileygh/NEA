#ifndef ENGINE_H
#define ENGINE_H

#include "vec3f.h"
#include "vec2f.h"
#include "ray.h"

#include <glfw/glfw3.h>

#include <map>
#include <tuple>

struct Camera {
    Vec3f m_position;
    Vec3f m_direction; // facing direction = -z direction in camera coordinate system
};

class Engine {
    public:
    void allocate_image_buffer();
    Vec2f get_pixel_coords(int row, int col) const;
    Vec3f trace(Ray &ray);
    GLubyte* get_render_data();

    void look_at(Vec3f& target);
    void move(Vec3f& pos);

    float get_fov() const;
    Matrix44f get_camera_to_world() const;

    void set_fov(float fov);
    void set_width(int width);
    void set_height(int height);
    void set_camera_pos(Vec3f position);
    void set_camera_dir(Vec3f direction);
    void set_camera_to_world(Matrix44f matrix);

    void set_defaults();

    private:
    float m_fov;
    int m_width, m_height;
    Camera m_camera;

    Matrix44f m_camera_to_world;

    GLubyte* m_image_buffer = nullptr;

    std::map<Ray, std::tuple<int, int>> m_primary_rays;
};

#endif