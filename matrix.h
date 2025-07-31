#ifndef MATRIX_H
#define MATRIX_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

typedef struct matrix_s
{
    float **data;
    int m;
    int n;
} matrix_t;

// Basic
matrix_t matrix(int m, int n);
void free_matrix(matrix_t *m);
void print_matrix(const matrix_t *mat);
// fill random
void rand_matrix(matrix_t *mat);
// mult
matrix_t multiply(const matrix_t *a, const matrix_t *b);
void multiply_into(const matrix_t *a, const matrix_t *b, matrix_t *c);
// add
matrix_t add_scalar(const matrix_t *a, float b);
void add_into(const matrix_t *a, const matrix_t *b, matrix_t *c);
// utils
float rand_float(void);
void set_zero(const matrix_t *mat);

#define ERROR(msg) fprintf(stderr, msg)

// error states
#define NULL_MATRIX matrix(0, 0)

#endif // MATRIX_H