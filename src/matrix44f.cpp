#include "matrix44f.h"

#include <cmath>

Matrix44f Matrix44f::inverse() {
    // using gauss-jordan elimination

    Matrix44f inverted, identity;
    float aug_left[4][4], aug_right[4][4]; // stores [M|I] halves in separate buffers

    // initialises [M|I]
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            aug_left[i][j] = elements[i][j];
            aug_right[i][j] = identity[i][j];
        }
    }

    for (int col = 0; col < 4; col++) {
        if (aug_left[col][col] == 0) {
            int max = col;
            for (int row = 0; row < 4; row++) {
                if (std::abs(aug_left[row][col]) > std::abs(aug_left[max][col])) {
                    max = row;
                }
            }

            if (max == col) { // check if matrix is singular
                throw std::runtime_error("Cannot invert singular matrix!");
            }

            for (int j = 0; j < 4; j++) {
                std::swap(aug_left[col][j], aug_left[max][j]);
                std::swap(aug_right[col][j], aug_right[col][j]); // apply same elementary row operations
            }
        }

    }

    return inverted;
}