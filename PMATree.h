#ifndef BTREE_H
#define BTREE_H

#include "Node.h"
#include "PackMemoryArray.h"

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
class PMATree
{
    int root;         // Index of the root node in the array
    int leave_height; // Height of the leaves in the tree; the default top height is 100.

    PackMemoryArray<Node<T>> array; // uncomment if finished

    // Function to rebalance the tree after insertion or deletion
    void rebalance_helper(int index);
    void rebalance(int index); // Function to rebalance the tree after insertion or deletion

    void shift_right(int index, int right_index); // Function to shift elements to the right in the array
    int left_insert(T value, int parrent, int current); // Function to insert a new node int the left subtree
    int right_insert(T value, int parrent, int current); // Function to insert a new node in the right subtree
    bool is_valid_node(int index); // Function to check if a node is valid (not deleted)
    bool is_leaf_node(int index); // Function to check if a node is a leaf node

    int insert_helper(T value); // helper function for soley inserting a new node and return the index of the new node
    int remove_helper(T value); // helper function for soley removing a node and return the index of the parent node
public:
    PMATree();
    ~PMATree();

    int insert(T value);    // Function to insert a new value into the tree
    void remove(T value);   // Function to remove a value from the tree
    int search(T value);    // Function to search for a value in the tree and return its index
    int get_height();       // Function to get the height of the tree

    void print_tree(); // Function to print the tree structure (for debugging purposes)
    void print_array(); // Function to print the array structure (for debugging purposes)

    class Iterator
    {
        int index; // Current index in the array of nodes

        Iterator();
        bool hasNext();
        int operator++(); // Overloaded operator to move the index to next element

        T operator[](int index);
    };
};

#include "PMATree.tpp"

#endif