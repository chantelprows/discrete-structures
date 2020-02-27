#include "Predicate.h"

Predicate::Predicate(string name, vector<Parameter> parameters) {
	this->name = name;
	this->parameters = parameters;
}

Predicate::Predicate(string name) {
	this->name = name;
}

void Predicate::setName(string value) {
	name = value;	
}

void Predicate::addParam(Parameter param) {
	parameters.push_back(param);
}

string Predicate::toString() {
	stringstream ss;

	ss << name << "(";
	for (unsigned int i = 0; i < parameters.size(); i++) {
		ss << parameters.at(i).getName();
		if (i != parameters.size() - 1) {
			ss << ",";
		}
	}
	ss << ")";

	return ss.str();

}

string Predicate::getName() {
	return name;
}