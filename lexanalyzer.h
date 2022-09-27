#ifndef LEXANALYZER_H
#define LEXANALYZER_H

using namespace std;

#include <vector>
#include <string>

enum class categoryType {
	KEYWORD,
	IDENTIFIER,
	STRING_LITERAL,
	NUMERIC_LITERAL,
	ASSIGNMENT_OP,
	ARITH_OP,
	LOGICAL_OP,
	RELATIONAL_OP,
	LEFT_PAREN,
	RIGHT_PAREN,
	COLON,
	COMMA,
	COMMENT,
	INDENT,
	UNKNOWN
};

typedef vector<vector<pair<string, categoryType>>> tokenType;
typedef vector<pair<string, categoryType>> tokenLineType;
typedef pair<string, categoryType> pairType;

class LexicalAnalyzer {
private:
	tokenType tokenInfo;
    tokenLineType tokenLine;
    pairType pair;
public:
	bool createTokens(vector<string>);
	void printTokens(vector<vector<std::pair<string, categoryType>>>);
};

#endif