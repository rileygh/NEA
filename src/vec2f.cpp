#include "vec2f.h"

// output operator for debug
std::ostream& operator<<(std::ostream& o, const Vec2f& v) {
    o << "Vec<" << v.x() << ", " << v.y() << '>';
    return o;
};

bool Vec2f::operator==(const Vec2f& other) const {
    return x() == other.x() && y() == other.y();
}

Vec2f Vec2f::operator-(const Vec2f& other) const {
    return Vec2f(x() - other.x(), y() - other.y());
}

// getters
float Vec2f::x() const { return m_coords[0]; }
float Vec2f::y() const { return m_coords[1]; }

// setters
void Vec2f::set_x(float val) { m_coords[0] = val; }
void Vec2f::set_y(float val) { m_coords[1] = val; }