#include "PackMemoryArray.h"

template <typename T>
PackMemoryArray<T>::PackMemoryArray()
    : size(0)
    : capacity(10)
{
    top_array = new T[10];
    //
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
    //If the operation causes the array needs to be resized
    resize();
}

template <typename T>
T *PackMemoryArray<T>::remove(T value)
{
    //If the operation causes the array needs to be resized
    resize();
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
    
}

