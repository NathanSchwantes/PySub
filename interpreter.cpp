#include "interpreter.h"
#include "lexanalyzer.h"
#include <iostream>

#include <vector>
#include <string>

LexicalAnalyzer lex; // bring class to this file

void Interpreter::interpretCode(std::vector<std::string>& programCode) {
    // run lexicalAnalysis on code for easier interpretation
    lex.createTokens(programCode);
    cout << "TOKEN VECT SIZE" << lex.tokenInfo.size() << endl;
    for (int i = 0; i < lex.tokenInfo.size(); i++) {
        cout << "fart10" << endl;
        // add current line to tokenLines struct
        lex.tokenLine = lex.tokenInfo[i];
        // if COMMENT do nothing
        if (lex.tokenInfo[i][0].second == categoryType::COMMENT) {
            Interpreter::interpretComment();
            cout << "fart2" << endl;
        }
        // if PRINT statement then run print function
        else if (lex.tokenInfo[i][0].second == categoryType::KEYWORD && lex.tokenInfo[i][0].first == "print") {
            Interpreter::interpretPrint(lex.tokenLine);
            cout << "fart3" << endl;
        }
    }
}

void Interpreter::interpretComment(void) {
    // do nothing
}

void Interpreter::interpretPrint(LexicalAnalyzer::tokenLineType& programLine) {
    // get iterator for end of programLine
    int end = programLine.size() - 1;
    // checks for balanced parenthesis
    if ((programLine[1].second == categoryType::LEFT_PAREN) && (programLine[end].second == categoryType::RIGHT_PAREN)) {
        if (programLine[2].second == categoryType::STRING_LITERAL) {
            cout << programLine[2].first << endl;
        }
    }
}