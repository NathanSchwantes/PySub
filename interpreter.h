#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include <string>
#include "lexanalyzer.h"

class Interpreter {
private:
    void interpretComment(void);
    void interpretPrint(LexicalAnalyzer::tokenType);
    void interpretAssignment();
public:
    void interpretCode(std::vector<std::string>& );
};

#endif
