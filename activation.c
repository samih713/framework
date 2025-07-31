#include <math.h>
#include "network.h"

void apply_activation(matrix_t *c, void (*activation)(float *))
{
    for (int i = 0; i < c->m; ++i)
    {
        for (int j = 0; j < c->n; ++j)
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