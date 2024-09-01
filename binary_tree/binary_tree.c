#include <stdio.h>
#include <malloc.h>
#include "binary_tree.h"

struct node_data {
    int id;
    BINTREE_ENTRY(node_data) entry;
};

BINTREE_HEAD(bin_tree, node_data);
BINTREE_GENERATE(bin_tree, node_data, entry);
struct bin_tree btree = BINTREE_INITIALIZER;

struct node_data *bin_tree_left_child_build(struct node_data *base)
{
    if (base == NULL) {
        return NULL;
    }

    struct node_data *child =
        (struct node_data *)malloc(sizeof(struct node_data));
    if (child == NULL) {
        return NULL;
    }
    child->id = base->id + 1;
    BINTREE_INSERT_AS_LC(&btree, base, child, entry);
    return child;
}

struct node_data *bin_tree_right_child_build(struct node_data *base)
{
    if (base == NULL) {
        return NULL;
    }

    struct node_data *child =
        (struct node_data *)malloc(sizeof(struct node_data));
    if (child == NULL) {
        return NULL;
    }
    child->id = base->id + 2;
    BINTREE_INSERT_AS_RC(&btree, base, child, entry);
    return child;
}

/** Example:
 *                          0
 *                         / \
 *                        1   2
 *                       / \   \
 *                      2   3   4
 */
void bin_tree_build(void)
{
    struct node_data *root =
        (struct node_data *)malloc(sizeof(struct node_data));
    if (root == NULL) {
        return;
    }
    root->id = 0;
    BINTREE_INSERT_ROOT(&btree, root);

    struct node_data *lc = bin_tree_left_child_build(root);
    struct node_data *rc = bin_tree_right_child_build(root);

    bin_tree_left_child_build(lc);
    bin_tree_right_child_build(lc);
    bin_tree_right_child_build(rc);
}

void preorder_traversal_r(struct node_data *node)
{
    if (node == NULL) {
        return;
    }
    printf("id: %d\n", node->id);

    preorder_traversal_r(node->entry.bte_left);
    preorder_traversal_r(node->entry.bte_right);
}

struct node_data *inorder_traversal_begin()
{
    struct node_data *node = NULL;
    struct node_data *parent = NULL;
    // traverse along left branch until the leaf
    node = BINTREE_ROOT(&btree);

    while (node) {
        parent = node;
        node = BINTREE_LEFT(node, entry);
    }

    return parent;
}

struct node_data *inorder_traversal_next(struct node_data *node)
{
    if (BINTREE_RIGHT(node, entry)) {
        node = BINTREE_RIGHT(node, entry);
        // traverse along left branch until the leaf
        while (BINTREE_LEFT(node, entry)) {
            node = BINTREE_LEFT(node, entry);
        }
    } else {
        // backtrack the parent of the left child
        if (BINTREE_PARENT(node, entry) &&
            node == BINTREE_LEFT(BINTREE_PARENT(node, entry), entry)) {
            node = BINTREE_PARENT(node, entry);
        } else {
            // backtrack the ancestor of the right child where is not traversed
            while (BINTREE_PARENT(node, entry) &&
                   node == BINTREE_RIGHT(BINTREE_PARENT(node, entry), entry)) {
                node = BINTREE_PARENT(node, entry);
            }
            node = BINTREE_PARENT(node, entry);
        }
    }

    return node;
}

void inorder_traversal_iter(void) {
    struct node_data *node = NULL;

    BINTREE_INORDER_FOREACH(bin_tree, &btree, node) {
        printf("id: %d\n", node->id);
    }
}

void inorder_traversal_r(struct node_data *node)
{
    if (node == NULL) {
        return;
    }

    inorder_traversal_r(node->entry.bte_left);
    printf("id: %d\n", node->id);
    inorder_traversal_r(node->entry.bte_right);
}

void inorder_traversal(void) {
    struct node_data *root = BINTREE_ROOT(&btree);

    printf("inorder recursion traversal: \n");
    inorder_traversal_r(root);

    printf("inorder iterator traversal: \n");
    inorder_traversal_iter();
}

void postorder_traversal_r(struct node_data *node)
{
    if (node == NULL) {
        return;
    }

    postorder_traversal_r(node->entry.bte_left);
    postorder_traversal_r(node->entry.bte_right);
    printf("id: %d\n", node->id);
}

void bin_tree_traversal_r(void)
{
    struct node_data *root = BINTREE_ROOT(&btree);

    printf("preorder recursion traversal: \n");
    preorder_traversal_r(root);

    printf("inorder traversal: \n");
    inorder_traversal();

    printf("postorder recursion traversal: \n");
    postorder_traversal_r(root);
}

int main()
{
    BINTREE_INIT(&btree);
    bin_tree_build();
    bin_tree_traversal_r();
    return 0;
}
