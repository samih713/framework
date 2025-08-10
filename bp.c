#include "network.h"

static float sigmoid_prime(float a)
{
    return (1.0f - a) * a;
}

void set_output_delta(network_t nw, matrix_t expected)
{
    size_t n_deltas = nw.nd->n_params;
    size_t n_outputs = nw.nd->n_outputs;

    matrix_t output_delta = nw.deltas[n_deltas - 1];

    float a;
    float expected_output;
    for (size_t i = 0; i < n_outputs; ++i)
    {
        a = MAT_AT(OUTPUTS(nw), i, 0);
        expected_output = MAT_AT(expected, i, 0);
        MAT_AT(output_delta, i, 0) = (2.0f * (a - expected_output)) * sigmoid_prime(a);
    }
}

void set_hidden_deltas(network_t nw)
{
    size_t n_deltas = nw.nd->n_params - 1;

    for (size_t i = n_deltas; i > 0; --i)
    {
        matrix_t wnext = nw.weights[i + 1];
        matrix_t dnext = nw.deltas[i + 1];
        matrix_t dcur = nw.deltas[i];
        matrix_t acur = nw.layers[i + 1];

        for (size_t j = 0; j < dcur.rows; ++j)
        {
            MAT_AT(dcur, j, 0) = 0;
        }
        for (size_t j = 0; j < dnext.rows; ++j)
        {
            float v = MAT_AT(dnext, j, 0);
            for (size_t k = 0; k < dcur.rows; ++k)
            {
                MAT_AT(dcur, k, 0) += MAT_AT(wnext, j, k) * v;
            }
        }
        for (size_t c = 0; c < dcur.rows; ++c)
        {
            float a = MAT_AT(acur, c, 0);
            MAT_AT(dcur, c, 0) *= sigmoid_prime(a);
        }
    }
}