#ifndef EDGE_ARRAY_H
#define EDGE_ARRAY_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Edge
{
    int src;
    int dest;
    int weight;

} Edge;

Edge *create_array(int size);
#endif