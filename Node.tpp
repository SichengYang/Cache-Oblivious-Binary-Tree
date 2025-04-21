#include "Node.h"

template <typename T>
Node<T>::Node(T value, int height)
    : data(value), height(height), left(-1), right(-1), parent(-1), childCount(0)
{
}