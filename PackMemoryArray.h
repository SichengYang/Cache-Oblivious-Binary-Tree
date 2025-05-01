#ifndef ARRAY_H
#define ARRAY_H

/// @details
/// This is a custom pack memory array that stores data in several (in this case 8)contiguous block of memory(segments).
/// There are gaps between each segments' data. The structure will shuffle or resize if the segments are too full for insertion
/// @tparam T

template <typename T>
class PackMemoryArray
{
public:
// Variables:
    // # of element in the array
    int ncount;
    // Segment size is set as 2*capacity/8, so we keep 8 segments
    int segment_size;
    // Expected Capacity, the size of pma array is set as 2*capacity
    int capacity;
// Arrays:
    // Array that stores the value
    T * store;
    // Array that indicate if the element is valid
    bool * exist;
    //Maintain an array as the buffer that hold the value of the data being shuffled in the segment
    T * temp_buffer;
    // Array that stores the number of elements stored in each segment
    int * segment_ncount;
    // Boolean variable to turn on/off the debug printing
    bool debug_mode;
// Constructors:
    PackMemoryArray(); // N is the initial pma array size
    ~PackMemoryArray();
    //Operation : Insert with position(in the external array, not index in store[])
    int insert(int position, T value);
    //Operation: Remove with position(in the external array, not index in store[])
    int remove(int position);
    //Operation: Get with position(in the external array, not index in store[])
    T& operator[](int position);
    
    // Get variables
    int size();
    int getSegment_size();
    void printPMA();
    void printPMAdata();
    void setDebug(bool var);

private: 
// Supprting Functions
    // Check if the array is above the bar of "almost full"
    void resizeCheck();
    // Function to resize if space is limited
    void resize(); 
    // Return the number of segment size
    int decide_segment(int size);
    // Return the segment number of the corresponding pma index
    int getSegmentNumber(int pos);
    // Return the pma index of the next nearest gap(empty position)
    int findNearestGap(int pos);
    // Check if value is in position pos
    bool match(T value, int pos);
    // Return the index of seaching the element value. Used as an debug function
    int insertSearch(T value);
    // Shuffle the array to keep gaps between each segments
    void shuffle();
    // Return the index of seaching the element by its index
    int searchPosition(int index);
    // Insert the element in a empty index spot, return the corresponding external index
    int insertInEmptySpot(int pma_position, int position,T value);
};

#include "PackMemoryArray.tpp"

#endif