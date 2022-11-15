#include "interpreter.h"
#include "lexanalyzer.h"

#include <vector>
#include <string>

LexicalAnalyzer lex; // bring class to this file

void Interpreter::interpretCode(std::vector<std::string>& programCode) {
    // run lexicalAnalysis on code for easier interpretation
    lex.createTokens(programCode);

    for (int i = 0; i < lex.tokenInfo.size(); i++) {
        // add current line to tokenLines struct
        lex.tokenInfo[i] = lex.tokenLine;
        // if COMMENT do nothing
        if (lex.tokenInfo[i][0].second == categoryType::COMMENT) {
            Interpreter::interpretComment();
        }

        else if (lex.tokenInfo[i][0].second == categoryType::KEYWORD && lex.tokenInfo[i][0].first == "print") {
            Interpreter::interpretPrint(lex.tokenLine)
        }
    }
}

void Interpreter::interpretComment(void) {
    // do nothing
}

void Interpreter::interpretPrint(LexicalAnalyzer::tokenLineType& programLine) {

}