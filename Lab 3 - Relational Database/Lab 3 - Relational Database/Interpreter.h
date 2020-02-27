#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Relation.h"
#include "Parser.h"
#include "Database.h"
#include "Predicate.h"
#include "Scheme.h"
#include "Token.h"
#include "Graph.h"
#include <iostream>
#include <sstream>

using namespace std;

class Interpreter {

public:

	Interpreter(DatalogProgram datalog);

	void queriesLoop(DatalogProgram datalog);

	//bool rulesLoop(DatalogProgram datalog);

	void sccRulesLoop(DatalogProgram datalog, vector<set<int>> SCCs);

	Relation evalQuery(Predicate query);

	void evaluateRules(Rule rule, Relation headRelation);

	vector<int> getColsToKeep(Relation r1, Relation r2);

	Graph buildGraph(DatalogProgram datalog);

	string dependencyGraph(Graph newGraph);

	bool headMatch(Rule rule);

	string sccToString(set<int> SCC);

private:
	Relation rCopy;
	string relationName;
	Database database;
	Scheme relationScheme;
	bool added;
	int sccPassCount = 0;

};


#endif
