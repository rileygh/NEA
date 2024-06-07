#include "vec3f.hpp"

// getters
float Vec3f::x() const {return coords[0];}
float Vec3f::y() const {return coords[1];}
float Vec3f::z() const {return coords[2];}

// setters
void Vec3f::set_x(float val) {coords[0] = val;}
void Vec3f::set_y(float val) {coords[1] = val;}
void Vec3f::set_z(float val) {coords[2] = val;}