#ifndef ARRAY_H
#define ARRAY_H

/// @details
/// This is a custom pack memory array that stores data in several contiguous block of memory. To make the data structure easy to use,
///
/// @tparam T

template <typename T>
class PackMemoryArray
{
public:
    T *top_array;     // Pointer to the top array which size is sqrt(n)
    T **bottom_array; // Pointer to the bottom array which size is n * [sqrt(n)]

    int size;
    int capacity;
    int * array;
    void resize(); // Function to resize if space is limited

    PackMemoryArray(); // Constructor to initialize the array with a default total size of 30
    ~PackMemoryArray();

    T *add(T value);
    int *remove(T value);
    int getSize();
    T *operator[](int index);
    int *search(T value);
};

#include "PackMemoryArray.tpp"

#endif