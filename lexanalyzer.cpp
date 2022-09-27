
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
				category = categoryType::LEFT_PAREN;
				tokenLine.push_back(make_pair(")", category));
			}

			// COLON
			if (inputCode[i][j] == ':') {
				category = categoryType::LEFT_PAREN;
				tokenLine.push_back(make_pair(":", category));
			}

			// COMMA
			if (inputCode[i][j] == ',') {
				category = categoryType::LEFT_PAREN;
				tokenLine.push_back(make_pair(",", category));
			}

			// ASSIGNMENT_OP
			if (inputCode[i][j] == '=') {
				category = categoryType::ASSIGNMENT_OP;
				tokenLine.push_back(make_pair("=", category));
			}

			// RELATIONAL_OP
			// "<"
			if (inputCode[i][j] == '<') {
				category = categoryType::ASSIGNMENT_OP;
				tokenLine.push_back(make_pair("<", category));
			}

			// ">"
			if (inputCode[i][j] == '>') {
				category = categoryType::ASSIGNMENT_OP;
				tokenLine.push_back(make_pair(">", category));
			}

			// "<="
			if (inputCode[i][j] == '<' && inputCode[i][j + 1] == '=') {
				category = categoryType::ASSIGNMENT_OP;
				tokenLine.push_back(make_pair("<=", category));
			}

			// ">="
			if (inputCode[i][j] == '>' && inputCode[i][j + 1] == '=') {
				category = categoryType::ASSIGNMENT_OP;
				tokenLine.push_back(make_pair(">=", category));
			}

			// "=="
			if (inputCode[i][j] == '=' && inputCode[i][j + 1] == '=') {
				category = categoryType::ASSIGNMENT_OP;
				tokenLine.push_back(make_pair("==", category));
			}

			// "!="
			if (inputCode[i][j] == '!' && inputCode[i][j + 1] == '=') {
				category = categoryType::ASSIGNMENT_OP;
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
		}
		// add tokenLine to the overall allToken structure
		allTokens.push_back(tokenLine);
	}
	return true;
}

void LexicalAnalyzer::printTokens(vector<vector<pair<string, categoryType>>> allTokens) {
	for (int i = 0; i < allTokens.size(); i++) {
		cout << "Line #" << i << ":" << endl;
		for (int j = 0; j < allTokens[i].size(); j++) {

		}
	}
}