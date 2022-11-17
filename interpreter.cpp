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
    if (programLine[1].second == categoryType::ASSIGNMENT_OP) {
        // add IDENTIFIER to symbolTable with temp value
        exp.symbolTable({programLine[0].first, temp});
        // erase first 2 items from vector
        programLine.erase(programLine.begin(), programLine.begin() + 1);
        for (int i = 0; i < programLine.size(); i++) {
            programLineTemp.insert(i,programLine[i].first);
            cout << "TEMP PROG LINE:" << programLineTemp << endl;
        }
        //exp.postEval(programLine);
    }
}

void Interpreter::interpretPrint(LexicalAnalyzer::tokenLineType& programLine) {
    // get iterator for end of programLine
    size_t endIter = programLine.size() - 1;
    // checks for balanced parenthesis
    if ((programLine[1].second == categoryType::LEFT_PAREN) && (programLine[endIter].second == categoryType::RIGHT_PAREN)) {
        for (int i = 2; i < endIter; i++) {
            if (programLine[i].second == categoryType::STRING_LITERAL) {
                programLine[i].first = Interpreter::removeQuotation(programLine[i].first);
                cout << programLine[i].first;
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