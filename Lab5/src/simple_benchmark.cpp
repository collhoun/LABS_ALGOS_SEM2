#include "edge_array.h"
#include "graph.h"
#include <chrono>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

typedef struct
{
    const char *name;
    int size;
    double time_ms;
} BenchmarkResult;

void print_header()
{
    std::cout << std::left << std::setw(30) << "Benchmark"
              << std::setw(15) << "Size"
              << std::setw(20) << "Time (ms)" << std::endl;
    std::cout << std::string(65, '-') << std::endl;
}

void print_result(const char *name, int size, double time_ms)
{
    std::cout << std::left << std::setw(30) << name
              << std::setw(15) << size
              << std::setw(20) << std::fixed << std::setprecision(6) << time_ms << std::endl;
}

void benchmark_floyd_warshall()
{
    std::cout << "\n=== Floyd-Warshall Algorithm ===" << std::endl;
    print_header();

    int sizes[] = {10, 20, 30, 50, 100, 200, 300};

    for (int size : sizes)
    {
        int num_edges = size * 2;
        srand(time(NULL));
        Edge *edges = create_array(num_edges);

        for (int i = 0; i < num_edges; i++)
        {
            edges[i].src = rand() % size;
            edges[i].dest = rand() % size;
            edges[i].weight = rand() % 100 + 1;
        }

        int **matrix = create_matrix(size, num_edges, edges);
        free(edges);

        auto start = std::chrono::high_resolution_clock::now();
        int **result = FloydWarshall(size, matrix);
        auto end = std::chrono::high_resolution_clock::now();

        double time_ms = std::chrono::duration<double, std::milli>(end - start).count();

        char buffer[64];
        snprintf(buffer, sizeof(buffer), "FloydWarshall(size=%d)", size);
        print_result(buffer, size, time_ms);

        free_matrix(result, size);
        free_matrix(matrix, size);
    }
}

int main()
{
    std::cout << "=== Graph Algorithms Benchmarking ===" << std::endl;

    benchmark_floyd_warshall();

    std::cout << "\n=== Benchmarking Complete ===" << std::endl;

    return 0;
}
