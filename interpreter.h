#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>

class Interpreter {
private:
	void interpretComment();
	void interpretPrint();
	void interpretAssignment();
public:
	void interpretLine(std::string);
};

#endif