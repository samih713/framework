#include "matrix.h"

/**
 * @brief Prints a matrix to stdout in a formatted way.
 * Displays matrix dimensions followed by all elements row by row.
 *
 * @param mat Pointer to the matrix structure to print
 */
void print_matrix(const matrix_t *mat)
{
    printf("matrix size (%i,%i)\n", mat->rows, mat->cols);
    printf("[\n");
    for (int i = 0; i < mat->rows; ++i)
    {
        for (int j = 0; j < mat->cols; ++j)
            printf("  %.3f  ", mat->data[i][j]);
        printf("\n");
    }
    printf("]\n");
}

void print_row(const matrix_t *mat, int i)
{
    for (int j = 0; j < mat->cols; ++j)
    {
        printf("%.3f", mat->data[i][j]);
        printf("\n");
    }
}

float rand_float(void)
{
    return (float)rand() / (float)RAND_MAX;
}

void set_zero(const matrix_t *mat)
{
    for (int i = 0; i < mat->rows; ++i)
    {
        for (int j = 0; j < mat->cols; ++j)
            mat->data[i][j] = 0;
    }
}