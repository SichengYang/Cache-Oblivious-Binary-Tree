#include "PackMemoryArray.h"

template <typename T>
PackMemoryArray<T>::PackMemoryArray()
    : size(0)
{
    top_array = new T[10];
}

template <typename T>
PackMemoryArray<T>::~PackMemoryArray()
{
    delete[] top_array;

    // Free the double pointer bottom array
    for (int i = 0; i < size; ++i)
    {
        delete[] bottom_array[i];
    }

    delete[] bottom_array;
}

template <typename T>
T *PackMemoryArray<T>::add(T value)
{
    
}

template <typename T>
T *PackMemoryArray<T>::remove(T value)
{
    
}

template <typename T>
int PackMemoryArray<T>::getSize()
{
    return size;
}

template <typename T>
T *PackMemoryArray<T>::operator[](int index)
{
    
}

