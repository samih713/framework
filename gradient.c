#include "network.h"

void set_weight_gradients(network_t *nw, float **inputs, float **expected, int train_count)
{
    float cost;
    float original_w;
    float *current_w;
    int current_size;

    float eps = nw->nd->eps;
    matrix_t *w_gradients = nw->w_gradients;
    matrix_t *weights = nw->weights;
    int n_weights = nw->nd->n_weights;

    for (int i = 0; i < n_weights; ++i)
    {
        current_size = w_gradients[i].rows * w_gradients[i].cols;
        cost = get_cost(nw, inputs, expected, train_count);
        for (int j = 0; j < current_size; ++j)
        {
            current_w = &(weights[i].data[0][j]);
            original_w = *current_w;
            // wiggle the weight
            *current_w += eps;
            // set the gradient
            w_gradients[i].data[0][j] = (get_cost(nw, inputs, expected, train_count) - cost) / eps;
            // restore weight
            *current_w = original_w;
        }
    }
}

void set_bais_gradients(network_t *nw, float **inputs, float **expected, int train_count)
{

    float cost;
    float original_b;
    float *current_b;
    int current_size;

    float eps = nw->nd->eps;
    matrix_t *b_gradients = nw->b_gradients;
    matrix_t *biases = nw->biases;
    int n_biases = nw->nd->n_biases;

    // set each element in the gradient matrices
    for (int i = 0; i < n_biases; ++i)
    {
        current_size = b_gradients[i].rows * b_gradients[i].cols;
        cost = get_cost(nw, inputs, expected, train_count);
        for (int j = 0; j < current_size; ++j)
        {
            current_b = &(biases[i].data[0][j]);
            original_b = *current_b;
            // wiggle the weight
            *current_b += eps;
            // set the gradient
            b_gradients[i].data[0][j] = (get_cost(nw, inputs, expected, train_count) - cost) / eps;
            // restore weight
            *current_b = original_b;
        }
    }
}

void apply_weight_gradients(network_t *nw)
{
    float rate = nw->nd->rate;

    matrix_t *w_gradients = nw->w_gradients;
    matrix_t *weights = nw->weights;

    int n_weights = nw->nd->n_weights;
    int current_size = 0;
    for (int i = 0; i < n_weights; ++i)
    {
        current_size = weights[i].rows * weights[i].cols;
        for (int j = 0; j < current_size; ++j)
        {
            weights[i].data[0][j] -= (w_gradients[i].data[0][j] * rate);
        }
    }
}

void apply_bias_gradients(network_t *nw)
{
    float rate = nw->nd->rate;

    matrix_t *b_gradients = nw->b_gradients;
    matrix_t *biases = nw->biases;

    int n_biases = nw->nd->n_biases;
    int current_size = 0;
    for (int i = 0; i < n_biases; ++i)
    {
        current_size = biases[i].rows * biases[i].cols;
        for (int j = 0; j < current_size; ++j)
        {
            biases[i].data[0][j] -= b_gradients[i].data[0][j] * rate;
        }
    }
}