#include <iostream>
#include "expEvaluator.h"
#include "lexanalyzer.h"

#include <string>
#include <vector>

std::string expEvaluator::inToPost(std::string codeInput) {
    // turn codeInput to vector so we can send it through createTokens()
    inputVector inputVect{codeInput};

    // add LexicalAnalyzer class to evaluate expression
    LexicalAnalyzer lex;

    // createTokens to get tokenInfo data
    lex.createTokens(inputVect);

    return codeInput;
}

int expEvaluator::getPrecedence(std::string inputChar) {
    if (
        inputChar == "*" ||
        inputChar == "/" ||
        inputChar == "%"
        ) {
        return 5;
    }

    else if (
        inputChar == "+" ||
        inputChar == "-"
            ) {
        return 4;
    }

    else if (
            inputChar == "<" ||
            inputChar == ">" ||
            inputChar == ">=" ||
            inputChar == "<=" ||
            inputChar == "!=" ||
            inputChar == "=="
            ) {
        return 3;
    }

    else if (
            inputChar == "not"
            ) {
        return 2;
    }

    else if (
            inputChar == "and"
            ) {
        return 1;
    }

    else if (
            inputChar == "or"
            ) {
        return 0;
    }
    return -1;
}