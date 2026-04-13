#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    RED,
    BLACK
} NodeColor;

typedef struct TreeNode
{
    char* key;
    int value;
    NodeColor color;
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *parent;
} TreeNode;

typedef struct RedBlackTree
{
    struct TreeNode *root;
} RedBlackTree;

extern TreeNode *NIL;

RedBlackTree *create_tree();
TreeNode *create_node(char* key, int value);

void insert(RedBlackTree *tree, char* key, int value);
void delete_tree_node(RedBlackTree *tree, char* key);
int find(RedBlackTree *tree, char* key);

void print_tree(TreeNode *root);
void print_tree_recursive(TreeNode *node, int depth);

void left_rotate(RedBlackTree *tree, TreeNode *current);
void right_rotate(RedBlackTree *tree, TreeNode *current);
void insert_fix(RedBlackTree *tree, TreeNode *node);
void delete_fix(RedBlackTree *tree, TreeNode *node);

#endif
