/**
 * file: location-proj2.cpp
 * author: Samuel Choi
 * course: CSI 3334
 * assignment: project 2
 * date: Feb 16, 2023
 * version: 1.0
 * 
 * This file contains the implementation of the location class, which represents 
 * the locations in a maze and provides methods to interact with the locations.
 */

#include "location-proj2.h"

/**
 * Location constructor
 * 
 * This function initializes a Location object.
 */
Location::Location(){
    word = "";
    iterationMode = DONE;
    indexToChange = 0;
    nextLetter = 'a';
}

/**
 * iterationBegin
 * 
 * This function prepares the location for iteration.
 */
void Location::iterationBegin(void){
    iterationMode = CHANGE_LETTER;
    indexToChange = 0;
    nextLetter = 'a';
    if(word[indexToChange] == nextLetter){
        nextLetter++;
    }
}

/**
 * iterationCurrent
 * 
 * This function returns the current neighbor during iteration.
 * 
 * Return value: the current neighbor.
 */
Location Location::iterationCurrent(void) const{
    Location neighbor = *this;

    if(iterationMode == CHANGE_LETTER){
        neighbor.word[indexToChange] = nextLetter;
    }
    else if(iterationMode == INSERT_LETTER){
        neighbor.word.insert(indexToChange, 1, nextLetter);
    }
    else if(iterationMode == DELETE_LETTER){
        neighbor.word.erase(indexToChange, 1);
    }

    return neighbor;
}

/**
 * iterationAdvance
 * 
 * This function advances the iteration to the next neighbor.
 */
void Location::iterationAdvance(void) {
    if (iterationMode == CHANGE_LETTER) {
        nextLetter++;
        if (nextLetter > 'z') {
            nextLetter = 'a';
            indexToChange++;
            if (indexToChange >= word.length()) {
                iterationMode = INSERT_LETTER;
                indexToChange = 0;
            }
        }
        if(word[indexToChange] == nextLetter){
            nextLetter++;
            if(nextLetter > 'z'){
                nextLetter = 'a';
                indexToChange++;
                if(word[indexToChange] == nextLetter){
                    nextLetter++;
                }
                if (indexToChange >= word.length()) {
                    iterationMode = INSERT_LETTER;
                    indexToChange = 0;
                }
            }
        }
    }
    else if (iterationMode == INSERT_LETTER) {
        nextLetter++;
        if (nextLetter > 'z') {
            nextLetter = 'a';
            indexToChange++;
            if (indexToChange > word.length()) {
                iterationMode = DELETE_LETTER;
                indexToChange = 0;
            }
        }
    }
    else if (iterationMode == DELETE_LETTER) {
        indexToChange++;
        if (indexToChange >= word.length()) {
            iterationMode = DONE;
        }
    }

}

/**
 * iterationDone
 * 
 * This function checks if the iteration is DONE.
 * 
 * Return value: true if the iteration is DONE, false otherwise.
 */
bool Location::iterationDone(void) const{
    return iterationMode == DONE;
}

/**
 * operator==
 * 
 * This function checks if two locations are equal.
 * 
 * Parameter:
 *   loc: the location to compare with.
 * 
 * Return value: true if the locations are equal, false otherwise.
 */
bool Location::operator==(const Location &loc) const{
    return word == loc.word;
}

/**
 * operator<<
 * 
 * This function allows printing a location to an output stream.
 * 
 * Parameters:
 *   os: the output stream.
 *   loc: the location to print.
 * 
 * Return value: a reference to the output stream.
 */
ostream &operator<<(ostream &os, const Location &loc){
    os << loc.word;
    return os;
}

/**
 * operator>>
 * 
 * This function allows reading a location from an input stream.
 * 
 * Parameters:
 *   is: the input stream.
 *   loc: the location to read into.
 * 
 * Return value: a reference to the input stream.
 */
istream &operator>>(istream &is, Location &loc){
    is >> loc.word;
    return is;
}

/**
 * operator<
 * 
 * This function compares two locations.
 * 
 * Parameter:
 *   loc: the location to compare with.
 * 
 * Return value: true if this location is less than the other, false otherwise.
 */
bool Location::operator<(const Location &loc) const{
    return word < loc.word;
}