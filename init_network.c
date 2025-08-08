#include "network.h"

static void init_layers(const meta_t *nd, matrix_t *layers);
static void init_weights(const meta_t *nd, matrix_t *weights);
static void init_weight_gradients(const meta_t *nd, matrix_t *gradients);
static void init_biases(const meta_t *nd, matrix_t *biases);
static void init_deltas(const meta_t *nd, matrix_t *deltas);
static void init_bias_gradients(const meta_t *nd, matrix_t *b_gradients);

network_t init_network(meta_t *nd)
{
    network_t nw; 
    nw.nd = nd;

    // layers
    nw.layers = malloc(sizeof(matrix_t) * nd->n_layers);
    init_layers(nw.nd, nw.layers);
    // weights
    nw.weights = malloc(sizeof(matrix_t) * nd->n_weights);
    init_weights(nw.nd, nw.weights);
    // w_gradients
    nw.w_gradients = malloc(sizeof(matrix_t) * nd->n_weights);
    init_weight_gradients(nw.nd, nw.w_gradients);
    // biases
    nw.biases = malloc(sizeof(matrix_t) * nd->n_biases);
    init_biases(nw.nd, nw.biases);
    // deltas
    nw.deltas = malloc(sizeof(matrix_t) * nd->n_layers);
    init_deltas(nw.nd, nw.deltas);
    // b_gradients
    nw.b_gradients = malloc(sizeof(matrix_t) * nd->n_biases);
    init_bias_gradients(nw.nd, nw.b_gradients);
    return nw;
}

static void init_layers(const meta_t *nd, matrix_t *layers)
{
    for (int i = 0; i < nd->n_layers; ++i)
    {
        layers[i] = matrix(nd->layer_sizes[i], 1);
    }
}



static void init_weights(const meta_t *nd, matrix_t *weights)
{
    int n_weights = nd->n_weights;

    for (int i = 0; i < n_weights; ++i)
    {
        weights[i] = matrix(nd->layer_sizes[i + 1], nd->layer_sizes[i]);
        rand_matrix(&(weights[i]));
    }
}

static void init_weight_gradients(const meta_t *nd, matrix_t *w_gradients)
{
    int n_weights = nd->n_weights;

    for (int i = 0; i < n_weights; ++i)
    {
        w_gradients[i] = matrix(nd->layer_sizes[i + 1], nd->layer_sizes[i]);
    }
}

static void init_biases(const meta_t *nd, matrix_t *biases)
{
    int n_biases = nd->n_biases;

    for (int i = 0; i < n_biases; ++i)
    {
        biases[i] = matrix(nd->layer_sizes[i + 1], 1);
        rand_matrix(&(biases[i]));
    }
}

static void init_deltas(const meta_t *nd, matrix_t *deltas)
{
    size_t n_deltas = nd->n_biases;

    for (size_t i = 0; i < n_deltas; ++i)
    {
        deltas[i] = matrix(nd->layer_sizes[i + 1], 1);
    }
}

static void init_bias_gradients(const meta_t *nd, matrix_t *b_gradients)
{
    int n_biases = nd->n_biases;

    for (int i = 0; i < n_biases; ++i)
    {
        b_gradients[i] = matrix(nd->layer_sizes[i + 1], 1);
    }
}