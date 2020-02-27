#ifndef RELATION_H
#define RELATION_H


#include "Scheme.h"
#include "Tuple.h"
#include <iostream>
#include <set>
#include <sstream>

using namespace std;

class Relation {

public:

	Relation() {};

	Relation(string name, Scheme scheme);

	~Relation() {};

	void addTuple(Tuple newTuple);
	string getName();
	void setName(string newName);
	Relation select(int column, string value);
	Relation select(int column1, int column2);
	Relation project(vector<int> columns);
	Relation rename(Scheme scheme);
	Scheme getScheme();
	set<Tuple> getTupleList();
	Relation join(Relation &relToJoin);
	bool joinable(const Tuple &t1, const Tuple &t2, const Scheme &s1, const Scheme &s2);
	void rUnion(Relation &relation);
	pair<Scheme, vector<int>> joinSchemes(const Scheme &s1, const Scheme &s2);
	Tuple joinTuples(const Tuple &t1, const Tuple &t2, vector<int> &columns);

private:
	string name;
	Scheme scheme;
	set<Tuple> tupleList;
	


};

#endif
