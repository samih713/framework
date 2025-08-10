#include "network.h"

void print_network(network_t nw)
{
    size_t n_layers = nw.nd->n_layers;
    for (size_t i = 0; i < n_layers; ++i)
    {
        if (i == 0)
        {
            printf("[Inputs]\n");
        }
        else if (i == n_layers - 1)
        {
            printf("[Outputs]\n");
        }
        else
        {
            printf("[Hidden Layer %zu]\n", i - 1);
        }
        print_matrix(nw.layers[i]);
        if (i != n_layers - 1)
        {
            print_matrix(nw.weights[i]);
        }
        printf("----------------------------\n");
    }
}

void free_network(network_t *nw)
{
    size_t n_layers = nw->nd->n_layers;
    size_t n_params = nw->nd->n_params;

    // free layers
    for (size_t i = 0; i < n_layers; ++i)
    {
        free_matrix(&(nw->layers[i]));
    }
    free(nw->layers);
    nw->layers = NULL;
    // free params
    for (size_t i = 0; i < n_params; ++i)
    {
        free_matrix(&(nw->weights[i]));
        free_matrix(&(nw->w_gradients[i]));
        free_matrix(&(nw->biases[i]));
        free_matrix(&(nw->b_gradients[i]));
        free_matrix(&(nw->deltas[i]));
    }
    free(nw->weights);
    free(nw->w_gradients);
    free(nw->biases);
    free(nw->b_gradients);
    free(nw->deltas);
    nw->weights = NULL;
    nw->w_gradients = NULL;
    nw->biases = NULL;
    nw->b_gradients = NULL;
    nw->deltas = NULL;
}

void set_inputs(network_t nw, matrix_t input)
{
    for (size_t i = 0; i < nw.nd->n_inputs; ++i)
    {
        MAT_AT(INPUTS(nw), i, 0) = MAT_AT(input, i, 0);
    }
}

void print_inputs(network_t nw)
{
    print_matrix(INPUTS(nw));
}

void print_outputs(network_t nw)
{
    print_matrix(OUTPUTS(nw));
}
