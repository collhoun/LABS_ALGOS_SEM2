#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/tree.h"
#include "test_tree_many.h"

typedef struct
{
    int op;
    char key[10];
    int value;
} Sample;

typedef struct
{
    char key[10];
    int value;
} Expected;

Sample samples[] = {
    {1, "y", -53},
    {1, "aaxmfo", -71},
    {2, "mlkj", -68},
    {4, "ap", 55},
    {1, "slyvlx", 79},
    {1, "u", 94},
    {4, "dunnz", -68},
    {4, "ttdz", 1},
    {4, "k", -57},
    {3, "gsorrm", -77},
    {4, "kfz", -66},
    {2, "rlweyd", -82},
    {1, "phzzu", -70},
    {1, "wtpp", -31},
    {4, "jrai", -46},
    {3, "dopu", -99},
    {2, "p", -65},
    {1, "rgcyy", 35},
    {1, "i", 80}};

Expected expected_inserts[] = {
    {"y", -53},
    {"aaxmfo", -71},
    {"slyvlx", 79},
    {"u", 94},
    {"phzzu", -70},
    {"wtpp", -31},
    {"rgcyy", 35},
    {"i", 80}};

void test_create_tree()
{
    RedBlackTree *tree = create_tree();
    assert(tree != NULL);
    assert(tree->root == NIL);
}

void test_insert_single()
{
    RedBlackTree *tree = create_tree();
    insert(tree, "test", 42);
    assert(find(tree, "test") == 42);
}

void test_insert_many_and_find()
{
    RedBlackTree *tree = create_tree();
    insert(tree, "a", 1);
    insert(tree, "b", 2);
    insert(tree, "c", 3);
    assert(find(tree, "a") == 1);
    assert(find(tree, "b") == 2);
    assert(find(tree, "c") == 3);
}

void test_find_not_in_tree()
{
    RedBlackTree *tree = create_tree();
    insert(tree, "a", 1);
    assert(find(tree, "b") == -1);
}

void test_delete_leaf()
{
    RedBlackTree *tree = create_tree();
    insert(tree, "a", 1);
    delete_tree_node(tree, "a");
    assert(find(tree, "a") == -1);
}

void test_delete_with_one_child()
{
    RedBlackTree *tree = create_tree();
    insert(tree, "b", 2);
    insert(tree, "a", 1);
    insert(tree, "c", 3);
    insert(tree, "d", 4);
    delete_tree_node(tree, "c");
    assert(find(tree, "c") == -1);
    assert(find(tree, "d") == 4);
}

void test_delete_with_two_children()
{
    RedBlackTree *tree = create_tree();
    insert(tree, "b", 2);
    insert(tree, "a", 1);
    insert(tree, "d", 4);
    insert(tree, "c", 3);
    insert(tree, "e", 5);
    delete_tree_node(tree, "d");
    assert(find(tree, "d") == -1);
    assert(find(tree, "c") == 3);
    assert(find(tree, "e") == 5);
}

void test_left_rotate()
{
    RedBlackTree *tree = create_tree();
    insert(tree, "a", 1);
    insert(tree, "b", 2);
    insert(tree, "c", 3);
    assert(find(tree, "a") == 1);
    assert(find(tree, "b") == 2);
    assert(find(tree, "c") == 3);
}

void test_right_rotate()
{
    RedBlackTree *tree = create_tree();
    insert(tree, "c", 3);
    insert(tree, "b", 2);
    insert(tree, "a", 1);
    assert(find(tree, "a") == 1);
    assert(find(tree, "b") == 2);
    assert(find(tree, "c") == 3);
}

void test_full_data()
{
    RedBlackTree *tree = create_tree();
    for (int i = 0; i < sizeof(samples) / sizeof(Sample); i++)
    {
        if (samples[i].op == 1)
        {
            insert(tree, samples[i].key, samples[i].value);
        }
    }

    for (int i = 0; i < sizeof(expected_inserts) / sizeof(Expected); i++)
    {
        int val = find(tree, expected_inserts[i].key);
        assert(val == expected_inserts[i].value);
    }
}

int main()
{
    test_create_tree();
    test_insert_single();
    test_insert_many_and_find();
    test_find_not_in_tree();
    test_delete_leaf();
    test_delete_with_one_child();
    test_delete_with_two_children();
    test_left_rotate();
    test_right_rotate();
    test_full_data();
    test_tree_many();
    printf("All tests passed!\n");
    return 0;
}