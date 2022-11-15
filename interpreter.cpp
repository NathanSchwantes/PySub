#include "interpreter.h"
#include "lexanalyzer.h"

#include <vector>
#include <string>

LexicalAnalyzer lex; // bring class to this file

void Interface::interpretCode(std::vector<std::string>& programCode) {
    lex.createTokens(programCode);
}
