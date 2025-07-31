#include "network.h"

void print_network(const network_t *nw)
{
    const int n_layers = nw->nd->n_layers;
    for (int i = 0; i < n_layers; ++i)
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
            printf("[Hidden Layer %d]\n", i - 1);
        }
        print_matrix(&(nw->layers[i]));
        if (i != n_layers - 1)
        {
            print_matrix(&(nw->weights[i]));
        }
        printf("----------------------------\n");
    }
}

void free_network(network_t *nw)
{
    int n_layers = nw->nd->n_layers;
    int n_weights = nw->nd->n_weights;
    int n_biases = nw->nd->n_biases;

    // free layers
    for (int i = 0; i < n_layers; ++i)
    {
        free_matrix(&(nw->layers[i]));
    }
    free(nw->layers);
    nw->layers = NULL;
    // free weights
    for (int i = 0; i < n_weights; ++i)
    {
        free_matrix(&(nw->weights[i]));
    }
    free(nw->weights);
    nw->weights = NULL;
    // free w_gradients
    for (int i = 0; i < n_weights; ++i)
    {
        free_matrix(&(nw->w_gradients[i]));
    }
    free(nw->w_gradients);
    nw->w_gradients = NULL;
    // free biases
    for (int i = 0; i < n_biases; ++i)
    {
        free_matrix(&(nw->biases[i]));
    }
    free(nw->biases);
    nw->biases = NULL;
    // free biases
    for (int i = 0; i < n_biases; ++i)
    {
        free_matrix(&(nw->b_gradients[i]));
    }
    free(nw->b_gradients);
    nw->b_gradients = NULL;
}

void set_inputs(network_t *nw, float *inputs_values)
{
    matrix_t inputs = nw->layers[0];
    int n_inputs = nw->nd->n_inputs;

    for (int i = 0; i < n_inputs; ++i)
    {
        inputs.data[0][i] = inputs_values[i];
    }
}

void print_outputs(network_t *nw)
{
    matrix_t outputs = nw->layers[nw->nd->n_layers - 1];
    print_matrix(&outputs);
}

void free_data(data_t *t)
{
    free_matrix(&(t->inputs));
    free_matrix(&(t->outputs));
}