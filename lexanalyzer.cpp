
#include <iostream>
#include "lexanalyzer.h"
#include <vector>
#include <string>

using namespace std;

bool LexicalAnalyzer::createTokens(vector<string> inputCode) {

	categoryType category;
	tokenLineType tokenLine;

	for (int i = 0; i < inputCode.size(); i++) {

		if (isspace(inputCode[i][0])) {
			category = categoryType::INDENT;
			tokenLine.push_back(make_pair("_____", category));
			cout << "indet" << endl;
		}

		for (int j = 0; j < inputCode[i].size(); j++) {

			if (inputCode[i][j] == '#') {
				category = categoryType::COMMENT;
				tokenLine.push_back(make_pair("#", category));
				cout << "commet" << endl;
				return true;
			}

		}
	}
	return false;
}

void LexicalAnalyzer::addTokens(tokenLineType tokenLine, string tokenText, categoryType category) {
	tokenLine.push_back(make_pair(tokenText, category));
}