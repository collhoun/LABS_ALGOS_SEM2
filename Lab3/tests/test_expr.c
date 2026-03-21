#include "test_expr.h"
void test_valid_expression()
{
    assert(validate_expression("2+3"));
    assert(validate_expression("2-3"));
    assert(validate_expression("2*3"));
    assert(validate_expression("2/3"));
    assert(validate_expression("2^3"));
}

void test_invalid_expression()
{
    assert(!validate_expression("2++++++3"));
    assert(!validate_expression("3^^2"));
    assert(!validate_expression("2*)(3"));
}

void test_invalid_characters()
{
    assert(!validate_expression("2+3$"));
    assert(!validate_expression("2-3#"));
    assert(!validate_expression("2*3%"));
    assert(!validate_expression("2/3&"));
    assert(!validate_expression("2^3@"));
}

void test_empty_expression()
{
    assert(!validate_expression(""));
}

void test_single_character_expression()
{
    assert(validate_expression("2"));
}

void test_many_sapces_expression()
{
    assert(validate_expression(" 2 +      3 "));
}