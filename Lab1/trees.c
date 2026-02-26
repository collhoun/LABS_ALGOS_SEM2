#include "trees.h"
// в каждом TreeNode храним список потомков
// список List - список потомков каждого узла дерева
// каждый Node List - структура с указателем на след. элемент и указателем на потомка узла дерева

TreeNode *create_TreeNode(int value, int max_children)
{
    // создание узла дерева
    TreeNode *treenode = (TreeNode *)malloc(sizeof(TreeNode));
    if (!treenode)
    {
        fprintf(stderr, "Unable to allocate memory");
        exit(1);
    }
    treenode->key = value;
    treenode->list_of_children = init_list();
    treenode->max_children = max_children;
    return treenode;
}

Node *create_node(TreeNode *treenode)
{
    // создание узла списка потомков
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node)
    {
        fprintf(stderr, "Unable to allocate memory");
        exit(1);
    }
    node->next = NULL;
    node->child = treenode;
    return node;
}

List *init_list()
{
    // инициализация списка
    List *list = (List *)malloc(sizeof(List));
    if (!list)
    {
        fprintf(stderr, "Unable to allocate memory");
        exit(1);
    }
    list->head = NULL;
    list->len = 0;
    return list;
}

void push_front(List *list, Node *node)
{
    // добавление элемента в список на месте
    if (!list->head)
    {
        list->head = node;
    }
    else
    {
        Node *prev_head = list->head;
        list->head = node;
        node->next = prev_head;
    }
    list->len++;
}

void push_back(List *list, Node *node)
{
    // добавление элемента в конец списка
    node->next = NULL;
    if (!list->head)
    {
        list->head = node;
    }
    else
    {
        Node *current = list->head;
        while (current->next)
        {
            current = current->next;
        }
        current->next = node;
    }
    list->len++;
}

void pop_front(List *list)
{
    // удаление элемента из списка на месте
    if (!list->head)
    {
        fprintf(stderr, "Unable to pop from empty list");
        exit(1);
    }
    Node *prev_head = list->head;
    list->head = list->head->next;
    free(prev_head);
    list->len--;
}

int delete_fromlist_by_key(List *list, int key)
{
    if (!list || !list->head)
        return 0;

    Node *cur = list->head;
    Node *prev = NULL;

    while (cur)
    {
        if (cur->child && cur->child->key == key)
        {
            if (prev == NULL)
            {
                list->head = cur->next;
            }
            else
            {
                prev->next = cur->next;
            }

            free(cur);
            list->len--;
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }

    return 0;
}

int clear_list(List *list)
{
    if (!list)
    {
        return 0;
    }

    Node *cur = list->head;
    Node *next = NULL;

    while (cur)
    {
        next = cur->next;
        free(cur);
        cur = next;
    }

    list->head = NULL;
    list->len = 0;

    return 1;
}

Tree *init_tree(TreeNode *root)
{
    // инициализация дерева с непустым корнем root
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    if (!tree)
    {
        fprintf(stderr, "Unable to allocate memory");
        exit(1);
    }
    tree->root = root;
    return tree;
}

int add_in_tree(TreeNode *root, TreeNode *treenode)
{

    if (!root || !treenode)
        return 0; // дописать уведомление об ошибке

    if (root->list_of_children->len < root->max_children)
    {
        Node *node = create_node(treenode);
        if (!node)
            return 0; // дописать уведомление об ошибке
        push_front(root->list_of_children, node);
        return 1;
    }
    Node *current = root->list_of_children->head;
    while (current)
    {
        if (add_in_tree(current->child, treenode))
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void print_tree(Tree *tree)
{
    if (!tree->root)
    {
        printf("Empty tree...\n");
        exit(1);
    }
    print_tree_recursive(tree->root, 0);
}

void print_tree_recursive(TreeNode *node, int depth)
{
    if (!node)
    {
        fprintf(stderr, "Erorr empty node");
        exit(1);
    };

    if (depth > 100)
    {
        printf("  ERROR: Tree depth exceeded 100 levels\n");
        exit(1);
    }

    for (int i = 0; i < depth; i++)
    {
        printf("  ");
    }
    printf("%d\n", node->key);

    if (!node->list_of_children)
        return;

    Node *child_node = node->list_of_children->head;
    int count = 0;
    while (child_node != NULL && count < node->list_of_children->len)
    {
        if (child_node->child)
            print_tree_recursive(child_node->child, depth + 1);
        child_node = child_node->next;
        count++;
    }
}

int delete_node(TreeNode *treenode, int key)
{
    if (!treenode)
    {
        fprintf(stderr, "Erorr empty treenode");
        exit(1);
    };

    if (treenode->key == key)
    {
        fprintf(stderr, "Cannot delete the root");
        exit(1);
    };

    Node *cur = treenode->list_of_children->head;
    while (cur)
    {
        if (cur->child && cur->child->key == key)
        {
            TreeNode *child_to_delete = cur->child;
            delete_fromlist_by_key(treenode->list_of_children, key);
            delete_tree_node(child_to_delete);
            return 1;
        }

        if (delete_node(cur->child, key))
            return 1;

        cur = cur->next;
    }
    return 0;
}

void delete_tree_node(TreeNode *node)
{
    if (!node)
    {
        fprintf(stderr, "Erorr empty node");
        exit(1);
    };

    Node *child_node = node->list_of_children->head;
    while (child_node)
    {
        Node *next = child_node->next;
        delete_tree_node(child_node->child);
        free(child_node);
        child_node = next;
    }

    free(node->list_of_children);

    free(node);
}

int count_width_tree(Tree *tree)
{
    if (!tree->root)
    {
        fprintf(stderr, "Erorr empty tree");
        exit(1);
    };
    return count_width(tree->root);
}

int count_width(TreeNode *root)
{
    if (!root)
    {
        fprintf(stderr, "Erorr empty root");
        exit(1);
    };

    List *queue = init_list();
    if (!queue)
    {
        fprintf(stderr, "Erorr empty queue");
        exit(1);
    };

    Node *root_node = create_node(root);
    if (!root_node)
    {
        free(queue);
        return 0;
    }

    push_back(queue, root_node);

    int max_width = 0;

    while (queue->len > 0)
    {
        int current_level_size = queue->len;

        if (current_level_size > max_width)
            max_width = current_level_size;

        // обрабатываем все узлы на текущем уровне
        for (int i = 0; i < current_level_size; i++)
        {
            if (queue->head == NULL)
                break;

            Node *current = queue->head;
            TreeNode *tree_node = current->child;

            // добавляем всех детей текущего узла в очередь
            if (tree_node && tree_node->list_of_children)
            {
                Node *child = tree_node->list_of_children->head;
                while (child)
                {
                    Node *new_node = create_node(child->child);
                    if (new_node)
                        push_back(queue, new_node);
                    child = child->next;
                }
            }

            pop_front(queue);
        }
    }

    free(queue);
    return max_width;
}