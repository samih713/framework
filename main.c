#include "network.h"
#include <stdlib.h>

// or gate
float train_in[] = {0, 0, 1, 0, 0, 1, 1, 1};
float train_expected[] = {0, 1, 1, 1};
int train_count = 4;

int main()
{
    int layer_sizes[] = {2, 2, 1, 1};
    int n_layers = sizeof(layer_sizes) / sizeof(layer_sizes[0]);
    float rate = 1e-1;
    float eps = 1e-1;
    int train_iter = 50000;


    // init
    srand(time(0));
    meta_t nd = init_meta(
        layer_sizes,
        n_layers,
        rate,
        eps);
    network_t nw = init_network(&nd);
    data_t t_set = set_data(2, train_in, 1, train_expected, train_count);

    // 
    train(&nw, t_set.inputs.data, t_set.outputs.data, t_set.train_count, train_iter);

    // test network
    test_network(&nw, &t_set);
    // Clean up
    free_network(&nw);
    free_data(&t_set);
    return 0;
}