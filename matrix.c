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

/**
 * @brief Fills a matrix with random floating-point values between 0 and 1.
 *
 * @param mat Pointer to the matrix to fill with random values
 */
void rand_matrix(matrix_t *mat)
{
    int size = mat->rows * mat->cols;
    for (int i = 0; i < size; ++i)
    {
        mat->data[0][i] = rand_float();
    }
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