
#include <iostream>
#include "lexanalyzer.h"
#include <vector>
#include <string>

using namespace std;

bool LexicalAnalyzer::createTokens(vector<string>& inputCode) {

	for (int i = 0; i < inputCode.size(); i++) {

		// clear tokenLine struct to encapusulate next line's data
		tokenLine.clear();

		// INDENT
		if (isspace(inputCode[i][0])) {
            pair.first = "____";
            pair.second = categoryType::INDENT;
			tokenLine.push_back(pair);
		}

		for (int j = 0; j < inputCode[i].size(); j++) {

			// COMMENT
			if (inputCode[i][j] == '#') {

				// local variable to encapsulate all characters on line
				string tokenText;
				for (; j < inputCode[i].size(); j++) {
					tokenText.push_back(inputCode[i][j]);
				}
                pair.first = tokenText;
                pair.second = categoryType::COMMENT;
                tokenLine.push_back(pair);
			}

			// NUMERIC LITERAL
			else if (isdigit(inputCode[i][j])) {

				// local variable to encapsulate all consecutive digits
				string tokenText;
				while (isdigit(inputCode[i][j])) {
					tokenText.push_back(inputCode[i][j]);
					j++;
				}
                pair.first = tokenText;
                pair.second = categoryType::NUMERIC_LITERAL;
                tokenLine.push_back(pair);
                // corrects iterator from while loop
                j--;
			}

			// KEYWORD, LOGICAL_OP, IDENTIFIER
			else if (isalpha(inputCode[i][j])) {

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
                    pair.first = tokenText;
                    pair.second = categoryType::KEYWORD;
                    tokenLine.push_back(pair);
				}

				// LOGICAL_OP
				else if (
					tokenText == "and" ||
					tokenText == "or" ||
					tokenText == "not"
					) {
                    pair.first = tokenText;
                    pair.second = categoryType::LOGICAL_OP;
                    tokenLine.push_back(pair);
				}

				// IDENTIFIER
				else {
                    pair.first = tokenText;
                    pair.second = categoryType::IDENTIFIER;
                    tokenLine.push_back(pair);
				}
                // corrects iterator from while loop
                j--;
			}

			// STRING_LITERAL

			// single quotation case
			else if (inputCode[i][j] == '\'') {
				j++;

				// local variable to encapsulate all characters within a quotation pair
				string tokenText;
				for (; inputCode[i][j] != '\''; j++) {
					tokenText.push_back(inputCode[i][j]);
				}
				tokenText.insert(0, "'");
				tokenText.append("'");
                pair.first = tokenText;
                pair.second = categoryType::STRING_LITERAL;
                tokenLine.push_back(pair);
			}

			// double quotation case
			else if (inputCode[i][j] == '\"') {
				j++;

				// local variable to encapsulate all characters within a quotation pair
				string tokenText;
				for (; inputCode[i][j] != '\"'; j++) {
					tokenText.push_back(inputCode[i][j]);
				}
				tokenText.insert(0, "\"");
				tokenText.append("\"");
                pair.first = tokenText;
                pair.second = categoryType::STRING_LITERAL;
                tokenLine.push_back(pair);
			}

			// LEFT_PAREN
			else if (inputCode[i][j] == '(') {
                pair.first = "(";
                pair.second = categoryType::LEFT_PAREN;
                tokenLine.push_back(pair);
			}

			// RIGHT_PAREN
			else if (inputCode[i][j] == ')') {
                pair.first = ")";
                pair.second = categoryType::RIGHT_PAREN;
                tokenLine.push_back(pair);
			}

			// COLON
			else if (inputCode[i][j] == ':') {
                pair.first = ":";
                pair.second = categoryType::COLON;
                tokenLine.push_back(pair);
			}

			// COMMA
			else if (inputCode[i][j] == ',') {
                pair.first = ",";
                pair.second = categoryType::COMMA;
                tokenLine.push_back(pair);
			}

			// RELATIONAL_OP

			// ">=", "<=", "==", "!="
			else if (
			(inputCode[i][j] == '>' && inputCode[i][j + 1] == '=') ||
			(inputCode[i][j] == '<' && inputCode[i][j + 1] == '=') ||
			(inputCode[i][j] == '=' && inputCode[i][j + 1] == '=') ||
			(inputCode[i][j] == '!' && inputCode[i][j + 1] == '=')
				) {
				// local variable to encapsulate both characters
				string tokenText;
				tokenText = inputCode[i][j];
				tokenText = tokenText + inputCode[i][j + 1];

                pair.first = tokenText;
                pair.second = categoryType::RELATIONAL_OP;
                tokenLine.push_back(pair);
				j++;

            }

			// "<"
			else if (inputCode[i][j] == '<') {
			pair.first = "<";
			pair.second = categoryType::RELATIONAL_OP;
			tokenLine.push_back(pair);
			}

			// ">"
			else if (inputCode[i][j] == '>') {
			pair.first = ">";
			pair.second = categoryType::RELATIONAL_OP;
			tokenLine.push_back(pair);

			}

			// ASSIGNMENT_OP
			else if (inputCode[i][j] == '=') {
			pair.first = "=";
			pair.second = categoryType::ASSIGNMENT_OP;
			tokenLine.push_back(pair);
			}

			// ARITH_OP
			else if (
				inputCode[i][j] == '+' || 
				inputCode[i][j] == '-' || 
				inputCode[i][j] == '*' || 
				inputCode[i][j] == '/' ||
				inputCode[i][j] == '%'
				) {
                pair.first = inputCode[i][j];
                pair.second = categoryType::ARITH_OP;
                tokenLine.push_back(pair);

            }

			// WHITESPACE
            else if (inputCode[i][j] == ' ') {
                // do nothing
            }

			else {
				return false;
			}
		}
		// add tokenLine to the overall allToken structure
		tokenInfo.push_back(tokenLine);
	}
	return true;
}

void LexicalAnalyzer::printTokens(vector<vector<std::pair<string, categoryType>>> allTokens) {

	// two-dimensional for loop to display all data within tokenType structure
	for (int i = 0; i < allTokens.size(); i++) {

		cout << "Line #" << i << ":" << endl;

		for (int j = 0; j < allTokens[i].size(); j++) {

			cout << "Token[" << j << "]: " << allTokens[i][j].first << " - ";

			// print the categoryType
			switch (allTokens[i][j].second) {
			case categoryType::KEYWORD: cout << "KEYWORD" << endl; break;
			case categoryType::IDENTIFIER: cout << "IDENTIFIER" << endl; break;
			case categoryType::STRING_LITERAL: cout << "STRING_LITERAL" << endl; break;
			case categoryType::NUMERIC_LITERAL: cout << "NUMERIC_LITERAL" << endl; break;
			case categoryType::ASSIGNMENT_OP: cout << "ASSIGNMENT_OP" << endl; break;
			case categoryType::ARITH_OP: cout << "ARITH_OP" << endl; break;
			case categoryType::LOGICAL_OP: cout << "LOGICAL_OP" << endl; break;
			case categoryType::RELATIONAL_OP: cout << "RELATIONAL_OP" << endl; break;
			case categoryType::LEFT_PAREN: cout << "LEFT_PAREN" << endl; break;
			case categoryType::RIGHT_PAREN: cout << "RIGHT_PAREN" << endl; break;
			case categoryType::COLON: cout << "COLON" << endl; break;
			case categoryType::COMMA: cout << "COMMA" << endl; break;
			case categoryType::COMMENT: cout << "COMMENT" << endl; break;
			case categoryType::INDENT: cout << "INDENT" << endl; break;
			case categoryType::UNKNOWN: cout << "UNKNOWN" << endl; break;
			}
		}
		cout << "--------------------------------------" << endl;
	}
}