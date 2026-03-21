#include "tree.h"
#include "tree_stack.h"
#include "tokenization.h"
// содержит функции для работы с деревом выражений
TreeNode *create_number_node(int value)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (!node)
        return NULL;
    node->type = NODE_NUMBER;
    node->data.number = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode *create_operator_node(char value)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (!node)
        return NULL;
    node->type = NODE_OPERATOR;
    node->data.operator = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode *build_expression_tree(char **postfix_expression, int len)
{
    if (!postfix_expression || len <= 0)
        return NULL;

    TreeStack *stack = NULL;

    for (int i = 0; i < len; i++)
    {
        char *token = postfix_expression[i];

        if (is_all_digits(token))
        {
            TreeNode *num_node = create_number_node(atoi(token));
            if (!stack)
                stack = init_tree_stack(num_node);
            else
                tree_stack_push(stack, num_node);
        }
        else
        {
            TreeNode *right = tree_stack_pop(stack);
            TreeNode *left = tree_stack_pop(stack);
            TreeNode *op_node = create_operator_node(token[0]);
            op_node->left = left;
            op_node->right = right;
            if (tree_stack_is_empty(stack))
            {
                destroy_tree_stack(stack);
                stack = init_tree_stack(op_node);
            }
            else
                tree_stack_push(stack, op_node);
        }
    }

    TreeNode *root = tree_stack_pop(stack);
    destroy_tree_stack(stack);
    return root;
}

void print_tree(TreeNode *root, int depth)
{
    if (!root)
        return;
    print_tree(root->right, depth + 1);
    for (int i = 0; i < depth; i++)
        printf("    ");
    if (root->type == NODE_NUMBER)
        printf("%d\n", root->data.number);
    else
        printf("%c\n", root->data.operator);
    print_tree(root->left, depth + 1);
}

void free_tree(TreeNode *root)
{
    if (!root)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

static int is_zero_node(TreeNode *node)
{
    return node && node->type == NODE_NUMBER && node->data.number == 0;
}

int refactor_expression_tree(TreeNode *root)
{
    if (!root)
        return 0;

    if (root->type != NODE_OPERATOR)
        return 0;

    refactor_expression_tree(root->left);
    refactor_expression_tree(root->right);

    TreeNode *left = root->left;
    TreeNode *right = root->right;

    if (!left || !right)
        return 0;

    char op = root->data.operator;

    if (op == '*' && (is_zero_node(left) || is_zero_node(right)))
    {
        free_tree(left);
        free_tree(right);
        root->type = NODE_NUMBER;
        root->data.number = 0;
        root->left = NULL;
        root->right = NULL;
        return 1;
    }

    if (op == '+' && (is_zero_node(left) || is_zero_node(right)))
    {
        TreeNode *tmp = is_zero_node(left) ? right : left;
        TreeNode *zero = is_zero_node(left) ? left : right;
        free(zero);

        root->type = tmp->type;
        root->data = tmp->data;
        root->left = tmp->left;
        root->right = tmp->right;
        free(tmp);
        return 1;
    }
    if (op == '-' && is_zero_node(right))
    {
        free(right);

        TreeNode *tmp = left;
        root->type = tmp->type;
        root->data = tmp->data;
        root->left = tmp->left;
        root->right = tmp->right;
        free(tmp);
        return 1;
    }

    return 0;
}
