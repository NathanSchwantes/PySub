#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include <string>
#include "lexanalyzer.h"

class Interpreter {
private:
    void interpretComment(void);
    void interpretPrint(LexicalAnalyzer::tokenLineType& );
    void interpretAssignment(LexicalAnalyzer::tokenLineType& );
    string removeQuotation(string& );
public:
    bool interpretCode(std::vector<std::string>& );
};

#endif
