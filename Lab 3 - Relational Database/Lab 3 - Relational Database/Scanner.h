
#ifndef SCANNER_H
#define SCANNER_H

#include <vector>
#include "Token.h"

using namespace std;

class Scanner {

public:

	Scanner();

	vector<Token> getTokens(string fileName);

private:

	string charToString(char c);
	int stringFunction(string &stringSequence, string input, int i, vector<Token> &output, int lineNumber, int &stringLineNum);
	int IDFinder(char c, string input, int i, vector <Token> &output, int lineNumber);
	int commentFunction(string &comment, string input, int i, vector<Token> &output, int lineNumber,
		int &commentLineNum);
	void pushToken(TType ttype, char c, int lineNumber, vector<Token> &output);
	int scanLine(char c, string input, string &comment, string &stringSequence);
	int colonDash(char c, string input);
	void multiLineChecker(string comment, string stringSequence, vector<Token> &output);

	int lineNumber = 0;
	int commentLineNum = 0;
	int stringLineNum = 0;
	int i;
	vector<Token> output;
	char c;
	bool is_empty(ifstream& ifs);


};

#endif