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
matrix_t multiply(matrix_t a, matrix_t b)
{
    assert(a.cols == b.rows && "Matrix multiplication not possible.\n");
    
    matrix_t c = matrix(a.rows, b.cols);
    for (size_t i = 0; i < a.rows; ++i)
    {
        for (size_t j = 0; j < b.cols; ++j)
        {
            for (size_t k = 0; k < a.cols; ++k)
                MAT_AT(c, i, j) += MAT_AT(a, i, k) * MAT_AT(b, k, j);
        }
    }
    return c;
}

void multiply_into(matrix_t a, matrix_t b, matrix_t c)
{
    assert(a.cols == b.rows && "Matrix multiplication not possible.\n");
    assert(c.rows == a.rows && c.cols == b.cols && "output matrix has wrong shape");

    for (size_t i = 0; i < a.rows; ++i)
    {
        for (size_t j = 0; j < b.cols; ++j)
        {
            MAT_AT(c, i, j) = 0;
            for (size_t k = 0; k < a.cols; ++k)
                MAT_AT(c, i, j) += MAT_AT(a, i, k) * MAT_AT(b, k, j);
        }
    }
}
