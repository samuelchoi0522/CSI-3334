/**
 * file: maze-proj2.cpp
 * author: Samuel Choi
 * course: CSI 3334
 * assignment: project 2
 * date: Feb 16, 2023
 * version: 1.0
 * 
 * This file contains the implementation of the Maze class, which represents a maze
 * and provides methods to interact with it.
 */
#include "maze-proj2.h"

/**
 * Maze constructor
 * 
 * This function initializes a Maze object.
 */
Maze::Maze(void){
}

/**
 * getStartLocation
 * 
 * This function returns the starting location of the maze.
 * 
 * Return value: the starting location of the maze.
 */
Location Maze::getStartLocation(void) const{
    return startLocation;
}

/**
 * isValidLocation
 * 
 * This function checks if a given location is valid (i.e., within the maze).
 * 
 * Parameter:
 *   loc: the location to be checked.
 * 
 * Return value: true if the location is valid, false otherwise.
 */
bool Maze::isValidLocation(const Location &loc) const{
    return validLocations.find(loc) != validLocations.end();
}

/**
 * isEndLocation
 * 
 * This function checks if a given location is the end location of the maze.
 * 
 * Parameter:
 *   loc: the location to be checked.
 * 
 * Return value: true if the location is the end location, false otherwise.
 */
bool Maze::isEndLocation(const Location &loc) const{
    return loc == endLocation;
}

/**
 * operator>>
 * 
 * This function overloads the >> operator to allow reading maze data from input stream.
 * 
 * Parameters:
 *   is: the input stream to read from.
 *   m: the Maze object to store the read data.
 * 
 * Return value: a reference to the input stream in order to allow input chaining.
 */
istream &operator>>(istream &is, Maze &m){
    m.validLocations.clear();
    int numLocations;
    Location temp;
    is >> numLocations;

    for(int i = 0; i < numLocations; i++){
        is >> temp;
        m.validLocations.insert(temp);
    }

    is >> m.startLocation;
    is >> m.endLocation;

    return is;
}