#include "network.h"

void free_data(data_t *t)
{
    free_matrix(&(t->inputs));
    free_matrix(&(t->expected));
}