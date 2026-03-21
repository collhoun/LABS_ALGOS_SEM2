#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    NODE_NUMBER,
    NODE_OPERATOR
} TreeNodeType;

typedef struct TreeNode
{
    TreeNodeType type;
    union
    {
        int number;
        char operator;
    } data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *create_number_node(int value);
TreeNode *create_operator_node(char value);
TreeNode *build_expression_tree(char **postfix_expression, int len);
void print_tree(TreeNode *root, int depth);
void free_tree(TreeNode *root);
int refactor_expression_tree(TreeNode *root);

#endif