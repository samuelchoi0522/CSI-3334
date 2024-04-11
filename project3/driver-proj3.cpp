/**
 * file: driver-proj3.cpp
 * author: Samuel Choi
 * course: CSI 3334
 * assignment: project 3
 * due date: March 1, 2024 
 * version: 1.0
 * 
 * This file is the driver that reads in commands from input and encrypt/decrypts
 * them according to the command.
 */
#include <iostream>
#include <sstream>
#include <string>
#include "bst-student-proj3.h"

using namespace std;

/**
 * Main
 *
 * This is entry point for the program. It reads input commands from the 
 * standard input and processes them accordingly to perform encryption, 
 * decryption, insertion, removal, printing in preorder,
 * or quitting the program.
 * 
 * Return value: 0 if the program runs without fault, 1 if an error is detected.
 * 
*/
int main() {
    EncryptionTree<string> *codebook = new EncryptionTree<string>();
    string inp;

    while(getline(cin, inp)){
        stringstream ss;
        string inpWord;
        ss << inp;
        char cmnd;
        ss >> cmnd;


        //input
        if(cmnd == 'i'){
            ss >> inpWord;
            codebook->insert(inpWord);
        }

        //remove
        else if(cmnd == 'r'){
            ss >> inpWord;
            codebook->remove(inpWord);
        }

        //encrypt
        else if (cmnd == 'e') {
            string message;
            getline(ss, message, '\'');
            getline(ss, message, '\'');
            stringstream word_ss(message);
            bool firstWord = true;

            while (word_ss >> inpWord) {
                if (!firstWord)
                    cout << " ";
                string encrypted = codebook->encrypt(inpWord);
                cout << encrypted;
                firstWord = false;
            }
            cout << endl;
        }

        //decrypt
        else if (cmnd == 'd') {
            string message;
            getline(ss, message, '\'');
            getline(ss, message, '\'');
            stringstream path_ss(message);
            bool firstWord = true;
            while (path_ss >> inpWord) {
                if (!firstWord)
                    cout << " ";
                const string *decrypted = codebook->decrypt(inpWord);
                if (decrypted)
                    cout << *decrypted;
                else
                    cout << "?";
                firstWord = false;
            }
            cout << endl;
        }
        
        //print preorder
        else if (cmnd == 'p') {
            codebook->printPreorder(cout);
        }

        //quit
        else if (cmnd == 'q') {
            break;
        }
    }

    delete codebook;
    
    return 0;
}
