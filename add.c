#include "matrix.h"

/**
 * @brief Adds a scalar value to each element of a matrix.
 *
 * @param a Input matrix
 * @param b Scalar value to add
 *
 * @return New matrix with scalar added to each element
 */
matrix_t add_scalar(const matrix_t *a, float b)
{
    matrix_t c = matrix(a->rows, a->cols);
    int c_size = c.rows * c.cols;
    for (int i = 0; i < c_size; ++i)
    {
        c.data[0][i] = a->data[0][i] + b;
    }
    return c;
}

void add_into(const matrix_t *a, const matrix_t *b, matrix_t *c)
{
    int size_a = a->rows * a->cols;
    int size_b = b->rows * b->cols;

    if (size_a != size_b)
    {
        ERROR("Addition not possible.\n");
        return;
    }

    for (int i = 0; i < size_a; ++i)
    {
        c->data[0][i] = a->data[0][i] + b->data[0][i];
    }
}