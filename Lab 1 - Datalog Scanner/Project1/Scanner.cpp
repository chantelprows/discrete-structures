#include "Scanner.h"
#include <fstream>
#include <sstream>
#include <ctype.h>

string Scanner::charToString(char c) {
	stringstream ss;
	string s;
	ss << c;
	ss >> s;
	return s;
}

Scanner::Scanner() {

}
	
vector<Token> Scanner::getTokens(string fileName) {

	ifstream ifs;
	ifs.open(fileName);

	string comment = "";
	string stringSequence = "";
	string input;

	while (getline(ifs, input))
	{
		lineNumber = lineNumber + 1;
		i = 0;
		if (comment != "") {
			size_t found = input.find("|#", i, 2);
			if (found != string::npos) {
				comment = comment + input.substr(i, found - i + 2);
				Token token(COMMENT, comment, commentLineNum);
				output.push_back(token);
				i = found + 2;
				comment = "";
			}
			else {
				comment = comment + input.substr(i, input.length()) + "\n";
				continue;
			}
		}
		if (stringSequence != "") {
			size_t found = input.find("'", i, 1);
			if (found != string::npos) {
				if (input[found + 1] == '\'') {
					stringSequence = stringSequence + input.substr(i, /*input.length() - i*/found - i + 1); //could be i + 2
					i = stringFunction(stringSequence, input, found + 1, output, lineNumber, stringLineNum);
					continue;
				}
				else {
					stringSequence = stringSequence + input.substr(i, found + 1 - i);
					Token token(STRING, stringSequence, stringLineNum);
					output.push_back(token);
					i = found + 1;
					stringSequence = "";
				}
			}
			else {
				stringSequence = stringSequence + input.substr(i, input.length() - i) + "\n";
				continue;
			}
		}
	
		i = scanLine(c, input, comment, stringSequence);
	}

	multiLineChecker(comment, stringSequence, output);
	
	Token token(TEOF, "", lineNumber + 1);
	output.push_back(token);
	return output;
}

void Scanner::pushToken(TType ttype, char c, int lineNumber, vector<Token> &output) {
	Token token(ttype, charToString(c), lineNumber);
	output.push_back(token);
}

int Scanner::scanLine(char c, string input, string &comment, string &stringSequence) {
	while ((c = input[i])) {
		if (isspace(c)) {
			i++;
			continue;
		}
		switch (c) {
		case ',': {
			pushToken(COMMA, c, lineNumber, output);
			break;
		}
		case '.': {
			pushToken(PERIOD, c, lineNumber, output);
			break;
		}
		case '?': {
			pushToken(Q_MARK, c, lineNumber, output);
			break;
		}
		case '(': {
			pushToken(LEFT_PAREN, c, lineNumber, output);
			break;
		}
		case ')': {
			pushToken(RIGHT_PAREN, c, lineNumber, output);
			break;
		}
		case ':': {
			i = colonDash(c, input);
				break;
		}
		case '*': {
			pushToken(MULTIPLY, c, lineNumber, output);
			break;
		}
		case '+': {
			pushToken(ADD, c, lineNumber, output);
			break;
		}
		case '#': {
			i = commentFunction(comment, input, i, output, lineNumber, commentLineNum);
			break;
		}
		case '\'': {
			stringLineNum = lineNumber;
			i = stringFunction(stringSequence, input, i, output, lineNumber, stringLineNum);
			break;
		}
		default:
		{
			i = IDFinder(c, input, i, output, lineNumber);
			break;
		}
		}
		i++;
	}	
	return i;
}

int Scanner::colonDash(char c, string input) {
	if (input[i + 1] == '-') {
		Token token(COLON_DASH, input.substr(i, 2), lineNumber);
		output.push_back(token);
		i++;
	}
	else {
		pushToken(COLON, c, lineNumber, output);
	}
	return i;
}

int Scanner::stringFunction(string &stringSequence, string input, int i, vector<Token> &output, int lineNumner, int &stringLineNum) {
	while (true) {
		size_t found = input.find("'", i + 1, 1);
		if (found != string::npos) {
			if (input[found + 1] == '\'') {
				stringSequence = stringSequence + input.substr(i, found - i + 1);
				i = found + 1;
				continue;
			}
			else {
				stringSequence = stringSequence + input.substr(i, found + 1 - i);
				Token token(STRING, stringSequence, stringLineNum);
				output.push_back(token);
				i = found;
				stringSequence = "";
				break;
			}
		}
		else {
			stringSequence = stringSequence + input.substr(i, input.length() - i) + "\n";
			i = input.length() - 1;
			break;
		}
	}
	return i;
}

int Scanner::commentFunction(string &comment, string input, int i, vector<Token> &output, int lineNumber, int &commentLineNum) {
	commentLineNum = lineNumber;

	size_t foundBar = input.find("|", i + 1, 1);
	if (foundBar != string::npos && input[i + 1] != '|') {
			comment = input.substr(i, input.length() - i);
			Token token(COMMENT, comment, commentLineNum);
			output.push_back(token);
			i = input.length() - 1;
			comment = "";
	}
	else if (foundBar == string::npos) {
		comment = input.substr(i, input.length() - i);
		Token token(COMMENT, comment, commentLineNum);
		output.push_back(token);
		i = input.length() - 1;
		comment = "";
	}
	else {
		size_t found = input.find("|#", i + 2, 2);
		if (found != string::npos) {
			comment = input.substr(i, found - i + 2);
			Token token(COMMENT, comment, commentLineNum);
			output.push_back(token);
			i = found + 1;
			comment = "";
		}
		else {
			comment = comment + input.substr(i, input.length() - i) + "\n";
			i = input.length() - 1;
		}
	}
	return i;
}

int Scanner::IDFinder(char c, string input, int i, vector <Token> &output, int lineNumber) {
	if (isalpha(c)) {
		string identifier;
		while (isalnum(c)) {
			identifier = identifier + c;
			i++;
			unsigned int j = i;
			if (j < input.length()) {
				c = input.at(i);
			}
			else {
				break;
			}
		}
		i--;
		if (identifier == "Schemes") {
			Token token(SCHEMES, identifier, lineNumber);
			output.push_back(token);
		}
		else if (identifier == "Rules") {
			Token token(RULES, identifier, lineNumber);
			output.push_back(token);
		}
		else if (identifier == "Facts") {
			Token token(FACTS, identifier, lineNumber);
			output.push_back(token);
		}
		else if (identifier == "Queries") {
			Token token(QUERIES, identifier, lineNumber);
			output.push_back(token);
		}
		else {
			Token token(ID, identifier, lineNumber);
			output.push_back(token);
		}
	}
	else {
		string undefined;
		undefined = undefined + c;
		Token token(UNDEFINED, undefined, lineNumber);
		output.push_back(token);
	}
	return i;
}

bool Scanner::is_empty(ifstream& ifs) {
	return ifs.peek() == std::ifstream::traits_type::eof();
}

void Scanner::multiLineChecker(string comment, string stringSequence, vector<Token> &output) {
	if (comment != "") {
		Token token(UNDEFINED, comment, commentLineNum);
		output.push_back(token);
	}
	if (stringSequence != "") {
		Token token(UNDEFINED, stringSequence, stringLineNum);
		output.push_back(token);
	}
}