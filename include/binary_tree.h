#ifndef __DSA_BINARY_TREE_H__
#define __DSA_BINARY_TREE_H__

#define BINTREE_HEAD(name, type)                                               \
    struct name {                                                              \
        struct type *bth_root; /* root of the tree */                          \
    }

#define BINTREE_ENTRY(type)                                                    \
    struct {                                                                   \
        struct type *bte_parent;                                               \
        struct type *bte_left;                                                 \
        struct type *bte_right;                                                \
    }

// clang-format off
#define BINTREE_INITIALIZER    { NULL }
// clang-format on

#define BINTREE_INIT(head)                                                     \
    do {                                                                       \
        (head)->bth_root = NULL;                                               \
    } while (0)

#define BINTREE_ROOT(head)          (head)->bth_root
#define BINTREE_LEFT(node, field)   (node)->field.bte_left
#define BINTREE_RIGHT(node, field)  (node)->field.bte_right
#define BINTREE_PARENT(node, field) (node)->field.bte_parent

#define BINTREE_INSERT_ROOT(head, root)                                        \
    do {                                                                       \
        if ((head)->bth_root == NULL) {                                        \
            (head)->bth_root = root;                                           \
        }                                                                      \
    } while (0)

#define BINTREE_INSERT_AS_LC(head, parent, lc, field)                          \
    do {                                                                       \
        (parent)->field.bte_left = lc;                                         \
        (lc)->field.bte_parent = parent;                                       \
    } while (0)

#define BINTREE_INSERT_AS_RC(head, parent, rc, field)                          \
    do {                                                                       \
        (parent)->field.bte_right = rc;                                        \
        (rc)->field.bte_parent = parent;                                       \
    } while (0)

#define BINTREE_GENERATE_INORDER_BEGIN(name, type, field)                      \
    struct type *name##_INORDER_BEGINE(struct name *head)                      \
    {                                                                          \
        struct type *tmp = NULL;                                               \
        struct type *parent = NULL;                                            \
        /* traverse along left branch until the leaf */                        \
        tmp = BINTREE_ROOT(head);                                              \
                                                                               \
        while (tmp) {                                                          \
            parent = tmp;                                                      \
            tmp = BINTREE_LEFT(tmp, field);                                    \
        }                                                                      \
                                                                               \
        return parent;                                                         \
    }

#define BINTREE_GENERATE_INORDER_NEXT(name, type, field)                       \
    struct type *name##_INORDER_NEXT(struct type *node)                        \
    {                                                                          \
        if (BINTREE_RIGHT(node, field)) {                                      \
            node = BINTREE_RIGHT(node, field);                                 \
            /* traverse along left branch until the leaf */                    \
            while (BINTREE_LEFT(node, field)) {                                \
                node = BINTREE_LEFT(node, field);                              \
            }                                                                  \
        } else {                                                               \
            /* backtrack the parent of the left child */                       \
            if (BINTREE_PARENT(node, field) &&                                 \
                node == BINTREE_LEFT(BINTREE_PARENT(node, field), field)) {    \
                node = BINTREE_PARENT(node, field);                            \
            } else {                                                           \
                /* backtrack the ancestor of the right child where is not      \
                 * traversed */                                                \
                while (BINTREE_PARENT(node, field) &&                          \
                       node == BINTREE_RIGHT(BINTREE_PARENT(node, field),      \
                                             field)) {                         \
                    node = BINTREE_PARENT(node, field);                        \
                }                                                              \
                node = BINTREE_PARENT(node, field);                            \
            }                                                                  \
        }                                                                      \
                                                                               \
        return node;                                                           \
    }

#define BINTREE_GENERATE(name, type, field)                                    \
    BINTREE_GENERATE_INORDER_BEGIN(name, type, field)                          \
    BINTREE_GENERATE_INORDER_NEXT(name, type, field)

#define BINTREE_INORDER_BEGIN(name, head) name##_INORDER_BEGINE(head)
#define BINTREE_INORDER_NEXT(name, node)  name##_INORDER_NEXT(node)

#define BINTREE_INORDER_FOREACH(name, head, var)                               \
    for (var = BINTREE_INORDER_BEGIN(name, head); var != NULL;                 \
         var = BINTREE_INORDER_NEXT(name, var))

#endif
