/**
 * file: driver-proj1.cpp
 * author: Samuel Choi
 * course: CSI 3334
 * assignment: project 1
 * due date: Feb 2, 2024
 * version: 1.1
 * 
 * This file contains the driver that allows the user to input a set of coordinates
 * for a maze game. Using that input, the driver solves the maze and outputs a list of
 * coordinates that the code took to find the end location.
 */

#include "location-proj1.h" 
#include "maze-proj1.h" 
#include "stack-proj1.h"
#include <iostream>
#include <stack>

using namespace std;

/**
 * main
 * 
 * Reads in file into maze, which then reads into validLocationCount and the list of 
 * validLocations. The game runs until either: the end location is reached, or when the
 * stack is empty. If the stack is empty, the game will report "No solution" or will report
 * "Solution found" with the coordinate path it took to find the end location.
 * 
 * Return value: 0, indicating the function ran without fault.
*/
int main(){
    Maze maze;
    Location currLoc, neighbor;
    LocationStack mazeStack;

    cin >> maze;
    
    currLoc = maze.getStartLocation();
    currLoc.iterationBegin();
    neighbor.iterationBegin();
    mazeStack.push(currLoc);
    neighbor = currLoc;
    
    while (!maze.isEndLocation(currLoc)) {
        neighbor = neighbor.iterationCurrent();
        neighbor.iterationBegin();

        if (maze.isValidLocation(neighbor) && !mazeStack.isOn(neighbor)) {
            mazeStack.pop();
            currLoc.iterationAdvance();
            mazeStack.push(currLoc);
            currLoc = neighbor;
            mazeStack.push(currLoc);
        } 

        else {
            currLoc.iterationAdvance();
            neighbor = currLoc;
        }

        if (neighbor.iterationDone()) {
            mazeStack.pop();

            if (mazeStack.isEmpty()) {
                cout << "No solution" << endl;
                break;
            }

            currLoc = mazeStack.getTop();
            neighbor = currLoc;
        } 


    }

    if(maze.isEndLocation(currLoc)){
        cout << "Solution found" << endl;
        cout << mazeStack;
    }

    return 0;
}