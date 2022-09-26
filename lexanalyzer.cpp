
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
				cout << "fart" << endl;
			}

			// KEYWORD, LOGICAL_OP, IDENTIFIER
			if (isalpha(inputCode[i][j])) {

				// local variable to encapsulate all consecutive alphabetic characters
				string tokenText;
				while (isalpha(inputCode[i][j])) {
					tokenText.push_back(inputCode[i][j]);
					j++;
				}

				// KEYWORD
				if (
					tokenText == "print" ||
					tokenText == "if" ||
					tokenText == "elif" ||
					tokenText == "else" ||
					tokenText == "while" ||
					tokenText == "int" ||
					tokenText == "input"
					) {
					category = categoryType::KEYWORD;
					tokenLine.push_back(make_pair(tokenText, category));
				}

				// LOGICAL_OP
				if (
					tokenText == "and" ||
					tokenText == "or" ||
					tokenText == "not"
					) {
					category = categoryType::LOGICAL_OP;
					tokenLine.push_back(make_pair(tokenText, category));
				}

				// IDENTIFIER
				else {
					category = categoryType::IDENTIFIER;
					tokenLine.push_back(make_pair(tokenText, category));
				}
			}

			// 
			if (inputCode[i][j] == '"' || "'") {

			}
		}
	}
}