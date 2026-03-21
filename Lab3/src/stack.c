#include "stack.h"
// содержит функции для работы со стеком операторов
Node *create_node(char value)
{
    // создание узла данных со значением value для стека операторов
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node)
        return NULL;

    node->prev = NULL;
    node->value = value;
    return node;
}

Stack *init_stack(char value)
{
    // инициализация стека с оператором value
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack)
        return NULL; // error
    Node *node = create_node(value);
    if (!node)
    {
        free(stack);
        return NULL;
    }
    stack->top = node;
    return stack;
}

int push(Stack *stack, char value)
{
    // добавление в стек операторов
    Node *node = create_node(value);
    if (!node)
        return 0; // error
    if (!stack)
        return 0;
    if (!stack->top)
        stack->top = node;
    else
    {
        Node *prev_head = stack->top;
        stack->top = node;
        node->prev = prev_head;
    }
    return 1;
}

char peek(Stack *stack)
{
    //  просмотр вершины стека
    if (!stack->top)
        return '\0';
    return stack->top->value;
}

char pop(Stack *stack)
{
    // удаление элемента с вершины стека операторов
    if (!stack || !stack->top)
        return '\0';
    Node *prev_top = stack->top;
    stack->top = stack->top->prev;
    char value = prev_top->value;
    free(prev_top);
    return value;
}
void destroy_stack(Stack *stack)
{
    // очистка стека операторов
    if (!stack)
        return;
    while (stack->top)
    {
        Node *tmp = stack->top;
        stack->top = stack->top->prev;
        free(tmp);
    }
    free(stack);
}

int is_empty(Stack *stack)
{
    // проверка стека на пустоту
    if (!stack || !stack->top)
        return 1;
    return 0;
}