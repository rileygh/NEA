#ifndef ENGINE_H
#define ENGINE_H

#include "vec3f.h"
#include "vec2f.h"
#include "ray.h"
#include "scene.h"

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
    Vec3f trace(Ray& ray);
    GLubyte* get_render_data();
    
    void update_camera_to_world();

    float get_fov() const;
    Vec3f get_camera_pos() const;
    Vec3f get_camera_dir() const;
    float get_movement_speed() const;
    float get_sensitivity() const;
    float get_yaw() const;
    float get_pitch() const;

    void set_fov(float fov);
    void set_width(int width);
    void set_height(int height);
    void set_camera_pos(Vec3f position);
    void set_camera_dir(Vec3f direction);
    void set_movement_speed(float speed);
    void set_yaw(float yaw);
    void set_pitch(float pitch);

    void set_scene(Scene& scene);
    void set_defaults();

    private:
    float m_fov;
    int m_width, m_height;
    Camera m_camera;
    
    float m_movement_speed;
    float m_sensitivity;
    float m_yaw;
    float m_pitch;

    Matrix44f m_camera_to_world;

    GLubyte* m_image_buffer = nullptr;
    Scene* m_scene = nullptr;

    std::map<Ray, std::tuple<int, int>> m_primary_rays;
};

#endif