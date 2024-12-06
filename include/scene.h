#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "vec3f.h"
#include "ray.h"

struct HitPayload {
    Vec3f point, colour;
};

class Object {
    public:
    virtual bool intersects(Ray& ray, float& t1, float& t2);
    virtual Vec3f normal(); // TODO
    private:
};

class Sphere : public Object {
    public:
    Sphere(int radius, Vec3f centre) : m_radius(radius), m_centre(centre) {};

    bool intersects(Ray& ray, float& t1, float& t2) override;

    private:
    float m_radius;
    Vec3f m_centre;
};

struct Scene {
    std::vector<Object> objects;
};

#endif