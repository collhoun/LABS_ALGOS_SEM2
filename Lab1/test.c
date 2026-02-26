#include "trees.h"

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

void test_1_add()
{
    printf("TEST_1 TREE ADD \n");
    TreeNode *root = create_TreeNode(1, 3);
    TreeNode *node1 = create_TreeNode(1, 3);
    TreeNode *node2 = create_TreeNode(2, 4);
    TreeNode *node3 = create_TreeNode(3, 3);

    Tree *tree = init_tree(root);
    add_in_tree(root, node1);
    add_in_tree(root, node2);
    add_in_tree(node1, node3);
    int ans = 1;
    if (!is_in_tree(root, node1) || !is_in_tree(root, node2) || !is_in_tree(root, node3))
        ans = 0;
    if (ans)
        printf("All nodes added successfully!\n");
    else
        printf("Something goes wrong\n");

    print_tree(tree);
    free(tree);
    printf("TEST_1 TREE ADD FINISHED WITH SUCCESS\n\n");
}

void test_2_delete()
{
    printf("TEST_2 TREE DELETE \n");
    TreeNode *root = create_TreeNode(1, 3);
    TreeNode *node1 = create_TreeNode(1, 3);
    TreeNode *node2 = create_TreeNode(2, 4);
    TreeNode *node3 = create_TreeNode(3, 3);

    Tree *tree = init_tree(root);
    add_in_tree(root, node1);
    add_in_tree(root, node2);
    add_in_tree(node1, node3);
    printf("Tree before deletion:\n");
    print_tree(tree);
    delete_node(root, node2->key);

    int ans = 0;
    if (!is_in_tree(root, node2))
        ans = 1;
    if (ans)
        printf("Node deleted successfully\n");
    else
        printf("Error: Nodes not deleted\n");
    printf("Tree after deletion:\n");
    print_tree(tree);
    free(tree);
    printf("TEST_2 TREE DELETE FINISHED WITH SUCCESS\n");
}

void test_3_find_width()
{
    printf("TEST_3 FIND WIDTH\n");

    TreeNode *root = create_TreeNode(0, 4);
    TreeNode *node1 = create_TreeNode(1, 4);
    TreeNode *node2 = create_TreeNode(2, 4);
    TreeNode *node3 = create_TreeNode(3, 4);

    Tree *tree = init_tree(root);
    add_in_tree(root, node1);
    add_in_tree(root, node2);
    add_in_tree(node1, node3);

    print_tree(tree);
    int width = count_width_tree(tree);
    if (width == 2)
        printf("Width=%d - True\n", width);
    else
        printf("ERORR\n");
    printf("TEST_3 FINISHED");
}

void test_4()
{
    printf("TEST_4 LINEAR LIST \n");
    TreeNode *root = create_TreeNode(0, 1);
    TreeNode *node1 = create_TreeNode(1, 1);
    TreeNode *node2 = create_TreeNode(2, 1);
    TreeNode *node3 = create_TreeNode(3, 1);

    Tree *tree = init_tree(root);
    add_in_tree(root, node1);
    add_in_tree(root, node2);
    add_in_tree(root, node3);

    int ans = 1;
    if (!is_in_tree(root, node1) || !is_in_tree(root, node2) || !is_in_tree(root, node3))
        ans = 0;

    int width = count_width_tree(tree);
    if (ans && width)
        printf("Linear list created successfully!\n");
    else
        printf("Linear list creation failed\n");

    print_tree(tree);
    free(tree);
    printf("TEST_4 FINISHED\n\n");
}

void test_5()
{
    printf("TEST_5 DELETE ROOT (expect program to exit)\n");
    TreeNode *root = create_TreeNode(100, 2);
    Tree *tree = init_tree(root);

    delete_node(root, root->key);

    printf("Error: delete_node did not exit when deleting root\n");
    free(tree);
}

int main()
{
    test_1_add();
    printf("------------------------------\n");
    test_2_delete();
    printf("------------------------------\n");
    test_3_find_width();
    printf("------------------------------\n");
    test_4();
    printf("------------------------------\n");
    test_5();

    return 0;
}