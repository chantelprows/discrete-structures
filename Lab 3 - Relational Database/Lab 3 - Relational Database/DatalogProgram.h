#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H

#include "Predicate.h"
#include "Rule.h"
#include <vector>
#include <set>
#include <sstream>


using namespace std;

class DatalogProgram {

public:

	DatalogProgram() {};

	vector<Predicate> schemes;
	vector<Predicate> facts;
	vector<Predicate> queries;
	vector<Rule> rules;
	set<string> domain; //Strings that show up in facts

	string toString();



};

#endif