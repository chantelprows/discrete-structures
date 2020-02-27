#ifndef RULE_H
#define RULE_H

#include "Token.h"
#include "Predicate.h"

#include <sstream>

class Rule {

public:

	Rule(Predicate head, vector<Predicate> predList);

	Rule(Predicate head);

	Rule() {};

	~Rule() {};

	//void addRule(Predicate pred);

	string toString();

private:

	Predicate head;
	vector<Predicate> predList;

};

#endif