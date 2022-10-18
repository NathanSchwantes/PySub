#include <iostream>
#include "expEvaluator.h"
#include "lexanalyzer.h"

#include <string>

std::string expEvaluator::inToPost(std::string& codeInput) {
    for (int i = 0; i < codeInput.size(); i++) {
        std::cout << codeInput[i] << std::endl;
    }
}