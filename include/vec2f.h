#ifndef VEC2F_H
#define VEC2F_H

#include <iostream>

#include "matrix44f.h"

class Vec2f {
    public:  
    Vec2f() : coords{0, 0} {}; // no args interchangable with Vec2f(0, 0)
    Vec2f(float x, float y) : coords{x, y} {};

    // define output operator (debug)
    friend std::ostream& operator<<(std::ostream& o, const Vec2f& v);

    bool operator==(const Vec2f& other) const;
    Vec2f operator-(const Vec2f& other) const;

    // getters
    float x() const;
    float y() const;

    // setters
    void set_x(float val);
    void set_y(float val);

    private:
    float coords[2];
};

#endif