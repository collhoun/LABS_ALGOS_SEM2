#include <stdio.h>
#include <string.h>
#include "tree.h"

int main()
{
    RedBlackTree *tree = create_tree();

    char choice_str[10];
    printf("Use CLI? (y/n): ");
    fgets(choice_str, sizeof(choice_str), stdin);

    if (choice_str[0] == 'y' || choice_str[0] == 'Y')
    {
        char command[256];
        char key_str[7];
        int value;
        printf("Entering CLI mode. Commands: insert <key> <value>, delete <key>, print, find <key>, exit\n");
        while (1)
        {
            printf("> ");
            if (!fgets(command, sizeof(command), stdin))
                break;

            if (sscanf(command, "insert %6s %d", key_str, &value) == 2)
            {
                insert(tree, key_str, value);
                printf("Inserted key %s with value %d\n", key_str, value);
            }
            else if (sscanf(command, "delete %6s", key_str) == 1)
            {
                delete_tree_node(tree, key_str);
                printf("Deleted key %s\n", key_str);
            }
            else if (strcmp(command, "print\n") == 0)
            {
                print_tree(tree->root);
            }
            else if (sscanf(command, "find %6s", key_str) == 1)
            {
                int finded_value = find(tree, key_str);
                if (finded_value != -1)
                {
                    printf("Found value: %d\n", finded_value);
                }
                else
                {
                    printf("Key %s not found\n", key_str);
                }
            }
            else if (strcmp(command, "exit\n") == 0)
            {
                break;
            }
            else
            {
                printf("Invalid command. Use: insert <key> <value>, delete <key>, print, find <key>, exit\n");
            }
        }
    }
    else
    {
        char *filename_in = "data/samples.txt";
        FILE *file_in = fopen(filename_in, "r");
        char *filename_out = "data/output.txt";
        FILE *file_out = fopen(filename_out, "w");

        if (!file_out)
        {
            printf("File not found\n");
            return 0;
        }

        if (!file_in)
        {
            printf("File not found\n");
            return 0;
        }

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
    }

    return 0;
}