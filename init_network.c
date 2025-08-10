#include "network.h"

static void init_layers(network_t *nw);
static void init_params(network_t *nw);
static void init_buffers(network_t *nw);

network_t init_network(meta_t *nd)
{
    network_t nw;
    nw.nd = nd;

    init_layers(&nw);
    init_params(&nw);
    init_buffers(&nw); 
    return nw;
}

static void init_layers(network_t *nw)
{
    size_t n_layers = nw->nd->n_layers;
    size_t *layer_sizes = nw->nd->layer_sizes;

    nw->layers = malloc(sizeof(matrix_t) * n_layers);
    for (size_t i = 0; i < n_layers; ++i)
    {
        nw->layers[i] = matrix(layer_sizes[i], 1);
    }
}

static void init_params(network_t *nw)
{
    size_t n_params = nw->nd->n_params;
    size_t cols;
    size_t rows;

    nw->weights = malloc(sizeof(matrix_t) * n_params);
    nw->biases = malloc(sizeof(matrix_t) * n_params);
    for (size_t i = 0; i < n_params; ++i)
    {
        rows = nw->nd->layer_sizes[i + 1];
        cols = nw->nd->layer_sizes[i];

        nw->weights[i] = matrix(rows, cols);
        rand_matrix(nw->weights[i]);
        nw->biases[i] = matrix(rows, 1);
        rand_matrix(nw->biases[i]);
    }
}

static void init_buffers(network_t *nw)
{
    size_t n_params = nw->nd->n_params;
    size_t cols;
    size_t rows;

    nw->deltas = malloc(sizeof(matrix_t) * n_params);
    nw->w_gradients = malloc(sizeof(matrix_t) * n_params);
    nw->b_gradients = malloc(sizeof(matrix_t) * n_params);
    for (size_t i = 0; i < n_params; ++i)
    {
        rows = nw->nd->layer_sizes[i + 1];
        cols = nw->nd->layer_sizes[i];

        nw->w_gradients[i] = matrix(rows, cols);
        nw->b_gradients[i] = matrix(rows, 1);
        nw->deltas[i] = matrix(rows, 1);
    }
}
