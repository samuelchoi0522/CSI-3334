#ifndef ARRAY_HEAP_STUDENT_PROJ6_H
#define ARRAY_HEAP_STUDENT_PROJ6_H

#include "arrayheap-prof-proj6.h"
#include <algorithm>
#include <iostream>

using namespace std;

template <typename T>
ArrayHeap<T>::ArrayHeap(){
    numItems = 0;
    capacity = 10;
    data = new T[capacity];
    heapAndFreeStack = new int[capacity];
    dataToHeap = new int[capacity];

    for(int i = 0; i < capacity; i++){
        heapAndFreeStack[i] = i;
    }
}

template <typename T>
ArrayHeap<T>::ArrayHeap(ArrayHeap<T> const &h){
    numItems = h.numItems;
    capacity = h.capacity;

    delete []data;
    delete []heapAndFreeStack;
    delete []dataToHeap;

    data = new T[capacity];
    heapAndFreeStack = new int[capacity];
    dataToHeap = new int[capacity];

    for (int i = 0; i < capacity; i++) {
        heapAndFreeStack[i] = h.heapAndFreeStack[i];
        data[i] = h.data[i];
        dataToHeap[i] = h.dataToHeap[i];
    }
}

template <typename T>
ArrayHeap<T>::~ArrayHeap(){
    delete []data;
    delete []heapAndFreeStack;
    delete []dataToHeap;

    data = nullptr;
    heapAndFreeStack = nullptr;
    dataToHeap = nullptr;
}

template <typename T>
ArrayHeap<T> const &ArrayHeap<T>::operator=(ArrayHeap<T> const &ah){
    if(this != &ah){
        numItems = ah.numItems;
        capacity = ah.capacity;

        delete []data;
        delete []heapAndFreeStack;
        delete []dataToHeap;

        data = new T[capacity];
        heapAndFreeStack = new int[capacity];

        for(int i = 0; i < capacity; i++){
            heapAndFreeStack[i] = ah.heapAndFreeStack[i];
            data[i] = ah.data[i];
            dataToHeap[i] = ah.dataToHeap[i];
        }
    }

    return *this;
}

template <typename T>
int ArrayHeap<T>::insert(T const &item){
    if(numItems == capacity){
        doubleCapacity();
    }

    data[heapAndFreeStack[numItems]] = item;
    dataToHeap[heapAndFreeStack[numItems]] = numItems;
    bubbleUp(numItems);

    numItems++;
    return heapAndFreeStack[numItems];
}

template <typename T>
void ArrayHeap<T>::removeMinItem(){
    if(numItems == 0){
        return;
    }
    swap(dataToHeap[heapAndFreeStack[0]], dataToHeap[heapAndFreeStack[numItems - 1]]);
    swap(heapAndFreeStack[0], heapAndFreeStack[numItems - 1]);

    numItems--;

    bubbleDown(0);
}

template <typename T>
T const &ArrayHeap<T>::getMinItem() const{
    return data[heapAndFreeStack[0]];
}

template <typename T>
int ArrayHeap<T>::getNumItems() const{
    return numItems;
}

template <typename T>
bool ArrayHeap<T>::isOnHeap(int key) const{
    return(dataToHeap[key] != -1) && (dataToHeap[key] < numItems);
}

template <typename T>
void ArrayHeap<T>::changeItemAtKey(int key, T const &newItem){
    if(isOnHeap(key)){
        data[key] = newItem;

        bubbleUp(dataToHeap[key]);
        bubbleDown(dataToHeap[key]);
    }
    else{
        return;
    }
}

template <typename T>
void ArrayHeap<T>::doubleCapacity(){
    capacity *= 2;

    T *temp = new T[capacity];
    int *tempHeap = new int[capacity];
    int *tempDataToHeap = new int[capacity];

    //init values of heap
    for(int i = 0; i < capacity; i++){
        tempHeap[i] = i;
        tempDataToHeap[i] = -1;
    }

    for(int i = 0; i < capacity / 2; i++){
        tempHeap[i] = heapAndFreeStack[i];
        temp[i] = data[i];
        tempDataToHeap[i] = dataToHeap[i];
    }

    delete []data;
    delete []heapAndFreeStack;
    delete []dataToHeap;

    data = temp;
    heapAndFreeStack = tempHeap;
    dataToHeap = tempDataToHeap;
}

template <typename T>
void ArrayHeap<T>::bubbleUp(int ndx){
    if(ndx == 0){
        return;
    }

    int parent = floor((ndx - 1) / 2);
    
    if( data[heapAndFreeStack[ndx]] < data[heapAndFreeStack[parent]]){
        swap(heapAndFreeStack[parent], heapAndFreeStack[ndx]);
        swap(dataToHeap[heapAndFreeStack[parent]], dataToHeap[heapAndFreeStack[ndx]]);

        bubbleUp(parent);
    }
}

template <typename T>
void ArrayHeap<T>::bubbleDown(int ndx){
    int size = getNumItems();
    int left = 2 * ndx + 1;
    int right = 2 * ndx + 2;

    if(size <= left){
        return;
    }

    int min = ndx;

    if(data[heapAndFreeStack[left]] < data[heapAndFreeStack[ndx]] ){
        min = left;
    }
    if((right < size) && (data[heapAndFreeStack[right]] < data[heapAndFreeStack[min]])){
        min = right;
    }

    if(min != ndx){
        swap(heapAndFreeStack[ndx], heapAndFreeStack[min]);
        swap(dataToHeap[heapAndFreeStack[ndx]], dataToHeap[heapAndFreeStack[min]]);
        
        bubbleDown(min);
    }
}


#endif


