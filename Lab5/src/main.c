#include "edge_array.h"
#include "graph.h"
#include <string.h>
int main()
{
    FILE *fp = NULL;
    printf("Choose input method:\n");
    printf("1. Console input\n");
    printf("2. File input\n");
    printf("Enter choice (1 or 2): ");
    int choice;
    scanf("%d", &choice);
    if (choice == 2)
    {
        printf("Enter filename: ");
        char filename[256];
        scanf("%s", filename);
        fp = fopen(filename, "r");
        if (!fp)
        {
            printf("Error opening file %s\n", filename);
            return 1;
        }
    }
    else
        fp = stdin;

    int size_edges, size_vertices;
    fscanf(fp, "%d %d", &size_edges, &size_vertices);
    Edge *edges = create_array(size_edges);
    for (int i = 0; i < size_edges; i++)
    {
        fscanf(fp, "%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    if (fp != stdin)
        fclose(fp);

    int **matrix = create_matrix(size_vertices, size_edges, edges);
    print_matrix(size_vertices, matrix);

    if (is_cycled(matrix, size_vertices))
        printf("Graph is cycled\n");
    else
    {
        printf("Graph is not cycled\n");
        int **dist = FloydWarshall(size_vertices, matrix);
        print_matrix(size_vertices, dist);
        free_matrix(dist, size_vertices);
    }

    free(edges);
    free_matrix(matrix, size_vertices);

    return 0;
}