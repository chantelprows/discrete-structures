
#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <map>

using namespace std;

enum TType {
	COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY,
	ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, TEOF
};

class Token {

public:

	Token(TType type, string value, int lineNumber);

	~Token();

	map<TType, string> tokenString{ {COMMA, "COMMA"}, {PERIOD, "PERIOD"}, {Q_MARK, "Q_MARK"},
		{LEFT_PAREN, "LEFT_PAREN"}, {RIGHT_PAREN, "RIGHT_PAREN"}, {COLON, "COLON"}, {COLON_DASH, "COLON_DASH"},
		{MULTIPLY, "MULTIPLY"}, {ADD, "ADD"}, {SCHEMES, "SCHEMES"}, {FACTS, "FACTS"}, {RULES, "RULES"},
		{QUERIES, "QUERIES"}, {ID, "ID"}, {STRING, "STRING"}, {COMMENT, "COMMENT"}, {UNDEFINED, "UNDEFINED"},
		{TEOF, "EOF"} };

	string getString(TType input);

	string printString();

	TType getType();

private:

	int lineNumber;
	string value;
	TType type;

};

#endif
