#include "matrix.h"

/**
 * @brief Multiplies two matrices using standard matrix multiplication.
 *
 * @param a First matrix
 * @param b Second matrix
 *
 * @return Result matrix of dimensions a->m x b->n,
 *
 * @note: returns NULL_MATRIX (empty) if multiplication is not possible.
 */
matrix_t multiply(const matrix_t *a, const matrix_t *b)
{
    if (a->n != b->m)
    {
        ERROR("Matrix multiplication not possible.\n");
        return NULL_MATRIX;
    }
    matrix_t c = matrix(a->m, b->n);
    for (int i = 0; i < a->m; ++i)
    {
        for (int j = 0; j < b->n; ++j)
        {
            for (int k = 0; k < a->n; ++k)
                c.data[i][j] += a->data[i][k] * b->data[k][j];
        }
    }
    return c;
}

void multiply_into(const matrix_t *a, const matrix_t *b, matrix_t *c)
{
    if (a->n != b->m)
    {
        ERROR("Matrix multiplication not possible.\n");
        return;
    }
    if ((c->m != a->m) | (c->n != b->n))
    {
        ERROR("Invalid size for Output matrix.\n");
        return;
    }
    for (int i = 0; i < a->m; ++i)
    {
        for (int j = 0; j < b->n; ++j)
        {
            c->data[i][j] = 0;
            for (int k = 0; k < a->n; ++k)
                c->data[i][j] += a->data[i][k] * b->data[k][j];
        }
    }
}

