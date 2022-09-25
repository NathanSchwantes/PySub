#ifndef INTERFACE_H
#define INTERFACE_H

#include <vector>
#include <string>

typedef std::vector<std::string> programType;

class Interface {
private:
    programType programCode;
    void helpUtility();
    void commandHelpData(std::string);
    bool checkValidInput(std::string);
public:
    void startInterface();
};

#endif