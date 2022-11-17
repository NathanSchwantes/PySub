#include "interpreter.h"
#include "lexanalyzer.h"
#include "expEvaluator.h"
#include <iostream>

#include <vector>
#include <string>

LexicalAnalyzer lex; // bring class to this file
expEvaluator exp; //bring class to this file

void Interpreter::interpretCode(std::vector<std::string>& programCode) {
    // run lexicalAnalysis on code for easier interpretation
    lex.createTokens(programCode);
    for (int i = 0; i < lex.tokenInfo.size(); i++) {
        // add current line to tokenLines struct
        lex.tokenLine = lex.tokenInfo[i];
        // if COMMENT do nothing
        if (lex.tokenInfo[i][0].second == categoryType::COMMENT) {
            Interpreter::interpretComment();
        }
        // if PRINT statement then run print function
        else if (lex.tokenInfo[i][0].second == categoryType::KEYWORD && lex.tokenInfo[i][0].first == "print") {
            Interpreter::interpretPrint(lex.tokenLine);
        }
        // if IDENTIFIER
        else if (lex.tokenInfo[i][0].second == categoryType::IDENTIFIER) {
            Interpreter::interpretAssignment(lex.tokenLine);
        }
    }
}

void Interpreter::interpretComment(void) {
    // do nothing
}

void Interpreter::interpretAssignment(LexicalAnalyzer::tokenLineType& programLine) {
    string programLineTemp;
    string identifierTemp = programLine[0].first;
    string expressionEvalTemp;
    if (programLine[1].second == categoryType::ASSIGNMENT_OP) {
        // erase first 2 items ex:"X=" from vector
        // leaves us with everything after "="
        programLine.erase(programLine.begin(), programLine.begin() + 2);
        for (int i = 0; i < programLine.size(); i++) {
            programLineTemp.append(programLine[i].first);
        }
        expressionEvalTemp = to_string(exp.postEval((exp.inToPost(programLineTemp))));
        exp.symbolTable.insert({identifierTemp, expressionEvalTemp});
    }
}

void Interpreter::interpretPrint(LexicalAnalyzer::tokenLineType& programLine) {
    // get iterator for end of programLine
    size_t endIter = programLine.size() - 1;
    // checks for balanced parenthesis
    if ((programLine[1].second == categoryType::LEFT_PAREN) && (programLine[endIter].second == categoryType::RIGHT_PAREN)) {
        for (int i = 2; i < endIter; i++) {
            // checks for correct syntax within print() statement
            if (
                    programLine[i].second == categoryType::STRING_LITERAL &&
                    (programLine[i+1].second == categoryType::COMMA || programLine[i+1].second == categoryType::RIGHT_PAREN)
                    ) {
                programLine[i].first = Interpreter::removeQuotation(programLine[i].first);
                cout << programLine[i].first;
            }
            // checks for correct syntax within print() statement
            else if (programLine[i].second == categoryType::IDENTIFIER) {
                string temp;
                while (programLine[i].second != categoryType::RIGHT_PAREN) {
                    temp.append(programLine[i].first);
                    i++;
                }
                cout << exp.postEval(exp.inToPost(temp));
            }
        }
        cout << endl;
    }
}

string Interpreter::removeQuotation(string& stringLiteral) {
    // removes double quotes
    if (stringLiteral[0] == '"') {
        stringLiteral.erase(std::remove(stringLiteral.begin(), stringLiteral.end(), '\"'), stringLiteral.end());
    }
    // removes single quotes
    else if (stringLiteral[0] == '\'') {
        stringLiteral.erase(std::remove(stringLiteral.begin(), stringLiteral.end(), '\''), stringLiteral.end());
    }
    return stringLiteral;
}