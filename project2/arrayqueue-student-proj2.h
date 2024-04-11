/**
 * file: arrayqueue-student-proj2.h
 * author: Samuel Choi
 * course: CSI 3334
 * assignment: project 2
 * date: Feb 16, 2023
 * version: 1.0
 * 
 * This file contains the templated implementations of the arrayqueue-prof-proj2.h header
 * file and provides methods to interact with the ArrayQueue.
 */

#ifndef ARRAY_QUEUE_STUDENT_PROJ2_H
#define ARRAY_QUEUE_STUDENT_PROJ2_H

using namespace std;

#include "arrayqueue-prof-proj2.h"
#include <cassert>
template <typename Base>

/**
 * ArrayQueue constructor
 * 
 * This function initializes an ArrayQueue object.
 */
ArrayQueue<Base>::ArrayQueue(){
    length = 0;
    capacity = 10;
    front = 0;
    data = new Base[capacity];
}

/**
 * Copy constructor
 * 
 * This function initializes an ArrayQueue object with the contents of another queue.
 * 
 * Parameter:
 *   q: the queue to be copied to this queue.
 */
template <typename Base>
ArrayQueue<Base>::ArrayQueue(const ArrayQueue<Base> &q){
    length = q.length;
    capacity = q.capacity;
    front = q.front;
    data = new Base[capacity];
    for(int i = 0; i < length; i++){
        data[(front + i) % capacity] = q.data[(q.front + i) % q.capacity];
    }
}

/**
 * Destructor
 * 
 * This function deallocates memory used by the queue.
 */
template <typename Base>
ArrayQueue<Base>::~ArrayQueue(){
    delete []data;
}

/**
 * add
 * 
 * This function adds an item to the end of the queue.
 * 
 * Parameter:
 *   item: the item to be added.
 */
template <typename Base>
void ArrayQueue<Base>::add(const Base &item){
    if(length >= capacity){
        doubleCapacity();
    }
    int index = (front + length) % capacity;
    data[index] = item;
    length++;
}

/**
 * remove
 * 
 * This function removes the front item from the queue.
 */
template <typename Base>
void ArrayQueue<Base>::remove(){
    if(length > 0){
        front = (front + 1) % capacity;
        length--;
    }
}

/**
 * getFront
 * 
 * This function returns the front item of the queue.
 * 
 * Return value: the front item of the queue.
 */
template <typename Base>
const Base &ArrayQueue<Base>::getFront() const{
    return data[front];
}

/**
 * getLength
 * 
 * This function returns the current length of the queue.
 * 
 * Return value: the current length of the queue.
 */
template <typename Base>
int ArrayQueue<Base>::getLength() const{
    return length;
}

/**
 * Assignment operator
 * 
 * This function assigns the contents of one queue to another.
 * 
 * Parameter:
 *   q: the queue to be assigned.
 * 
 * Return value: a reference to the modified queue.
 */
template <typename Base>
const ArrayQueue<Base> &ArrayQueue<Base>::operator=(const ArrayQueue<Base> &q){
    if(this != &q){
        Base *temp = new Base[q.capacity];
        for(int i = 0; i < q.length; i++){
            temp[i] = q.data[(q.front + i) % q.capacity];
        }
        delete []data;
        data = temp;
        capacity = q.capacity;
        length = q.length;
        
        front = 0;
    }
    return *this;
}

/**
 * doubleCapacity
 * 
 * This function doubles the capacity of the array.
 */
template <typename Base>
void ArrayQueue<Base>::doubleCapacity(){
    int n = capacity * 2;
    Base *temp = new Base[n];
    for(int i = 0; i < length; i++){
        temp[i] = data[(front + i) % capacity];
    }
    delete []data;
    data = temp;
    capacity = n;
    front = 0;
}

#endif