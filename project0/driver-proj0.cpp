/* CSI 3334
 * Project 0 -- Undo Redo
 * Filename: driver-proj0.cpp
 * Student name: Samuel Choi
 *
 * Contains the program that enables the user to type, undo, and redo a text file,
 * similar to that of a .txt file.
 */
#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include <sstream>

using namespace std;

/* main
 *  parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  return value: 0 (indicating a successful run)
 *
 *  The main function reads in the first input which determines the amount
 *  of times the loops is required to run. Then it checks for any functions
 *  calling empty stacks and reports an error if it is done so. Then, utilizing
 *  if statements, we look for the input (t,r,u) and perform the respective
 *  tasks. Words were pushed to the typing stack for t, word were put into a
 *  temp variable before being popped and pushed to their respective stacks
 *  for r and u. Then the typing and undo stacks were reversed in order to print
 *  the typing and undo stack from 'bottom to top'.
 */
int main(int argc, char **argv){
    // these are the two stacks used to store the typed words and the undone
    // words
    stack<string> typing, undo;
    int n;
    char func;
    string word, popped;

    // input for amount of times to run
    cin >> n;

    // input for t, r, u
    for (int i = 1; i <= n; i++){
        cin >> func;

        // check for empty stacks
        if (func == 'u' && typing.empty() == 1){
            cout << "nothing to undo on command " << i << endl;
        }

        else if (func == 'u'){
            popped = typing.top();
            typing.pop();
            undo.push(popped);
        }

        if (func == 'r' && undo.empty() == 1){
            cout << "nothing to redo on command " << i << endl;
        }

        else if (func == 'r'){
            popped = undo.top();
            undo.pop();
            typing.push(popped);
        }
        if (func == 't'){
            cin >> word;
            typing.push(word);
        }
    }

    // reverse stack
    stack<string> revtyping, revundo;
    string temp;
    int tsize = typing.size();
    int usize = undo.size();

    for (int i = 0; i < tsize; i++){
        temp = typing.top();
        typing.pop();
        revtyping.push(temp);
    }
    for (int i = 0; i < usize; i++){
        temp = undo.top();
        undo.pop();
        revundo.push(temp);
    }

    // print lists
    for (int i = 1; i <= tsize; i++){
        if (i == tsize){
            cout << revtyping.top();
        }
        else{
            cout << revtyping.top() << " ";
        }
        revtyping.pop();
    }
    cout << endl;

    for (int i = 1; i <= usize; i++){
        if (i == usize){
            cout << revundo.top();
        }
        else{
            cout << revundo.top() << " ";
        }
        revundo.pop();
    }
    cout << endl;

    return 0;
}