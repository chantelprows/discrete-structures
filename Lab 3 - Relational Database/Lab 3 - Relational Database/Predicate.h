#ifndef PREDICATE_H
#define PREDICATE_H

#include "Parameter.h"
#include "Token.h"
#include <vector>
#include <sstream>

class Predicate {

public:

	Predicate() {};

	Predicate(string name, vector<Parameter> parameters);

	Predicate(string name);

	~Predicate() {};

	void setName(string value);

	void addParam(Parameter param);

	string toString();

	string getName();

	vector<Parameter> getParameters();


private:
	
	string name;
	vector<Parameter> parameters;

};


#endif
