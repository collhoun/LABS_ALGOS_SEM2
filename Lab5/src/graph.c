#include "edge_array.h"

// наверное тут стоило выделить память для одномерного массива
int **create_matrix(int size, int num_edges, Edge *edges)
{
    int **matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        matrix[i] = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < num_edges; i++)
    {
        matrix[edges[i].src][edges[i].dest] = edges[i].weight;
    }
    return matrix;
}

void print_matrix(int size, int **matrix)
{
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int **FloydWarshall(int size, int **matrix)
{
    const int INT_MAX = 2147483647;
    int **dist = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        dist[i] = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++)
        {
            if (matrix[i][j] != 0)
                dist[i][j] = matrix[i][j];
            else if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INT_MAX;
        }
    }

    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    return dist;
}
int is_negative_cycle(int size, int **dist)
{
    for (int i = 0; i < size; i++)
    {
        if (dist[i][i] < 0)
            return 1;
    }
    return 0;
}