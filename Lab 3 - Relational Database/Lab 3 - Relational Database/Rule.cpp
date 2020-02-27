#include "Rule.h"

Rule::Rule(Predicate head, vector<Predicate> predList) {
	this->head = head;
	this->predList = predList;
}

Rule::Rule(Predicate head) {
	this->head = head;
}

string Rule::toString() {
	stringstream ss;

	ss << head.toString() << " :- ";
	for (unsigned int i = 0; i < predList.size(); i++) {
		ss << predList.at(i).toString();
		if (i != predList.size() - 1) {
			ss << ",";
		}
	}
	ss << "";

	return ss.str();
}

Predicate Rule::getHead() {
	return head;
}

vector<Predicate> Rule::getPredList() {
	return predList;
}