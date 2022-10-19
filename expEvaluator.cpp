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
        else if (lex.tokenInfo[0][i].second == categoryType::LEFT_PAREN) {
            stackVect.push(lex.tokenInfo[0][i].first);
        }

        // if RIGHT_PAREN pop until LEFT_PAREN is detected
        else if (lex.tokenInfo[0][i].second == categoryType::RIGHT_PAREN) {
            while (stackVect.top() != "(") {
                postfixVect.append(stackVect.top());
                stackVect.pop();
                if (stackVect.empty()) {
                    cout << "ERROR: Imbalanced parenthesis detected" << endl;
                    exit;
                }
            }
            // pops the "("
            stackVect.pop();
        }

        // if XXXX_OP
        else if (
            lex.tokenInfo[0][i].second == categoryType::ARITH_OP ||
            lex.tokenInfo[0][i].second == categoryType::RELATIONAL_OP ||
            lex.tokenInfo[0][i].second == categoryType::LOGICAL_OP
            ) {
            while (
                !stackVect.empty() &&
                stackVect.top() != "(" &&
                getPrecedence(stackVect.top()) >= getPrecedence(lex.tokenInfo[0][i].first)
                ) {
                postfixVect.append(stackVect.top());
                stackVect.pop();
            }
            stackVect.push(lex.tokenInfo[0][i].first);
        }
    }
    while (!stackVect.empty()) {
        postfixVect.append(stackVect.top());
        stackVect.pop();
    }
 
    cout << postfixVect << endl;

    return postfixVect;
}

std::string expEvaluator::postEval(std::string postfixVect) {

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