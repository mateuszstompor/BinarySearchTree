//
//  performance.cpp
//  binary_search_tree_tests
//
//  Created by Mateusz Stompór on 29/06/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#include <benchmark/benchmark.h>
#include <iostream>
#include <map>
#include "binary_search_tree.h"

#define binary_search_tree_int_is_greater(a, b) a > b
binary_search_tree(int);

static void BM_BST_Insert(benchmark::State& state) {
  struct binary_search_tree_int * tree;
  binary_search_tree_alloc(int, tree);
  for (auto _ : state) {
    binary_search_tree_insert(int, tree, 2);
  }
  binary_search_tree_release(int, tree);
}
BENCHMARK(BM_BST_Insert);

static void BM_Map_Insert(benchmark::State& state) {
  std::map<int, int> m;
  for (auto _ : state) {
    m.insert(std::make_tuple<int, int>(2, 2));
  }
}
BENCHMARK(BM_Map_Insert);

BENCHMARK_MAIN();
