# BinarySearchTree
[![Build Status](https://travis-ci.org/mateuszstompor/BinarySearchTree.svg?branch=master)](https://travis-ci.org/mateuszstompor/BinarySearchTree)
</br>
A generic data structure written in pure C, uses macros 😂.
It seems to me that using macros to achieve generic data structure is quite clean approach.

## Important
Before using the tree a macro with the type you want to store in the data structure must be declared.

## Recommendation
If you wonder how does the code work I highly recommend reading an article from the link below.
https://gcc.gnu.org/onlinedocs/cpp/Macros.html

## Usage
In order to start using the code include single header as it is shown on the example.

```c

#include "binary_search_tree.h"

typedef struct Point2D {
    float x;
    float y;
} Point2D;

// Declare a tree with a specific type
// Name of struct which will be generated follows pattern
// binary_tree_type
// where "type" is the same as one which you provided

binary_search_tree(int);

// If you use custom type remember to typedef its name

binary_search_tree(Point2D);


// Define how elements should be compared against each other
// Use macro for that purpose, it has to follow pattern
// binary_tree_type_is_greater

#define binary_search_tree_int_is_greater(a, b) a > b
#define binary_search_tree_Point2D_is_greater(a, b) a.x > b.x

int main() {

    int v = 4;
    struct binary_search_tree_int * intTree;
    binary_search_tree_alloc(int, intTree);
    binary_search_tree_insert(int, intTree, v);
    binary_search_tree_release(int, intTree);

    Point2D p = {2.3f, 3.0f};
    struct binary_search_tree_Point2D * point2DTree;
    binary_search_tree_alloc(Point2D, point2DTree);
    binary_search_tree_insert(Point2D, point2DTree, p);
    binary_search_tree_release(Point2D, point2DTree);

}

```

## Traversal
The tree provides a way to traverse its values.
It uses concept of iterator but is implemented purely in procedural manner.
It means that objects representing end or begin of tree cannot be generated on the fly.

```c

#include <stdio.h>
#include "binary_search_tree.h"

binary_search_tree(int);

#define binary_search_tree_int_is_greater(a, b) a > b

int main() {

    struct binary_search_tree_int * intTree;
    binary_search_tree_alloc(int, intTree);
    binary_search_tree_insert(int, intTree, 2);
    binary_search_tree_insert(int, intTree, 1);

    struct binary_search_tree_iterator_int * it, *end;
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

## Running tests on your own
Docker is the only requirement. Build the image first
```
docker build -f ./tests/Dockerfile -t bst-tests .
```
And then run the container
```
docker run --rm bst-tests
```
