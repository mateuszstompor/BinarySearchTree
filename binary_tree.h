//
//  binary_tree.h
//  test_C
//
//  Created by Mateusz Stompór on 19/06/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <stdlib.h>

// do not forget about data alignment
#define bt_node(T)\
struct bt_node_##T {\
    struct bt_node_##T * left;\
    struct bt_node_##T * right;\
    struct bt_node_##T * parent;\
    T data;\
}\

#define bt_node_alloc(T, bt_node_ptr, l, r, p, v) ({\
    bt_node_ptr = malloc(sizeof(struct bt_node_##T));\
    bt_node_ptr->right = NULL;\
    bt_node_ptr->left = l;\
    bt_node_ptr->parent = p;\
    bt_node_ptr->data = v;\
})\

#define bt_node_release(T, bt_node_ptr) ({\
    free(bt_node_ptr);\
})\

#define binary_tree(T)\
struct binary_tree_##T {\
    size_t size;\
    bt_node(T) * root;\
    struct bt_node_##T * min;\
    struct bt_node_##T * max;\
}\

#define binary_tree_alloc(T, tree) ({\
    tree = malloc(sizeof(struct binary_tree_##T));\
    tree->size = 0;\
    tree->root = NULL;\
    tree->min = NULL;\
    tree->max = NULL;\
})\

// c - current
#define binary_tree_release(T, tree_ptr) ({\
    struct bt_node_##T * c = tree_ptr->min;\
    struct bt_node_##T * max = tree_ptr->max;\
    while(c != max) {\
        if(c->parent != NULL && c->parent->left == c) {\
            c = c->parent;\
            bt_node_release(T, c->left);\
            if(c->right != NULL) {\
                c = c->right;\
                while(c->left != NULL) {\
                    c = c->left;\
                }\
            }\
        } else {\
            do {\
                c = c->parent;\
                bt_node_release(T, c->right);\
            } while (c->parent != NULL || c != c->parent->right);\
        }\
    }\
    while(c != NULL) {\
        bt_node_release(T, c);\
        c = c->parent;\
    }\
    free(tree_ptr);\
})\

#define binary_tree_insert(T, tree, value) ({\
    if (tree->root == NULL) {\
        binary_tree_insert_to_empty(T, tree, value);\
    } else {\
        binary_tree_insert_to_non_empty(T, tree, value);\
    }\
})\

#define binary_tree_insert_to_empty(T, tree, value) ({\
    bt_node_alloc(T, tree->root, NULL, NULL, NULL, value);\
    tree->size += 1;\
    tree->min = tree->root;\
    tree->max = tree->root;\
})\

// n - next, c - current, t - temporary value
#define binary_tree_insert_to_non_empty(T, tree, value) ({\
    struct bt_node_##T * c = tree->root;\
    struct bt_node_##T * n = binary_tree_##T##_is_greater(value, tree->root->data) ? tree->root->right : tree->root->left;\
    while(n != NULL) {\
        c = n;\
        n = binary_tree_##T##_is_greater(value, n->data) ? n->right : n->left;\
    }\
    struct bt_node_##T ** t = binary_tree_##T##_is_greater(value, c->data) ? &(c->right) : &(c->left);\
    bt_node_alloc(T, (*t), NULL, NULL, c, value);\
    if(binary_tree_##T##_is_greater(value, tree->max->data)) {\
        tree->max=(*t);\
    } else if (binary_tree_##T##_is_greater(tree->min->data, value)) {\
        tree->min=(*t);\
    }\
    tree->size += 1;\
})\
