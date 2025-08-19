#ifndef MATRIX_H
#define MATRIX_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

typedef struct matrix_s
{
    float **data;
    size_t rows;
    size_t cols;
} matrix_t;

#define MAT_AT(m, i, j) ((m).data[(i)][(j)])
#define ROW(m, i) ((m).data[(i)])

// Basic
matrix_t matrix(int rows, int cols);
void free_matrix(matrix_t *rows);
void print_matrix(const matrix_t mat);
void print_row(matrix_t m, size_t i);
void print_col(matrix_t m, size_t j);
// fill random
void rand_matrix(matrix_t mat);
void fill_matrix(matrix_t mat, float v);
// mult
matrix_t multiply(matrix_t a, matrix_t b);
void multiply_into(matrix_t a, matrix_t b, matrix_t c);
// transpose
matrix_t transpose(matrix_t m);
// add
matrix_t add_scalar(matrix_t a, float b);
void add_into(matrix_t a, matrix_t b, matrix_t c);
// utils
float rand_float(void);
void set_zero(const matrix_t *mat);

#define ERROR(msg) fprintf(stderr, msg)

// error states
#define NULL_MATRIX matrix(0, 0)

#endif // MATRIX_H