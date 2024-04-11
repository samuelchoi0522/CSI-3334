/**
 * file: maze-proj1.cpp
 * author: Samuel Choi
 * course: CSI 3334
 * assignment: project 1
 * due date: Feb 2, 2024
 * version: 1.1
 * 
 * This file contains function definitions for maze-proj1.h.
 */

#include "maze-proj1.h"

/**
 * Maze
 * 
 * Default constructor for Maze.
*/
Maze::Maze(void){
    validLocationCount = 0;
    validLocations = nullptr;
}

/**
 * ~Maze
 * 
 * Destructor for Maze.
*/
Maze::~Maze(){
    delete []validLocations;
}

/**
 * getStartLocation
 * 
 * Returns the start location for the Maze.
 * 
 * Return value: the start location for the maze.
*/
Location Maze::getStartLocation(void) const{
    return startLocation;
}

/**
 * isValidLocation
 * 
 * Iterates through the current list of valid locations and returns true or false
 * if loc is equal to validLocations[i].
 * 
 * Parameters:
 * loc: the location that is being checked within the maze stack
 * 
 * Return value: true if the location is on the stack, false otherwise.
*/
bool Maze::isValidLocation(const Location &loc) const{
    for(int i = 0; i < validLocationCount; i++){
        if(validLocations[i] == loc){
            return true;
        }
    }
    return false;
}

/**
 * isEndLocation
 * 
 * Checks if loc is equal to the endLocation and returns true or false.
 * 
 * Parameters:
 * loc: the location that is being checked if it is the end location.
 * 
 * Return value: true if loc is equal to the endLocation, false otherwise.
*/
bool Maze::isEndLocation(const Location &loc) const{
    if(loc == endLocation){
        return true;
    }
    else{
        return false;
    }
}

/**
 * operator>>
 * 
 * Reads input from istream and updates the validLocationCount. It populates
 * the Maze object m with valid locations by reading input from is.
 * 
 * Parameters:
 *   is: a reference to an input stream (istream) from which input is read.
 *   m: a reference to a Maze object to be populated with input data.
 * 
 * Return value: returns the input stream is back for input chaining.
 */
istream &operator>>(istream &is, Maze &m) {
    delete []m.validLocations;

    is >> m.validLocationCount;

    m.validLocations = new Location[m.validLocationCount];

    for (int i = 0; i < m.validLocationCount; i++) {
        is >> m.validLocations[i];
    }

    is >> m.startLocation >> m.endLocation;

    return is;
}