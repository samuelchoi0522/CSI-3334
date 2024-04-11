/**
 * file: arrayheap-student-proj5.h
 * author: Samuel Choi
 * course: CSI 3334
 * assignment: project 5
 * due date: April 5, 2024
 * version: 1.0
 * 
 * This file contains the definitions of the functions in arrayheap-prof-proj5.h
 */

#ifndef ARRAY_HEAP_PROJ5_STUDENT_H
#define ARRAY_HEAP_PROJ5_STUDENT_H

#include "arrayheap-prof-proj5.h"
#include <algorithm>
#include <iostream>


using namespace std;


/**
 * ArrayHeap Constructor
 *
 * Initializes an ArrayHeap object with default values for the number of items and capacity, 
 * and allocates memory for the data array and heapAndFreeStack array.
 */
template <typename T>
ArrayHeap<T>::ArrayHeap(){
    numItems = 0;
    capacity = 10;
    data = new T[capacity];
    heapAndFreeStack = new int[capacity];

    for(int i = 0; i < capacity; i++){
        heapAndFreeStack[i] = i;
    }

}

/**
 * ArrayHeap Copy Constructor
 *
 * Creates a deep copy of the given ArrayHeap object.
 * 
 * Parameters:
 *   h: The ArrayHeap object to copy
 */
template <typename T>
ArrayHeap<T>::ArrayHeap(ArrayHeap<T> const &h){
    numItems = h.numItems;
    capacity = h.capacity;

    delete []data;
    delete []heapAndFreeStack;

    data = new T[capacity];
    heapAndFreeStack = new int[capacity];

    for (int i = 0; i < capacity; i++) {
        heapAndFreeStack[i] = h.heapAndFreeStack[i];
        data[i] = h.data[i];
    }
}

/**
 * ArrayHeap Destructor
 *
 * Deallocates memory for the data array and heapAndFreeStack array.
 */
template <typename T>
ArrayHeap<T>::~ArrayHeap(){
    delete []data;
    delete []heapAndFreeStack;

    data = nullptr;
    heapAndFreeStack = nullptr;
}

/**
 * operator=
 *
 * Assigns the contents of the given ArrayHeap object to this ArrayHeap object.
 * 
 * Parameters:
 *   ah: The ArrayHeap object to copy
 * 
 * Return value: A reference to this ArrayHeap object after assignment
 */
template <typename T>
ArrayHeap<T> const &ArrayHeap<T>::operator=(ArrayHeap<T> const &ah){
    if(this != &ah){
        numItems = ah.numItems;
        capacity = ah.capacity;

        delete []data;
        delete []heapAndFreeStack;

        data = new T[capacity];
        heapAndFreeStack = new int[capacity];

        for(int i = 0; i < capacity; i++){
            heapAndFreeStack[i] = ah.heapAndFreeStack[i];
            data[i] = ah.data[i];
        }
    }

    return *this;
}

/**
 * insert
 *
 * Inserts an item into the heap, ensuring that the heap property is maintained.
 * 
 * Parameters:
 *   item: The item to insert into the heap
 */
template <typename T>
void ArrayHeap<T>::insert(T const &item){
    if(numItems == capacity){
        doubleCapacity();
    }

    data[heapAndFreeStack[numItems]] = item;
    bubbleUp(numItems);

    numItems++;
}

/**
 * removeMinItem
 *
 * Removes the minimum item from the heap, ensuring that the heap property is maintained.
 */
template <typename T>
void ArrayHeap<T>::removeMinItem(){
    if(numItems == 0){
        return;
    }

    swap(heapAndFreeStack[0], heapAndFreeStack[numItems - 1]);
    numItems--;

    bubbleDown(0);
}

/**
 * getMinItem
 *
 * Retrieves the minimum item from the heap.
 * 
 * Return value: A reference to the minimum item in the heap
 */
template <typename T>
T const &ArrayHeap<T>::getMinItem() const{
    return data[heapAndFreeStack[0]];
}

/**
 * getNumItems
 *
 * Gets the number of items currently in the heap.
 * 
 * Return value: The number of items in the heap
 */
template <typename T>
int ArrayHeap<T>::getNumItems() const{
    return numItems;
}

/**
 * doubleCapacity
 *
 * Doubles the capacity of the heap and reallocates memory for the data array and 
 * heapAndFreeStack array.
 */
template <typename T>
void ArrayHeap<T>::doubleCapacity(){
    capacity *= 2;

    T *temp = new T[capacity];
    int *tempHeap = new int[capacity];

    //init values of heap
    for(int i = 0; i < capacity; i++){
        tempHeap[i] = i;
    }

    for(int i = 0; i < capacity / 2; i++){
        tempHeap[i] = heapAndFreeStack[i];
        temp[i] = data[i];
    }

    delete []data;
    delete []heapAndFreeStack;

    data = temp;
    heapAndFreeStack = tempHeap;
}

/**
 * bubbleUp
 *
 * Moves an item up in the heap until the heap property is satisfied.
 * 
 * Parameters:
 *   ndx: The index of the item to bubble up
 */
template <typename T>
void ArrayHeap<T>::bubbleUp(int ndx){
    if(ndx == 0){
        return;
    }

    int parent = floor((ndx - 1) / 2);
    
    if( data[heapAndFreeStack[ndx]] < data[heapAndFreeStack[parent]]){
        swap(heapAndFreeStack[parent], heapAndFreeStack[ndx]);
        bubbleUp(parent);
    }
}


/**
 * bubbleDown
 *
 * Moves an item down in the heap until the heap property is satisfied.
 * 
 * Parameters:
 *   ndx: The index of the item to bubble down
 */
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
        bubbleDown(min);
    }
}


#endif
