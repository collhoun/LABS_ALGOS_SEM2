#include "test_calculator.h"

void test_calc_addition()
{
    TreeNode *root = create_operator_node('+');
    root->left = create_number_node(3);
    root->right = create_number_node(4);
    assert(calculate_tree(root) == 7);
    free_tree(root);
}

void test_calc_multiplication()
{
    TreeNode *root = create_operator_node('*');
    root->left = create_number_node(6);
    root->right = create_number_node(7);
    assert(calculate_tree(root) == 42);
    free_tree(root);
}

void test_calc_division_by_zero()
{
    TreeNode *root = create_operator_node('/');
    root->left = create_number_node(10);
    root->right = create_number_node(0);
    assert(calculate_tree(root) == 0);
    free_tree(root);
}

void test_calc_complex_expression()
{
    TreeNode *root = create_operator_node('*');
    root->left = create_operator_node('+');
    root->left->left = create_number_node(2);
    root->left->right = create_number_node(3);
    root->right = create_number_node(4);
    assert(calculate_tree(root) == 20);
    free_tree(root);
}
