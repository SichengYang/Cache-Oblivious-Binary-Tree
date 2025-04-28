#include "PackMemoryArray.h"
#include <math.h>
#define c 2 // N elements stored in O(N) memory. we set the memory size to be 2N (elements + gaps)
template <typename T>
PackMemoryArray<T>::PackMemoryArray(int N)
    : ncount(0)
    : capacity(N)
{

    store = new T[N * c];              // Using cN memory space
    exist = new bool[N * c];           // Using cN memory space
    segment_size = decide_segment(N*c);  // N/8, in total we have 16 segments with c=2
    temp_buffer = new T[segment_size]; // Buffer to temporarily store the elements to be suffled in a segment
}

template <typename T>
PackMemoryArray<T>::~PackMemoryArray()
{
    delete[] store;
    delete[] exist;
    delete[] temp_buffer;
}
template <typename T>
int PackMemoryArray<T>::findNearestGap(int pos)
{
    bool found = false;
    int start = getSegmentNumber(pos);
    int gap_before = 0;
    int gap_after = 0;
    while (found == false)
    {
        if (pos - gap_before >= 0)
        {
            if (exist[pos - gap_before] == false)
            {
                found = true;
                return pos - gap_before;
            }
            else
            {
                gap_before++;
            }
        }
        else if (pos + gap_after <= c * N - 1)
        {
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

template <typename T>
int PackMemoryArray<T>::getSegmentNumber(int pos)
{
    return floor(((double)pos) / segment_size);
}

template <typename T>
T *PackMemoryArray<T>::add(T value)
{
    int pos = search(value);
    if (pos < 0)
    {
        pos = -pos - 1;
    }
    int gap_pos = findNearestGap(pos);
    if (gap_pos < 0)
    {
        cout<<"Error! in fundtion :add(), gap position not found."<<endl;
    }
    else if (gap_pos > pos)
    { // Move this chunck of data afterward
        memmove(store + pos + 1, store + pos, sizeof(T) * (gap_pos - pos));
    }
    else
    { // Move this chunck of data forward
        memmove(store + gap_pos, store + gap_pos + 1, sizeof(T) * (pos - gap_pos));
    }

    ncount++;
    resize(); // If the operation causes the array needs to be resized
}

template <typename T>
int PackMemoryArray<T>::decide_segment(int value)
{
    // Each segment should be c*N/8 where N is the total data size
    return value/8;
}
// Binary Search, return the index of the element found
template <typename T>
int *PackMemoryArray<T>::search(T value)
{
    int low = 0, high = size;
    while (low <= high)
    {
        int mid = ((high - low) / 2) + low;
        if (store[mid] == value && exist[mid] == true)
        {
            return mid;
        }
        if (store[mid] > target)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -high - 1; // Not found, return the position that is insertable n, as -(n+1)
}

template <typename T>
T *PackMemoryArray<T>::remove(T value)
{
    T temp;
    int index = search(value);
    if (index != -1)
    {
        exist[mid] = false;
        ncount -= 1;
        // TKTK: If the operation causes the array needs to be resized
        resize();
        return temp;
    }
    // Element not fount
    else
    {
        return -1;
    }
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
int PackMemoryArray<T>::printPMA()
{
     cout<<" Segement Size= "<<segment_size<<" Size = "<<ncount<<" Capacity= "<<capacity<<endl;
    for (int i = 0; i < capacity*c; i++)
    {
        if((i%segment_size)==0){
            cout<<endl<<"Segment"<<i/segment_size<<":";
        }
        if (exist[i] == true)
        {
            cout<<" ["<<i<<"]="store[i];
        }
        else{
            cout<<" ["<<i<<"]=--";
        }
    }
    cout<<endl;
}

template <typename T>
void PackMemoryArray<T>::resize()
{
    cout<<"Resize!"<<endl;
    if (self.getSize() > (capacity * 3 / 4))
    { // Too many elements in the array, we need to reallocate them with proper gap between the elements
        temp_new_store=new T[capacity * 2];
        temp_new_exist=new T[capacity * 2];
        for(int i=0; i< N*C/segment_size;i++){
            memcpy(temp_new_store+2*i*segment_size, store+i*segment_size, segment_size * sizeof(T));
            memcpy(temp_new_exist+2*i*segment_size, exist+i*segment_size, segment_size * sizeof(T));
        }
        delete[] store;
        delete[] exist;
        store = temp_new_store;
        exist = temp_new_exist;
        segment_size = segment_size * 2;
        capacity=capacity*2;
    }
}
template <typename T>
T *PackMemoryArray<T>::operator[](int index)
{
    int temp_count=0;
    if (index > ncount || index < 0)
    {
        return NULL;
    }
    else 
    {
        for(int i=0; i<capacity*c;i++){
            if(exist[i]==true){
                if(temp_count==index){
                    return store[i];
                }
                temp_count++;
            }
        }
    }
}
