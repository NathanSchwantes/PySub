
#include <iostream>
#include "lexanalyzer.h"
#include <vector>
#include <string>

using namespace std;

bool LexicalAnalyzer::createTokens(vector<string> inputCode) {

	categoryType category;
	tokenLineType tokenLine;

	for (int i = 0; i < inputCode.size(); i++) {

		// INDENT
		if (isspace(inputCode[i][0])) {
			category = categoryType::INDENT;
			tokenLine.push_back(make_pair("____", category));
		}

		for (int j = 0; j < inputCode[i].size(); j++) {

			// COMMENT
			if (inputCode[i][j] == '#') {
				category = categoryType::COMMENT;
				tokenLine.push_back(make_pair("#", category));
			}

			// NUMERIC LITERAL
			if (isdigit(inputCode[i][j])) {

				// local variable to encapsulate all consecutive digits
				string tokenText;

				while (isdigit(inputCode[i][j])) {
					tokenText.push_back(inputCode[i][j]);
					j++;
				}
				category = categoryType::NUMERIC_LITERAL;
				tokenLine.push_back(make_pair(tokenText, category));
			}
		}
	}
	return false;
}