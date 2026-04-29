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
int dfs_recursive(int v, int veritates_number, int *visited, int **matrix)
{
    // возвращает 1 если есть циклы в графе, 0 иначе
    visited[v] = 1;
    for (int i = 0; i < veritates_number; i++)
    {
        if (matrix[v][i] != 0)
        {
            if (visited[i])
                return 1;
            if (!visited[i] && dfs_recursive(i, veritates_number, visited, matrix))
                return 1;
        }
    }
    visited[v] = 2;
    return 0;
}

void dfs(int **matrix, int veritates_number)
{
    int *visited = (int *)malloc(sizeof(int) * veritates_number);
    for (int i = 0; i < veritates_number; i++)
    {
        visited[i] = 0;
    }
    for (int i = 0; i < veritates_number; i++)
    {
        if (!visited[i])
        {
            dfs_recursive(i, veritates_number, visited, matrix);
        }
    }

    free(visited);
}

int is_cycled(int **matrix, int veritates_number)
{
    if (!matrix || veritates_number <= 0)
        return 0;
    int *visited = (int *)malloc(sizeof(int) * veritates_number);
    for (int i = 0; i < veritates_number; i++)
        visited[i] = 0;

    int result = 0;
    for (int i = 0; i < veritates_number; i++)
    {
        if (visited[i] == 0)
        {
            if (dfs_recursive(i, veritates_number, visited, matrix))
            {
                result = 1;
                break;
            }
        }
    }

    free(visited);
    return result;
}
