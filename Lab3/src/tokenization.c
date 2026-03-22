#include "tokenization.h"
#include <ctype.h>
// содержит вспомогательные функции для токенизации выражения
char *read_expr()
{
    // читает выражение из входного потока данных stdin
    // возвращает указатель на прочитанную строку
    char *expression = NULL;
    size_t len = 0;
    ssize_t readed;
    while ((readed = getline(&expression, &len, stdin)) != -1)
    {
        if (readed > 0 && expression[readed - 1] == '\n')
        {
            expression[readed - 1] = '\0';
            return expression;
        }
    }

    return expression;
}

char *insertzeros(char *expr)
{
    if (!expr)
        return NULL;

    size_t len = strlen(expr);
    char *result = malloc(len * 2 + 1);
    if (!result)
        return NULL;

    int res_idx = 0;
    char prev_znachimiy = '\0';

    for (size_t i = 0; i < len; ++i)
    {
        char ch = expr[i];
        if (ch == '-')
        {
            int is_unary = 0;

            if (prev_znachimiy == '\0')
                is_unary = 1;

            else if (prev_znachimiy == '(')
                is_unary = 1;

            if (is_unary)
            {
                result[res_idx++] = '0';
                result[res_idx++] = '-';
            }
            else
                result[res_idx++] = '-';

            prev_znachimiy = '-';
        }
        else
        {
            result[res_idx++] = ch;
            prev_znachimiy = ch;
        }
    }

    result[res_idx] = '\0';

    char *final_result = realloc(result, res_idx + 1);
    if (!final_result)
    {
        free(result);
        return NULL;
    }
    return final_result;
}

int tokenize(char *expression, char **tokens)
{
    // разделяет выражение на токены
    // на вход подается уже валидное выражение!!!
    // возвращает количество токенов, что то же самое что и длина массива токенов
    const int MAX_TOKEN_LEN = 15;
    int i = 0;
    int cnt_tokens = 0;
    int len = strlen(expression);

    while (i < len)
    {

        if (isspace(expression[i]))
        {
            i++;
            continue;
        }

        if (isdigit(expression[i]))
        {
            int j = 0;
            tokens[cnt_tokens] = (char *)malloc(MAX_TOKEN_LEN + 1);
            if (!tokens[cnt_tokens])
                return -1;
            while (i < len && isdigit(expression[i]) && j < MAX_TOKEN_LEN)
            {
                tokens[cnt_tokens][j++] = expression[i++];
            }
            tokens[cnt_tokens][j] = '\0';
            cnt_tokens++;
        }
        else
        {
            tokens[cnt_tokens] = (char *)malloc(2);
            if (!tokens[cnt_tokens])
                return -1;
            tokens[cnt_tokens][0] = expression[i];
            tokens[cnt_tokens][1] = '\0';
            i++;
            cnt_tokens++;
        }
    }
    return cnt_tokens;
}

void free_tokens(char **tokens, int count)
{
    // освобождает память, выделенную под токены
    for (int i = 0; i < count; i++)
    {
        free(tokens[i]);
    }
    free(tokens);
}

int find_priority(char operator)
{
    // находит приоритет операций
    char OPERATORS_PRIORITY[3][2] = {{'+', '-'}, {'*', '/'}, {'^', '^'}};
    int len_operators = 3;
    int i = 0;
    while (i < len_operators)
    {
        for (int j = 0; j < 2; j++)
        {
            if (OPERATORS_PRIORITY[i][j] == operator)
                return i;
        }
        i++;
    }
    return -1;
}

int is_all_digits(char *token)
{
    // проверяет является ли токен числом
    for (int i = 0; i < strlen(token); i++)
    {
        if (!isdigit(token[i]))
            return 0;
    }
    return 1;
}

int make_postfix(char *expr, char **tokens, char **postfix_entry)
{
    // переводит токенизированное выражение в постфиксную запись
    // по умолчанию передается пустой список токенов - это нужно, чтобы передать его в функцию tokenize
    // возвращает длину списка постфиксной записи, она должна совпадать с количеством токенов
    int MAX_TOKEN_LEN = 15;

    if (!validate_expression(expr))
    {
        printf("Invalid expression\n");
        return -1;
    }
    int len_tokens = tokenize(expr, tokens);
    int cnt_tokens = 0;
    Stack *stack = NULL;
    int i = 0;
    while (i < len_tokens)
    {
        if (is_all_digits(tokens[i]))
        {
            postfix_entry[cnt_tokens] = (char *)malloc(MAX_TOKEN_LEN + 1);
            if (!postfix_entry[cnt_tokens])
                return -1;
            strcpy(postfix_entry[cnt_tokens], tokens[i]);
            cnt_tokens++;
        }
        else if (tokens[i][0] == '(')
        {
            if (stack)
                push(stack, '(');
            else
                stack = init_stack('(');
        }
        else if (tokens[i][0] == ')')
        {
            while (peek(stack) != '(')
            {
                char popped_value = pop(stack);
                postfix_entry[cnt_tokens] = (char *)malloc(2);
                if (!postfix_entry[cnt_tokens])
                    return -1;
                postfix_entry[cnt_tokens][0] = popped_value;
                postfix_entry[cnt_tokens][1] = '\0';
                cnt_tokens++;
            }
            pop(stack);
        }
        else
        {
            // если токен - арифметичсекий оператор, то находим его приоретет и находим приоритет оператора на вершине стека
            int curr_priority = find_priority(tokens[i][0]);
            if (stack)
            {
                while (peek(stack) && peek(stack) != '(' && find_priority(peek(stack)) >= curr_priority)
                {
                    char popped_value = pop(stack);
                    postfix_entry[cnt_tokens] = (char *)malloc(2);
                    if (!postfix_entry[cnt_tokens])
                        return -1;
                    postfix_entry[cnt_tokens][0] = popped_value;
                    postfix_entry[cnt_tokens][1] = '\0';
                    cnt_tokens++;
                }
            }
            if (stack)
                push(stack, tokens[i][0]);
            else
                stack = init_stack(tokens[i][0]);
        }
        i++;
    }
    while (peek(stack))
    {
        char popped = pop(stack);
        postfix_entry[cnt_tokens] = (char *)malloc(2);
        if (!postfix_entry[cnt_tokens])
            return -1;
        postfix_entry[cnt_tokens][0] = popped;
        postfix_entry[cnt_tokens][1] = '\0';
        cnt_tokens++;
    }
    return cnt_tokens;
}