#ifndef BTREE_H
#define BTREE_H

#include "Node.h"
#include "PackMemoryArray.h"

// library for temprary use
using namespace std;
#include <vector>
#include <iostream>

/// @class CSE549T
/// @author Sicheng Yang and Yanqing(Lily) Fu
/// @details
/// This is self-balancing binary tree structure that supports efficient insertion, deletion, search, and scan (via the iterator)
/// operations. Our group review the papers about the B-Tree and implement this data structure. Unlike the common tree on the internet,
/// we use a custom pack memory array to store the data in a contiguous block of memory. This is done to improve cache performance and
/// reduce memory transfers.
/// @tparam T

template <typename T>
class BTree
{
    int root;         // Index of the root node in the array
    int leave_height; // Height of the leaves in the tree; the default top height is 100.

    vector<Node<T>> array;
    // PackMemoryArray<T> array; // uncomment if finished

    // Function to rebalance the tree after insertion or deletion
    void split(Node<T> *node); // Function to split a node when it exceeds the maximum number of children
    void merge(Node<T> *node); // Function to merge nodes when the number of children is less than the minimum required

public:
    BTree();
    ~BTree();

    int insert(T value);
    void remove(T value);
    int search(T value);

    void print_tree(); // Function to print the tree structure (for debugging purposes)

    class Iterator
    {
        int index; // Current index in the array of nodes

        Iterator();
        bool hasNext();
        int operator++(); // Overloaded operator to move the index to next element

        T operator[](int index);
    };
};

#include "BTree.tpp"

#endif