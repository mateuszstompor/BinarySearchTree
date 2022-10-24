//
//  Created by Mateusz Stompór on 29/06/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include <gtest/gtest.h>
#include <binary_search_tree.h>

struct TS {
    int a;
    char b;
    float c;
};

typedef struct TS TS;

#define binary_search_tree_TS_is_greater(c, d) c.a > d.a
#define binary_search_tree_int_is_greater(a, b) a > b

binary_search_tree(TS);
binary_search_tree(int);

TEST (BinarySearchTreeTest, InitAndRelease) {
    struct binary_search_tree_TS * tree = nullptr;
    binary_search_tree_alloc(TS, tree);
    ASSERT_TRUE(tree != nullptr);
    binary_search_tree_release(TS, tree);
}

TEST (BinarySearchTreeTest, SizeString) {
    struct binary_search_tree_TS * tree = nullptr;
    binary_search_tree_alloc(TS, tree);
    TS ts_test{2, 'a', 2.3f};
    ASSERT_TRUE(binary_search_tree_size(tree) == 0);
    binary_search_tree_insert(TS, tree, ts_test);
    ASSERT_TRUE(binary_search_tree_size(tree) == 1);
    binary_search_tree_release(TS, tree);
}

TEST (BinarySearchTreeTest, SizeInt) {
    struct binary_search_tree_int * tree = nullptr;
    binary_search_tree_alloc(int, tree);

    int a = 2;
    ASSERT_TRUE(binary_search_tree_size(tree) == 0);
    binary_search_tree_insert(int, tree, 1);
    ASSERT_TRUE(binary_search_tree_size(tree) == 1);
    binary_search_tree_insert(int, tree, a);
    ASSERT_TRUE(binary_search_tree_size(tree) == 2);
    binary_search_tree_insert(int, tree, 6);
    ASSERT_TRUE(binary_search_tree_size(tree) == 3);
    binary_search_tree_insert(int, tree, 4);
    ASSERT_TRUE(binary_search_tree_size(tree) == 4);
    binary_search_tree_insert(int, tree, 5);
    ASSERT_TRUE(binary_search_tree_size(tree) == 5);

    binary_search_tree_release(int, tree);
}

class BinarySearchTreeTestFixture : public ::testing::Test {

protected:

    virtual void SetUp() {
        binary_search_tree_alloc(int, tree);
        binary_search_tree_iterator_alloc(int, i);
        binary_search_tree_iterator_alloc(int, k);
    }

    virtual void TearDown() {
        binary_search_tree_release(int, tree);
        binary_search_tree_iterator_release(int, i);
        binary_search_tree_iterator_release(int, k);
    }

    struct binary_search_tree_int * tree;
    struct binary_search_tree_iterator_int * i;
    struct binary_search_tree_iterator_int * k;

};

TEST_F(BinarySearchTreeTestFixture, Iterator) {
    binary_search_tree_begin(int, tree, i);
    binary_search_tree_end(int, tree, k);
    ASSERT_TRUE(binary_search_tree_iterator_equal(int, i, k));
    binary_search_tree_iterator_next(int, k);
    ASSERT_TRUE(binary_search_tree_iterator_equal(int, i, k));
    binary_search_tree_iterator_next(int, i);
    ASSERT_TRUE(binary_search_tree_iterator_equal(int, i, k));
}
