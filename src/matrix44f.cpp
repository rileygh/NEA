#include "matrix44f.h"

#include <cmath>
#include <stdexcept>

// algorithm from https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/matrix-inverse/matrix-inverse.html
Matrix44f Matrix44f::inverse() {
    // using gauss-jordan elimination

    Matrix44f inverted, identity;
    float aug_left[4][4], aug_right[4][4]; // stores [M|I] halves in separate buffers

    // initialises [M|I]
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            aug_left[i][j] = m_elements[i][j];
            aug_right[i][j] = identity[i][j];
        }
    }

    // sets pivot coefficients to 0 with elementary row operations
    // so that the solution set of the matrix is preserved
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

            for (int i = 0; i < 4; i++) {
                std::swap(aug_left[col][i], aug_left[max][i]);
                std::swap(aug_right[col][i], aug_right[max][i]); // apply same operations
            }
        }
    }

    // row-reduction of coefficients under the pivot
    for (int col = 0; col < 3; col++) { // loop 3 times as last column has pivot coefficient in bottom row
        for (int row = col + 1; row < 4; row++) {
            float k = -(aug_left[row][col] / aug_left[col][col]);

            for (int i = 0; i < 4; i++) {
                aug_left[row][i] += k * aug_left[col][i];
                aug_right[row][i] += k * aug_right[col][i]; // apply same operations
            }
        }
    }

    // scale pivot coefficients to 1
    for (int row = 0; row < 4; row++) {
        float k = aug_left[row][row];

        for (int col = 0; col < 4; col++) {
            aug_left[row][col] /= k;
            aug_right[row][col] /= k;
        }
    }

    // row-reduction of coefficients above the pivot
    for (int row = 0; row < 4; row++) {
        for (int col = row + 1; col < 4; col++) {
            float k = -(aug_left[row][col]);
            
            for (int i = 0; i < 4; i++) {
                aug_left[row][i] += k * aug_left[col][i];
                aug_right[row][i] += k * aug_right[col][i];
            }
        }
    }

    // get Matrix44f object with inverted values
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            inverted[i][j] = aug_right[i][j];
        }
    }

    return inverted;
}