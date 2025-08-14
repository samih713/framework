#include "network.h"

void set_gradients(network_t nw)
{
    // Compute gradients only: w_gradients = delta * a_prev^T ; b_gradients = delta
    size_t n_params = nw.nd->n_params;
    for (size_t i = 0; i < n_params; ++i)
    {
        matrix_t w_grad = nw.w_gradients[i];
        matrix_t b_grad = nw.b_gradients[i];
        matrix_t delta = nw.deltas[i];
        matrix_t a_prev = nw.layers[i];

        for (size_t j = 0; j < w_grad.rows; ++j)
        {
            float d = MAT_AT(delta, j, 0);
            MAT_AT(b_grad, j, 0) = d; // bias gradient
            for (size_t k = 0; k < w_grad.cols; ++k)
            {
                MAT_AT(w_grad, j, k) = d * MAT_AT(a_prev, k, 0);
            }
        }
    }
}

void apply_gradients(network_t nw)
{
    // Apply gradient descent update: W -= rate * dW ; b -= rate * db
    size_t n_params = nw.nd->n_params;
    float rate = nw.nd->rate;
    for (size_t i = 0; i < n_params; ++i)
    {
        matrix_t w = nw.weights[i];
        matrix_t b = nw.biases[i];
        matrix_t w_grad = nw.w_gradients[i];
        matrix_t b_grad = nw.b_gradients[i];
        for (size_t r = 0; r < w.rows; ++r)
        {
            // bias update
            MAT_AT(b, r, 0) -= rate * MAT_AT(b_grad, r, 0);
            for (size_t c = 0; c < w.cols; ++c)
            {
                MAT_AT(w, r, c) -= rate * MAT_AT(w_grad, r, c);
            }
        }
    }
}
