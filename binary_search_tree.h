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
#include <stdlib.h>

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
    node_ptr->right = NULL;\
    node_ptr->left = l;\
    node_ptr->parent = p;\
    node_ptr->data = v;\
})\

#define binary_search_tree_node_release(T, node_ptr) ({\
    free(node_ptr);\
})\

#define binary_search_tree_iterator(T)\
struct binary_search_tree_iterator_##T {\
    struct binary_search_tree_node_##T * current;\
}\

#define binary_search_tree_iterator_alloc(T, iterator_ptr) ({\
    iterator_ptr = (struct binary_search_tree_iterator_##T *)malloc(sizeof(struct binary_search_tree_iterator_##T));\
})
  
#define binary_search_tree_iterator_next(T, iterator_ptr) ({\
    if(iterator_ptr->current != NULL){\
        if(iterator_ptr->current->right != NULL) {\
            iterator_ptr->current = iterator_ptr->current->right;\
            while(iterator_ptr->current->left != NULL) {\
                iterator_ptr->current = iterator_ptr->current->left;\
            }\
        }else {\
            while(iterator_ptr->current->parent != NULL && iterator_ptr->current == iterator_ptr->current->parent->right){\
                iterator_ptr->current = iterator_ptr->current->parent;\
            }\
            if(iterator_ptr->current != NULL) {\
                iterator_ptr->current = iterator_ptr->current->parent;\
            }\
        }\
    }\
})
    
#define binary_search_tree_iterator_release(T, iterator_ptr) ({\
    free(iterator_ptr);\
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
    tree->size = 0;\
    tree->root = NULL;\
    tree->min = NULL;\
    tree->max = NULL;\
})\

// c - current
#define binary_search_tree_release(T, tree_ptr) ({\
    struct binary_search_tree_node_##T * c = tree_ptr->min;\
    struct binary_search_tree_node_##T * max = tree_ptr->max;\
    while(c != max) {\
        if(c->parent != NULL && c->parent->left == c) {\
            c = c->parent;\
            binary_search_tree_node_release(T, c->left);\
            if(c->right != NULL) {\
                c = c->right;\
                while(c->left != NULL) {\
                    c = c->left;\
                }\
            }\
        } else {\
            do {\
                c = c->parent;\
                binary_search_tree_node_release(T, c->right);\
            } while (c->parent != NULL || c != c->parent->right);\
        }\
    }\
    while(c != NULL) {\
        binary_search_tree_node_release(T, c);\
        c = c->parent;\
    }\
    free(tree_ptr);\
})\

#define binary_search_tree_insert(T, tree, value) ({\
    if (tree->root == NULL) {\
        binary_search_tree_insert_to_empty(T, tree, value);\
    } else {\
        binary_search_tree_insert_to_non_empty(T, tree, value);\
    }\
})\

#define binary_search_tree_insert_to_empty(T, tree, value) ({\
    binary_search_tree_node_alloc(T, tree->root, NULL, NULL, NULL, value);\
    tree->size += 1;\
    tree->min = tree->root;\
    tree->max = tree->root;\
})\

// n - next, c - current, t - temporary value
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

#define binary_search_tree_begin(T, tree_ptr, iterator_ptr) ({\
    iterator_ptr->current = tree_ptr->min;\
})\

#define binary_search_tree_end(T, tree_ptr, iterator_ptr) ({\
    iterator_ptr->current = NULL;\
})\
    
#ifdef __cplusplus
}
#endif
