#include "test_expr.h"
#include "test_tokenization.h"
#include "test_stack.h"
#include "test_tree_stack.h"
#include "test_tree.h"
#include "test_calculator.h"

int main()
{
    test_valid_expression();
    test_invalid_expression();
    test_invalid_characters();
    test_empty_expression();
    test_single_character_expression();

    test_init();
    test_pop();
    test_pop_empty();
    test_push();
    test_stack_many();

    test_addition();
    test_with_spaces();
    test_big_nums();
    test_many_operators();
    test_single_number();
    test_empty_string();

    test_tree_stack_init();
    test_tree_stack_push_pop();
    test_tree_stack_peek_test();
    test_tree_stack_pop_empty();
    test_tree_stack_is_empty_test();

    test_create_number_node();
    test_build_expression_tree_null();
    test_refactor_multiply_by_zero();
    test_refactor_no_change();

    test_calc_addition();
    test_calc_multiplication();
    test_calc_division_by_zero();
    test_calc_complex_expression();

    return 0;
}