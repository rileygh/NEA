#include "vec3f.h"
#include "ray.h"
#include "utils.h"

#include <map>
#include <cmath>
#include <tuple>

struct Camera {
    Vec3f position, facing; // facing: unit direction vector
};

class Engine {
    public:
    #define ASPECT_RATIO width / height;

    Vec3f get_pixel_coords(Vec3f camera_pos, float fov, int row, int col) {
        float x = (2 * ((row + 0.5f) / width) - 1) * tan(radians(fov / 2)) * ASPECT_RATIO;
        float y = (1 - 2 * (col + 0.5f) / height) * tan(radians(fov / 2));
        return Vec3f(x, y, -1); // camera starts being aligned with -z axis
    }

    void render() {
        
    }

    private:
    float fov;
    int width, height;

    std::map<Ray, std::tuple<int, int>> primary_rays;
};