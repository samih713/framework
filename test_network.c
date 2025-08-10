#include "network.h"

void test_network(network_t nw, data_t test)
{
    for (int i = 0; i < test.train_count; ++i)
    {
        set_inputs(nw, ROW(test.inputs, i));
        forward(nw);

        printf("Set {%d}\n\n", i + 1);
        printf("[INPUT]\n");
        print_inputs(nw);
        printf("[OUTPUT]\n");
        print_outputs(nw);
        printf("[EXPECTED]\n");
        print_row(test.expected, i);
        printf("----------------\n\n");
    }
}