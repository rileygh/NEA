#include "engine.h"
#include "vec3f.h"
#include "vec2f.h"
#include "matrix44f.h"
#include "ray.h"
#include "utils.h"

#include <glfw/glfw3.h>

#include <cmath>
#include <cstdlib>
#include <tuple>
#include <variant>

#include <omp.h>

void Engine::allocate_image_buffer() {
    m_image_buffer = new GLubyte[m_width * m_height * 3];
}

Vec3f Engine::trace(Ray &ray) { // return RGB triplet
    float closest_hit = std::numeric_limits<float>::max();
    Vec3f colour;

    for (const auto& object : m_scene->m_objects) {
        auto result = object->intersect(ray); // polymorphic call
        if (result) {
            const HitPayload& hit_payload = *result;
            if (hit_payload.m_t < closest_hit) {
                closest_hit = hit_payload.m_t;
                colour = hit_payload.m_colour;
            }
        }
    }

    return closest_hit < std::numeric_limits<float>::max() ? colour : Vec3f();
}

Vec2f Engine::get_pixel_coords(int row, int col) const {
    const float aspect_ratio = static_cast<float>(m_width) / m_height;
    float x = (2 * ((col + 0.5f) / m_width) - 1)  * tan(radians(m_fov / 2)) * aspect_ratio;
    float y = (1 - 2 * (row + 0.5f) / m_height) * tan(radians(m_fov / 2));
    return Vec2f(x, y);
}

GLubyte* Engine::get_render_data() {
    GLubyte* pixel = m_image_buffer;

    #pragma omp parallel for collapse(2)
    for (int row = 0; row < m_height; row++) {
        for (int col = 0; col < m_width; col++) {
            // assume camera is at (0, 0, 0) facing (0, 0, -1), then transform results with world to camera matrix
            Vec2f pixel_xy = get_pixel_coords(row, col);
            Vec3f pixel_coords(
                pixel_xy.x(),
                pixel_xy.y(),
                -1
            );
            Vec3f ray_direction = (pixel_coords - m_camera.m_position).norm();
            Ray ray(m_camera.m_position, ray_direction, PRIMARY);

            // #pragma omp critical
            // {
            //     std::cerr << ray.origin << " | " << ray.direction << " | " << ray.ray_type << '\n';
            // }

            Vec3f colour = trace(ray);
            *pixel = colour.x();
            *(pixel + 1) = colour.y();
            *(pixel + 2) = colour.z();

            pixel += 3;
        }
    }
    return m_image_buffer;
}

void Engine::look_at(Vec3f& target) {
    Vec3f world_up(0, 1, 0);
    Vec3f forward = (m_camera.m_position - target).norm();
    Vec3f right = world_up.cross(forward).norm();
    Vec3f up = forward.cross(right);
    // don't need to normalise up vector as both inputs are already normalised and the angle will always be 90 degrees

    m_camera_to_world = Matrix44f(
        right.x(), right.y(), right.z(), 0,
        up.x(), up.y(), up.z(), 0,
        forward.x(), forward.y(), forward.z(), 0,
        m_camera.m_position.x(), m_camera.m_position.y(), m_camera.m_position.z(), 1
    );
}

void Engine::move(Vec3f& pos) {
    m_camera_to_world[3][0] = pos.x();
    m_camera_to_world[3][1] = pos.y();
    m_camera_to_world[3][2] = pos.z();
}

float Engine::get_fov() const { return m_fov; }
Matrix44f Engine::get_camera_to_world() const { return m_camera_to_world; }

void Engine::set_fov(float fov) { m_fov = fov; }
void Engine::set_width(int width) { m_width = width; }
void Engine::set_height(int height) { m_height = height; }
void Engine::set_camera_pos(Vec3f position) { m_camera.m_position = position; }
void Engine::set_camera_dir(Vec3f direction) { m_camera.m_direction = direction; }
void Engine::set_camera_to_world(Matrix44f matrix) { m_camera_to_world = matrix; }

void Engine::set_scene(Scene& scene) {
    m_scene = &scene;
}

void Engine::set_defaults() {
    m_fov = 90;
    m_camera.m_position = Vec3f();
    m_camera.m_direction = Vec3f(0, 0, -1); // begin looking down -z axis
}