#ifndef TREES_H
#define TREES_H

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// Forward declarations структур
typedef struct TreeNode TreeNode;
typedef struct Tree Tree;

typedef struct TreeNode
{
    // узел дерева
    List *list_of_children;
    int key;
    int max_children;
} TreeNode;

typedef struct Tree
{
    // само дерево
    TreeNode *root;
} Tree;

// функции для создания узлов дерева
TreeNode *create_TreeNode(int value, int max_children);

// функции для работы с деревом
Tree *init_tree(TreeNode *root);
int add_in_tree(TreeNode *root, TreeNode *treenode);
void print_tree(Tree *tree);
void print_tree_recursive(TreeNode *node, int depth);
int delete_node(TreeNode *treenode, int key);
void delete_tree_node(TreeNode *node);
int count_width_tree(Tree *tree);
int count_width(TreeNode *root);
int is_in_tree(TreeNode *root, TreeNode *treenode);

#endif
