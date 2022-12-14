#ifndef EXPEVALUATOR_H
#define EXPEVALUATOR_H

#include "lexanalyzer.h"

#include <map>
#include <string>
#include <vector>

class expEvaluator {
private:
    friend class Interface;
    friend class Interpreter;

    typedef std::map<std::string, std::string> symbolTableType;
    symbolTableType symbolTable;

    typedef std::vector<std::string> inputVector;
public:
    std::string inToPost(std::string);
    double postEval(std::string);
    int getPrecedence(std::string);
    void printVariables(void);
};

#endif