#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    char value;
    struct Node *prev;
} Node;

typedef struct Stack
{
    Node *top;
} Stack;

Node *create_node(char value);
Stack *init_stack(char value);
int push(Stack *stack, char value);
char peek(Stack *stack);
char pop(Stack *stack);
void destroy_stack(Stack *stack);
int is_empty(Stack *stack);
#endif