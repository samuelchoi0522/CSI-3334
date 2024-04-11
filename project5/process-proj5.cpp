/**
 * file: process-proj5.cpp
 * author: Samuel Choi
 * course: CSI 3334
 * assignment: project 5
 * due date: April 5, 2024
 * version: 1.0
 * 
 * This file contains the definitions of the functions in process-proj5.h
 */

#include "process-proj5.h"

/**
 * Process Constructor
 *
 * Initializes a Process object with the given ID and default values for submission 
 * time, deadline, required time, and information.
 * 
 * Parameters:
 *   theId: ID of the process
 */
Process::Process(int theId){
    id = theId;
    submissionTime = 0;
    deadline = 0;
    requiredTime = 0;
    information = "";
}

/**
 * run
 *
 * Executes the process at the current SYSTEM time, printing out its ID, current 
 * SYSTEM time, and information. Returns the updated SYSTEM time after the process 
 * completes.
 * 
 * Parameters:
 *   currentSystemTime: The current SYSTEM time when the process runs
 * 
 * Return value: The updated SYSTEM time after the process completes
 */
int Process::run(int currentSystemTime) const{
    cout << "running process id " << id << " at " << currentSystemTime << endl;
    cout << information << endl;
    return currentSystemTime + requiredTime;
}

/**
 * canComplete
 *
 * Checks whether the process can complete before its deadline based on the current 
 * SYSTEM time.
 * 
 * Parameters:
 *   currentSystemTime: The current SYSTEM time
 * 
 * Return value: True if the process can complete before the deadline, false otherwise
 */
bool Process::canComplete(int currentSystemTime) const{
    return (currentSystemTime + requiredTime) <= deadline;
}

/**
 * getId
 *
 * Gets the ID of the process.
 * 
 * Return value: The ID of the process
 */
int Process::getId() const{
    return id;
}

/**
 * getSubmissionTime
 *
 * Gets the submission time of the process.
 * 
 * Return value: The submission time of the process
 */
int Process::getSubmissionTime() const{
    return submissionTime;
}

/**
 * operator<
 *
 * Compares two Process objects based on their deadlines, required times, and IDs.
 * 
 * Parameters:
 *   p: The Process object to compare with
 * 
 * Return value: True if this process has a lower priority than the other process, 
 * false otherwise
 */
bool Process::operator<(Process const &p) const{
    if (deadline != p.deadline){
        return deadline < p.deadline;
    }

    if (requiredTime != p.requiredTime){
        return requiredTime < p.requiredTime;
    }

    return id < p.id;
}

/**
 * operator>>
 *
 * Reads in data from the input stream into the Process object, including 
 * submission time, deadline, required time, and information.
 * 
 * Parameters:
 *   is: The input stream
 *   p: The Process object to store the read-in data
 * 
 * Return value: The input stream after the read operation
 */
istream &operator>>(istream &is, Process &p){
    is >> p.submissionTime;
    is >> p.deadline;
    is >> p.requiredTime;

    getline(is >> ws, p.information);

    return is;
}

/////////////////////////////////////////////////////////////

//delete

int Process::getDeadline() const{
    return deadline;
}

int Process::getRequiredTime() const{
    return requiredTime;
}

string Process::getInformation() const{
    return information;
}
// delete this
ostream &operator<<(ostream &os, Process &p){
    os << p.getSubmissionTime() << " " << p.getDeadline() << " " << p.getRequiredTime() << " " << p.getInformation();
    return os;
}

/////////////////////////////////////////////////////////