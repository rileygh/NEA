#include "engine.h"
#include "vec3f.h"
#include "vec2f.h"
#include "matrix44f.h"
#include "ray.h"
#include "utils.h"
#include "scene.h"

#include <glfw/glfw3.h>

#include <cmath>
#include <cstdlib>
#include <tuple>

#include <omp.h>

void Engine::allocate_image_buffer() {
    m_image_buffer = new GLubyte[m_width * m_height * 3];
}

Vec3f Engine::trace(Ray &ray) { // return RGB triplet
    // test
    return Vec3f(ray.direction.x() * 255, ray.direction.x() * 255, ray.direction.y() * 255);
}

Vec2f Engine::get_pixel_coords(Vec3f camera_pos, int row, int col) const {
    const float aspect_ratio = 1.0f; static_cast<float>(m_width) / m_height;
    // assume camera is at (0, 0, 0) facing (0, 0, -1), then transform results with world to camera matrix
    float x = (2 * ((row + 0.5f) / m_width) - 1)  * tan(radians(m_fov / 2)) * aspect_ratio;
    float y = (1 - 2 * (col + 0.5f) / m_height) * tan(radians(m_fov / 2));
    return Vec2f(x, y);
}

GLubyte* Engine::get_render_data() {
    GLubyte* pixel = m_image_buffer;

    Vec3f world_origin(0, 0, 0);
    Matrix44f world_to_camera = Matrix44f(
        // TODO: set this
    );

    #pragma omp parallel for collapse(2)
    for (int row = 0; row < m_height; row++) {
        for (int col = 0; col < m_width; col++) {
            Vec2f pixel_xy = get_pixel_coords(m_camera.position, row, col);
            Vec3f pixel_coords(
                pixel_xy.x(),
                pixel_xy.y(),
                m_camera.position.z() + m_camera.direction.z()
            );
            Vec3f ray_direction = Vec3f(pixel_coords - m_camera.position).norm();
            Ray ray(m_camera.position, ray_direction, PRIMARY);

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
void Engine::set_camera_pos(Vec3f position) { m_camera.position = position; }
void Engine::set_camera_dir(Vec3f direction) { m_camera.direction = direction; }

void Engine::set_defaults() {
    m_fov = 90;
    m_camera.position = Vec3f();
    m_camera.direction = Vec3f(0, 0, -1); // begin looking down -z axis
}