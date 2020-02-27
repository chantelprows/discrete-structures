#include "Relation.h"

Relation::Relation(string name, Scheme scheme) {
	this->name = name;
	this->scheme = scheme;
}

void Relation::addTuple(Tuple newTuple) {
	tupleList.insert(newTuple);
}

Scheme Relation::getScheme() {
	return scheme;
}

string Relation::getName() {
	return name;
}

void Relation::setName(string newName) {
	name = newName;
}

set<Tuple> Relation::getTupleList() {
	return tupleList;
}

Relation Relation::select(int column, string value) {
	Relation newRelation(name, scheme);

	for (Tuple t : tupleList) {
		if (t.at(column) == value) {
			newRelation.addTuple(t);
		}
	}
	return newRelation;
}

Relation Relation::select(int column1, int column2) {
	Relation newRelation(name, scheme);

	for (Tuple t : tupleList) {
		if (t.at(column1) == t.at(column2)) {
			newRelation.addTuple(t);
		}
	}
	return newRelation;
}

Relation Relation::project(vector<int> columns) {
	Scheme newScheme;
	
	for (unsigned int i = 0; i < columns.size(); i++) {
		newScheme.push_back(scheme[columns.at(i)]);
	}

	Relation newRelation(name, newScheme);
		
	for (Tuple t : tupleList) {
		Tuple newTuple;
		for (unsigned int i = 0; i < columns.size(); i++) {
			newTuple.push_back(t.at(columns.at(i)));
		}
		newRelation.addTuple(newTuple);
	}
	return newRelation;
}

Relation Relation::rename(Scheme newScheme) {

	Relation newRelation(name, newScheme);

	for (Tuple t : tupleList) {
		newRelation.addTuple(t);
	}
	return newRelation;
}

Relation Relation::join(Relation &relToJoin) {

	Scheme newScheme;
	Tuple newTuple;
	newScheme = joinSchemes(scheme, relToJoin.getScheme()).first;
	vector<int> newTupleColumns = joinSchemes(scheme, relToJoin.getScheme()).second;
	Relation newRelation = Relation(name, newScheme);
	set<Tuple> newTupleList = relToJoin.getTupleList();
	Scheme myScheme = relToJoin.getScheme();

	for (const Tuple &t1 : tupleList) {
		for (const Tuple &t2 : newTupleList) {
			if (joinable(t1, t2, scheme, myScheme)) {
				newTuple = joinTuples(t1, t2, newTupleColumns);
				newRelation.addTuple(newTuple);
			}
		}
	}
	return newRelation;
}

pair<Scheme, vector<int>> Relation::joinSchemes(const Scheme &s1, const Scheme &s2) {
	Scheme newScheme;
	set<string> schemeList;
	vector<int> columnsToKeep;

	for (unsigned int i = 0; i < s1.size(); i++) {
		newScheme.push_back(s1.at(i));
		schemeList.insert(s1.at(i));
	}
	for (unsigned int i = 0; i < s2.size(); i++) {
		if (!schemeList.count(s2.at(i))) {
			newScheme.push_back(s2.at(i));
			columnsToKeep.push_back(i);
		}
	}
	return make_pair(newScheme, columnsToKeep);
}

Tuple Relation::joinTuples(const Tuple &t1, const Tuple &t2, vector<int> &columns) {
	Tuple newTuple;

	for (unsigned int i = 0; i < t1.size(); i++) {
		newTuple.push_back(t1.at(i));
	}
	for (unsigned int i = 0; i < columns.size(); i++) {
		newTuple.push_back(t2.at(columns.at(i)));
	}
	return newTuple;
}

bool Relation::joinable(const Tuple &t1, const Tuple &t2, const Scheme &s1, const Scheme &s2) {

	for (unsigned int i = 0; i < s1.size(); i++) {
		for (unsigned int j = 0; j < s2.size(); j++) {
			if (s1.at(i) == s2.at(j)) {
				if (t1.at(i) != t2.at(j)) {
					return false;
				}
			}
		}
	}
	return true;
}

void Relation::rUnion(Relation &relation) {
	for (const Tuple &t : relation.getTupleList()) {
		if (tupleList.insert(t).second) {
			unsigned int j = 1;
			cout << "  ";
			for (unsigned int i = 0; i < getScheme().size(); i++) {
				cout << getScheme().at(i) << "=" << t.at(i);
				if (j < t.size()) {
					cout << ", ";
					j++;
				}
			}
			if (t.size() != 0) {
				cout << endl;
			}
		}
	}
}

