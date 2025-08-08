#include "network.h"

void forward(network_t *nw)
{
    matrix_t *weights = nw->weights;
    matrix_t *biases = nw->biases;
    matrix_t *layers = nw->layers;
    const int n_weights = nw->nd->n_weights;

    for (int i = 0; i < n_weights; ++i)
    {
        multiply_into(&weights[i], &layers[i], &layers[i + 1]);
        add_into(&biases[i], &layers[i + 1], &layers[i + 1]);
        apply_activation(&layers[i + 1], sigmoidf);
    }
}

void train(network_t *nw, float **inputs, float **expected, int train_count, int rounds)
{
    for (int i = 0; i < rounds; ++i)
    {
        compute_output_delta(nw, expected);
        set_weight_gradients(nw, inputs, expected, train_count);
        set_bais_gradients(nw, inputs, expected, train_count);
        apply_weight_gradients(nw);
        apply_bias_gradients(nw);
    }
}
