#include <cmath>
#include <optional>
#include <memory>

#include "scene.h"
#include "vec3f.h"
#include "ray.h"

Object::~Object() {}

std::optional<HitPayload> Sphere::intersect(Ray& ray) {
    Vec3f origin_to_centre = (m_centre - ray.m_origin);
    float dist_to_closest = origin_to_centre.dot(ray.m_direction);

    float squared_dist_to_ray = origin_to_centre.dot(origin_to_centre) - std::pow(dist_to_closest, 2);

    float squared_radius = std::pow(m_radius, 2);

    if (squared_dist_to_ray > squared_radius) { return std::nullopt; } // ray doesn't intersect

    float offset = std::sqrt(squared_radius - squared_dist_to_ray);
    float t1 = dist_to_closest - offset;
    float t2 = dist_to_closest + offset;

    float t_hit = (t1 > 0) ? t1 : t2;

    if (t_hit < 0) { return std::nullopt; } // both intersections are behind the ray

    return HitPayload(
        t_hit,
        Vec3f(255, 255, 255) // shading will be done later
    );
}

void Scene::add_object(std::shared_ptr<Object> object) { m_objects.push_back(object); }