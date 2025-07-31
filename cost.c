#include "network.h"

static float get_sqerror(float *outputs, float *expected, int n_outputs);


float get_cost(network_t *nw, float **inputs, float **expected, int train_count)
{
    matrix_t *output = &(nw->layers[nw->nd->n_layers - 1]);
    int n_outputs = nw->nd->n_outputs;

    float cost = 0;
    for (int i = 0; i < train_count; ++i)
    {
        set_inputs(nw, inputs[i]);
        forward(nw);
        cost += get_sqerror(output->data[0], expected[i], n_outputs);
    }
    return (cost / (float)train_count);
}

static float get_sqerror(float *outputs, float *expected, int n_outputs)
{
    float d;
    float total = 0;

    for (int i = 0; i < n_outputs; ++i)
    {
        d = expected[i] - outputs[i];
        total += d * d;
    }

    return total;
}