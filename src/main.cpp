#include <iostream>

int main() {
    const int img_width = 1920;
    const int img_height = 1080;

    // render ppm (ref. example at https://en.wikipedia.org/wiki/Netpbm)
    std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n"; // P3 indicates RGB colour image in ASCII, followed by width, height, then max value for a colour
    for (int i = 0; i < img_height; i++) {
        for (int j = 0; j < img_width; j++) {
            // example gradient
            int r = 255 * i / img_height;
            int g = 0;
            int b = 255 * j / img_width;

            std::cout << r << ' ' << g << ' ' << b << ' ';
        }
    }
    std::clog << "done!";
    return 0;
}