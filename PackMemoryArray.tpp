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
    : ncount(0),capacity(N)
{

    store = new T[N * 2];              // Using cN memory space
    exist = new bool[N * 2];           // Using cN memory space
    memset(exist, false, N*2);
    segment_size = decide_segment(N*2);  // N/8, in total we have 16 segments with c=2
    segment_ncount = new int[8](); // Buffer to temporarily store the elements to be suffled in a segment
}

template <typename T>
PackMemoryArray<T>::~PackMemoryArray()
{
    delete[] store;
    delete[] exist;
    delete[] segment_ncount;
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

template <typename T>
int PackMemoryArray<T>::getSegmentNumber(int pos)
{
    return floor(((double)pos) / segment_size);
}

template <typename T>
T PackMemoryArray<T>::insert(T value)
{
    int pos=0;
    //Find the position to insert
    pos = insertSearch(value);
    if(pos<0){
        cout<<"Error! in fundtion :add(), insert position not found."<<endl;
        return value;
    }
    cout<<"DEBUG: pos="<<pos<<endl;
    //We want to check if the segment is too full
    if(segment_ncount[(int)(pos/segment_size)]==segment_size){
        //shuffle needed
        cout<<"DEBUG: suffle needed for "<<segment_ncount[(int)(pos/segment_size)]<<" = "<<segment_size<<endl;
        shuffle();
        pos = insertSearch(value);
        cout<<"DEBUG: pos="<<pos<<endl;
    }
    if(pos<0){
        cout<<"Error! in fundtion :add(), insert position not found."<<endl;
        return value;
    }
    else{
        int gap_pos = findNearestGap(pos);
        cout<<"DEBUG: gap_pos="<<gap_pos<<endl;
        memmove(store + pos + 1, store + pos, sizeof(T) * (gap_pos - pos));
        memmove(exist + pos + 1, exist + pos, sizeof(bool) * (gap_pos - pos));
        store[pos]=value;
        exist[pos]=true;
        ncount++;
        resize();
        segment_ncount[(int)(pos/segment_size)]++;
    }
    // cout<<"Add value"<<value<<" to:"<< pos<<endl;//DEBUG:
    return value;
}

template <typename T>
void PackMemoryArray<T>::shuffle(){
    int valid_index=0;
    int distribute_size=ceil(((double)ncount)/8);
    cout<<"DEBUG: shuffle() distribute_size= "<<distribute_size<<" ncount="<<ncount<<endl;
    cout<<"DEBUG: shuffle() capacity*2= "<<capacity*2<<endl;
    //printPMA();
    //Collect
    T* temp_store=new T[ncount];
    for(int i=0;i<capacity*2;i++){
        if(exist[i]==true){
            // cout<<"["<<valid_index<<"]="<<store[i]<<" "<<endl;
            temp_store[valid_index]=store[i];
            valid_index++;
        }
    }
    // cout<<endl;
    // cout<<"aftershuffle:1"<<endl;
    memset(exist, (bool)false, capacity*2);
    delete[] segment_ncount;
    segment_ncount = new int[8]();
    //Distribute
    valid_index=0;
    for(int i=0; i<8;i++){
        for(int j=0;j<distribute_size;j++){
            if(valid_index<ncount){
                store[i*segment_size+j]=temp_store[valid_index];
                exist[i*segment_size+j]=true;
                segment_ncount[i]++;
                valid_index++;
            }
            
        }
    }
    // cout<<"aftershuffle:"<<endl;
    // printPMA();
    // printPMA();

}

template <typename T>
int PackMemoryArray<T>::decide_segment(int value)
{
    // Each segment should be c*N/8 where N is the total data size
    return value/8;
}
template <typename T>
bool PackMemoryArray<T>::match(T value, int pos)
{
    if(store[pos]==value && exist[pos]==true){
        return true;
    }
    else{
        return false;
    }
}
template <typename T>
int PackMemoryArray<T>::search(T value)
{
    for(int i=0;i<8;i++){
    if(match(value,segment_size*i)){
        return segment_size*i; //If the element is the same as the first element in the segment
    }
    if(i!=7){
        //The i+1 segment is larger than value, we want to look for value in i segment
        if(store[segment_size*(i+1)]>value && exist[segment_size*(i+1)]==true){ 
            //loop through the segment to find the position
            for(int j=0; j<segment_size;j++){
                if(match(value,segment_size*(i)+j)){
                    return segment_size*(i)+j;
                }
            }
            //if all the element in i segment is smaller than value, the element DNE
            return -1;
        }
        //The i+1 segment is empty
        else if(exist[segment_size*(i+1)]==false){
            //loop through the segment to find the position
            for(int j=0; j<segment_size;j++){
                if(match(value,segment_size*(i)+j)){
                    return segment_size*(i)+j;
                }
            }
            //if all the element in i segment is smaller than value, the element DNE
            return -1;
        }
    }
    //loop through the last segment
    else{
        //loop through the segment to find the position
        for(int j=0; j<segment_size;j++){
            if(match(value,segment_size*(i)+j)){
                return segment_size*(i)+j;
            }
        }
        //if all the element in i segment is smaller than value, the element DNE
        return -1;
    }
}
return -1;
}
// Binary Search, return the index of the element found
template <typename T>
int PackMemoryArray<T>::insertSearch(T value)
{
    if(ncount==0){
        return 0;
    }
    for(int i=0;i<8;i++){
        if(match(value,segment_size*i)){
            return segment_size*i; //If the element is the same as the first element in the segment
        }
        if(i!=7){
            //The i+1 segment is larger than value, we want to see if we can place the value in i segment
            if(store[segment_size*(i+1)]>value && exist[segment_size*(i+1)]==true){ 
                //loop through the segment to find the position to insert:
                //The position of the first element that is larger or equal than value, or an empty space
                for(int j=0; j<segment_size;j++){
                    if(store[segment_size*(i)+j]>=value && exist[segment_size*(i)+j]==true){
                        return segment_size*(i)+j;
                    }
                    else if( exist[segment_size*(i)+j]==false){
                        return segment_size*(i)+j;
                    }
                }
                //if all the element in i segment is smaller than value, then insert it at the beginning of the next segment
                return segment_size*(i+1);
            }
            //The i+1 segment is empty, we start to fill out this segment
            else if(exist[segment_size*(i+1)]==false){
                return segment_size*(i+1);
            }
        }
        //We cannot insert the element into former 7 segments, loop through the last segment
        else{
            for(int j=0; j<segment_size;j++){
                if(store[segment_size*(i)+j]>=value && exist[segment_size*(i)+j]==true){
                    return segment_size*(i)+j;
                }
                else if( exist[segment_size*(i)+j]==false){
                    return segment_size*(i)+j;
                }
            }
            //if all the element in i segment is smaller than value, then insert it at the end of the array
            return segment_size*(i);
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
            cout<<endl<<"Segment ["<<i/segment_size<<"] with ["<<segment_ncount[i/segment_size]<<"] elements:";
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
    cout<<"???"<<endl;
}

template <typename T>
void PackMemoryArray<T>::resize()
{
    if (getNcount()>=capacity*2*3/4)
    { // Too many elements in the array, we need to reallocate them with proper gap between the elements
        cout<<"Resize!"<<endl;
        T* temp_new_store=new T[capacity * 4];
        bool* temp_new_exist=new bool[capacity * 4];
        memset(temp_new_exist, false, capacity*4);
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
