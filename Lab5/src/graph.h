#ifndef GRAPH_H
#define GRAPH_H

#include "edge_array.h"

int **create_matrix(int size, int num_edges, Edge *edges);
void print_matrix(int size, int **matrix);
void free_matrix(int **matrix, int size);
int **FloydWarshall(int size, int **matrix);
int is_cycled(int **matrix, int size);
#endif