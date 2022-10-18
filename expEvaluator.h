#ifndef EXPEVALUATOR_H
#define EXPEVALUATOR_H

#include "lexanalyzer.h"

#include <map>
#include <string>

class expEvaluator {
private:
    typedef std::map<std::string, std::string> symbolTableType;
    symbolTableType symbolTable;
public:
    std::string inToPost(std::string& );
    int getPrecedence(std::string);
};

#endif