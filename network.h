#ifndef NETWORK_H
#define NETWORK_H

#include "matrix.h"
#include <stdio.h>

typedef struct meta_s
{
    size_t n_inputs;
    size_t n_outputs;
    size_t n_layers;
    size_t n_params;
    float rate;
    size_t *layer_sizes;
} meta_t;

typedef struct network_s
{
    meta_t *nd;
    matrix_t *layers;
    matrix_t *weights;
    matrix_t *biases;
    // buffers
    matrix_t *deltas;
    matrix_t *w_gradients;
    matrix_t *b_gradients;
} network_t;

typedef struct data_s
{
    matrix_t inputs;
    matrix_t expected;
    int train_count;
} data_t;

#define INPUTS(nw) ((nw).layers[0])
#define OUTPUTS(nw) ((nw).layers[(nw).nd->n_layers - 1])

// nd
meta_t init_meta(size_t *layer_sizes, size_t n_layers, float rate);
// network
network_t init_network(meta_t *nd);
void forward(network_t nw);
void train(network_t nw, data_t train_data, size_t rounds);
void test_network(network_t nw, data_t test_data);
// data
data_t set_data(int input_size, float *inputs, int output_size, float *outputs, int train_count);
// bp
void set_output_delta(network_t nw, matrix_t expected);
void set_hidden_deltas(network_t nw);
// gradient
void set_gradients(network_t nw);
void apply_gradients(network_t nw);
// utils
void free_data(data_t *t);
void print_network(network_t nw);
void free_network(network_t *nw);
void set_inputs(network_t nw, float *input);
void print_inputs(network_t nw);
void print_outputs(network_t nw);
// activation
void apply_activation(matrix_t c, void (*activation)(float *));
void sigmoidf(float *y);
void relu(float *y);

#endif // NETWORK_H