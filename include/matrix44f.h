#ifndef MATRIX44F_H
#define MATRIX44F_H

class Vec3f; // forward declaration to solve circular dependency
#include "vec3f.h"

#include <cstring>

class Matrix44f {
    public:
    Matrix44f() { // no args creates identity matrix
        memset(elements, 0, sizeof(elements));
        elements[0][0] = elements[1][1] = elements[2][2] = elements[3][3] = 1.0f;
    };

    Matrix44f(
        float a, float b, float c, float d,
        float e, float f, float g, float h,
        float i, float j, float k, float l,
        float m, float n, float o, float p
    ) 
    : elements{{a, b, c, d}, {e, f, g, h}, {i, j, k, l}, {m, n, o, p}} {};

    Matrix44f inverse();

    // getter
    const float* operator[](int i) const { return elements[i]; }

    // setter (returns reference to row)
    float* operator[](int i) { return elements[i]; };

    private:
    float elements[4][4];
};

#endif