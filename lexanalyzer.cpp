
#include <iostream>
#include "lexanalyzer.h"
#include <vector>
#include <string>

using namespace std;

bool LexicalAnalyzer::createTokens(vector<string> inputCode) {

	categoryType category;
	tokenLineType tokenLine;
	tokenType allTokens;

	for (int i = 0; i < inputCode.size(); i++) {

		tokenLine.clear();

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
				if (
					tokenText != "print" &&
					tokenText != "if" &&
					tokenText != "elif" &&
					tokenText != "else" &&
					tokenText != "while" &&
					tokenText != "int" &&
					tokenText != "input" &&
					tokenText != "and" &&
					tokenText != "or" &&
					tokenText != "not"
					) {
					category = categoryType::IDENTIFIER;
					tokenLine.push_back(make_pair(tokenText, category));
				}
			}

			// STRING_LITERAL

			// single quotation case
			if (inputCode[i][j] == '\'') {
				j++;

				// local variable to encapsulate all characters within a quotation pair
				string tokenText;
				for (j; inputCode[i][j] != '\''; j++) {
					tokenText.push_back(inputCode[i][j]);
				}
				tokenText.insert(0, "'");
				tokenText.append("'");
				category = categoryType::STRING_LITERAL;
				tokenLine.push_back(make_pair(tokenText, category));
			}

			// double quotation case
			if (inputCode[i][j] == '\"') {
				j++;

				// local variable to encapsulate all characters within a quotation pair
				string tokenText;
				for (j; inputCode[i][j] != '\"'; j++) {
					tokenText.push_back(inputCode[i][j]);
				}
				tokenText.insert(0, "\"");
				tokenText.append("\"");
				category = categoryType::STRING_LITERAL;
				tokenLine.push_back(make_pair(tokenText, category));
			}

			// LEFT_PAREN
			if (inputCode[i][j] == '(') {
				category = categoryType::LEFT_PAREN;
				tokenLine.push_back(make_pair("(", category));
			}

			// RIGHT_PAREN
			if (inputCode[i][j] == ')') {
				category = categoryType::RIGHT_PAREN;
				tokenLine.push_back(make_pair(")", category));
			}

			// COLON
			if (inputCode[i][j] == ':') {
				category = categoryType::COLON;
				tokenLine.push_back(make_pair(":", category));
			}

			// COMMA
			if (inputCode[i][j] == ',') {
				category = categoryType::COMMA;
				tokenLine.push_back(make_pair(",", category));
			}

			// ASSIGNMENT_OP
			if (inputCode[i][j] == '=') {
				category = categoryType::RELATIONAL_OP;
				tokenLine.push_back(make_pair("=", category));
			}

			// RELATIONAL_OP
			// "<"
			if (inputCode[i][j] == '<') {
				category = categoryType::RELATIONAL_OP;
				tokenLine.push_back(make_pair("<", category));
			}

			// ">"
			if (inputCode[i][j] == '>') {
				category = categoryType::RELATIONAL_OP;
				tokenLine.push_back(make_pair(">", category));
			}

			// "<="
			if (inputCode[i][j] == '<' && inputCode[i][j + 1] == '=') {
				category = categoryType::RELATIONAL_OP;
				tokenLine.push_back(make_pair("<=", category));
			}

			// ">="
			if (inputCode[i][j] == '>' && inputCode[i][j + 1] == '=') {
				category = categoryType::RELATIONAL_OP;
				tokenLine.push_back(make_pair(">=", category));
			}

			// "=="
			if (inputCode[i][j] == '=' && inputCode[i][j + 1] == '=') {
				category = categoryType::RELATIONAL_OP;
				tokenLine.push_back(make_pair("==", category));
			}

			// "!="
			if (inputCode[i][j] == '!' && inputCode[i][j + 1] == '=') {
				category = categoryType::RELATIONAL_OP;
				tokenLine.push_back(make_pair("!=", category));
			}

			// ARITH_OP
			// "+"
			if (inputCode[i][j] == '+') {
				category = categoryType::ARITH_OP;
				tokenLine.push_back(make_pair("+", category));
			}

			// "-"
			if (inputCode[i][j] == '-') {
				category = categoryType::ARITH_OP;
				tokenLine.push_back(make_pair("-", category));
			}

			// "*"
			if (inputCode[i][j] == '*') {
				category = categoryType::ARITH_OP;
				tokenLine.push_back(make_pair("*", category));
			}

			// "/"
			if (inputCode[i][j] == '/') {
				category = categoryType::ARITH_OP;
				tokenLine.push_back(make_pair("/", category));
			}

			// "%"
			if (inputCode[i][j] == '%') {
				category = categoryType::ARITH_OP;
				tokenLine.push_back(make_pair("%", category));
			}

			//else {
			//	category = categoryType::UNKNOWN;
			//	string tokenText;
			//	tokenText = inputCode[i][j];
			//	tokenLine.push_back(make_pair(tokenText, category));
			//}
		}
		// add tokenLine to the overall allToken structure
		allTokens.push_back(tokenLine);
	}
	printTokens(allTokens);
	return true;
}

void LexicalAnalyzer::printTokens(vector<vector<pair<string, categoryType>>> allTokens) {
	for (int i = 0; i < allTokens.size(); i++) {

		cout << "Line #" << i << ":" << endl;

		for (int j = 0; j < allTokens[i].size(); j++) {

			cout << "Token[" << j << "]: " << allTokens[i][j].first << " - ";

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