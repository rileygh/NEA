#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <optional>
#include <memory>

#include "vec3f.h"
#include "ray.h"

struct HitPayload {
    HitPayload(float t, Vec3f colour) : m_t(t), m_colour(colour) {};
    float m_t;
    Vec3f m_colour;
};

class Object {
    public:
    virtual ~Object();
    virtual std::optional<HitPayload> intersect(Ray& ray) = 0;
    private:
};

struct Scene {
    std::vector<std::shared_ptr<Object>> m_objects;

    void add_object(std::shared_ptr<Object> object);

    // void gen_random_spheres(int num_spheres);
};

class Sphere : public Object {
    public:
    Sphere(float radius, Vec3f centre, Vec3f colour, Scene &scene) 
    : m_radius(radius), m_centre(centre), m_colour(colour) {
        scene.add_object(std::make_shared<Sphere>(*this));
    };

    std::optional<HitPayload> intersect(Ray& ray) override;

    private:
    float m_radius;
    Vec3f m_centre, m_colour;
};

#endif