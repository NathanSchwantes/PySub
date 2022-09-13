#ifndef INTERFACE_H
#define INTERFACE_H

#include <vector>
#include <string>

typedef std::vector<std::string> programType;
class Interface {
private:
    programType programCode;
public:
    void startInterface();
};

#endif