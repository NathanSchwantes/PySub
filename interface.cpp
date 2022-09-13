#include <iostream>
#include "interface.h"
#include <fstream>
#include <ostream>

using namespace std;

void Interface::startInterface()
{
    cout << "PySUB Interpreter 1.0 on Windows (September 2022)" << endl;
    cout << "By: Nathan Schwantes - CSCI 230 - Fall 2022" << endl;
    cout << "Enter program lines or read (<filename>.py) at command line interface" << endl;
    cout << "Type 'help' for more information or 'quit' to exit" << endl;

    string input;

    cout << ">>>";

    getline(cin, input);

    bool quitStatus = false;

    while (!quitStatus) {

        // quit
        if (input == "quit()" || input == "quit") {
            quitStatus = true;
        }

        //read needs to be read( <filename.py> )
        //check if first 5 chars of text == read(
        //check if last char is == .py)
        vector<string> input;
        vector<string> vlast(4);
        copy(input.end() - vlast.size(), input.end(), vlast.begin());
        cout << vlast.size() << endl;
        //if (input.substr(0,5) == "read(" || input.)

    }
}