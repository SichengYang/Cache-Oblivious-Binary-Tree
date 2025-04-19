#ifndef NODE_H
#define NODE_H

/// @brief A Node structure that knows the height and children number restrictions
/// @tparam T

template <typename T>
class Node
{
public:
    T *data; // Data stored in the node

    int height;     // Height of the node in the tree
    int min;        // Min children allowed
    int max;        // Max children allowed
    int childCount; // Number of children

    Node *left;
    Node *right;
    Node *parent;

    Node(T *value); // The data itself is in PackMemoryArray, so we just need to store the pointer to it
};

#include "Node.tpp"

#endif