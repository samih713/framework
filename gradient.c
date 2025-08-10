#include "network.h"

void set_gradients(network_t nw)
{
    size_t n_params = nw.nd->n_params;
    float rate = nw.nd->rate;

    for (size_t i = 0; i < n_params; ++i)
    {
        matrix_t w_gradients = nw.w_gradients[i];
        matrix_t b_gradients = nw.b_gradients[i];
        matrix_t delta = nw.deltas[i];
        matrix_t aprev = nw.layers[i];

        for (size_t j = 0; j < w_gradients.rows; ++j) {
            float d = MAT_AT(delta, j, 0);
            MAT_AT(b_gradients, j, 0) = d * rate;
            for (size_t k = 0; k < w_gradients.cols; ++k) {
                MAT_AT(w_gradients, j, k) = d * MAT_AT(aprev, k, 0);
            }
        }
    }
}
