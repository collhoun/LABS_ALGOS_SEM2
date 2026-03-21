#include "tree_stack.h"
// содержит функции для работы со стеком узлов дерева
TreeStackNode *create_tree_stack_node(TreeNode *tree_node)
{
    TreeStackNode *node = (TreeStackNode *)malloc(sizeof(TreeStackNode));
    if (!node)
        return NULL;

    node->prev = NULL;
    node->tree_node = tree_node;
    return node;
}

TreeStack *init_tree_stack(TreeNode *tree_node)
{
    TreeStack *stack = (TreeStack *)malloc(sizeof(TreeStack));
    if (!stack)
        return NULL;
    TreeStackNode *node = create_tree_stack_node(tree_node);
    if (!node)
    {
        free(stack);
        return NULL;
    }
    stack->top = node;
    return stack;
}

int tree_stack_push(TreeStack *stack, TreeNode *tree_node)
{
    TreeStackNode *node = create_tree_stack_node(tree_node);
    if (!node)
        return 0;
    if (!stack)
        return 0;
    if (!stack->top)
        stack->top = node;
    else
    {
        TreeStackNode *prev_head = stack->top;
        stack->top = node;
        node->prev = prev_head;
    }
    return 1;
}

TreeNode *tree_stack_peek(TreeStack *stack)
{
    if (!stack || !stack->top)
        return NULL;
    return stack->top->tree_node;
}

TreeNode *tree_stack_pop(TreeStack *stack)
{
    if (!stack || !stack->top)
        return NULL;
    TreeStackNode *prev_top = stack->top;
    stack->top = stack->top->prev;
    TreeNode *tree_node = prev_top->tree_node;
    free(prev_top);
    return tree_node;
}

void destroy_tree_stack(TreeStack *stack)
{
    if (!stack)
        return;
    while (stack->top)
    {
        TreeStackNode *tmp = stack->top;
        stack->top = stack->top->prev;
        free(tmp);
    }
    free(stack);
}

int tree_stack_is_empty(TreeStack *stack)
{
    if (!stack || !stack->top)
        return 1;
    return 0;
}
