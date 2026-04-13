#include "tree.h"

static char *my_strdup(const char *s)
{
    size_t len = strlen(s) + 1;
    char *dup = malloc(len);
    if (dup)
    {
        memcpy(dup, s, len);
    }
    return dup;
}

static TreeNode NIL_NODE = {NULL, 0, BLACK, &NIL_NODE, &NIL_NODE, &NIL_NODE};
TreeNode *NIL = &NIL_NODE;

TreeNode *create_node(char *key, int value)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (!node)
        return NULL;
    node->key = my_strdup(key);
    node->value = value;
    node->color = RED;
    node->left = NIL;
    node->right = NIL;
    node->parent = NIL;
    return node;
}

RedBlackTree *create_tree()
{
    RedBlackTree *tree = (RedBlackTree *)malloc(sizeof(RedBlackTree));
    if (!tree)
        return NULL;
    tree->root = NIL;
    return tree;
}

void insert(RedBlackTree *tree, char *key, int value)
{
    TreeNode *new_node = create_node(key, value);
    if (!new_node)
        return;
    TreeNode *parent = NIL;
    TreeNode *current = tree->root;

    while (current != NIL)
    {
        parent = current;
        if (strcmp(new_node->key, current->key) < 0)
            current = current->left;
        else
            current = current->right;
    }

    new_node->parent = parent;
    if (parent == NIL)
        tree->root = new_node; // дерево было пустое
    else if (strcmp(new_node->key, parent->key) < 0)
        parent->left = new_node;
    else
        parent->right = new_node;

    insert_fix(tree, new_node);
}

void left_rotate(RedBlackTree *tree, TreeNode *current)
{
    TreeNode *right_child = current->right;
    current->right = right_child->left;

    if (right_child->left != NIL)
        right_child->left->parent = current;

    right_child->parent = current->parent;

    if (current->parent == NIL)
        tree->root = right_child;
    else if (current == current->parent->left)
        current->parent->left = right_child;
    else
        current->parent->right = right_child;

    right_child->left = current;
    current->parent = right_child;
}

void right_rotate(RedBlackTree *tree, TreeNode *current)
{
    TreeNode *left_child = current->left;
    current->left = left_child->right;

    if (left_child->right != NIL)
        left_child->right->parent = current;

    left_child->parent = current->parent;

    if (current->parent == NIL)
        tree->root = left_child;
    else if (current == current->parent->right)
        current->parent->right = left_child;
    else
        current->parent->left = left_child;

    left_child->right = current;
    current->parent = left_child;
}

void insert_fix(RedBlackTree *tree, TreeNode *node)
{
    // пока два красных узла подряд
    while (node->parent->color == RED)
    {
        TreeNode *grandfather = node->parent->parent;

        if (node->parent == grandfather->left)
        {
            TreeNode *uncle = grandfather->right;

            if (uncle->color == RED)
            {
                // красный дядя - просто перекрашиваем
                node->parent->color = BLACK;
                uncle->color = BLACK;
                grandfather->color = RED;
                node = grandfather; // двигаемся вверх
            }
            else
            {
                // случаи 2 и 3: черный дядя - нужны повороты
                if (node == node->parent->right)
                {
                    // случай 2:
                    // Левый поворот для папы
                    node = node->parent;
                    left_rotate(tree, node);
                }
                // случай 3:
                // правый поворот для деда
                node->parent->color = BLACK;
                grandfather->color = RED;
                right_rotate(tree, grandfather);
            }
        }
        else
        {
            // ЗЕРКАЛЬНЫЕ СЛУЧАИ
            TreeNode *uncle = grandfather->left;

            if (uncle->color == RED)
            {
                // случай 1: красный дядя
                node->parent->color = BLACK;
                uncle->color = BLACK;
                grandfather->color = RED;
                node = grandfather;
            }
            else
            {
                // случаи 2 и 3: черный дядя
                if (node == node->parent->left)
                {

                    node = node->parent;
                    right_rotate(tree, node);
                }
                // левый поворот для деда
                node->parent->color = BLACK;
                grandfather->color = RED;
                left_rotate(tree, grandfather);
            }
        }
    }
    tree->root->color = BLACK; // корень всегда черный
}

void delete_fix(RedBlackTree *tree, TreeNode *node)
{
    // node несет в себе "двойную черноту". балансируем, пока не дойдем до корня
    // или пока не сможем сбросить эту черноту на красный узел
    while (node != tree->root && node->color == BLACK)
    {
        TreeNode *parent = node->parent;

        if (node == parent->left)
        {
            TreeNode *brother = parent->right;

            // случай 1: Брат красный
            if (brother->color == RED)
            {
                brother->color = BLACK;
                parent->color = RED;
                left_rotate(tree, parent);
                brother = parent->right; // после поворота брат сменился
            }

            // случай 2: брат черный и оба его ребенка черные
            if (brother->left->color == BLACK && brother->right->color == BLACK)
            {
                brother->color = RED; // забираем черноту у брата
                node = parent;        // переводим "двойную черноту" на родителя и идем вверх
            }
            else
            {
                // случай 3: брат черный, правый ребенок черный (а левый красный)
                if (brother->right->color == BLACK)
                {
                    brother->left->color = BLACK;
                    brother->color = RED;
                    right_rotate(tree, brother);
                    brother = parent->right; // Обновляем брата
                }

                // случай 4: Брат черный, правый ребенок красный
                brother->color = parent->color;
                parent->color = BLACK;
                brother->right->color = BLACK;
                left_rotate(tree, parent);

                // дерево сбалансировано, выходим из цикла
                node = tree->root;
            }
        }
        else
        {
            // ЗЕРКАЛЬНЫЕ СЛУЧАИ
            TreeNode *brother = parent->left;

            // случай 1
            if (brother->color == RED)
            {
                brother->color = BLACK;
                parent->color = RED;
                right_rotate(tree, parent);
                brother = parent->left;
            }

            // случай 2
            if (brother->right->color == BLACK && brother->left->color == BLACK)
            {
                brother->color = RED;
                node = parent;
            }
            else
            {
                // случай 3
                if (brother->left->color == BLACK)
                {
                    brother->right->color = BLACK;
                    brother->color = RED;
                    left_rotate(tree, brother);
                    brother = parent->left;
                }

                // случай 4
                brother->color = parent->color;
                parent->color = BLACK;
                brother->left->color = BLACK;
                right_rotate(tree, parent);

                node = tree->root;
            }
        }
    }
    // если node стал красным, мы просто красим его в черный, скидывая "двойную черноту"
    node->color = BLACK;
}

void delete_tree_node(RedBlackTree *tree, char *key)
{
    if (!tree)
        return;
    TreeNode *root = tree->root;
    if (!root)
        return;
    TreeNode *current = root;
    while (current != NIL && strcmp(key, current->key) != 0)
    {
        if (strcmp(key, current->key) > 0)
            current = current->right;
        else
            current = current->left;
    }

    if (current == NIL)
        return;

    // удаляем узел с двумя потомками как в bst
    if (current->left != NIL && current->right != NIL)
    {

        TreeNode *successor = current->right;
        while (successor->left != NIL)
        {
            successor = successor->left;
        }

        free(current->key);
        current->key = my_strdup(successor->key);
        current->value = successor->value;

        // теперь наша задача - удалить не первоначальный узел, а преемника
        // просто переводим указатель current на преемника, а потом current попадет в нижние условия и удалит его
        current = successor;
    }

    if (current->left == NIL && current->right == NIL)
    {
        // простой случай - удаляем красный лист
        if (current->color == RED)
        {
            if (current->parent->left == current)
                current->parent->left = NIL;
            else
                current->parent->right = NIL;
            free(current->key);
            free(current);
        }
        else
        {
            // удаление черного листа
            if (current->parent == NIL)
            {
                tree->root = NIL; // удаляем последний элемент (корень)
                free(current->key);
                free(current);
            }
            else
            {
                // 1. Трюк с NIL: Балансировщик будет стартовать от узла NIL (т.к. у current нет детей).
                //  нужно, чтобы внутри delete_fix() вызов node->parent выдал родителя current.
                NIL->parent = current->parent;

                // 2. отсвязываем удаляемый узел (ставим NIL на его место ДО балансировки)
                if (current == current->parent->left)
                    current->parent->left = NIL;
                else
                    current->parent->right = NIL;

                delete_fix(tree, NIL);
                NIL->parent = NIL;
                free(current->key);
                free(current);
            }
        }
    }
    // удаляем черный узел с одним красным потомком
    else if (current->left != NIL && current->right == NIL)
    {
        if (current->color == BLACK && current->left->color == RED)
        {
            if (current->parent == NIL)
            {
                tree->root = current->left; // Новый корень дерева
            }
            else
            {
                if (current->parent->left == current)
                    current->parent->left = current->left;
                else
                    current->parent->right = current->left;
            }
            current->left->parent = current->parent;
            current->left->color = BLACK;
            free(current->key);
            free(current);
        }
    }
    // удаляем черный узел с одним красным потомком
    else if (current->left == NIL && current->right != NIL)
    {
        if (current->color == BLACK && current->right->color == RED)
        {
            if (current->parent == NIL)
            {
                tree->root = current->right; // Новый корень дерева
            }
            else
            {
                if (current->parent->right == current)
                    current->parent->right = current->right;
                else
                    current->parent->left = current->right;
            }
            current->right->parent = current->parent;
            current->right->color = BLACK;
            free(current->key);
            free(current);
        }
    }
}

void print_tree_recursive(TreeNode *node, int depth)
{
    if (node == NIL)
        return;

    print_tree_recursive(node->right, depth + 1);

    for (int i = 0; i < depth; i++)
    {
        printf("    ");
    }
    printf("%s (%s,%d)\n", node->key, node->color == RED ? "RED" : "BLACK", node->value);

    print_tree_recursive(node->left, depth + 1);
}

void print_tree(TreeNode *root)
{
    print_tree_recursive(root, 0);
}

int find(RedBlackTree *tree, char *key)
{
    TreeNode *current = tree->root;
    while (current != NIL && strcmp(key, current->key) != 0)
    {
        if (strcmp(key, current->key) < 0)
            current = current->left;
        else
            current = current->right;
    }
    if (current != NIL)
        return current->value;
    else
        return -1;
}
