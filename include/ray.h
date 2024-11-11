#ifndef RAY_H
#define RAY_H

#include <vec3f.h>

// ray stores a point of origin and a unit vector which indicates the direction of the ray
class Ray {
    public:
    Ray(Vec3f orig, Vec3f dir) : origin(orig), direction(dir) {};

    private:
    Vec3f origin, direction;
};

#endif