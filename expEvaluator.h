#ifndef EXPEVALUATOR_H
#define EXPEVALUATOR_H

#include "lexanalyzer.h"

#include <map>
#include <string>
#include <vector>

class expEvaluator {
private:
    typedef std::map<std::string, std::string> symbolTableType;
    symbolTableType symbolTable;

    typedef std::vector<std::string> inputVector;
    inputVector inputVect;
public:
    std::string inToPost(std::string);
    int getPrecedence(std::string);
};

#endif