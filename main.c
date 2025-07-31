#include "network.h"
#include <stdlib.h>

float train_in[] = {0, 0, 1, 0, 0, 1, 1, 1};
float train_expected[] = {1, 1, 1, 0};
int train_count = 4;

int main()
{
    int layer_sizes[] = {2, 2, 1, 1};

    meta_t nd = init_meta(
        layer_sizes, // layers
        4,
        1e-1,
        1e-3);
    network_t nw = init_network(&nd);

    data_t test_set = set_data(2, train_in, 1, train_expected, 4);

    train(&nw, test_set.inputs.data, test_set.outputs.data, test_set.train_count, 5);
    test_network(&nw, &test_set);
    // Clean up
    free_network(&nw);
    free_data(&test_set);
    return 0;
}