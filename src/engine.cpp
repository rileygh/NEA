#include "engine.h"
#include "vec3f.h"
#include "vec2f.h"
#include "matrix44f.h"
#include "ray.h"
#include "utils.h"
#include "mesh.h"

#include <glfw/glfw3.h>

#include <cmath>
#include <cstdlib>
#include <tuple>

#include <omp.h>

void Engine::allocate_image_buffer() {
    m_image_buffer = new GLubyte[m_width * m_height * 3];
}

Vec3f Engine::trace(Ray &ray) { // return RGB triplet
    return Vec3f();
}

Vec2f Engine::get_pixel_coords(int row, int col) const {
    const float aspect_ratio = static_cast<float>(m_width) / m_height;
    float x = (2 * ((col + 0.5f) / m_width) - 1)  * tan(radians(m_fov / 2)) * aspect_ratio;
    float y = (1 - 2 * (row + 0.5f) / m_height) * tan(radians(m_fov / 2));
    return Vec2f(x, y);
}

GLubyte* Engine::get_render_data() {
    GLubyte* pixel = m_image_buffer;

    Vec3f world_origin(0, 0, 0);
    Matrix44f world_to_camera = get_camera_to_world_matrix().inverse();

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

Matrix44f Engine::get_camera_to_world_matrix() const {
    return Matrix44f(

    );
}

float Engine::get_fov() const { return m_fov; }

void Engine::set_fov(float fov) { m_fov = fov; }
void Engine::set_width(int width) { m_width = width; }
void Engine::set_height(int height) { m_height = height; }
void Engine::set_camera_pos(Vec3f position) { m_camera.m_position = position; }
void Engine::set_camera_dir(Vec3f direction) { m_camera.m_direction = direction; }

void Engine::set_defaults() {
    m_fov = 90;
    m_camera.m_position = Vec3f();
    m_camera.m_direction = Vec3f(0, 0, -1); // begin looking down -z axis
}