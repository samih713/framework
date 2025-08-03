#include <math.h>
#include "network.h"

void apply_activation(matrix_t *c, void (*activation)(float *))
{
    for (int i = 0; i < c->rows; ++i)
    {
        for (int j = 0; j < c->cols; ++j)
        {
            activation(&(c->data[i][j]));
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