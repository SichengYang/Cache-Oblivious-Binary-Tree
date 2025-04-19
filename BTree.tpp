#include "BTree.h"

template <typename T>
BTree<T>::BTree(int d) : d(d), root(nullptr) {}

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
void BTree<T>::insert(T value)
{
}

template <typename T>
void BTree<T>::remove(T value)
{
}

template <typename T>
Node<T> *BTree<T>::search(T value)
{
    return nullptr;
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