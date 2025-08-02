#include "matrix.h"

/**
 * @brief Prints a matrix to stdout in a formatted way.
 * Displays matrix dimensions followed by all elements row by row.
 * 
 * @param mat Pointer to the matrix structure to print
 */
void print_matrix(const matrix_t *mat)
{
    printf("matrix size (%i,%i)\n", mat->m, mat->n);
    for (int i = 0; i < mat->m; ++i)
    {
        for (int j = 0; j < mat->n; ++j)
            if (j == mat->n - 1)
            {
                printf("%.2f", mat->data[i][j]);
            }
            else
            {
                printf("%.2f, ", mat->data[i][j]);
            }
        printf("\n");
    }
}

float rand_float(void)
{
    return (float)rand() / (float)RAND_MAX;
}

void set_zero(const matrix_t *mat)
{
    for (int i = 0; i < mat->m; ++i)
    {
        for (int j = 0; j < mat->n; ++j)
           mat->data[i][j] = 0;
    }
}