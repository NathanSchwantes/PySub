#ifndef INTERPRETER_H
#define NTERPRETER_H

#include <vector>
#include <string>

class Interface {
private:
    void interpretComment();
    void interpretPrint();
    void interpretAssignment();
public:
    void interpretCode(std::vector<std::string>& );
};

#endif
