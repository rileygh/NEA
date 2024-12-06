#ifndef RAY_H
#define RAY_H

#include "vec3f.h"

enum RayType {
    PRIMARY,
    SHADOW,
    REFLECTION,
    REFRACTION
};

// ray stores a point of origin and a unit vector which indicates the direction of the ray
struct Ray {
    Ray(Vec3f &origin, Vec3f &direction, RayType ray_type) 
    : m_origin(origin), m_direction(direction), m_ray_type(ray_type) {};
    Vec3f m_origin, m_direction;
    RayType m_ray_type;
};

#endif