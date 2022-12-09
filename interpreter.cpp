#include "interpreter.h"
#include "lexanalyzer.h"
#include "expEvaluator.h"
#include <iostream>

#include <vector>
#include <string>

LexicalAnalyzer lex; // bring class to this file
expEvaluator expEval; //bring class to this file

bool Interpreter::interpretCode(std::vector<std::string>& programCode) {
    // run lexicalAnalysis on code for easier interpretation
    lex.createTokens(programCode);
    for (int i = 0; i < lex.tokenInfo.size(); i++) {
        // add current line to tokenLines struct
        lex.tokenLine = lex.tokenInfo[i];
        // if COMMENT do nothing
        if (lex.tokenInfo[i][0].second == categoryType::COMMENT) {
            Interpreter::interpretComment();
        }
        // if PRINT statement then run print function
        else if (lex.tokenInfo[i][0].second == categoryType::KEYWORD && lex.tokenInfo[i][0].first == "print") {
            Interpreter::interpretPrint(lex.tokenLine);
        }
        // if IDENTIFIER
        else if (lex.tokenInfo[i][0].second == categoryType::IDENTIFIER) {
            Interpreter::interpretAssignment(lex.tokenLine);
        }
        // if CONDITIONAL
        else if (lex.tokenInfo[i][0].second == categoryType::CONDITIONAL && lex.tokenInfo[i][(lex.tokenInfo[i].size() - 1)].second == categoryType::COLON) {
            if (Interpreter::evaluateConditional(i)) {
                int indentIter;
                Interpreter::encapsulateConditional(i + 1);
            }
        }
        else {
            return false;
        }
    }
    expEval.printVariables();
    return true;
}

void Interpreter::interpretComment(void) {
    // do nothing
}

void Interpreter::interpretAssignment(LexicalAnalyzer::tokenLineType& programLine) {
    string programLineTemp;
    string identifierTemp = programLine[0].first;
    string expressionEvalTemp;
    // if it has KEYWORD such as INPUT
    if (programLine[1].second == categoryType::ASSIGNMENT_OP && programLine[2].second == categoryType::KEYWORD) {
        for (int i = 2; i < programLine.size(); i++) {
            if (programLine[i].first == "input" && programLine[i+1].second == categoryType::LEFT_PAREN) {
                string input;
                cout << removeQuotation(programLine[i+2].first);
                getline(cin, input);
                expEval.symbolTable.insert({ programLine[0].first, input });
            }
            else if (programLine[i].first == "int" && programLine[i + 1].second == categoryType::LEFT_PAREN) {
                // do nothing, int is default value
            }
        }
    }
    // if it is just an expression
    else if (programLine[1].second == categoryType::ASSIGNMENT_OP) {
        // erase first 2 items ex:"X=" from vector
        // leaves us with everything after "="
        programLine.erase(programLine.begin(), programLine.begin() + 2);
        for (int i = 0; i < programLine.size(); i++) {
            programLineTemp.append(programLine[i].first);
        }
        expressionEvalTemp = to_string(expEval.postEval((expEval.inToPost(programLineTemp))));
        expEval.symbolTable.insert({identifierTemp, expressionEvalTemp});
    }
    else {
        cout << "ERROR: INCORRECT SYNTAX" << endl;
    }
}

void Interpreter::interpretPrint(LexicalAnalyzer::tokenLineType& programLine) {
    // get iterator for end of programLine
    size_t endIter = programLine.size() - 1;
    // checks for balanced parenthesis
    if ((programLine[1].second == categoryType::LEFT_PAREN) && (programLine[endIter].second == categoryType::RIGHT_PAREN)) {
        for (int i = 2; i < endIter; i++) {
            // checks for correct syntax within print() statement
            if (
                    programLine[i].second == categoryType::STRING_LITERAL &&
                    (programLine[i+1].second == categoryType::COMMA || programLine[i+1].second == categoryType::RIGHT_PAREN)
               ) {
                // prints out the statement if it is STRING_LITERAL
                programLine[i].first = Interpreter::removeQuotation(programLine[i].first);
                cout << programLine[i].first;
            }
            // checks for correct syntax within print() statement
            else if (programLine[i].second == categoryType::IDENTIFIER) {
                string temp;
                while (programLine[i].second != categoryType::RIGHT_PAREN) {
                    // attaches expression to a single string variable
                    temp.append(programLine[i].first);
                    i++;
                }
                // evaluates that expression using expEvaluator class
                cout << expEval.postEval(expEval.inToPost(temp));
            }
        }
        cout << endl;
    }
}

string Interpreter::removeQuotation(string& stringLiteral) {
    // removes double quotes
    if (stringLiteral[0] == '"') {
        stringLiteral.erase(std::remove(stringLiteral.begin(), stringLiteral.end(), '\"'), stringLiteral.end());
    }
    // removes single quotes
    else if (stringLiteral[0] == '\'') {
        stringLiteral.erase(std::remove(stringLiteral.begin(), stringLiteral.end(), '\''), stringLiteral.end());
    }
    return stringLiteral;
}

bool Interpreter::evaluateConditional(int iter) {
    std::string conditionalString;
    size_t statementEnd;
    int statementBool;
    statementEnd = lex.tokenInfo[iter].size() - 1;
    // encapsulates data within IF statement for evaluation
    for (int j = 1; j < statementEnd; j++) {
        conditionalString.append(lex.tokenInfo[iter][j].first);
    }
    statementBool = expEval.postEval(expEval.inToPost(conditionalString));
    if (statementBool == 0) {
        return false;
    }
    else if (statementBool == 1) {
        return true;
    }
    else {
        cout << "ERROR IN EVALUATING EXPRESSION WITHIN CONDITIONAL" << endl;
        return -1;
    }
}

vector<string> encapsulateConditional(int iter) {
    vector<string> conditionalVector;
    while (lex.tokenInfo[iter][0].second == categoryType::INDENT) {
        for (int i = 1; i < lex.tokenInfo[iter].size(); i++) {
            conditionalVector[i-1].append(lex.tokenInfo[iter][i].first);
        }
        iter++;
    }
    for (int j = 0; j < conditionalVector.size(); j++) {
        cout << conditionalVector[j] << endl;
    }
    return conditionalVector;
}