#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "../src/tree.h"

void test_tree_many()
{
    RedBlackTree *tree = create_tree();
    assert(tree != NULL);

    char *keys[30] = {
        "key01", "key02", "key03", "key04", "key05",
        "key06", "key07", "key08", "key09", "key10",
        "key11", "key12", "key13", "key14", "key15",
        "key16", "key17", "key18", "key19", "key20",
        "key21", "key22", "key23", "key24", "key25",
        "key26", "key27", "key28", "key29", "key30"};
    int values[30] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        21, 22, 23, 24, 25, 26, 27, 28, 29, 30};

    for (int i = 0; i < 30; i++)
    {
        insert(tree, keys[i], values[i]);
    }

    for (int i = 0; i < 30; i++)
    {
        int found = find(tree, keys[i]);
        assert(found == values[i]);
    }

    int not_found = find(tree, "nonexistent");
    assert(not_found == -1);

    for (int i = 0; i < 30; i += 2)
    {
        delete_tree_node(tree, keys[i]);
    }

    for (int i = 0; i < 30; i++)
    {
        int found = find(tree, keys[i]);
        if (i % 2 == 0)
        {
            assert(found == -1);
        }
        else
        {
            assert(found == values[i]);
        }
    }

    not_found = find(tree, "another_nonexistent");
    assert(not_found == -1);
}