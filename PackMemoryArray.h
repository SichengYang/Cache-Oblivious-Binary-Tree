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
//Variables:
    // # of element in the array
    int ncount;
    // Segment size
    int segment_size;
    // TKTK
    int nchunks;
    int nlevels; 
//Arrays:
    // Array that stores the value
    T * store;
    // Array that indicate if the element is valid
    bool * exist;
    
//Constructors:
    PackMemoryArray(); // Default size
    PackMemoryArray(T* v_store, bool* v_exist, int ncount, int segment_size, int nchunks, int nlevels); //Constructor with array
    ~PackMemoryArray();
    //Operation:Insert, Remove, Get by index
    T *add(T value);
    T *remove(T value);
    T *operator[](int index);
    // Get variables
    int getNcount();
    int getSegment_size();
    int printPMA();
private:
// Supprting Functions
    void resize(); // Function to resize if space is limited
    void relanace();
    int getSize(); //TKTK: do we really need this?
    int *decide_segment(T value);
    // Search
    int *search(T value);
};

#include "PackMemoryArray.tpp"

#endif