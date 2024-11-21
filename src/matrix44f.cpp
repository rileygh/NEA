#include "matrix44f.h"

#include <cmath>

Matrix44f Matrix44f::inverse() {
    // using gauss-jordan elimination

    Matrix44f inverted, identity; // all will initialise to the identity matrix, but we will alter values in inverted
    float aug[4][8]; // will act as a matrix with no functionality, just stores numbers

    // set aug to [M|I] where M is the current matrix
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            aug[i][j] = elements[i][j];
            aug[i][j + 4] = identity[i][j];
        }
    }

    for (int i = 0; i < 4; i++) {
        // partial pivoting - largest element in column i
        int row_max = i;
        for (int k = i + 1; k < 4; k++) {
            if (std::abs(aug[k][i]) > std::abs(aug[row_max][i])) {
                row_max = k;
            }
        }

        // swap rows if needed
        if (row_max != i) {
            for (int j = 0; j < 8; j++) {
                std::swap(aug[i][j], aug[row_max][j]);
            }
        }

        // in order to invert a matrix, it must be non-singular (square ie. n x n, and its determinant does not equal 0)
        // if the pivot element is 0 then the matrix is singular
        if (std::abs(aug[i][i]) == 0) {
            throw std::runtime_error("Cannot convert singular matrix!");
        }

        // scale pivot row
        float pivot = aug[i][i];
        for (int j = 0; j < 8; j++) {
            aug[i][j] /= pivot;
        }

        // reduce matrix by removing column elements above and below the pivot
        for (int j = 0; j < 4; j++) {
            if (j != i) {
                float factor = aug[j][i];
                for (int k = 0; k < 8; k++) {
                    aug[j][k] -= factor * aug[i][k];
                }
            }
        }
    }

    // the inverted matrix is now equal to the right half of aug
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            inverted[i][j] = aug[i][j] + 4; // set each element to the corresponding element in the right half of aug
        }
    }

    return inverted;
}