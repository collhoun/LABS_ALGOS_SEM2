#include "test_tree.h"

void test_create_number_node()
{
    TreeNode *node = create_number_node(42);
    assert(node != NULL);
    assert(node->type == NODE_NUMBER);
    assert(node->data.number == 42);
    assert(node->left == NULL);
    assert(node->right == NULL);
    free_tree(node);
}

void test_build_expression_tree_null()
{
    assert(build_expression_tree(NULL, 0) == NULL);
    assert(build_expression_tree(NULL, 5) == NULL);
    char *postfix[] = {"1"};
    assert(build_expression_tree(postfix, 0) == NULL);
}

void test_refactor_multiply_by_zero()
{
    TreeNode *root = create_operator_node('*');
    root->left = create_number_node(5);
    root->right = create_number_node(0);
    int changed = refactor_expression_tree(root);
    assert(changed == 1);
    assert(root->type == NODE_NUMBER);
    assert(root->data.number == 0);
    assert(root->left == NULL);
    assert(root->right == NULL);
    free_tree(root);
}

void test_refactor_no_change()
{
    TreeNode *root = create_operator_node('+');
    root->left = create_number_node(3);
    root->right = create_number_node(4);
    int changed = refactor_expression_tree(root);
    assert(changed == 0);
    assert(root->type == NODE_OPERATOR);
    assert(root->data.operator == '+');
    free_tree(root);
}
