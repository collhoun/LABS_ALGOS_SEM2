#include <gtest/gtest.h>
#include <vector>

// помогаем линкеру найти именно сишные функции, а не плюсовые
extern "C"
{
#include "../src/graph.h"
#include "../src/edge_array.h"
}

TEST(EdgeArrayTest, CreateArray)
{
    int size = 5;
    Edge *arr = create_array(size);
    ASSERT_NE(arr, nullptr);
    free(arr);
}

TEST(GraphTest, CreateMatrix)
{
    int size = 3;
    int num_edges = 2;
    Edge edges[2] = {{0, 1, 5}, {1, 2, 3}};
    int **matrix = create_matrix(size, num_edges, edges);
    ASSERT_NE(matrix, nullptr);
    ASSERT_EQ(matrix[0][1], 5);
    ASSERT_EQ(matrix[1][2], 3);
    ASSERT_EQ(matrix[0][0], 0);
    for (int i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}

TEST(GraphTest, FloydWarshall)
{
    int size = 3;
    int **matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        matrix[i] = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++)
            matrix[i][j] = 0;
    }
    matrix[0][1] = 1;
    matrix[1][2] = 2;
    int **dist = FloydWarshall(size, matrix);
    ASSERT_EQ(dist[0][2], 3);
    ASSERT_EQ(dist[0][0], 0);
    for (int i = 0; i < size; i++)
    {
        free(matrix[i]);
        free(dist[i]);
    }
    free(matrix);
    free(dist);
}

TEST(GraphTest, IsCycledAcyclic)
{
    int size = 4;
    int **matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        matrix[i] = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++)
            matrix[i][j] = 0;
    }
    matrix[0][1] = 1;
    matrix[1][2] = 1;
    matrix[2][3] = 1;
    ASSERT_EQ(is_cycled(matrix, size), 0);

    for (int i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}

TEST(GraphTest, IsCycledCyclic)
{
    int size = 3;
    int **matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        matrix[i] = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++)
            matrix[i][j] = 0;
    }
    matrix[0][1] = 1;
    matrix[1][2] = 1;
    matrix[2][0] = 1;
    ASSERT_EQ(is_cycled(matrix, size), 1);

    for (int i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}

TEST(GraphTest, IsCycledSelfLoop)
{
    int size = 3;
    int **matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        matrix[i] = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++)
            matrix[i][j] = 0;
    }
    matrix[0][0] = 1;
    ASSERT_EQ(is_cycled(matrix, size), 1);

    for (int i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}

TEST(GraphTest, IsCycledDisconnectedCyclic)
{
    int size = 5;
    int **matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        matrix[i] = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++)
            matrix[i][j] = 0;
    }

    matrix[0][1] = 1;
    matrix[1][2] = 1;
    matrix[2][0] = 1;
    matrix[3][4] = 1;
    ASSERT_EQ(is_cycled(matrix, size), 1);

    for (int i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}