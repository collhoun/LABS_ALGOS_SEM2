#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

// Forward declarations
typedef struct Node Node;
typedef struct TreeNode TreeNode;

typedef struct Node
{
    // узел односвязного списка
    TreeNode *child;
    Node *next;
} Node;

typedef struct List
{
    // сам односвязный список
    Node *head;
    Node *tail;
    int len;
} List;

// функции для работы со списком
List *init_list();
void push_front(List *list, Node *node);
void push_back(List *list, Node *node);
int pop_front(List *list);
int delete_fromlist_by_key(List *list, int key);
int clear_list(List *list);

// функции для создания узлов списка
Node *create_node(TreeNode *treenode);

#endif
