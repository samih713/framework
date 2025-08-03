#include "network.h"
#include <stdlib.h>

// xor gate
// 3-input average
float train_in_avg3[]       = {
    0,0,0,  0,0,1,  0,1,0,  0,1,1,
    1,0,0,  1,0,1,  1,1,0,  1,1,1
};
float train_expected_avg3[] = {
    0.0f,  1.0f/3.0f,  1.0f/3.0f,  2.0f/3.0f,
    1.0f/3.0f,  2.0f/3.0f,  2.0f/3.0f,  1.0f
};
int train_count_avg3 = 8;

float test_in_avg3[] = {
    0.0f, 0.0f, 0.0f,   // avg = 0.0
    1.0f, 1.0f, 1.0f,   // avg = 1.0
    0.5f, 0.5f, 0.5f,   // avg = 0.5
    0.2f, 0.8f, 0.0f,   // avg ≈ 0.333333
    1.0f, 0.5f, 0.5f,   // avg ≈ 0.666667
    0.1f, 0.2f, 0.3f,   // avg = 0.2
    0.9f, 0.9f, 0.1f,   // avg ≈ 0.633333
    0.33f, 0.33f, 0.34f,// avg ≈ 0.333333
    0.7f, 0.2f, 0.1f,   // avg ≈ 0.333333
    0.25f, 0.75f, 0.5f, // avg = 0.5
    0.9f, 0.1f, 0.0f,   // avg ≈ 0.333333
    0.123f, 0.456f, 0.789f, // avg = (0.123+0.456+0.789)/3 = 0.456
    0.33f, 0.66f, 0.99f // avg = (0.33+0.66+0.99)/3 = 0.66
};
float test_expected_avg3[] = {
    0.0f,
    1.0f,
    0.5f,
    0.333333f,
    0.666667f,
    0.2f,
    0.633333f,
    0.333333f,
    0.333333f,
    0.5f,
    0.333333f,
    0.456000f,
    0.660000f
};
int test_count_avg3 = 13;


int main()
{
    float rate = 10e-1;
    float eps = 1e-1;
    int train_iter = 50000;
    int input_size = 3;
    int output_size = 1;

    int layer_sizes[] = {input_size, 3, 2, 3, output_size};
    int n_layers = sizeof(layer_sizes) / sizeof(layer_sizes[0]);


    // init
    srand(time(0));
    meta_t nd = init_meta(
        layer_sizes,
        n_layers,
        rate,
        eps);
    network_t nw = init_network(&nd);

    data_t train_set = set_data(3, train_in_avg3, 1, train_expected_avg3, train_count_avg3);
    data_t test_set = set_data(3, test_in_avg3, 1, test_expected_avg3, test_count_avg3);

    // 
    train(&nw, train_set.inputs.data, train_set.outputs.data, train_count_avg3, train_iter);

    // test network
    test_network(&nw, &test_set);
    // Clean up
    free_network(&nw);
    free_data(&test_set);
    free_data(&train_set);
    return 0;
}