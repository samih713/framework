#include <math.h>
#include "network.h"

void apply_activation(matrix_t c, void (*activation)(float *))
{
    for (size_t i = 0; i < c.rows; ++i)
    {
        for (size_t j = 0; j < c.cols; ++j)
        {
            activation(&(MAT_AT(c, i, j)));
        }
    }
}

// activation functions
void sigmoidf(float *y)
{
    *y = (1.0f / (1.0f + expf(-*y)));
}

void relu(float *y)
{
    if (*y < 0)
        *y = 0;
}