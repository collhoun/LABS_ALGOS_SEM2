#include "calculator.h"
#include <math.h>
int calculate_tree(TreeNode *root)
{
    // функция для вычисления значения выражения в дереве
    if (!root)
        return 0;

    if (root->type == NODE_NUMBER)
        return root->data.number;

    int left_val = calculate_tree(root->left);
    int right_val = calculate_tree(root->right);

    switch (root->data.operator)
    {
    case '+':
        return left_val + right_val;
    case '-':
        return left_val - right_val;
    case '*':
        return left_val * right_val;
    case '/':
        if (right_val == 0)
            return 0;
        return left_val / right_val;
    case '^':
        return pow(left_val, right_val);
    default:
        return 0;
    }
}