#include "PackMemoryArray.h"
#include <math.h>
// debug and printing purpose
using namespace std;
#include <iostream>
#include <iomanip>
#include <cstring>
// N elements stored in O(N) memory. we set the memory size to be 2N (elements + gaps)
template <typename T>
PackMemoryArray<T>::PackMemoryArray(int N)
    : ncount(0), capacity(N)
{

    store = new T[N * 2];    // Using cN memory space
    exist = new bool[N * 2]; // Using cN memory space
    memset(exist, false, N * 2);
    segment_size = decide_segment(N * 2); // N/8, in total we have 16 segments with c=2
    segment_ncount = new int[8]();        // Buffer to temporarily store the elements to be suffled in a segment
    debug_mode = false;
}

template <typename T>
PackMemoryArray<T>::~PackMemoryArray()
{
    delete[] store;
    delete[] exist;
    delete[] segment_ncount;
}
// Operation : Insert with position(in the external array, not index in store[])
template <typename T>
int PackMemoryArray<T>::insert(int position, T value)
{
    int pma_position=0;
    // The pma array is empty insert the first element
    if (ncount == 0 && position == 0)
    {
        exist[0] = true;
        store[0] = value;
        ncount++;
        segment_ncount[0]++;
        return position;
    }
    // If position equals ncount, append to the last element
    else if(position == ncount)
    {
        int target_segment=-1;
        for(int i=1; i<8;i++){
            if(segment_ncount[i]==0){
                target_segment=i-1;
                pma_position=target_segment*segment_size;
                if (debug_mode)
                {
                    cout << "DEBUG: pma_position=" << pma_position << " position= " << position << endl;
                }
                insertInEmptySpot(pma_position, position, value);
                break;
            }
        }
        if(target_segment==-1){
            if(segment_ncount[7]==segment_size){
                shuffle();
            }
                for(int i=0;i<segment_size;i++){
                    if(exist[7*segment_size+i]==false){
                        pma_position=7*segment_size+i;
                        insertInEmptySpot(pma_position, position, value);
                        break;
                    }
                }
        }

    }
    else
    {
        pma_position = searchPosition(position);
        if (debug_mode)
        {
            cout << "DEBUG: pma_position=" << pma_position << " position= " << position << endl;
        }
        // index is out of range 0-ncount
        if (pma_position < 0)
        {
            cout << "Error: insert index "<<position<<" not found: element index range needs to be 0 to " << ncount << endl;
            return -1;
        }
        // Check if the position is occupied
        // pma position is available
        if (exist[pma_position] == false && pma_position < capacity * 2)
        {

            return insertInEmptySpot(pma_position, position, value);
        }
        // pma position is not available
        // Search for the nearest gap
        else
        {
            // Find the nearest gap
            int gap_pos = findNearestGap(pma_position);
            if (gap_pos < 0)
            {
                // cout << "Error! in fundtion :add(), gap position =-1" << endl;
                // Shuffle if needed
                if (debug_mode)
                {
                    cout << " DEBUG: suffle needed " << endl;
                }
                shuffle();
                pma_position = searchPosition(position);
                if (debug_mode)
                {
                    cout << "DEBUG: pma_position=" << pma_position;
                }
                if (exist[pma_position] == false)
                {
                    return insertInEmptySpot(pma_position, position, value);
                }
                gap_pos = findNearestGap(pma_position);
                // Usually won't happened, there must be gaps after shuffle
                if (gap_pos < 0)
                {
                    cout << "Error! in fundtion :add(), gap position =-1" << endl;
                }
            }
            
            memmove(store + pma_position+1, store + pma_position, sizeof(T) * (gap_pos - pma_position));
            memmove(exist + pma_position+1, exist + pma_position, sizeof(bool) * (gap_pos - pma_position));
            store[pma_position] = value;
            exist[pma_position] = true;
            ncount++;
            segment_ncount[getSegmentNumber(gap_pos)]++;
            resizeCheck();
            return position;
        }
    }
    return position;
}
// Operation: Remove with position(in the external array, not index in store[])
template <typename T>
int PackMemoryArray<T>::remove(int position)
{
    T temp;
    int index = searchPosition(position);
    if (index != -1)
    {
        exist[index] = false;
        ncount -= 1;
        segment_ncount[getSegmentNumber(index)]--;
        return index;
    }
    // Element not fount
    else
    {
        return -1;
    }
}
// Operation: Get with position(in the external array, not index in store[])
template <typename T>
T& PackMemoryArray<T>::operator[](int index)
{
    int pma_index = searchPosition(index);
    // cout<<"pma_index: "<<pma_index<<endl;
    if (pma_index == -1)
    {
        return store[0];
    }
    else
    {
        return store[pma_index];
    }
}
// Get variables
template <typename T>
void PackMemoryArray<T>::setDebug(bool var)
{
    debug_mode = var;
}

template <typename T>
int PackMemoryArray<T>::getNcount()
{
    return ncount;
}

template <typename T>
int PackMemoryArray<T>::getSegment_size()
{
    return segment_size;
}

template <typename T>
void PackMemoryArray<T>::printPMA()
{
    cout << "============Segement Size= " << segment_size << " Size = " << ncount << " Capacity= " << capacity << "============" << endl;
    for (int i = 0; i < capacity * 2; i++)
    {
        if ((i % segment_size) == 0)
        {
            cout << endl
                 << "Segment [" << i / segment_size << "] with [" << segment_ncount[i / segment_size] << "] elements:";
        }
        if (exist[i] == true)
        {
            cout << " [" << i << "]=" << store[i];
        }
        else
        {
            cout << " [" << i << "]=--";
        }
    }
    cout << endl;
}

// Return the pma index of the next nearest gap(empty position)
template <typename T>
int PackMemoryArray<T>::findNearestGap(int pos)
{
    bool found = false;
    // int start = getSegmentNumber(pos);
    int gap_after = 0;
    while (found == false)
    {
        if (pos + gap_after <= 2 * capacity - 1)
        {
            // cout<<pos+gap_after<<endl;
            if (exist[pos + gap_after] == false)
            {
                found = true;
                return pos + gap_after;
            }
            else
            {
                gap_after++;
            }
        }
        else
        {
            break;
        }
    }
    return -1;
}

// Return the segment number of the corresponding pma index
template <typename T>
int PackMemoryArray<T>::getSegmentNumber(int pos)
{
    return (int)(pos / segment_size);
}

// Insert the element in a empty index spot, return the corresponding external index
template <typename T>
int PackMemoryArray<T>::insertInEmptySpot(int pma_position, int position, T value)
{
    // Check if we can distrubute to other segements
    bool segment_distribute = true;
    if (segment_distribute)
    {
        int current_segement_number = getSegmentNumber(pma_position);
        if (current_segement_number != 7 && exist[(current_segement_number + 1) * segment_size] == false)
        {
            exist[(current_segement_number + 1) * segment_size] = true;
            store[(current_segement_number + 1) * segment_size] = value;
            ncount++;
            segment_ncount[current_segement_number + 1]++;
            resizeCheck();
            return position;
        }
    }
    exist[pma_position] = true;
    store[pma_position] = value;
    ncount++;
    segment_ncount[getSegmentNumber(pma_position)]++;
    resizeCheck();
    return position;
}

// Shuffle the array to keep gaps between each segments
template <typename T>
void PackMemoryArray<T>::shuffle()
{
    int valid_index = 0;
    int distribute_size = ceil(((double)ncount) / 8);
    // cout<<"DEBUG: shuffle() distribute_size= "<<distribute_size<<" ncount="<<ncount<<endl;
    // cout<<"DEBUG: shuffle() capacity*2= "<<capacity*2<<endl;
    // printPMA();
    // Collect
    T *temp_store = new T[ncount];
    for (int i = 0; i < capacity * 2; i++)
    {
        if (exist[i] == true)
        {
            // cout<<"["<<valid_index<<"]="<<store[i]<<" "<<endl;
            temp_store[valid_index] = store[i];
            valid_index++;
        }
    }
    // cout<<endl;
    // cout<<"aftershuffle:1"<<endl;
    memset(exist, (bool)false, capacity * 2);
    delete[] segment_ncount;
    segment_ncount = new int[8]();
    // Distribute
    valid_index = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < distribute_size; j++)
        {
            if (valid_index < ncount)
            {
                store[i * segment_size + j] = temp_store[valid_index];
                exist[i * segment_size + j] = true;
                segment_ncount[i]++;
                valid_index++;
            }
        }
    }
    // cout<<"aftershuffle:"<<endl;
}

// Return the number of segment size
template <typename T>
int PackMemoryArray<T>::decide_segment(int value)
{
    // Each segment should be c*N/8 where N is the total data size
    return value / 8;
}

// Check if value is in position pos
template <typename T>
bool PackMemoryArray<T>::match(T value, int pos)
{
    if (store[pos] == value && exist[pos] == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Function that mapping the element position to PMA position
template <typename T>
int PackMemoryArray<T>::searchPosition(int index)
{
    if (index >= ncount || index < 0)
    {
        if (debug_mode)
        {
            cout << "Error: index: " << index << ">=ncountt: " << ncount << endl;
        }
        return -1;
    }
    else
    {
        int temp_count = 0;
        int target_segment = 0;
        // Find the segement number of this element
        for (int i = 0; i < 8; i++)
        {
            temp_count += segment_ncount[i];
            if (temp_count > index)
            {
                target_segment = i;
                temp_count -= segment_ncount[i];
                break;
            }
        }
        if (debug_mode)
        {
            cout << "DEBUG: temp_count: " << temp_count << " target_segment: " << target_segment << endl;
        }
        // valid_count holds the amount of elements in the previous segements
        // Start is the index in pma which is the position of the current segement we are searching
        int start = target_segment * segment_size;
        int valid_count = temp_count;
        for (int i = 0; i < segment_size; i++)
        {
            if (exist[start + i] == true)
            {
                if (valid_count == index)
                {
                    return start + i;
                }
                valid_count++;
            }
        }
    }
    return -1;
}

// Return the index of seaching the element value. Used as an debug function
template <typename T>
int PackMemoryArray<T>::insertSearch(T value)
{
    if (ncount == 0)
    {
        return 0;
    }
    for (int i = 0; i < 8; i++)
    {
        if (match(value, segment_size * i))
        {
            return segment_size * i; // If the element is the same as the first element in the segment
        }
        if (i != 7)
        {
            // The i+1 segment is larger than value, we want to see if we can place the value in i segment
            if (store[segment_size * (i + 1)] > value && exist[segment_size * (i + 1)] == true)
            {
                // loop through the segment to find the position to insert:
                // The position of the first element that is larger or equal than value, or an empty space
                for (int j = 0; j < segment_size; j++)
                {
                    if (store[segment_size * (i) + j] >= value && exist[segment_size * (i) + j] == true)
                    {
                        return segment_size * (i) + j;
                    }
                    else if (exist[segment_size * (i) + j] == false)
                    {
                        return segment_size * (i) + j;
                    }
                }
                // if all the element in i segment is smaller than value, then insert it at the beginning of the next segment
                return segment_size * (i + 1);
            }
            // The i+1 segment is empty, we start to fill out this segment
            else if (exist[segment_size * (i + 1)] == false)
            {
                return segment_size * (i + 1);
            }
        }
        // We cannot insert the element into former 7 segments, loop through the last segment
        else
        {
            for (int j = 0; j < segment_size; j++)
            {
                if (store[segment_size * (i) + j] >= value && exist[segment_size * (i) + j] == true)
                {
                    return segment_size * (i) + j;
                }
                else if (exist[segment_size * (i) + j] == false)
                {
                    return segment_size * (i) + j;
                }
            }
            // if all the element in i segment is smaller than value, then insert it at the end of the array
            return segment_size * (i + 1) - 1;
        }
    }
    return -1;
}

// Check if the array is above the bar of "almost full"
template <typename T>
void PackMemoryArray<T>::resizeCheck()
{
    if (getNcount() >= capacity * 2 * 3 / 4)
    {
        resize();
    }
}

// Function to resize if space is limited
template <typename T>
void PackMemoryArray<T>::resize()
{
    // Too many elements in the array, we need to reallocate them with proper gap between the elements
    if (debug_mode)
    {
        cout << "Resize!" << endl;
    }
    T *temp_new_store = new T[capacity * 4];
    bool *temp_new_exist = new bool[capacity * 4];
    memset(temp_new_exist, false, capacity * 4);
    for (int i = 0; i < capacity * 2 / segment_size; i++)
    {
        memcpy(temp_new_store + 2 * i * segment_size, store + i * segment_size, segment_size * sizeof(T));
        memcpy(temp_new_exist + 2 * i * segment_size, exist + i * segment_size, segment_size * sizeof(bool));
    }
    delete[] store;
    delete[] exist;
    store = temp_new_store;
    exist = temp_new_exist;
    segment_size = segment_size * 2;
    capacity = capacity * 2;
}
