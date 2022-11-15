#include "interpreter.h"
#include "lexanalyzer.h"

#include <vector>
#include <string>

LexicalAnalyzer lex; // bring class to this file

void Interface::interpretCode(std::vector<std::string>& programCode) {
    // run lexicalAnalysis on code for easier interpretation
    lex.createTokens(programCode);

    for (int i = 0; i < lex.tokenInfo.size(); i++) {
        for (int j = 0; j < lex.tokenInfo[i].size(); j++) {
            // if COMMENT do nothing
            if (lex.tokenInfo[i][j].second == categoryType::COMMENT) {
                Interface::interpretComment();
            }

            else if (lex.tokenInfo[i][j].second == categoryType::KEYWORD && lex.tokenInfo[i][j].first == "print") {
                Interface::interpretPrint(lex.tokenInfo[i].first)
            }
        }
    }
}

void Interface::interpretComment(void) {
    // do nothing
}
