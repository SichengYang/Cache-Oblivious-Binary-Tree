#include "PackMemoryArray.h"

template <typename T>
PackMemoryArray<T>::PackMemoryArray()
    : size(0)
    : capacity(10)
{
    array=new int[10];

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
    if(search(value)==-1){
        size++;
        resize();
        //我再研究一下这个add
    }
    //If the operation causes the array needs to be resized
    else{
        return -1; //Duplicate value
    }
}

//Binary Search
template <typename T>
int *PackMemoryArray<T>::search(T value){
    int low = 0, high = size;
    while (low <= high) {
        int mid = ((high - low) / 2) + low;
        if (array[mid] == value) {
            return mid;
        }
        if (array[mid] > target)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1; //Not found
}

template <typename T>
int *PackMemoryArray<T>::remove(T value)
{
    int temp=0;
    int index=search(value);
    if(index!=-1){
        array[mid]=-1;
        size-=1;
        //If the operation causes the array needs to be resized
        resize();
        return temp;
    }
    else{
        return -1;
    }
}

template <typename T>
int PackMemoryArray<T>::getSize()
{
    return size;
}
template <typename T>
void PackMemoryArray<T>::resize(){
    if(self.getSize()< capacity/2 && self.getSize()>10 ){ //TKTK: Too few element in the array (regardless of the initial size 10)
        // delete[] array;
        // array=new int[capacity/2];
        // capacity=capacity/2;
        
    }
    else if(self.getSize()>(capacity*3/4)){ // Too many elements in the array, we need to reallocate them with proper gap between the elements
        int* temp_array=new int[capacity];
        memcpy(temp_array,array,capacity*sizeof(int));
        delete[] array;
        array=new int[capacity*2];
        memcpy(array,temp_array,capacity*sizeof(int));
        capacity=capacity*2;

    }

}
template <typename T>
T *PackMemoryArray<T>::operator[](int index)
{
    if(index>size){
        return NULL;
    }
    else{
        return array[index];
    }
    
}

