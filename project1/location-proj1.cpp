/**
 * file: location-proj1.cpp
 * author: Samuel Choi
 * course: CSI 3334
 * assignment: project 1
 * due date: Feb 2, 2024
 * version: 1.1
 * 
 * This file contains function definitions for location-proj1.h.
 */

#include "location-proj1.h"

/**
 * Location
 * 
 * The default constructor for Location.
*/
Location::Location(){
    col = 0;
    row = 0;
    nextDirection = DONE;
}

/**
 * iterationBegin
 * 
 * Sets the default iteration to RIGHT (0).
*/
void Location::iterationBegin(){
    nextDirection = RIGHT;
}

/**
 * iterationCurrent
 * 
 * Changes the location of neighbor by moving it one place on the maze depending on 
 * the current direction.
 * 
 * Return value: returns neighbor with the updates col/row position.
*/
Location Location::iterationCurrent() const{
    Location neighbor = *this;

    if(nextDirection == RIGHT){
        neighbor.col++;
    }
    else if(nextDirection == DOWN){
        neighbor.row++;
    }
    else if(nextDirection == LEFT){
        neighbor.col--;
    }
    else if(nextDirection == UP){
        neighbor.row--;
    }

    return neighbor;
}

/**
 * iterationAdvance
 * 
 * Changes the iteration to the next iteration once called upon.
*/
void Location::iterationAdvance(){
    if(nextDirection == RIGHT){
        nextDirection = DOWN;
    }
    else if(nextDirection == DOWN){
        nextDirection = LEFT;
    }
    else if(nextDirection == LEFT){
        nextDirection = UP;
    }
    else if(nextDirection == UP){
        nextDirection = DONE;
    }
}

/**
 * iterationDone
 * 
 * Returns true or false depending on if the current direction is done.
 * 
 * Return value: returns true if the direction is DONE (4), false otherwise.
*/
bool Location::iterationDone() const{
    return nextDirection == DONE;
}

/**
 * operator==
 * 
 * Returns true of false depending on if the current location is equal to loc.
 * 
 * Parameters:
 * loc: the location that is being checked with the current location
 * 
 * Return value: returns true if loc.row and loc.col is equal to the current row and col,
 * false otherwise.
*/
bool Location::operator==(const Location &loc) const{
    return (row == loc.row) && (col == loc.col);
}

/**
 * operator<<
 * 
 * Outputs loc.row and loc.col to the output stream os.
 * 
 * Parameters:
 *   os: a reference to an output stream (ostream) to which the location
 *       information is being written.
 *   loc: the Location object that is being inserted into the output stream.
 * 
 * Return value: returns the output stream os to allow output stream chaining.
 */
ostream &operator<<(ostream &os, const Location &loc){
    os  << loc.row << " " << loc.col;
    return os;
}

/**
 * operator>>
 * 
 * Reads in loc.row and loc.col from the input stream is and stores the
 * information in the given Location object loc.
 * 
 * Parameters:
 *   is: a reference to an input stream (istream) from which input is read.
 *   loc: the Location object where the read information is being stored.
 * 
 * Return value: returns the input stream is to allow input chaining.
 */
istream &operator>>(istream &is, Location &loc){
    is >> loc.row;
    is >> loc.col;
    return is;
}
