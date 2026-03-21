#include "test_tokenization.h"

void test_addition()
{
    char expr[] = "12+3";
    char **tokens = malloc(strlen(expr) * sizeof(char *));
    int cnt = tokenize(expr, tokens);
    assert(cnt == 3);
    assert(strcmp(tokens[0], "12") == 0);
    assert(strcmp(tokens[1], "+") == 0);
    assert(strcmp(tokens[2], "3") == 0);
    free_tokens(tokens, cnt);
}

void test_with_spaces()
{
    char expr[] = " 12  + 3 - 144 ";
    char **tokens = malloc(strlen(expr) * sizeof(char *));
    int cnt = tokenize(expr, tokens);
    assert(cnt == 5);
    assert(strcmp(tokens[0], "12") == 0);
    assert(strcmp(tokens[1], "+") == 0);
    assert(strcmp(tokens[2], "3") == 0);
    assert(strcmp(tokens[3], "-") == 0);
    assert(strcmp(tokens[4], "144") == 0);
    free_tokens(tokens, cnt);
}

void test_big_nums()
{
    char expr[] = "12345+67890";
    char **tokens = malloc(strlen(expr) * sizeof(char *));
    int cnt = tokenize(expr, tokens);
    assert(cnt == 3);
    assert(strcmp(tokens[0], "12345") == 0);
    assert(strcmp(tokens[1], "+") == 0);
    assert(strcmp(tokens[2], "67890") == 0);
    free_tokens(tokens, cnt);
}

void test_many_operators()
{
    char expr[] = "12*(3+4)/2";
    char **tokens = malloc(strlen(expr) * sizeof(char *));
    int cnt = tokenize(expr, tokens);
    assert(cnt == 9);
    assert(strcmp(tokens[0], "12") == 0);
    assert(strcmp(tokens[1], "*") == 0);
    assert(strcmp(tokens[2], "(") == 0);
    assert(strcmp(tokens[3], "3") == 0);
    assert(strcmp(tokens[4], "+") == 0);
    assert(strcmp(tokens[5], "4") == 0);
    assert(strcmp(tokens[6], ")") == 0);
    assert(strcmp(tokens[7], "/") == 0);
    assert(strcmp(tokens[8], "2") == 0);
    free_tokens(tokens, cnt);
}

void test_single_number()
{
    char expr[] = "42";
    char **tokens = malloc(strlen(expr) * sizeof(char *));
    int cnt = tokenize(expr, tokens);
    assert(cnt == 1);
    assert(strcmp(tokens[0], "42") == 0);
    free_tokens(tokens, cnt);
}

void test_empty_string()
{
    char expr[] = "";
    char **tokens = malloc(1 * sizeof(char *));
    int cnt = tokenize(expr, tokens);
    assert(cnt == 0);
}
