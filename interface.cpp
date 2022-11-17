#include <iostream>
#include "interface.h"
#include "lexanalyzer.h"
#include "expEvaluator.h"
#include "interpreter.h"
#include <fstream>

using namespace std;

void Interface::startInterface()
{
    // allows for conversion to string for createTokens() interpretation
    vector<string> expressionEval;
    // lexicalAnalyzer class declaration
    LexicalAnalyzer lexAnalysis;
    // expEvaluator class declaration
    expEvaluator expEvaluation;
    // Interpreter class declaration
    Interpreter pysubi;

    cout << "PySUB Interpreter 1.0 on Windows (September 2022)" << endl;
    cout << "By: Nathan Schwantes - CSCI 230 - Fall 2022" << endl;
    cout << "Enter program lines or read (<filename>.py) at command line interface" << endl;
    cout << "Type 'help' for more information or 'quit' to exit" << endl;

    bool quitStatus = false;

    while (!quitStatus) {

        // accepts user input
        string input;
        cout << ">>> ";
        getline(cin, input);
        expressionEval.push_back(input);

        // quit
        if (input == "quit()" || input == "quit") {
            quitStatus = true;
        }

        // read
        // gets fileName and fileExtension from input
        else if (input.substr(0, 5) == "read(" && input.size() > 8 && input.find(".") != string::npos) {
            size_t extensionIndex;
            string fileExtension;
            string fileName;

            extensionIndex = input.find_last_of(".");
            fileExtension = input.substr(extensionIndex);
            fileName = input.substr(5, extensionIndex - 2);
        

            //checks that fileExtension is a python file
            //reads the file into the programCode data structure
            if (fileExtension == ".py)") {

                programCode.clear();

                ifstream fileRead;
                fileRead.open(fileName);

                if (!fileRead) {
                    cout << "Error reading file, please type correct filename" << endl;
                    break;
                }

                string lines;
                while (getline(fileRead, lines)) {
                    programCode.push_back(lines);
                }

                // create tokens and add to tokenInfo struct
                lexAnalysis.createTokens(programCode);

                cout << "File sucessfully read. Use 'show' to view file content" << endl;
                fileRead.close();
            }
            else {
                cout << "Please enter filename with .py extension" << endl;
            }
        }

        // run
        else if (input == "run") {
            pysubi.interpretCode(programCode);
        }

        // show variables
        else if (input == "show(variables)") {
            if (expEvaluation.symbolTable.size() == 0) {
                cout << "No variables stored in memory" << endl;
            }
            else {
                expEvaluation.printVariables();
            }
        }

        // show tokens
        else if (input == "show(tokens)") {
            if (lexAnalysis.tokenInfo.size() == 0) {
                cout << "No file in memory to read from. Use 'read(<filename>.py)' command" << endl;
            }
            else {
                lexAnalysis.printTokens(lexAnalysis.tokenInfo);
            }
        }

        // show
        else if (input == "show" || input == "show()") {
            if (programCode.size() == 0) {
                cout << "No file in memory to read from. Use 'read(<filename>.py)' command" << endl;
            }
            else {
                size_t lineCount = programCode.size();
                for (int i = 0; i < lineCount; i++) {
                    cout << '[' << i << ']' << ' ' << programCode.at(i) << endl;
                }
            }
        }

        // clear
        else if (input == "clear" || input == "clear()") {
            programCode.clear();
            // clear tokenInfo strcuture
            lexAnalysis.tokenInfo.clear();
            // clear symbolTable structure
            expEvaluation.symbolTable.clear();
            cout << "Stored data has sucessfully been cleared" << endl;
        }

        // help
        // enter helpUtility
        else if (input == "help" || input == "help()") {
            helpUtility();
        }
        
        // gets command if user inputted it using the help funciton
        else if (input.substr(0, 5) == "help(" && input.back() == ')') {
            string cmd = input.substr(5);
            cmd.pop_back();
            commandHelpData(cmd);
        }

        // if user forgets to input as a function
        else if (input == "read" || input == "read()") {
            commandHelpData("read");
        }

        // expEvaluation if its a digit
        else if (isdigit(input[0])) {
            lexAnalysis.tokenInfo.clear();
            lexAnalysis.createTokens((expressionEval));
            string temp = expEvaluation.inToPost(input);
            cout << expEvaluation.postEval(temp) << endl;
        }

        // if user inputs unsupported command, direct them to helpUtility
        else {
            cout << "ERROR: UNSUPPORTED COMMAND" << endl << "Type 'help(commands)' for a list of supported commands" << endl;
        }
    }
}

void Interface::helpUtility() {

    bool helpUtilityQuit = false;

    cout << endl << "Welcome to the help Utility!" << endl << endl;
    cout << "* Type 'exit' to return to the CLI" << endl;
    cout << "* To see all commands, type 'commands'" << endl;
    cout << "* To get a description of any command, just type the command within help Utility" << endl;
    
    while (!helpUtilityQuit) {

        // get input from user within helpUtility
        string input;
        cout << "help> ";
        getline(cin, input);

        // checks if they inputted a supported command
        if (checkValidInput(input)) {
            commandHelpData(input);
        }
        else if (input == "exit") {
            helpUtilityQuit = true;
        }
        else {
            cout << "Type 'commands' for a list of supported commands" << endl;
        }
    }
}

void Interface::commandHelpData(string cmd) {
    // HelpData stored which can be called to print a description of a command
    if (cmd == "read") {
        cout << "Use: 'read(<filename>.py)' to read the data from a Python file." << endl;
    }
    else if (cmd == "quit") {
        cout << "Use: 'quit' or 'quit()' to exit the PySub CLI." << endl;
    }
    else if (cmd == "clear") {
        cout << "Use: 'clear' or 'clear()' to clear any data stored by the read() command." << endl;
    }
    else if (cmd == "show") {
        cout << "Use: 'show' or 'show()' to print the data from a previously read() Python file line-by-line." << endl;
        cout << "OR: 'show(tokens)' to run the Lexical Analyzer on a previously read() Python file." << endl;
    }
    else if (cmd == "help") {
        cout << "Use: 'help' or 'help(<command>)' to enter the help Utility which provides descriptions of every command" << endl;
    }
    else if (cmd == "commands") {
        cout << endl << "Supported Commands:" << endl << endl;
        cout << "read   ";
        cout << "quit   ";
        cout << "clear" << endl;
        cout << "show   ";
        cout << "help" << endl << endl;
        cout << "NOTE: All commands can also be entered as a function:" << endl << endl;
        cout << "read()   ";
        cout << "quit()   ";
        cout << "clear()" << endl;
        cout << "show()   ";
        cout << "help()" << endl << endl;
    }
}

// stores all possible valid user input
bool Interface::checkValidInput(string input) {
    if (
        input == "read" ||
        input == "quit" ||
        input == "clear" ||
        input == "show" ||
        input == "show(tokens)" ||
        input == "help" ||
        input == "commands" ||
        input == "read()" ||
        input == "quit()" ||
        input == "clear()" ||
        input == "show()" ||
        input == "help()" ||
        input == "help(help)" ||
        input == "help(read)" ||
        input == "help(clear)" ||
        input == "help(show)" ||
        input == "help(quit)" ||
        input == "help(commands)"
        ) {
        return true;
    }
    else if (input.substr(0, 5) == "read(" && input.size() > 8 && input.find(".") != string::npos) {
        size_t extensionIndex;
        string fileExtension;
        string fileName;

        extensionIndex = input.find_last_of(".");
        fileExtension = input.substr(extensionIndex);
        fileName = input.substr(5, extensionIndex - 2);

        if (fileExtension == ".py") {
            return true;
        }
    }
    else {
        return false;
    }
    return false;
}