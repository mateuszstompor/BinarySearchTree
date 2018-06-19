# BinarySearchTree
a generic data structure written in pure C, uses macros 😂

## Drawbacks
You can declare variables of a specyfic type ONLY ONCE.

## Important
You need to declare a macro which will be used by the BTS to compare elements.

## Recommendation
If you wonder how does the code run I highly recommend reading an article from the link below.
https://gcc.gnu.org/onlinedocs/cpp/Macros.html

## Usage
In order to start using the code include single header as it is shown on the example. 

```c

#include <stdio.h>

#define binary_tree_int_is_greater(a, b) a > b
#define binary_tree_Point2D_is_greater(a, b) a.x > b.x

typedef struct Point2D {
    float x;
    float y;
} Point2D;

#include "binary_tree.h"

int main(int argc, const char * argv[]) {

    binary_tree(int) * intTree;
    binary_tree_alloc(int, intTree);
    binary_tree_insert(int, intTree, 2);
    binary_tree_release(int, intTree);


    Point2D p = {2.3f, 3.0f};
    binary_tree(Point2D) * point2DTree;
    binary_tree_alloc(Point2D, point2DTree);
    binary_tree_insert(Point2D, point2DTree, p);
    binary_tree_release(Point2D, point2DTree);
    return 0;

}

```
