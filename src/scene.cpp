#include <cmath>
#include <optional>
#include <random>
#include <memory>

#include "scene.h"
#include "vec3f.h"
#include "ray.h"

Object::~Object() {} // need some object method to allow vtable to generate

std::optional<HitPayload> Sphere::intersect(Ray& ray) {
    Vec3f origin_to_centre = (m_centre - ray.m_origin);
    float dist_to_closest = origin_to_centre.dot(ray.m_direction);

    float squared_dist_to_ray = std::pow(origin_to_centre.mag(), 2) - std::pow(dist_to_closest, 2);

    float squared_radius = std::pow(m_radius, 2);

    if (squared_dist_to_ray > squared_radius) { return std::nullopt; } // ray doesn't intersect

    float offset = std::sqrt(squared_radius - squared_dist_to_ray);
    float t1 = dist_to_closest - offset;
    float t2 = dist_to_closest + offset;

    float t_hit = (t1 > 0) ? t1 : t2;

    if (t_hit < 0) { return std::nullopt; } // both intersections are behind the ray

    return HitPayload(
        t_hit,
        m_colour // shading will be done later
    );
}

void Scene::add_object(std::shared_ptr<Object> object) { m_objects.push_back(object); }

// void Scene::gen_random_spheres(int num_spheres) {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_real_distribution<float> radius_dist(1.0f, 10.0f);
//     std::uniform_real_distribution<float> position_dist(-100.0f, 0);
//     std::uniform_int_distribution<int> color_dist(0, 255);

//     for (int i = 0; i < num_spheres; i++) {
//         float radius = radius_dist(gen);
//         Vec3f centre(
//             position_dist(gen), 
//             position_dist(gen), 
//             position_dist(gen)
//         );

//         Vec3f colour(
//             static_cast<float>(color_dist(gen)),
//             static_cast<float>(color_dist(gen)),
//             static_cast<float>(color_dist(gen))
//         );

//         auto sphere = std::make_shared<Sphere>(radius, centre, colour, *this);
//         add_object(sphere);
//     }
// }