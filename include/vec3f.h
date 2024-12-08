#ifndef VEC3F_H
#define VEC3F_H

#include <iostream>

#include "matrix44f.h"

class Vec3f {
    public:  
    Vec3f() : m_coords{0, 0, 0} {}; // no args interchangable with Vec3f(0, 0, 0)
    Vec3f(float x, float y, float z) : m_coords{x, y, z} {};

    float mag() const;
    Vec3f norm() const;

    // define output operator (debug)
    friend std::ostream& operator<<(std::ostream& o, const Vec3f& v);

    bool operator==(const Vec3f& other) const;
    Vec3f operator-(const Vec3f& other) const;
    Vec3f operator+(const Vec3f& other) const;
    Vec3f operator*(const float scalar) const; // multiply by scalar

    float dot(const Vec3f& other) const;
    Vec3f cross(const Vec3f& other) const;
    Vec3f mult_with_matrix44f(const Matrix44f& matrix) const;

    // getters
    float x() const;
    float y() const;
    float z() const;

    // setters
    void set_x(float val);
    void set_y(float val);
    void set_z(float val);

    private:
    float m_coords[3];
};

#endif