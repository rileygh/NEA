#ifndef MATRIX44F_H
#define MATRIX44F_H

#include <cstring>
#include <iostream>

class Matrix44f {
    public:
    Matrix44f() { // no args creates identity matrix
        memset(m_elements, 0, sizeof(m_elements));
        m_elements[0][0] = m_elements[1][1] = m_elements[2][2] = m_elements[3][3] = 1.0f;
    };

    Matrix44f(
        float a, float b, float c, float d,
        float e, float f, float g, float h,
        float i, float j, float k, float l,
        float m, float n, float o, float p
    ) 
    : m_elements{{a, b, c, d}, {e, f, g, h}, {i, j, k, l}, {m, n, o, p}} {};

    Matrix44f inverse();

    friend std::ostream& operator<<(std::ostream& o, const Matrix44f& m);

    // getter
    const float* operator[](int i) const { return m_elements[i]; }

    // setter (returns reference to row)
    float* operator[](int i) { return m_elements[i]; };

    private:
    float m_elements[4][4];
};

#endif