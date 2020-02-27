#include "Parser.h"
#include "DatalogProgram.h"
#include "Predicate.h"


Parser::Parser(vector<Token> tokens) {
	tokenList = tokens;
	currentToken = tokenList.at(i).getType();
}

Parser::~Parser() {

}

DatalogProgram Parser::parse() {
	try {
		return datalogProgram();
		//return true;
	}
	catch (Token error) {
		error = tokenList.at(i);
		cout << "Failure!" << endl  << "   " << error.printString();
		//return false;
		return DatalogProgram();
	}
}

void Parser::match(TType tokenType) {
		if (currentToken == tokenType) {
			currentToken = tokenList.at(i + 1).getType();
			i++;
		}
		else if (currentToken == COMMENT) {
			currentToken = tokenList.at(i + 1).getType();
			i++;
			match(tokenType);
		}
		else {
			throw tokenList.at(i);
		}
}

DatalogProgram Parser::datalogProgram() {
	match(SCHEMES);
	match(COLON);
	scheme();
	schemeList();
	match(FACTS);
	match(COLON);
	factList();
	match(RULES);
	match(COLON);
	ruleList();
	match(QUERIES);
	match(COLON);
	query();
	queryList();

	if (currentToken == TEOF) {
		//cout << "Success!" << endl;
		return datalog;
	}

	else {
		throw tokenList.at(i);
	}

}
void Parser::schemeList() {
	if (currentToken == ID) {
		scheme();
		schemeList();
	}
	else {
		return;
	}
}

void Parser::factList() {
	if (currentToken == ID) {
		fact();
		factList();
	}
	else {
		return;
	}
}

void Parser::ruleList() {
	if (currentToken == ID) {
		rule();
		ruleList();
	}
	else {
		return;
	}
}

void Parser::queryList() {
	if (currentToken == ID) {
		query();
		queryList();
	}
	else {
		return;
	}
}

void Parser::scheme() {
	headPredicate();
	if (tempPred.getName() != "") {
		datalog.schemes.push_back(tempPred);
	}

}

void Parser::fact() {
	tempPred = Predicate(tokenList.at(i).getValue());

	match(ID);
	match(LEFT_PAREN);

	datalog.domain.insert((tokenList.at(i).getValue()));
	tempParam = Parameter(tokenList.at(i).getValue());
	tempPred.addParam(tempParam);

	match(STRING);
	stringList();
	match(RIGHT_PAREN);
	match(PERIOD);

	datalog.facts.push_back(tempPred);
}

void Parser::rule() {
	headPredicate();

	Predicate headPred = tempPred;
	Rule rule(headPred);

	match(COLON_DASH);
	predicate();

	rulesList.push_back(tempPred);

	predicateList();

	Rule ruleList(headPred, rulesList);
	datalog.rules.push_back(ruleList);
	
	match(PERIOD);

	rulesList.clear();
}

void Parser::query() {
	predicate();
	if (predMade) {
		datalog.queries.push_back(tempPred);
		match(Q_MARK);
	}
}

void Parser::headPredicate() {
	
		match(ID);

		tempPred = Predicate(tokenList.at(i - 1).getValue());

		match(LEFT_PAREN);
		match(ID);

		tempParam = Parameter(tokenList.at(i - 1).getValue());
		tempPred.addParam(tempParam);

		idList();
		match(RIGHT_PAREN);
	
}

void Parser::predicate() {

	tempPred = Predicate(tokenList.at(i).getValue());

		match(ID);
		match(LEFT_PAREN);
		parameter(false);
		parameterList();
		match(RIGHT_PAREN);

		predMade = true;
	
}

void Parser::predicateList() {
	if (currentToken == COMMA) {
		match(COMMA);
		predicate();

		rulesList.push_back(tempPred);

		predicateList();
	}
	else {
		return;
	}
}

void Parser::parameterList() {
	if (currentToken == COMMA) {
		match(COMMA);
		parameter(false);
		parameterList();
	}
	else {
		return;
	}
}

void Parser::stringList() {
	if (currentToken == COMMA) {
		match(COMMA);
		match(STRING);

		datalog.domain.insert((tokenList.at(i-1).getValue()));
		tempParam = Parameter(tokenList.at(i-1).getValue());
		tempPred.addParam(tempParam);

		stringList();
	}
	else {
		return;
	}
}

void Parser::idList() {
	if (currentToken == COMMA) {
		match(COMMA);
		match(ID);

		tempParam = Parameter(tokenList.at(i - 1).getValue());
		tempPred.addParam(tempParam);

		idList();
	}
	else {
		return;
	}
}

void Parser::parameter(bool inExpression) {
	if (currentToken == STRING) {

		tempParam = Parameter(tokenList.at(i).getValue());
		if (!inExpression) {
			tempPred.addParam(tempParam);
		}

		match(STRING);
	}
	else if (currentToken == ID) {


		tempParam = Parameter(tokenList.at(i).getValue());
		if (!inExpression) {
			tempPred.addParam(tempParam);
		}

		match(ID);
	}
	else if (currentToken == LEFT_PAREN) {
		expression();
		inEmbedded = true;
		if (!inExpression) {
			inEmbedded = false;
			Parameter exParam = Parameter(paramExpression);
			tempPred.addParam(exParam);
			paramExpression = "";
		}
		
	} 
	else {
		return;
	}
}

void Parser::expression() {
	if (currentToken == LEFT_PAREN) {
		match(LEFT_PAREN);
		paramExpression = paramExpression + "(";
		inEmbedded = false;

		parameter(true);

		if (!inEmbedded) {
			paramExpression = paramExpression + tempParam.getName();
		}

		parseOperator();
		inEmbedded = false;
		
		parameter(true);

		if (!inEmbedded) {
			paramExpression = paramExpression + tempParam.getName();
		}

		match(RIGHT_PAREN);
		paramExpression = paramExpression + ")";
	}
	else {
		return;
	}
}

void Parser::parseOperator() {
	if (currentToken == ADD) {
		paramExpression = paramExpression + "+";
		match(ADD);
	}
	else {
		paramExpression = paramExpression + "*";
		match(MULTIPLY);
	}
}