#include "network.h"

void forward(network_t nw)
{
    matrix_t *weights = nw.weights;
    matrix_t *biases = nw.biases;
    matrix_t *layers = nw.layers;
    const int n_weights = nw.nd->n_params;

    for (int i = 0; i < n_weights; ++i)
    {
        multiply_into(weights[i], layers[i], layers[i + 1]);
        add_into(biases[i], layers[i + 1], layers[i + 1]);
        apply_activation(layers[i + 1], sigmoidf);
    }
}

void backward(network_t nw, matrix_t expected_row)
{
    // expected_row is a (n_outputs x 1) matrix view; reuse buffer: temporarily overwrite OUTPUTS? Instead build a temp target matrix.
    // Simpler: create a small stack matrix_t pointing to expected_row data not allocated; but current helpers allocate.
    // We'll adapt set_output_delta signature in-place by passing a matrix with expected outputs per neuron.
    set_output_delta(nw, expected_row);
    set_hidden_deltas(nw);
    set_gradients(nw);
    apply_gradients(nw);
}

void train(network_t nw, data_t train, size_t rounds)
{
    // Expected layout: train.inputs: (train_count x n_inputs)
    //                   train.expected: (train_count x n_outputs)
    for (size_t epoch = 0; epoch < rounds; ++epoch)
    {
        for (int sample = 0; sample < train.train_count; ++sample)
        {
            set_inputs(nw, ROW(train.inputs, sample));
            forward(nw);
            // Build a temporary expected matrix view with shape (n_outputs x 1)
            matrix_t expected_row;
            expected_row.rows = nw.nd->n_outputs;
            expected_row.cols = 1;
            expected_row.data = malloc(sizeof(float*) * expected_row.rows);
            for (size_t r = 0; r < expected_row.rows; ++r) {
                expected_row.data[r] = &train.expected.data[sample][r];
            }
            backward(nw, expected_row);
            free(expected_row.data); // only free pointer array, not underlying floats
        }
    }
}
