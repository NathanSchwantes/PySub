#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "interface.h"

class Interpreter {
private:
	void interpretComment();
	void interpretPrint();
	void interpretAssignment();
public:
	void interpretLine(programType& programCode);
};

#endif