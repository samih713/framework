#include "matrix.h"

void __intit_matrix(matrix_t *mat, int rows, int cols);

/**
 * @brief Creates and initializes a new matrix with specified dimensions.
 *
 * @param rows Number of rows
 * @param cols Number of columns
 *
 * @return Initialized matrix_t structure
 */
matrix_t matrix(int rows, int cols)
{
    matrix_t new;
    __intit_matrix(&new, rows, cols);
    return new;
}

void __intit_matrix(matrix_t *mat, int rows, int cols)
{
    // initialize to safe values
    mat->data = NULL;
    mat->rows = 0;
    mat->cols = 0;
    // allocate row pointers
    mat->data = malloc(sizeof(float *) * rows);
    if (!mat->data)
    {
        ERROR("Allocation failed.\n");
        return;
    }
    // allocate block
    mat->data[0] = calloc((rows * cols), sizeof(float));
    if (!mat->data[0])
    {
        ERROR("Allocation failed.\n");
        free(mat->data);  // Clean up the row pointers
        mat->data = NULL;
        return;
    }
    // set row pointers
    for (int i = 1; i < rows; ++i)
    {
        mat->data[i] = mat->data[i - 1] + cols;
    }
    // set the size
    mat->rows = rows;
    mat->cols = cols;
}