#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "lexanalyzer.h"

class Interpreter {
private:
	void interpretComment();
	void interpretPrint();
	void interpretAssignment();
public:
	void interpretLine(LexicalAnalyzer::tokenLineType);
};

#endif