#include "network.h"

data_t set_data(int input_size, float *inputs, int output_size, float *outputs, int train_count)
{
    data_t sample;
    sample.inputs = matrix(train_count, input_size);
    sample.expected = matrix(train_count, output_size);
    sample.train_count = train_count;
    // set inputs
    for (int i = 0; i < train_count; ++i)
    {
        for (int j = 0; j < input_size; ++j)
        {
            sample.inputs.data[i][j] = inputs[(i * input_size) + j];
        }
    }
    // set outputs
    for (int i = 0; i < train_count; ++i)
    {
        for (int j = 0; j < output_size; ++j)
        {
            sample.expected.data[i][j] = outputs[(i * output_size) + j];
        }
    }
    return sample;
}