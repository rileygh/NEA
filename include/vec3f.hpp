#ifndef VEC3F_HPP
#define VEC3F_HPP

class Vec3f {
    public:  
    Vec3f() : coords{0, 0, 0} {}; // no args interchangable with Vec3f(0, 0, 0)
    Vec3f(float x, float y, float z) : coords{x, y, z} {};

    // getters
    float x() const;
    float y() const;
    float z() const;

    // setters
    void set_x(float val);
    void set_y(float val);
    void set_z(float val);

    private:
    float coords[3];
};

#endif