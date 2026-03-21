#include "tree.h"
#include "tokenization.h"
#include "calculator.h"
// написать функцию для вставки нуля при нахождении унарного минуса
int main()
{
    // пример для вычисления: 213  -23*(12-10)+3
    printf("Enter expression: ");
    char *expr = read_expr();
    char **tokens = malloc(strlen(expr) * sizeof(char *));
    int cnt_tokens = tokenize(expr, tokens);
    char **postfix_entry = malloc(cnt_tokens * sizeof(char *));
    int cnt_postfix = make_postfix(expr, tokens, postfix_entry);
    TreeNode *root = build_expression_tree(postfix_entry, cnt_postfix);
    print_tree(root, 0);
    refactor_expression_tree(root);
    printf("-------------------------------\n");
    print_tree(root, 0);
    int result = calculate_tree(root);
    printf("Result: %d\n", result);
    return 0;
}