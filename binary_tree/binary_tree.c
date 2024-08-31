#include <stdio.h>
#include <malloc.h>
#include "binary_tree.h"

struct node_data {
    int id;
    BINTREE_ENTRY(node_data) entry;
};

BINTREE_HEAD(bin_tree, node_data);
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

int main()
{
    BINTREE_INIT(&btree);
    bin_tree_build();
    struct node_data *root = BINTREE_ROOT(&btree);
    printf("root id: %d\n", root->id);
    struct node_data *root_lc = BINTREE_LEFT(root, entry);
    printf("root left child id: %d\n", root_lc->id);
    struct node_data *root_rc = BINTREE_RIGHT(root, entry);
    printf("root right child id: %d\n", root_rc->id);
    return 0;
}
