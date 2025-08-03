#include "matrix.h"

/**
 * @brief Multiplies two matrices using standard matrix multiplication.
 *
 * @param a First matrix
 * @param b Second matrix
 *
 * @return Result matrix of dimensions a->rows x b->cols,
 *
 * @note: returns NULL_MATRIX (empty) if multiplication is not possible.
 */
matrix_t multiply(const matrix_t *a, const matrix_t *b)
{
    if (a->cols != b->rows)
    {
        ERROR("Matrix multiplication not possible.\n");
        return NULL_MATRIX;
    }
    matrix_t c = matrix(a->rows, b->cols);
    for (int i = 0; i < a->rows; ++i)
    {
        for (int j = 0; j < b->cols; ++j)
        {
            for (int k = 0; k < a->cols; ++k)
                c.data[i][j] += a->data[i][k] * b->data[k][j];
        }
    }
    return c;
}

void multiply_into(const matrix_t *a, const matrix_t *b, matrix_t *c)
{
    if (a->cols != b->rows)
    {
        ERROR("Matrix multiplication not possible.\n");
        return;
    }
    if ((c->rows != a->rows) | (c->cols != b->cols))
    {
        ERROR("Invalid size for Output matrix.\n");
        return;
    }
    for (int i = 0; i < a->rows; ++i)
    {
        for (int j = 0; j < b->cols; ++j)
        {
            c->data[i][j] = 0;
            for (int k = 0; k < a->cols; ++k)
                c->data[i][j] += a->data[i][k] * b->data[k][j];
        }
    }
}

