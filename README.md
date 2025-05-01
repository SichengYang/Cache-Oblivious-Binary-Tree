# Cache-Oblivious-Binary-Tree

## Description
This is a reading project that aims to let us understand the conept of the cache oblivious binary tree

## Folder Structure
* PMA test: the result of PMA runtime
* PMA tree test result: the run time of binary tree with PMA
* Vector tree result: the runtime of vector binary tree
* Vector tree test script: the test script for the vector binary tree

## Source File
* BTree.h and BTree.tpp: vector implementation of binary tree
* PMATree.h and PMATree.tpp: PMA implementation of binary tree
* Node.h and Node.tpp: the node structure in the tree
* PMA_tree_test.cpp: a visual test of tree
* search_test.cpp: search performance of PMA tree

## Usage
* Vector tree:
```
#include "BTree.h"

BTree<int> tree;
```

* PMA tree:
```
#include "PMATree.h"

PMATree<int> tree;
```