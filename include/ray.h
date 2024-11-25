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
    Ray(Vec3f &_origin, Vec3f &_direction, RayType _ray_type) 
    : origin(_origin), direction(_direction), ray_type(_ray_type) {};
    Vec3f origin, direction;
    RayType ray_type;
};

#endif