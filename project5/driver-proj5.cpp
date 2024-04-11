/**
 * file: driver-proj5.cpp
 * author: Samuel Choi
 * course: CSI 3334
 * assignment: project 5
 * due date: April 5, 2024
 * version: 1.0
 * 
 * This file is the driver that reads in submission/deadline/required time followed 
 * by a string and is ordered in a min-heap. It processes/skips the highest priority 
 * process depending on the current SYSTEM time. 
 */

#include "arrayheap-student-proj5.h"
#include "process-proj5.h"
#include <iostream>
#include <iomanip>

using namespace std;

/**
 * Main
 * 
 * This is the function that reads in submission/deadline/required time followed 
 * by a string and is ordered in a min-heap. It processes/skips the highest priority 
 * process depending on the current SYSTEM time. 
*/
int main(){
    ArrayHeap<Process> processHeap;
    int finalSystemTime = 0;
    int finalProcessesRun = 0;
    int finalProcessesSkipped = 0;

    int numProcesses;
    cin >> numProcesses;

    for(int i = 0; i < numProcesses; i++){
        Process currProcess(i);
        cin >> currProcess;

        if(currProcess.getSubmissionTime() <= finalSystemTime){
            processHeap.insert(currProcess);
        }

        else if(processHeap.getNumItems() == 0){
            finalSystemTime = currProcess.getSubmissionTime();
            processHeap.insert(currProcess);
        }
        else{
            while(processHeap.getNumItems() != 0){
                Process highestPri = processHeap.getMinItem();

                processHeap.removeMinItem();
                if(highestPri.canComplete(finalSystemTime)){
                    finalSystemTime = highestPri.run(finalSystemTime);

                    finalProcessesRun++;
                }
                else{
                    cout << "skipping process id " << highestPri.getId() << 
                    " at " << finalSystemTime << endl;

                    finalSystemTime++;

                    finalProcessesSkipped++;
                }
                

                if(currProcess.getSubmissionTime() <= finalSystemTime && 
                currProcess.getId() != highestPri.getId()){
                    processHeap.insert(currProcess);
                    break;
                }
                else if(processHeap.getNumItems() == 0){
                    finalSystemTime = currProcess.getSubmissionTime();
                    processHeap.insert(currProcess);
                    break;
                }
            }
        }
        
    }

    while(processHeap.getNumItems() != 0){
        Process highestPri = processHeap.getMinItem();

        processHeap.removeMinItem();

        if(highestPri.canComplete(finalSystemTime)){
            finalSystemTime = highestPri.run(finalSystemTime);

            finalProcessesRun++;
        }
        else{
            cout << "skipping process id " << highestPri.getId() << " at " 
            << finalSystemTime << endl;

            finalSystemTime++;

            finalProcessesSkipped++;
        }
        
    }


    cout << "final clock is                 " << finalSystemTime << endl;
    cout << "number of processes run is     " << finalProcessesRun << endl;
    cout << "number of processes skipped is " << finalProcessesSkipped << endl;

    return 0;
}