#ifndef PARSER_H
#define PARSER_H

#include "Scanner.h"
#include "Predicate.h"
#include "Parameter.h"
#include "DatalogProgram.h"
#include <iostream>

using namespace std;

class Parser {

public:

	Parser(vector<Token> tokens);
	~Parser();

	//bool parse();
	DatalogProgram parse();
	void match(TType tokenType);
	DatalogProgram datalogProgram();
	void schemeList();
	void factList();
	void ruleList();
	void queryList();
	void scheme();
	void fact();
	void rule();
	void query();
	void headPredicate();
	void predicate();
	void predicateList();
	void parameterList();
	void stringList();
	void idList();
	void parameter(bool inExpression);
	void expression();
	void parseOperator();


private:

	TType currentToken;
	vector<Token> tokenList;
	vector<Predicate> rulesList;
	int i = 0;
	Predicate tempPred;
	Parameter tempParam;
	Rule tempRule;
	string paramExpression;
	bool predMade;
	bool inEmbedded = false;
	DatalogProgram datalog;

};


#endif
