#ifndef MESH_H
#define MESH_H

#include "vec3f.h"
#include "vec2f.h"

#include <vector> // for triangle storage, not the same as Vec3f

struct Vertex {
    Vec3f m_position, m_normal;
    Vec2f m_tex_coords;
};

class Mesh {
    public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<int>& indices);

    private:
    std::vector<Vertex> vertices;
    std::vector<int> indices;

    int VAO, VBO, EBO;
};

#endif