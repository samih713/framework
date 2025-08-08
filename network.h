#ifndef NETWORK_H
#define NETWORK_H

#include "matrix.h"
#include <stdio.h>

typedef struct meta_s
{
    int n_inputs;
    int n_outputs;
    int n_layers;
    int n_weights;
    int n_biases;
    float rate;
    float eps;
    int *layer_sizes;
} meta_t;

typedef struct network_s
{
    meta_t *nd;
    matrix_t *deltas;
    matrix_t *layers;
    matrix_t *weights;
    matrix_t *w_gradients;
    matrix_t *biases;
    matrix_t *b_gradients;
} network_t;

typedef struct data_s
{
    matrix_t inputs;
    matrix_t outputs;
    int train_count;
} data_t;

// nd
meta_t init_meta(int *layer_sizes, int n_layers, float rate, float eps);
// network
network_t init_network(meta_t *nd);
void forward(network_t *nw);
void train(network_t *nw, float **inputs, float **expected, int train_count, int rounds);
void test_network(network_t *nw, const data_t *test_data);
// data
data_t set_data(int input_size, float *inputs, int output_size, float *outputs, int train_count);
// cost
float get_cost(network_t *nw, float **inputs, float **expected, int train_count);
// bp
void compute_output_delta(network_t *nw, float **expected);
// gradient
void set_weight_gradients(network_t *nw, float **inputs, float **expected, int train_count);
void set_bais_gradients(network_t *nw, float **inputs, float **expected, int train_count);
void apply_weight_gradients(network_t *nw);
void apply_bias_gradients(network_t *nw);
// utils
void free_data(data_t *t);
void print_network(const network_t *nw);
void free_network(network_t *nw);
void set_inputs(network_t *nw, float *inputs_values);
void print_outputs(network_t *nw);
// activation
void apply_activation(matrix_t *c, void (*activation)(float *));
void sigmoidf(float *y);
void relu(float *y);

#endif // NETWORK_H