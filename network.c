#include "network.h"

void forward(network_t nw)
{
    matrix_t *weights = nw.weights;
    matrix_t *biases = nw.biases;
    matrix_t *layers = nw.layers;
    const int n_weights = nw.nd->n_params;

    for (int i = 0; i < n_weights; ++i)
    {
        multiply_into(weights[i], layers[i], layers[i + 1]);
        add_into(biases[i], layers[i + 1], layers[i + 1]);
        apply_activation(layers[i + 1], sigmoidf);
    }
}

void backward(network_t nw, data_t train)
{
    set_output_delta(nw, train.expected);
    set_hidden_deltas(nw);
    set_gradients(nw);
}

void train(network_t nw, data_t train, int rounds)
{
    for (int i = 0; i < rounds; ++i)
    {
       set_inputs(nw, train.inputs);
       forward(nw);
       backward(nw, train);
    }
}
