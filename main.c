#include "network.h"
#include <stdlib.h>

// xor gate
// 5 inputs per sample, 1 output (0/1)
float train_in_spam[40 * 5] = {
    // caps, links, free, excl, repInv
    0.05f, 0.00f, 0.0f, 0.01f, 0.10f,  // 0 ham
    0.60f, 0.80f, 1.0f, 0.70f, 0.90f,  // 1 spam
    0.10f, 0.05f, 0.0f, 0.02f, 0.20f,  // 2 ham
    0.40f, 0.70f, 1.0f, 0.60f, 0.85f,  // 3 spam
    0.15f, 0.10f, 0.0f, 0.05f, 0.25f,  // 4 ham
    0.30f, 0.65f, 0.0f, 0.50f, 0.80f,  // 5 spam
    0.08f, 0.02f, 0.0f, 0.01f, 0.15f,  // 6 ham
    0.55f, 0.40f, 1.0f, 0.35f, 0.75f,  // 7 spam
    0.12f, 0.08f, 0.0f, 0.03f, 0.18f,  // 8 ham
    0.50f, 0.55f, 0.0f, 0.60f, 0.88f,  // 9 spam
    0.07f, 0.01f, 0.0f, 0.00f, 0.12f,  // 10 ham
    0.35f, 0.30f, 1.0f, 0.25f, 0.70f,  // 11 spam
    0.18f, 0.06f, 0.0f, 0.02f, 0.22f,  // 12 ham
    0.62f, 0.20f, 1.0f, 0.55f, 0.65f,  // 13 spam
    0.09f, 0.03f, 0.0f, 0.01f, 0.14f,  // 14 ham
    0.48f, 0.75f, 0.0f, 0.70f, 0.92f,  // 15 spam
    0.11f, 0.04f, 0.0f, 0.02f, 0.17f,  // 16 ham
    0.70f, 0.35f, 1.0f, 0.40f, 0.78f,  // 17 spam
    0.13f, 0.09f, 0.0f, 0.03f, 0.21f,  // 18 ham
    0.58f, 0.62f, 0.0f, 0.55f, 0.86f,  // 19 spam
    0.06f, 0.00f, 0.0f, 0.00f, 0.10f,  // 20 ham
    0.33f, 0.28f, 1.0f, 0.22f, 0.68f,  // 21 spam
    0.20f, 0.07f, 0.0f, 0.03f, 0.26f,  // 22 ham
    0.57f, 0.18f, 1.0f, 0.45f, 0.72f,  // 23 spam
    0.16f, 0.05f, 0.0f, 0.02f, 0.23f,  // 24 ham
    0.46f, 0.68f, 0.0f, 0.63f, 0.90f,  // 25 spam
    0.14f, 0.04f, 0.0f, 0.01f, 0.19f,  // 26 ham
    0.65f, 0.33f, 1.0f, 0.38f, 0.77f,  // 27 spam
    0.17f, 0.09f, 0.0f, 0.04f, 0.24f,  // 28 ham
    0.52f, 0.58f, 0.0f, 0.57f, 0.87f,  // 29 spam
    0.10f, 0.02f, 0.0f, 0.01f, 0.16f,  // 30 ham
    0.38f, 0.25f, 1.0f, 0.20f, 0.66f,  // 31 spam
    0.19f, 0.06f, 0.0f, 0.02f, 0.27f,  // 32 ham
    0.60f, 0.22f, 1.0f, 0.42f, 0.73f,  // 33 spam
    0.15f, 0.05f, 0.0f, 0.02f, 0.22f,  // 34 ham
    0.44f, 0.72f, 0.0f, 0.66f, 0.91f,  // 35 spam
    0.12f, 0.03f, 0.0f, 0.01f, 0.18f,  // 36 ham
    0.68f, 0.31f, 1.0f, 0.37f, 0.76f,  // 37 spam
    0.21f, 0.08f, 0.0f, 0.03f, 0.28f,  // 38 ham
    0.54f, 0.60f, 0.0f, 0.58f, 0.89f   // 39 spam
};

float train_expected_spam[40] = {
    0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
    0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
    0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
    0, 1, 0, 1, 0, 1, 0, 1, 0, 1
};
int train_count_spam = 40;

float test_in_spam[20 * 5] = {
    0.04f, 0.01f, 0.0f, 0.00f, 0.11f,  // ham
    0.61f, 0.79f, 1.0f, 0.72f, 0.93f,  // spam
    0.22f, 0.12f, 0.0f, 0.06f, 0.30f,  // ham
    0.47f, 0.66f, 0.0f, 0.62f, 0.89f,  // spam
    0.09f, 0.02f, 0.0f, 0.01f, 0.13f,  // ham
    0.36f, 0.29f, 1.0f, 0.24f, 0.69f,  // spam
    0.18f, 0.07f, 0.0f, 0.03f, 0.25f,  // ham
    0.63f, 0.21f, 1.0f, 0.43f, 0.74f,  // spam
    0.16f, 0.05f, 0.0f, 0.02f, 0.22f,  // ham
    0.45f, 0.71f, 0.0f, 0.65f, 0.90f,  // spam
    0.07f, 0.01f, 0.0f, 0.00f, 0.12f,  // ham
    0.69f, 0.34f, 1.0f, 0.39f, 0.77f,  // spam
    0.20f, 0.09f, 0.0f, 0.04f, 0.27f,  // ham
    0.53f, 0.57f, 0.0f, 0.56f, 0.88f,  // spam
    0.11f, 0.03f, 0.0f, 0.01f, 0.16f,  // ham
    0.39f, 0.26f, 1.0f, 0.21f, 0.67f,  // spam
    0.23f, 0.10f, 0.0f, 0.05f, 0.31f,  // ham
    0.59f, 0.23f, 1.0f, 0.41f, 0.73f,  // spam
    0.14f, 0.04f, 0.0f, 0.01f, 0.19f,  // ham
    0.43f, 0.73f, 0.0f, 0.67f, 0.91f   // spam
};

float test_expected_spam[20] = {
    0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
    0, 1, 0, 1, 0, 1, 0, 1, 0, 1
};
int test_count_spam = 20;



#if 1
int main()
{
    float rate = 10e-1;
    size_t train_iter = 500;
    size_t input_size = 5;
    size_t output_size = 1;

    // y-output = mx + c, y-actual, c=(y-output - y-actual)**2 // x**2, 2x
    size_t layer_sizes[] = {input_size, 5, 5, output_size};
    size_t n_layers = sizeof(layer_sizes) / sizeof(layer_sizes[0]);


    // init
    srand(time(0));
    meta_t nd = init_meta(
        layer_sizes,
        n_layers,
        rate);
    network_t nw = init_network(&nd);

    data_t train_set = set_data(input_size, train_in_spam, output_size, train_expected_spam, train_count_spam);
    data_t test_set = set_data(input_size, test_in_spam, output_size, test_expected_spam, test_count_spam);

    // 
    train(nw, train_set, train_iter);

    // test network
    test_network(nw, test_set);
    // Clean up
    free_network(&nw);
    free_data(&test_set);
    free_data(&train_set);
    return 0;
}
#endif

#if 0 // unit test
int main() {
    float rate = 10e-1;
    // size_t train_iter = 5;
    size_t input_size = 3;
    size_t output_size = 1;

    size_t layer_sizes[] = {input_size, 3, 2, 3, output_size};
    size_t n_layers = sizeof(layer_sizes) / sizeof(layer_sizes[0]);


    // init
    srand(time(0));
    meta_t nd = init_meta(
        layer_sizes,
        n_layers,
        rate);
    network_t nw = init_network(&nd);
    data_t t = set_data(3, test_in_avg3, 1, test_expected_avg3, test_count_avg3);
    set_inputs(nw, ROW(t.inputs, 2));
    print_matrix(t.inputs);
    print_row(t.inputs, 2);
    print_matrix(INPUTS(nw));

    free_data(&t);
    free_network(&nw);
}
#endif 


#include <immintrin.h>
#if 0
int main() {
    // a
    matrix_t a = matrix(2, 2);
    fill_matrix(a, 1);
    // b
    matrix_t b = matrix(2, 2);
    fill_matrix(b, 1);
    
    
    // check the matrices
    print_matrix(a);
    print_matrix(b);
}
#endif // 