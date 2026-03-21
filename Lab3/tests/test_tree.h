#ifndef TEST_TREE_H
#define TEST_TREE_H

#include <assert.h>
#include <string.h>
#include "../src/tree.h"
#include "../src/tokenization.h"
#include "../src/calculator.h"

void test_create_number_node();
void test_build_expression_tree_null();
void test_refactor_multiply_by_zero();
void test_refactor_no_change();

#endif
