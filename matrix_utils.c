#include "matrix.h"

/**
 * @brief Prints a matrix to stdout in a formatted way.
 * Displays matrix dimensions followed by all elements row by row.
 *
 * @param mat Pointer to the matrix structure to print
 */
void print_matrix(const matrix_t m)
{
    printf("matrix size (%zu,%zu)\n", m.rows, m.cols);
    printf("[\n");
    for (size_t i = 0; i < m.rows; ++i)
    {
        for (size_t j = 0; j < m.cols; ++j)
            printf("  %.3f  ", MAT_AT(m, i, j));
        printf("\n");
    }
    printf("]\n");
}

/**
 * @brief Fills a matrix with random floating-posize_t values between 0 and 1.
 *
 * @param mat Pointer to the matrix to fill with random values
 */
void rand_matrix(matrix_t mat)
{
    size_t size = mat.rows * mat.cols;
    for (size_t i = 0; i < size; ++i)
    {
        mat.data[0][i] = rand_float();
    }
}

void print_row(matrix_t m, size_t i)
{
    printf("[  ");
    for (size_t j = 0; j < m.cols; ++j)
    {
        printf("%.3f  ", MAT_AT(m, i, j));
    }
    printf("]\n");
}

void print_col(matrix_t m, size_t j)
{
    printf("[\n");
    for (size_t i = 0; i < m.rows; ++i)
    {
        printf("  %.3f  ", MAT_AT(m, i, j));
        printf("\n");
    }
    printf("]\n");
}

float rand_float(void)
{
    return (float)rand() / (float)RAND_MAX;
}

void set_zero(const matrix_t *mat)
{
    for (size_t i = 0; i < mat->rows; ++i)
    {
        for (size_t j = 0; j < mat->cols; ++j)
            mat->data[i][j] = 0;
    }
}

/**
 * @brief Frees the internal data arrays of a matrix structure
 *
 * Deallocates the memory used by the matrix's data arrays and resets
 * the matrix dimensions to zero.
 *
 * @param mat Pointer to the matrix structure to free
 *
 * @note Does not free the matrix structure itself.
 */
void free_matrix(matrix_t *mat)
{
    if (!mat)
        return;
    if (mat->data)
    {
        free(mat->data[0]);
        free(mat->data);
    }
    mat->data = NULL;
    mat->rows = 0;
    mat->cols = 0;
}

void fill_matrix(matrix_t mat, float v) {
    size_t size = mat.rows * mat.cols;
    for (size_t i = 0; i < size; ++i)
    {
        mat.data[0][i] = v;
    }
}