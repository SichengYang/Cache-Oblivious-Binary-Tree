#include "PackMemoryArray.h"

template <typename T>
PackMemoryArray<T>::PackMemoryArray()
    : ncount(0)
    : segment_size(10)
    : nchunks(0)
    : nlevels(0) 
{
    store=new T[10];
    exist=new bool[10];

}
template <typename T>
PackMemoryArray<T>::PackMemoryArray(T* v_store, bool* v_exist, int ncount, int segment_size, int nchunks, int nlevels)
    : ncount(ncount)
    : segment_size(segment_size)
    : nchunks(nchunks)
    : nlevels(nlevels) 
{
    store=v_store;
    exist=v_exist; //TKTK
    
}

template <typename T>
PackMemoryArray<T>::~PackMemoryArray()
{
    delete[] store;
    delete[] exist;
}

template <typename T>
T *PackMemoryArray<T>::add(T value)
{
    if(search(value)==-1){
        ncount++;
        resize();
        //我再研究一下这个add.
    }
    //If the operation causes the array needs to be resized
    else{
        return -1; //Duplicate value
    }
}
template <typename T>
int *PackMemoryArray<T>::decide_segment(T value){

}
//Binary Search, return the index of the element found
template <typename T>
int *PackMemoryArray<T>::search(T value){
    int low = 0, high = size;
    while (low <= high) {
        int mid = ((high - low) / 2) + low;
        if (store[mid] == value && exist[mid]==true) {
            return mid;
        }
        if (store[mid] > target)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1; //Not found
}

template <typename T>
T *PackMemoryArray<T>::remove(T value)
{
    T temp;
    int index=search(value);
    if(index!=-1){
        exist[mid]=false;
        ncount-=1;
        //TKTK: If the operation causes the array needs to be resized
        resize();
        return temp;
    }
    // Element not fount
    else{
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
    return     int segment_size;
    ;
}
template <typename T>
int PackMemoryArray<T>::printPMA()
{
    for(int i=0; i<segment_size;i++){
        if(exist[i]==true){
            print("[%d]=%d\n",i,store[i]);
        }
    }
}
template <typename T>
void PackMemoryArray<T>::resize(){
    if(self.getSize()< capacity/2 && self.getSize()>10 ){ //TKTK: Too few element in the array (regardless of the initial size 10)
        // delete[] array;
        // array=new int[capacity/2];
        // capacity=capacity/2;
        
    }
    else if(self.getSize()>(capacity*3/4)){ // Too many elements in the array, we need to reallocate them with proper gap between the elements
        //TKTK可能需要优化，我有点忘了这里该怎么处理了
        int* temp_store=new T[segment_size];
        int* temp_exist=new T[segment_size];
        memcpy(temp_store,store,segment_size*sizeof(T));
        memcpy(temp_exist,exist,segment_size*sizeof(T));
        delete[] store;
        delete[] exist;
        store=new int[capacity*2];
        exist=new int[capacity*2];
        memcpy(store,temp_store,segment_size*sizeof(T));
        memcpy(exist,temp_exist,segment_size*sizeof(T));
        segment_size=segment_size*2;
    }

}
template <typename T>
T *PackMemoryArray<T>::operator[](int index)
{
    if(index>size){
        return NULL;
    }
    else if(exist[index]==false){
        return NULL;
    }
    else{
        return store[index];
    }
    
}

