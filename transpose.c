#include "matrix.h"

matrix_t transpose(matrix_t m) {
    matrix_t t = matrix(m.cols, m.rows);
    for (size_t i = 0; i < m.cols; ++i) {
        for (size_t j = 0; j < m.rows; ++j) {
            MAT_AT(t, i, j) = MAT_AT(m, j, i);
        }
    }
    return t;
}
