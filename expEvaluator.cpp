#include <iostream>
#include "expEvaluator.h"
#include "lexanalyzer.h"

#include <string>
#include <vector>
#include <stack>

std::string expEvaluator::inToPost(std::string codeInput) {
    // temporary stack and output string
    std::string postfixVect;
    std::stack<std::string> stackVect;

    // turn codeInput to vector so we can send it through createTokens()
    inputVector inputVect{codeInput};

    // add LexicalAnalyzer class to evaluate expression
    LexicalAnalyzer lex;

    // createTokens to get tokenInfo data
    lex.createTokens(inputVect);

    for (int i = 0; i < lex.tokenInfo[0].size(); i++) {

        // if NUMERIC_LITERAL just add to postfixVect
        if (lex.tokenInfo[0][i].second == categoryType::NUMERIC_LITERAL) {
            postfixVect.append(lex.tokenInfo[0][i].first);
        }

        // if LEFT_PAREN add to stackVect
        if (lex.tokenInfo[0][i].second == categoryType::LEFT_PAREN) {
            stackVect.push(lex.tokenInfo[0][i].first);
        }

        //
        if (
        (
        lex.tokenInfo[0][i].second == categoryType::ARITH_OP ||
        lex.tokenInfo[0][i].second == categoryType::RELATIONAL_OP ||
        lex.tokenInfo[0][i].second == categoryType::LOGICAL_OP
        ) &&
        stackVect.empty() &&
        stackVect.top() != "(" &&
        getPrecedence(stackVect.top()) >= getPrecedence(lex.tokenInfo[0][i].first)
            ) {

        }
    }

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