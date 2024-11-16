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
    Vec3f origin, direction;
    RayType ray_type;
};

#endif