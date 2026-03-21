#ifndef TREE_STACK_H
#define TREE_STACK_H

#include "tree.h"

typedef struct TreeStackNode
{
    TreeNode *tree_node;
    struct TreeStackNode *prev;
} TreeStackNode;

typedef struct TreeStack
{
    TreeStackNode *top;
} TreeStack;

TreeStackNode *create_tree_stack_node(TreeNode *tree_node);
TreeStack *init_tree_stack(TreeNode *tree_node);
int tree_stack_push(TreeStack *stack, TreeNode *tree_node);
TreeNode *tree_stack_peek(TreeStack *stack);
TreeNode *tree_stack_pop(TreeStack *stack);
void destroy_tree_stack(TreeStack *stack);
int tree_stack_is_empty(TreeStack *stack);

#endif
