#include "trees.h"
// в каждом TreeNode храним список потомков
// список List - список потомков каждого узла дерева
// каждый Node List - структура с указателем на след. элемент и указателем на потомка узла дерева

// доделать консоль с вводом выводом

TreeNode *create_TreeNode(int value, int max_children)
{
    // создание узла дерева
    TreeNode *treenode = (TreeNode *)malloc(sizeof(TreeNode));
    if (!treenode)
    {
        fprintf(stderr, "Unable to allocate memory");
        return NULL;
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
        return NULL;
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
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
    return list;
}

void push_front(List *list, Node *node)
{
    // добавление элемента в начало списка
    if (!list->head)
    {
        list->head = node;
        list->tail = node;
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
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }
    list->len++;
}

int pop_front(List *list)
{
    // удаление элемента из списка на месте
    if (!list->head)
    {
        fprintf(stderr, "Unable to pop from empty list");
        return 0;
    }
    Node *prev_head = list->head;
    list->head = list->head->next;
    if (list->head == NULL)
    {
        list->tail = NULL;
    }
    free(prev_head);
    list->len--;
    return 1;
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
            if (cur == list->tail)
            {
                list->tail = prev;
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
    list->tail = NULL;
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
        return NULL;
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
        return;
    }
    print_tree_recursive(tree->root, 0);
}

void print_tree_recursive(TreeNode *node, int depth)
{
    if (!node)
    {
        fprintf(stderr, "Erorr empty node");
        return;
    };

    if (depth > 100)
    {
        printf("  ERROR: Tree depth exceeded 100 levels\n");
        return;
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
        return 0;
    };

    if (treenode->key == key)
    {
        fprintf(stderr, "Cannot delete the root");
        return 0;
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
        return;
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
        return 0;
    };
    return count_width(tree->root);
}

int count_width(TreeNode *root)
{
    if (!root)
    {
        fprintf(stderr, "Erorr empty root");
        return 0;
    };

    List *queue = init_list();
    if (!queue)
    {
        fprintf(stderr, "Erorr empty queue");
        return 0;
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

// вспомогательная функция для проверки наличия узла в дереве
int is_in_tree(TreeNode *root, TreeNode *treenode)
{
    if (!root || !treenode)
        return 0;

    if (root == treenode || root->key == treenode->key)
        return 1;

    if (!root->list_of_children)
        return 0;

    Node *cur = root->list_of_children->head;
    while (cur)
    {
        if (is_in_tree(cur->child, treenode))
            return 1;
        cur = cur->next;
    }
    return 0;
}

void interactive_mode()
{
    int choice = 0;
    Tree *tree = NULL;
    while (choice != 6)
    {

        printf("Choose an option:\n");
        printf("1. Create a tree\n");
        printf("2. Add a node\n");
        printf("3. Print the tree\n");
        printf("4. Delete a node\n");
        printf("5. Count tree width\n");
        printf("6. Exit\n");
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("Enter root key and max children: ");
            int root_key, max_children;
            scanf("%d %d", &root_key, &max_children);
            TreeNode *root = create_TreeNode(root_key, max_children);
            tree = init_tree(root);
        }
        else if (choice == 2)
        {
            printf("Enter key and max children: ");
            int new_node_key, max_children;
            scanf("%d %d", &new_node_key, &max_children);
            TreeNode *new_node = create_TreeNode(new_node_key, max_children);
            if (!tree)
            {
                fprintf(stderr, "Tree not init.\n");
                return;
            }
            add_in_tree(tree->root, new_node);
        }
        else if (choice == 3)
        {
            if (!tree)
            {
                fprintf(stderr, "Tree is not init.\n");
                return;
            }
            printf("---------------------------------\n");
            print_tree(tree);
            printf("---------------------------------\n");
        }
        else if (choice == 4)
        {
            printf("Enter key of node to delete: ");
            int key;
            scanf("%d", &key);
            if (!tree)
            {
                fprintf(stderr, "Tree is not init.\n");
                return;
            }
            delete_node(tree->root, key);
        }
        else if (choice == 5)
        {
            if (!tree)
            {
                fprintf(stderr, "Tree is not init.\n");
                return;
            }
            int width = count_width(tree->root);
            printf("Tree width: %d\n", width);
        }
        else if (choice == 6)
        {
            printf("Exiting...\n");
            exit(0);
        }
    }
}
