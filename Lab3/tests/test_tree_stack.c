#include "test_tree_stack.h"

void test_tree_stack_init()
{
    TreeNode *node = create_number_node(42);
    TreeStack *stack = init_tree_stack(node);
    assert(stack != NULL);
    assert(stack->top != NULL);
    assert(stack->top->tree_node == node);
    assert(stack->top->tree_node->data.number == 42);
    tree_stack_pop(stack);
    free_tree(node);
    destroy_tree_stack(stack);
}

void test_tree_stack_push_pop()
{
    TreeNode *n1 = create_number_node(1);
    TreeNode *n2 = create_number_node(2);
    TreeNode *n3 = create_operator_node('+');

    TreeStack *stack = init_tree_stack(n1);
    assert(tree_stack_push(stack, n2) == 1);
    assert(tree_stack_push(stack, n3) == 1);

    TreeNode *popped = tree_stack_pop(stack);
    assert(popped == n3);
    assert(popped->type == NODE_OPERATOR);
    assert(popped->data.operator == '+');

    popped = tree_stack_pop(stack);
    assert(popped == n2);
    assert(popped->data.number == 2);

    popped = tree_stack_pop(stack);
    assert(popped == n1);
    assert(popped->data.number == 1);

    assert(tree_stack_pop(stack) == NULL);

    free_tree(n1);
    free_tree(n2);
    free_tree(n3);
    destroy_tree_stack(stack);
}

void test_tree_stack_peek_test()
{
    TreeNode *n1 = create_number_node(10);
    TreeNode *n2 = create_number_node(20);

    TreeStack *stack = init_tree_stack(n1);
    assert(tree_stack_peek(stack) == n1);

    tree_stack_push(stack, n2);
    assert(tree_stack_peek(stack) == n2);

    tree_stack_pop(stack);
    assert(tree_stack_peek(stack) == n1);

    free_tree(n2);
    tree_stack_pop(stack);
    free_tree(n1);
    destroy_tree_stack(stack);
}

void test_tree_stack_pop_empty()
{
    TreeNode *n1 = create_number_node(5);
    TreeStack *stack = init_tree_stack(n1);
    tree_stack_pop(stack);
    free_tree(n1);

    assert(tree_stack_pop(stack) == NULL);
    assert(tree_stack_peek(stack) == NULL);
    assert(tree_stack_is_empty(stack) == 1);

    destroy_tree_stack(stack);
}

void test_tree_stack_is_empty_test()
{
    TreeNode *n1 = create_number_node(7);
    TreeStack *stack = init_tree_stack(n1);
    assert(tree_stack_is_empty(stack) == 0);

    tree_stack_pop(stack);
    free_tree(n1);
    assert(tree_stack_is_empty(stack) == 1);

    destroy_tree_stack(stack);
}
