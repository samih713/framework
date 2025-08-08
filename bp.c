#include "network.h"

static float sigmoid_prime(float a) {
    return (1.0f - a) * a;
}

void compute_output_delta(network_t *nw, float **expected) {
    size_t n_deltas = nw->nd->n_biases;
    size_t n_outputs = nw->nd->n_outputs;
    size_t n_layers = nw->nd->n_layers;

    matrix_t output_delta = nw->deltas[n_deltas - 1];
    matrix_t output_layer = nw->layers[n_layers - 1];

    // output delta
    float a;
    float expected_output;
    for (size_t i = 0; i < n_outputs; ++i) {
        a = output_layer.data[0][i];
        expected_output = expected[0][i];
        output_delta.data[0][i] = (2.0f * (a - expected_output)) * sigmoid_prime(a);
    }
    printf("------------\n");
    print_matrix(&(nw->deltas[n_deltas - 1]));
    printf("------------\n");
}

void compute_hidden_deltas(network_t *nw, float **expected) {
    size_t n_deltas = nw->nd->n_biases;
    size_t n_outputs = nw->nd->n_outputs;
    size_t n_layers = nw->nd->n_layers;
}