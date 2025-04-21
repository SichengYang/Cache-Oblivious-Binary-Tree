#include "BTree.h"

using namespace std;

template <typename T>
BTree<T>::BTree() : root(-1), leave_height(100) {}

template <typename T>
BTree<T>::~BTree() {}

template <typename T>
void BTree<T>::split(Node<T> *node)
{
}

template <typename T>
void BTree<T>::merge(Node<T> *node)
{
}

template <typename T>
int BTree<T>::insert(T value)
{
    // if tree is empty, create a new root node
    if (root == -1)
    {
        const int default_height = 100;
        Node<T> rootNode(value, 100);
        auto pos = array.insert(array.begin(), rootNode);
        int index = pos - array.begin();
        root = index;
        return index;
    }

    // if tree is not empty, find the correct position to insert the new node
    while(true)
    {
        int current = root;

        // check if we have a right child insertion available
        if(array[current].data < value)
        {
            if (array[current].right == -1) {}
        }
    }

    return -1; // return -1 if insertion fails
}

template <typename T>
void BTree<T>::remove(T value)
{
}

template <typename T>
int BTree<T>::search(T value)
{
    return 0;
}

template <typename T>
void BTree<T>::print_tree()
{
    cout << "Array: ";
    for (int i = 0; i < array.size(); ++i)
    {
        cout << array[i].data << " ";
    }
    cout << endl;

    if (root != -1)
    {
        cout << "Root: " << array[root].data << endl;
    }
    else
    {
        cout << "Tree is empty." << endl;
    }
}

template <typename T>
BTree<T>::Iterator::Iterator() : index(0) {}

template <typename T>
bool BTree<T>::Iterator::hasNext()
{
    return index < array.getSize();
}

template <typename T>
int BTree<T>::Iterator::operator++()
{
    return ++index;
}

template <typename T>
T BTree<T>::Iterator::operator[](int index)
{
    return array[index];
}