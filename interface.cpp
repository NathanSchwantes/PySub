#include <iostream>
#include "interface.h"
#include <fstream>
#include <iostream>

using namespace std;

void Interface::startInterface()
{
    cout << "PySUB Interpreter 1.0 on Windows (September 2022)" << endl;
    cout << "By: Nathan Schwantes - CSCI 230 - Fall 2022" << endl;
    cout << "Enter program lines or read (<filename>.py) at command line interface" << endl;
    cout << "Type 'help' for more information or 'quit' to exit" << endl;

    bool quitStatus = false;

    while (!quitStatus) {

        // accepts user input
        string input;
        cout << ">>>";
        getline(cin, input);

        // quit
        if (input == "quit()" || input == "quit") {
            quitStatus = true;
        }

        // read
        // gets fileName and fileExtension from input
        size_t extensionIndex;
        string fileExtension;
        string fileName;

        extensionIndex = input.find_last_of(".");
        fileExtension = input.substr(extensionIndex);
        fileName = input.substr(5, extensionIndex - 2);

        //checks that fileExtension is a python file.
        if (input.substr(0, 5) == "read(" && fileExtension == ".py)") {

            programCode.clear();

            ifstream fileRead;
            fileRead.open(fileName);

            if (!fileRead) {
                cout << "please enter valid file" << endl;
            }

            string lines;
            while (getline(fileRead, lines)) {
                programCode.push_back(lines);
            }

        }
        else {
            cout << "error or did not submit correct file extension" << endl;
        }

        // show
        if (input == "show" || input == "show()") {

        }

    }
}