#include "validation.h"

// содержит функции для валидации входного выражения
int validate_expression(char *expr)
{
    /*
    функция для валидации данных входного выражения
    проверяет:
    - корректность расстановки скобок
    - отсутствие некорректных символов в выражении
    - проверка на отсутсвие повторяющихся подряд операторов (только ++ -- // ** ^^)
    */
    const char *POSSIBLE_SYMBOLS = "+-*/^0123456789() ";
    const char *POSSIBLE_OPERATORS = "+-*/^";
    Stack *stack = NULL;
    size_t len = strlen(expr);
    if (len == 0)
        return 0;
    for (int i = 0; i < len; i++)
    {
        // проверка на корректность скобок
        if (expr[i] == '(')
        {
            if (!stack)
                stack = init_stack('(');
            else
                push(stack, '(');
        }
        else if (expr[i] == ')')
        {
            if (!stack)
                return 0;
            else if (peek(stack) == '(')
                pop(stack);
            else
            {
                destroy_stack(stack);
                return 0;
            }
        }

        // проверка на возможыне символы в выражении
        if (strchr(POSSIBLE_SYMBOLS, expr[i]) == NULL)
            return 0;
        if ((expr[i] == expr[i + 1]) && (strchr(POSSIBLE_OPERATORS, expr[i])))
            return 0;
    }

    if (!is_empty(stack))
    {
        destroy_stack(stack);
        return 0;
    }
    return 1;
}