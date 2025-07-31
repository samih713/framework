#include "network.h"

meta_t init_meta(int *layer_sizes, int n_layers, float rate, float eps)
{
    meta_t nd;

    // set parameters
    nd.n_inputs = layer_sizes[0];
    nd.n_outputs = layer_sizes[n_layers - 1];
    nd.n_layers = n_layers;
    nd.n_weights = n_layers - 1;
    nd.n_biases = n_layers - 1;
    nd.rate = rate;
    nd.eps = eps;

    // set layer sizes
    nd.layer_sizes = layer_sizes;
    
    return nd;
}