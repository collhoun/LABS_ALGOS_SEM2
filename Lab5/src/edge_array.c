#include "edge_array.h"

Edge *create_array(int size)
{
    Edge *vector = (Edge *)malloc(sizeof(Edge) * size);
    if (!vector)
        return NULL;
    return vector;
}
