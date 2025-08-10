#include "matrix.h"

/**
 * @brief Adds a scalar value to each element of a matrix.
 *
 * @param a Input matrix
 * @param b Scalar value to add
 *
 * @return New matrix with scalar added to each element
 */
matrix_t add_scalar(matrix_t a, float b)
{
    matrix_t c = matrix(a.rows, a.cols);

    for (size_t i = 0; i < a.rows; ++i)
    {
        for (size_t j = 0; i < a.cols; ++i)
            MAT_AT(c, i, j) = MAT_AT(a, i, j) + b;
    }
    return c;
}

void add_into(matrix_t a, matrix_t b, matrix_t c)
{
    assert(a.rows == b.rows && a.cols == b.cols && "Addition not possible.\n");
    for (size_t i = 0; i < a.rows; ++i)
    {
        for (size_t j = 0; i < a.cols; ++i)
            MAT_AT(c, i, j) = MAT_AT(a, i, j) + MAT_AT(b, i, j);
    }
}