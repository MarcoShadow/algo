#ifndef __DSA_BINARY_TREE_H__
#define __DSA_BINARY_TREE_H__

#define BINTREE_HEAD(name, type)                                               \
    struct name {                                                              \
        struct type *bth_root; /* root of the tree */                          \
    }

#define BINTREE_ENTRY(type)                                                    \
    struct {                                                                   \
        struct type *parent;                                                   \
        struct type *left;                                                     \
        struct type *right;                                                    \
    }

// clang-format off
#define BINTREE_INITIALIZER    { NULL }
// clang-format on

#define BINTREE_INIT(head)                                                     \
    do {                                                                       \
        (head)->bth_root = NULL;                                               \
    } while (0)

#define BINTREE_ROOT(head)         (head)->bth_root
#define BINTREE_LEFT(base, field)  (base)->field.left
#define BINTREE_RIGHT(base, field) (base)->field.right

#define BINTREE_INSERT_ROOT(head, root)                                        \
    do {                                                                       \
        if ((head)->bth_root == NULL) {                                        \
            (head)->bth_root = root;                                           \
        }                                                                      \
    } while (0)

#define BINTREE_INSERT_AS_LC(head, base, lc, field)                            \
    do {                                                                       \
        (base)->field.left = lc;                                               \
        (lc)->field.parent = base;                                             \
    } while (0)

#define BINTREE_INSERT_AS_RC(head, base, rc, field)                            \
    do {                                                                       \
        (base)->field.right = rc;                                              \
        (rc)->field.parent = base;                                             \
    } while (0)

#endif
