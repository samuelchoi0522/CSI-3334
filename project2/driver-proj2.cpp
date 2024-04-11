/**
 * file: driver-proj2.cpp
 * author: Samuel Choi
 * course: CSI 3334
 * assignment: project 2
 * date: Feb 16, 2023
 * version: 1.0
 * 
 * This file contains an implementation of a word search program using breadth-first search.
 */

#include <iostream>
#include "arrayqueue-student-proj2.h"
#include "location-proj2.h"
#include "maze-proj2.h"
#include <map>
#include <stack>

using namespace std;

/**
 * main
 * 
 * This function serves as the entry point of the maze solver program. It reads a maze
 * from standard input, performs breadth-first search to find a path from the start
 * location to the end location, and then outputs the solution if found.
 * 
 * Return Value: int, an indication if the main ran without fault.
 */
int main() {
    Maze maze;
    Location currLoc, neighbor;
    ArrayQueue<Location> arrQueue;
    map<Location, Location> previousLocations;

    cin >> maze;

    currLoc = maze.getStartLocation();
    arrQueue.add(currLoc);
    previousLocations[currLoc] = currLoc;

    neighbor = currLoc;

    while (!maze.isEndLocation(currLoc) && !(arrQueue.getLength() == 0)) {
        currLoc = arrQueue.getFront();
        arrQueue.remove();

        currLoc.iterationBegin();
        while (!currLoc.iterationDone()) {
            neighbor = currLoc.iterationCurrent();
            bool notPrev = previousLocations.find(neighbor) == previousLocations.end();
            if (maze.isValidLocation(neighbor) && notPrev) {
                arrQueue.add(neighbor);
                previousLocations[neighbor] = currLoc;
            }
            currLoc.iterationAdvance();
        }
    }

    if (maze.isEndLocation(currLoc)) {
        stack<Location> finalSolution;
        cout << "Solution found" << endl;

        while (!(currLoc == maze.getStartLocation())) {
            finalSolution.push(currLoc);
            currLoc = previousLocations[currLoc];
        }
        finalSolution.push(maze.getStartLocation());
        while(!finalSolution.empty()){
            cout << finalSolution.top() << endl;
            finalSolution.pop();
        }
    } 
    else {
        cout << "No solution" << endl;
    }

    return 0;
}
