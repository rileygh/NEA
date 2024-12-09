#include "vec3f.h"
#include "matrix44f.h"

#include <cmath>

float Vec3f::mag() const {
    float x = this->x();
    float y = this->y();
    float z = this->z();
    return std::sqrt(x * x + y * y + z * z);
}

Vec3f Vec3f::norm() const {
    // get components
    float x = this->x();
    float y = this->y();
    float z = this->z();
    float mag = this->mag();

    if (mag == 0) {
        return Vec3f(); // vector (0, 0, 0) if magnitude is 0 to avoid division by 0 error
    }
    else {
        return Vec3f(x / mag, y / mag, z / mag); // formula for normalised vector
    }
}

// output operator for debug
std::ostream& operator<<(std::ostream& o, const Vec3f& v) {
    o << "Vec<" << v.x() << ", " << v.y() << ", " << v.z() << '>';
    return o;
};

bool Vec3f::operator==(const Vec3f& other) const {
    return x() == other.x() && y() == other.y() && z() == other.z();
}

Vec3f Vec3f::operator-(const Vec3f& other) const {
    return Vec3f(x() - other.x(), y() - other.y(), z() - other.z());
}

Vec3f Vec3f::operator+(const Vec3f& other) const {
    return Vec3f(x() + other.x(), y() + other.y(), z() + other.z());
}

Vec3f Vec3f::operator*(const float scalar) const {
    return Vec3f(x() * scalar, y() * scalar, z() * scalar);
}

Vec3f Vec3f::mult_with_matrix44f(const Matrix44f& matrix) const {
    Vec3f result;
    result.set_x(x() * matrix[0][0] + y() * matrix[1][0] + z() * matrix[2][0] + matrix[3][0]);
    result.set_y(x() * matrix[0][1] + y() * matrix[1][1] + z() * matrix[2][1] + matrix[3][1]);
    result.set_z(x() * matrix[0][2] + y() * matrix[1][2] + z() * matrix[2][2] + matrix[3][2]);
    return result;
}

float Vec3f::dot(const Vec3f& other) const {
    return x() * other.x() + y() * other.y() + z() * other.z();
}

Vec3f Vec3f::cross(const Vec3f& other) const {
    return Vec3f(
        y() * other.z() - z() * other.y(), 
        z() * other.x() - x() * other.z(),
        x() * other.y() - y() * other.x()
    );
}

// getters
float Vec3f::x() const { return m_coords[0]; }
float Vec3f::y() const { return m_coords[1]; }
float Vec3f::z() const { return m_coords[2]; }

// setters
void Vec3f::set_x(float val) { m_coords[0] = val; }
void Vec3f::set_y(float val) { m_coords[1] = val; }
void Vec3f::set_z(float val) { m_coords[2] = val; }