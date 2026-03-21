#ifndef TOKENIZATION_H
#define TOKENIZATION_H

#include "stack.h"
#include "validation.h"
#include <ctype.h>

char *read_expr();
int tokenize(char *expression, char **tokens);
void free_tokens(char **tokens, int count);
int find_priority(char operator);
int is_all_digits(char *token);
int make_postfix(char *expr, char **tokens, char **postfix_entry);
char *insertzeros(char *expr);

#endif