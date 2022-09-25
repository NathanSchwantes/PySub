
#include <iostream>
#include "lexanalyzer.h"
#include <vector>
#include <string>

using namespace std;

bool LexicalAnalyzer::createTokens(vector<string> inputCode) {

	categoryType category;
	tokenLineType tokenLine;
	string tokenText;

	for (int i = 0; i < inputCode.size(); i++) {

		// INDENT
		if (isspace(inputCode[i][0])) {
			category = categoryType::INDENT;
			tokenText = "_____";
			tokenLine.push_back(make_pair(tokenText, category));
		}

		for (int j = 0; j < inputCode[i].size(); j++) {

			// COMMENT
			if (inputCode[i][j] == '#') {
				category = categoryType::COMMENT;
				tokenText = "#";
				tokenLine.push_back(make_pair(tokenText, category));
			}

			// NUMERIC LITERAL
			if (isdigit(inputCode[i][j])) {
				tokenText.clear();
				while (isdigit(inputCode[i][j])) {
					tokenText.push_back(inputCode[i][j]);
					j++;
				}
				category = categoryType::NUMERIC_LITERAL;
				tokenLine.push_back(make_pair(tokenText, category));
				cout << tokenLine[1].first << endl;
			}
		}
	}
	return false;
}