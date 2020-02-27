#include "Token.h"

Token::Token(TType type, string value, int lineNumber) {
	this->type = type;
	this->value = value;
	this->lineNumber = lineNumber;
}

Token::~Token() {

}

string Token::getString(TType input) {
	return tokenString[input];
}

string Token::printString() {
	return "(" + getString(type) + ",\"" + value + "\"," + to_string(lineNumber) + ")";
}

TType Token::getType() {
	return type;
}

string Token::getValue() {
	return value;
}