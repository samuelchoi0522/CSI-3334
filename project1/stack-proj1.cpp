/**
 * file: stack-proj1.cpp
 * author: Samuel Choi
 * course: CSI 3334
 * assignment: project 1
 * due date: Feb 2, 2024
 * version: 1.1
 * 
 * This file contains function definitions for stack-proj1.h.
 */

#include "stack-proj1.h"

/**
 * LocationStack
 * 
 * Default constructor for LocationStack.
*/
LocationStack::LocationStack(void){
    top = nullptr;
}

/**
 * ~LocationStack
 * 
 * Destructor for LocationStack.
*/
LocationStack::~LocationStack() {
    delete top;
}



/**
 * push
 * 
 * This function pushes the given location to the stack and sets top equal to that pushed
 * location.
 * 
 * Parameters:
 * loc: the Location coordinates being pushed to the stack.
*/
void LocationStack::push(const Location &loc){
    LocationStackNode *temp = new LocationStackNode(loc, top);
    top = temp;
}

/**
 * pop
 * 
 * Removes the the top Location from the Location Stack and sets top to the next node.
*/
void LocationStack::pop() {
    if (!isEmpty()) {
        LocationStackNode *temp = top;
        top = top->getNextNode();
        temp->setNextNode(nullptr);
        delete temp;
    }
}

/**
 * getTop
 * 
 * Returns the top value of the LocationStack.
 * 
 * Return value: Location coordinates of the top of the stack.
*/
const Location &LocationStack::getTop(void) const{
    return top->getLocation();
}

/**
 * isEmpty
 * 
 * Returns true or false depending on if the LocationStack is empty.
 * 
 * Return value: true if the top is equal to nullptr. False if top is equal to a Location.
*/
bool LocationStack::isEmpty(void) const{
    if(top == nullptr){
        return true;
    }
    
    else{
        return false;
    }
}

/**
 * isOn
 * 
 * Returns true or false depending on if loc is on the LocationStack.
 * 
 * Parameters:
 * loc: the location that is being checked with on the stack.
 * 
 * Return value: returns true if loc is a value on the stack, returns false otherwise.
*/
bool LocationStack::isOn(const Location &loc) const{
    LocationStackNode *temp = top;

    while(temp != nullptr){

        if(temp->getLocation() == loc){
            return true;
        }

        else{
            temp = temp->getNextNode();
        }

    }
    return false;
}

/**
 * operator<<
 * 
 * Flips the LocationStack and writes it to the output stream os.
 * 
 * Parameters:
 *   os: the output stream to which the LocationStack will be written.
 *   s: a reference to the LocationStack to be written to the output stream.
 * 
 * Return value: returns os to allow for output chaining.
 */
ostream &operator<<(ostream &os, const LocationStack &s) {
    LocationStackNode *curr = s.top;
    LocationStackNode *prev = nullptr;
    LocationStackNode *next = s.top;

    while (curr != nullptr) {
        next = next->getNextNode();
        curr->setNextNode(prev);
        prev = curr;
        curr = next;
    }

    curr = next = prev;
    prev = nullptr;

    while (curr != nullptr) {
        os << curr->getLocation() << endl;
        next = next->getNextNode();
        curr->setNextNode(prev);
        prev = curr;
        curr = next;
    }

    return os;
}



/**
 * LocationStackNode
 * 
 * Default constructor for LocationStackNode.
 * 
 * Parameters:
 * loc: the location that is being created as a new node.
 * next: the next Node that loc will be pointing at.
 * 
*/
LocationStackNode::LocationStackNode(const Location &loc, LocationStackNode *next){
    location = loc;
    nextNode = next;
}

/**
 * ~LocationStackNode
 * 
 * Destructor for LocationStackNode.
*/
LocationStackNode::~LocationStackNode(){
    delete nextNode;
}

/**
 * getLocation
 * 
 * Returns the location in the LocationStackNode.
 * 
 * Return value: the location of the current position in the stack.
*/
const Location &LocationStackNode::getLocation() const{
    return location;
}

/**
 * getNextNode
 * 
 * Returns the next node in the LocationStackNode.
 * 
 * Return value: returns the next node of the current position in the stack.
*/
LocationStackNode *LocationStackNode::getNextNode() const{
    return nextNode;
}

/**
 * setNextNode
 * 
 * Sets nextNode to next.
 * 
 * Parameters: 
 * next: the next node that the top of the stack will be pointing to.
*/
void LocationStackNode::setNextNode(LocationStackNode *next){
    nextNode = next;
}