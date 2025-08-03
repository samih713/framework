#include "network.h"

void test_network(network_t *nw, const data_t *test_data)
{

    matrix_t *out = &nw->layers[nw->nd->n_layers - 1];
    matrix_t expected = test_data->outputs;
    matrix_t *in = &nw->layers[0];

    for (int i = 0; i < test_data->train_count; ++i)
    {
        set_inputs(nw, test_data->inputs.data[i]);
        forward(nw);

        printf("Set {%d}\n\n", i + 1);
        printf("[INPUT]\n");
        print_matrix(in);
        printf("[OUTPUT]\n");
        print_matrix(out);
        printf("[EXPECTED]\n");
        print_row(&expected, i);
        printf("----------------\n\n");
    }
}