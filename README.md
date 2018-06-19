# BinarySearchTree
a generic data structure written in pure C, uses macros 😂

## Drawbacks
You can declare variables of a specyfic type ONLY ONCE.

## Important
You need to declare a macro which will be used by the BTS to compare elements.

## Recommendation
If you wonder how does the code run I highly recommend reading an article from the link below.
https://gcc.gnu.org/onlinedocs/cpp/Macros.html

```c

#include <stdio.h>

#define binary_tree_int_is_greater(a, b) a > b
#include "binary_tree.h"

int main(int argc, const char * argv[]) {
    binary_tree(int) *a;
    binary_tree_alloc(int, a);
    binary_tree_insert(int, a, 2);
    binary_tree_insert(int, a, 1);
    binary_tree_insert(int, a, 3);
    binary_tree_release(int, a);
    return 0;
}

```
