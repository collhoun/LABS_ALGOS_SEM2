#include "tree.h"

int main()
{
    char *filename_in = "data/samples.txt";
    FILE *file_in = fopen(filename_in, "r");
    char *filename_out = "data/output.txt";
    FILE *file_out = fopen(filename_out, "w");

    if (!file_out)
    {
        printf("FIle not found\n");
        return 0;
    }

    if (!file_in)
    {
        printf("FIle not found\n");
        return 0;
    }
    RedBlackTree *tree = create_tree();

    char line[256];
    int operation_number, value;
    char key_str[7]; // для строк до 6 символов + \0
    int finded_value;
    while (fgets(line, sizeof(line), file_in))
    {
        sscanf(line, "%d %6s %d", &operation_number, key_str, &value);
        switch (operation_number)
        {
        case 1:
            printf("=========================================\n");
            printf("Insert key %s in tree\n", key_str);
            fprintf(file_out, "Insert key %s in tree\n", key_str);
            insert(tree, key_str, value);
            printf("=========================================\n");
            break;
        case 2:
            printf("=========================================\n");
            printf("Trying to delete key %s in tree\n", key_str);
            fprintf(file_out, "Trying to delete key %s in tree\n", key_str);
            delete_tree_node(tree, key_str);
            printf("=========================================\n");
            break;
        case 3:
            printf("=========================================\n");
            printf("PRINTED TREE:\n");
            fprintf(file_out, "PRINTED TREE:\n");
            print_tree(tree->root);
            printf("=========================================\n");
            break;
        case 4:
            printf("=========================================\n");
            printf("Trying to find key %s\n", key_str);
            finded_value = find(tree, key_str);
            if (finded_value != -1)
            {
                printf("Finded value: %d\n", finded_value);
                fprintf(file_out, "Finded value: %d\n", finded_value);
            }
            else
            {
                printf("Key %s not found\n", key_str);
                fprintf(file_out, "Key %s not found\n", key_str);
            }
            printf("=========================================\n");
            break;
        default:
            printf("Invalid operation %d. Should be 1-4\n", operation_number);
            break;
        }
    }

    print_tree(tree->root);
    fclose(file_in);
    fclose(file_out);
    return 0;
}