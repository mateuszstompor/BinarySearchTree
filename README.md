# BinarySearchTree
a generic data structure written in pure C, uses macros 😂

## Drawbacks
You can declare variables of a specific type ONLY ONCE.

## Important
You need to declare a macro which will be used by the BTS to compare elements.

## Recommendation
If you wonder how does the code run I highly recommend reading an article from the link below.
https://gcc.gnu.org/onlinedocs/cpp/Macros.html

## Usage
In order to start using the code include single header as it is shown on the example.

```c

#include "binary_tree.h"

typedef struct Point2D {
    float x;
    float y;
} Point2D;

// Declare a tree with a specific type
// Name of struct which will be generated follows pattern
// binary_tree_type
// where "type" is the same as one which you provided

binary_tree(int);

// If you use custom type remember to typedef its name

binary_tree(Point2D);


// Define how elements should be compared against each other
// Use macro for that purpose, it has to follow pattern
// binary_tree_type_is_greater

#define binary_tree_int_is_greater(a, b) a > b
#define binary_tree_Point2D_is_greater(a, b) a.x > b.x && a.y > b.y

int main() {

    struct binary_tree_int * intTree;
    binary_tree_alloc(int, intTree);
    binary_tree_insert(int, intTree, 2);
    binary_tree_release(int, intTree);

    Point2D p = {2.3f, 3.0f};
    struct binary_tree_Point2D * point2DTree;
    binary_tree_alloc(Point2D, point2DTree);
    binary_tree_insert(Point2D, point2DTree, p);
    binary_tree_release(Point2D, point2DTree);

}

```
