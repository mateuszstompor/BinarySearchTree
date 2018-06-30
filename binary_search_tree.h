//
//  binary_tree.h
//  test_C
//
//  Created by Mateusz Stompór on 19/06/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

//  POLICY
//  ALLOC   -   there is no verification if the pointer which was passed to one of the functions is NULL
//  RELEASE -   there is no verification if the pointer is different than null, pointer is not set to null after deallocation as well

#define usually(ptr) __builtin_expect(!!(ptr), 1)

#define rarely(ptr) __builtin_expect(!!(ptr), 0)

// do not forget about data alignment
#define binary_search_tree_node(T)\
struct binary_search_tree_node_##T {\
    struct binary_search_tree_node_##T * left;\
    struct binary_search_tree_node_##T * right;\
    struct binary_search_tree_node_##T * parent;\
    T data;\
}\

#define binary_search_tree_node_alloc(T, node_ptr, l, r, p, v) ({\
    node_ptr = (struct binary_search_tree_node_##T *)malloc(sizeof(struct binary_search_tree_node_##T));\
    if(usually(node_ptr)) {\
        node_ptr->right = r;\
        node_ptr->left = l;\
        node_ptr->parent = p;\
        node_ptr->data = v;\
    }\
})\

#define binary_search_tree_node_release(T, node_ptr) ({\
    if(node_ptr) {\
        free(node_ptr);\
        node_ptr = NULL;\
    }\
})\

#define binary_search_tree_iterator(T)\
struct binary_search_tree_iterator_##T {\
    struct binary_search_tree_node_##T * current;\
}\

#define binary_search_tree_iterator_alloc(T, iterator_ptr) ({\
    iterator_ptr = (struct binary_search_tree_iterator_##T *)malloc(sizeof(struct binary_search_tree_iterator_##T));\
})

#define binary_search_tree_iterator_not_equal(T, lhs_ptr, rhs_ptr) lhs_ptr->current != rhs_ptr->current

#define binary_search_tree_iterator_equal(T, lhs_ptr, rhs_ptr) lhs_ptr->current == rhs_ptr->current

#define binary_search_tree_iterator_next(T, iterator_ptr) ({\
    if(iterator_ptr->current != NULL){\
        if(iterator_ptr->current->right != NULL) {\
            iterator_ptr->current = iterator_ptr->current->right;\
            while(iterator_ptr->current->left != NULL)\
                iterator_ptr->current = iterator_ptr->current->left;\
        }else {\
            while(iterator_ptr->current->parent != NULL && iterator_ptr->current == iterator_ptr->current->parent->right)\
                iterator_ptr->current = iterator_ptr->current->parent;\
            if(iterator_ptr->current != NULL)\
                iterator_ptr->current = iterator_ptr->current->parent;\
        }\
    }\
})

#define binary_search_tree_iterator_release(T, iterator_ptr) ({\
    if(iterator_ptr) {\
        free(iterator_ptr);\
        iterator_ptr = NULL;\
    }\
})

#define binary_search_tree(T)\
binary_search_tree_node(T);\
binary_search_tree_iterator(T);\
struct binary_search_tree_##T {\
    size_t size;\
    struct binary_search_tree_node_##T * root;\
    struct binary_search_tree_node_##T * min;\
    struct binary_search_tree_node_##T * max;\
}\

#define binary_search_tree_alloc(T, tree) ({\
    tree = (struct binary_search_tree_##T *)malloc(sizeof(struct binary_search_tree_##T));\
    if(usually(tree)) {\
        tree->size = 0;\
        tree->root = NULL;\
        tree->min = NULL;\
        tree->max = NULL;\
    }\
})\

// c - current
#define binary_search_tree_release(T, tree_ptr) ({\
    if(tree_ptr) {\
        if(tree_ptr->root) {\
            struct binary_search_tree_node_##T * c = tree_ptr->min;\
            assert(c != NULL);\
            if(c == tree_ptr->root && c->right != NULL) {\
                c = c->right;\
                while(c->right != NULL || c->left != NULL)\
                    c = c->left != NULL ? c->left : c->right;\
            }\
            assert(c != NULL);\
            while(c != NULL) {\
                struct binary_search_tree_node_##T * p = c->parent;\
                if(p != NULL) {\
                    if(p->right == c){\
                        binary_search_tree_node_release(T, c);\
                    } else {\
                        binary_search_tree_node_release(T, c);\
                        c = p->right;\
                        if(c) {\
                            while(c->right != NULL || c->left != NULL)\
                                c = c->left != NULL ? c->left : c->right;\
                        }\
                    }\
                } else {\
                    binary_search_tree_node_release(T, c);\
                }\
                c = p;\
            }\
        }\
        free(tree_ptr);\
        tree_ptr = NULL;\
    }\
})\

#define binary_search_tree_insert(T, tree, value) ({\
    if (usually(tree->root != NULL)) {\
        binary_search_tree_insert_to_non_empty(T, tree, value);\
    } else {\
        binary_search_tree_insert_to_empty(T, tree, value);\
    }\
})\

#define binary_search_tree_insert_to_empty(T, tree, value) ({\
    binary_search_tree_node_alloc(T, tree->root, NULL, NULL, NULL, value);\
    tree->min = tree->root;\
    tree->max = tree->root;\
    if(tree->root)\
        tree->size += 1;\
})\

// n - next, c - current, t - temporary value, v - value
#define binary_search_tree_insert_to_non_empty(T, tree, value) ({\
    struct binary_search_tree_node_##T * c = tree->root;\
    struct binary_search_tree_node_##T * n = binary_search_tree_##T##_is_greater(value, tree->root->data) ? tree->root->right : tree->root->left;\
    while(n != NULL) {\
        c = n;\
        n = binary_search_tree_##T##_is_greater(value, n->data) ? n->right : n->left;\
    }\
    struct binary_search_tree_node_##T ** t = binary_search_tree_##T##_is_greater(value, c->data) ? &(c->right) : &(c->left);\
    binary_search_tree_node_alloc(T, (*t), NULL, NULL, c, value);\
    if(binary_search_tree_##T##_is_greater(value, tree->max->data)) {\
        tree->max=(*t);\
    } else if (binary_search_tree_##T##_is_greater(tree->min->data, value)) {\
        tree->min=(*t);\
    }\
    tree->size += 1;\
})\

#define binary_search_tree_size(tree_ptr) tree_ptr->size

#define binary_search_tree_begin(T, tree_ptr, iterator_ptr) ({\
    iterator_ptr->current = tree_ptr->min;\
})\

#define binary_search_tree_end(T, tree_ptr, iterator_ptr) ({\
    iterator_ptr->current = NULL;\
})\

#ifdef __cplusplus
}
#endif
