# BinarySearchTree &middot; [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) [![Build Status](https://travis-ci.org/mateuszstompor/BinarySearchTree.svg?branch=master)](https://travis-ci.org/mateuszstompor/BinarySearchTree)

The aim of this repository is to demonstrate how a generic data structure in pure C can be implemented.
I investigated here an approach that utilizes macros.
It seems a convenient way to make a data structure reusable keeping strong typing at the same time.
To find out more information about the topic I suggest using [official documentation](https://gcc.gnu.org/onlinedocs/cpp/Macros.html)

## About the data structure
> binary search tree (BST), also called an ordered or sorted binary tree, is a rooted binary tree data structure with the key of each internal node being greater than all the keys in the respective node's left subtree and less than the ones in its right subtree

-- <cite>Wikipedia</cite>


## Declaration
To start using the tree of a certain type you must perform two steps. 
`<type>` in the examples below refers to the actual C type, such as `int`, `float` or any other complex type that you define.
1. Declare a tree of a certain type
```c
binary_search_tree(<type>);
```
2. Declare comparison macro
```c
#define binary_search_tree_<type>_is_greater(a, b) <bool>
```

## Example - Insertion
```c

#include <binary_search_tree.h>

typedef struct Point2D {
    float x;
    float y;
} Point2D;

binary_search_tree(Point2D);

// Define how elements should be compared against each other
#define binary_search_tree_Point2D_is_greater(a, b) a.x > b.x

int main() {
    Point2D p = {2.3f, 3.0f};
    struct binary_search_tree_Point2D * point2DTree;
    binary_search_tree_alloc(Point2D, point2DTree);
    binary_search_tree_insert(Point2D, point2DTree, p);
    binary_search_tree_release(Point2D, point2DTree);
}

```

## Example - Traversal
The tree provides a way to traverse its values.
It uses the concept of an iterator but is implemented purely in a procedural manner.
It means that objects representing end or begin of tree cannot be generated on the fly.

```c

#include <stdio.h>
#include <binary_search_tree.h>

binary_search_tree(int);

#define binary_search_tree_int_is_greater(a, b) a > b

int main() {
    struct binary_search_tree_int * intTree;
    binary_search_tree_alloc(int, intTree);
    binary_search_tree_insert(int, intTree, 2);
    binary_search_tree_insert(int, intTree, 1);

    struct binary_search_tree_iterator_int * it, * end;
    binary_search_tree_iterator_alloc(int, it);
    binary_search_tree_iterator_alloc(int, end);
    binary_search_tree_begin(int, intTree, it);
    binary_search_tree_end(int, intTree, end);


    while (it->current != end->current) {
        printf("%i\n", it->current->data);
        binary_search_tree_iterator_next(int, it);
    }

    binary_search_tree_iterator_release(int, it);
    binary_search_tree_iterator_release(int, end);
    binary_search_tree_release(int, intTree);
}

```

## Requirements
* cmake 3.7.0
* docker (optional, tests execution)

## Running tests
1. Navigate to the repository's root folder
2. Build the image
```
docker build -f ./tests/Dockerfile -t bst-tests .
```
3. Run the container
```
docker run --rm bst-tests
```

