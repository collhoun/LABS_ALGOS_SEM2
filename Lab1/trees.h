#ifndef TREES_H
#define TREES_H

#include <stdio.h>
#include <stdlib.h>

// Forward declarations структур
typedef struct Node Node;
typedef struct TreeNode TreeNode;
typedef struct List List;
typedef struct Tree Tree;

typedef struct Node
{
    // узел односвзяного списка
    TreeNode *child;
    Node *next;
} Node;

typedef struct List
{
    // сам односвзяный список
    Node *head;
    int len;
} List;

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

// функции для работы со списком
List *init_list();
void push_front(List *list, Node *node);
void push_back(List *list, Node *node);
void pop_front(List *list);
int delete_fromlist_by_key(List *list, int key);
int clear_list(List *list);

// функции для создания узлов
TreeNode *create_TreeNode(int value, int max_children);
Node *create_node(TreeNode *treenode);

// функции для работы с деревом
Tree *init_tree(TreeNode *root);
int add_in_tree(TreeNode *root, TreeNode *treenode);
void print_tree(Tree *tree);
void print_tree_recursive(TreeNode *node, int depth);
int delete_node(TreeNode *treenode, int key);
void delete_tree_node(TreeNode *node);
int count_width_tree(Tree *tree);
int count_width(TreeNode *root);

#endif
