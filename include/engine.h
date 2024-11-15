#ifndef ENGINE_H
#define ENGINE_H

#include "ray.h"
#include "vec3f.h"
#include "camera.h"

class Engine {
    public:
    Vec3f trace_ray(Ray ray, Camera camera); // returns intersection pos
    Vec3f get_intersection_colour(Vec3f intersection, Camera camera);
};

#endif