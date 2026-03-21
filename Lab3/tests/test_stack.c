#include "test_stack.h"

void test_init()
{
    Stack *s = init_stack('a');
    assert(s != NULL);
    assert(s->top != NULL);
    assert(s->top->value == 'a');
    destroy_stack(s);
}

void test_push()
{
    Stack *s = init_stack('a');
    assert(push(s, 'b') == 1);
    assert(peek(s) == 'b');
    assert(push(s, 'c') == 1);
    assert(peek(s) == 'c');
    destroy_stack(s);
}

void test_pop()
{
    Stack *s = init_stack('a');
    push(s, 'b');
    push(s, 'c');
    assert(pop(s) == 'c');
    assert(peek(s) == 'b');
    assert(pop(s) == 'b');
    assert(peek(s) == 'a');
    assert(pop(s) == 'a');
    assert(s->top == NULL);
    destroy_stack(s);
}

void test_pop_empty()
{
    Stack *s = init_stack('a');
    pop(s);
    assert(pop(s) == '\0');
    assert(peek(s) == '\0');

    destroy_stack(s);
}

void test_stack_many()
{

    Stack *s = init_stack('1');
    assert(s != NULL);
    const char *data = "2345";
    for (const char *p = data; *p; p++)
    {
        assert(push(s, *p) == 1);
    }

    assert(pop(s) == '5');
    assert(peek(s) == '4');
    assert(pop(s) == '4');
    assert(peek(s) == '3');
    assert(pop(s) == '3');
    assert(peek(s) == '2');
    assert(pop(s) == '2');
    assert(peek(s) == '1');
    assert(pop(s) == '1');
    assert(s->top == NULL);
    assert(pop(s) == '\0');
    destroy_stack(s);
}
