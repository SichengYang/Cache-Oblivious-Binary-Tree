#include "PackMemoryArray.h"
#include <math.h>
// debug and printing purpose
using namespace std;
#include <iostream>
#include <iomanip>
// N elements stored in O(N) memory. we set the memory size to be 2N (elements + gaps)
template <typename T>
PackMemoryArray<T>::PackMemoryArray(int N)
    : ncount(0),capacity(N)
{

    store = new T[N * 2];              // Using cN memory space
    exist = new bool[N * 2];           // Using cN memory space
    segment_size = decide_segment(N*2);  // N/8, in total we have 16 segments with c=2
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
    //int start = getSegmentNumber(pos);
    int gap_after = 0;
    while (found == false)
    {
        if (pos + gap_after <= 2 * capacity - 1)
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
T PackMemoryArray<T>::add(T value)
{
    int pos=0;
    if(ncount==0){
        store[0]=value;
        exist[0]=true;
        ncount++;
    }
    else{
    pos = search(value);
    cout<<"pos="<<pos<<endl;
    int gap_pos = findNearestGap(pos);
    cout<<"gap_pos="<<gap_pos<<endl;
    if (gap_pos < 0)
    {
        cout<<"Error! in fundtion :add(), gap position not found."<<endl;
        return value;
    }
    else if (gap_pos >= pos)
    { // Move this chunck of data afterward
        // cout<<"store["<<pos+1<<"]: "<<store[pos+1]<<" store["<<pos<<"]: "<<store[pos]<<endl;//DEBUG:
        memmove(store + pos + 1, store + pos, sizeof(T) * (gap_pos - pos));
        memmove(exist + pos + 1, exist + pos, sizeof(bool) * (gap_pos - pos));
        store[pos]=value;
        exist[pos]=true;
        // cout<<"store["<<pos+1<<"]:"<<store[pos+1]<<" store["<<pos<<"]: "<<store[pos]<<endl;//DEBUG:
    }
    ncount++;
    resize(); // If the operation causes the array needs to be resized
    }
    // cout<<"Add value"<<value<<" to:"<< pos<<endl;//DEBUG:
    return value;
}

template <typename T>
int PackMemoryArray<T>::decide_segment(int value)
{
    // Each segment should be c*N/8 where N is the total data size
    return value/8;
}
// Binary Search, return the index of the element found
template <typename T>
int PackMemoryArray<T>::search(T value)
{
    for(int i=0;i<8;i++){
        if(exist[segment_size*i]==false){
            cout<<"exist[segment_size*i]==false"<<endl;
        }
        if(store[segment_size*i]>value || exist[segment_size*i]==false){
            for(int j=0;j<segment_size;i++){
                if(store[segment_size*(i-1)+j]==value && exist[segment_size*(i-1)+j]==true){
                    return segment_size*(i-1)+j;
                }
                else if((store[segment_size*(i-1)+j]>value && exist[segment_size*(i-1)+j]==true)){
                    return segment_size*(i-1)+j-1;
                }
                else if(exist[segment_size*(i-1)+j]==false){
                    return segment_size*(i-1)+j;
                }
                
            }
        }
    }
    return -1;
}

template <typename T>
T PackMemoryArray<T>::remove(T value)
{
    T temp;
    int index = search(value);
    if (store[index]==value && exist[index]==true)
    {
        exist[index] = false;
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
void PackMemoryArray<T>::printPMA()
{
    cout<<"Segement Size= "<<segment_size<<" Size = "<<ncount<<" Capacity= "<<capacity<<endl;
    for (int i = 0; i < capacity*2; i++)
    {
        if((i%segment_size)==0){
            cout<<endl<<"Segment"<<i/segment_size<<":";
        }
        if (exist[i] == true)
        {
            cout<<" ["<<i<<"]="<<store[i];
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
    if (getNcount() > (capacity * 3 / 4))
    { // Too many elements in the array, we need to reallocate them with proper gap between the elements
        cout<<"Resize!"<<endl;
        T* temp_new_store=new T[capacity * 2];
        bool* temp_new_exist=new bool[capacity * 2];
        for(int i=0; i< capacity*2/segment_size;i++){
            memcpy(temp_new_store+2*i*segment_size, store+i*segment_size, segment_size * sizeof(T));
            memcpy(temp_new_exist+2*i*segment_size, exist+i*segment_size, segment_size * sizeof(bool));
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
T PackMemoryArray<T>::operator[](int index)
{
    int temp_count=0;
    if (index > ncount || index < 0)
    {
        return NULL;
    }
    else 
    {
        for(int i=0; i<capacity*2;i++){
            if(exist[i]==true){
                if(temp_count==index){
                    return store[i];
                }
                temp_count++;
            }
        }
    }
}
