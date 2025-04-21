#ifndef NODE_H
#define NODE_H

/// @brief A Node structure that knows the height and children number restrictions
/// @tparam T

template <typename T>
class Node
{
public:
    T data; // Data stored in the node

    int height;     // Height of the node in the tree
    int childCount; // Number of children

    // Because the realloation may change the address of the node, we need to store the index of the node in the array
    int left;
    int right;
    int parent;

    Node(T value, int height);
};

#include "Node.tpp"

#endif