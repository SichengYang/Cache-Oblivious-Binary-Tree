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
    // Expected Capacity
    int capacity;
//Arrays:
    // Array that stores the value
    T * store;
    // Array that indicate if the element is valid
    bool * exist;
    //Maintain an array as the buffer that hold the value of the data being shuffled in the segment
    T * temp_buffer;
    
//Constructors:
    PackMemoryArray(int N); // Default size
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
    int decide_segment(int value);
    int findNearestGap(int pos);
    int getSegmentNumber(int pos);
    
    // Search
    int *search(T value);
};

#include "PackMemoryArray.tpp"

#endif