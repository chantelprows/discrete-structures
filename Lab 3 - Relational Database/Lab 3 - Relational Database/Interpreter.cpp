#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram datalog) {

	for (Predicate s : datalog.schemes) {
		relationName = s.getName();
		Scheme newScheme;
		for (Parameter p : s.getParameters()) {
			newScheme.push_back(p.getName());
		}
		Relation newRelation(relationName, newScheme);
		database.relationList[relationName] = newRelation;
	}

	for (Predicate f : datalog.facts) {
		Tuple tupleList;
		relationName = f.getName();
		for (Parameter p : f.getParameters()) {
			tupleList.push_back(p.getName());
		}
		database.relationList[relationName].addTuple(tupleList);
	}

	Graph ruleGraph = buildGraph(datalog);

	cout << "Dependency Graph" << endl;

	cout << dependencyGraph(ruleGraph) << endl;

	ruleGraph.dfsForest();

	ruleGraph.findSCC();

	cout << "Rule Evaluation" << endl;

	sccRulesLoop(datalog, ruleGraph.getSCCList());

	/*
	int count = 0;
	
	do {
		added = rulesLoop(datalog);
		count++;
	} while (added);

	cout << endl << "Schemes populated after " << count << " passes through the Rules." << endl << endl;
	*/

	queriesLoop(datalog);

}

void Interpreter::queriesLoop(DatalogProgram datalog) {

	cout << endl << "Query Evaluation" << endl;

	for (Predicate q : datalog.queries) {
		Relation newRelation = evalQuery(q);
		cout << q.toString() << "? ";
		if (newRelation.getTupleList().size() != 0) {
			cout << "Yes(" << newRelation.getTupleList().size() << ")";
		}
		else {
			cout << "No";
		}

		cout << endl;

		for (Tuple t : newRelation.getTupleList()) {
			unsigned int j = 1;
			if (t.size() != 0) {
				cout << "  ";
			}
			for (unsigned int i = 0; i < newRelation.getScheme().size(); i++) {
				cout << newRelation.getScheme().at(i) << "=" << t.at(i);
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

void Interpreter::sccRulesLoop(DatalogProgram datalog, vector<set<int>> SCCs) {
	Relation headRelation;
	bool newTupleAdded;

	for (unsigned int i = 0; i < SCCs.size(); i++) {
		sccPassCount = 0;
		cout << "SCC: " << sccToString(SCCs[i]);
		if (SCCs[i].size() == 1 && !headMatch(datalog.rules.at(*(SCCs[i].begin())))) {
				headRelation = evalQuery(datalog.rules.at(*(SCCs[i].begin())).getHead());
				evaluateRules(datalog.rules.at(*(SCCs[i].begin())), headRelation);
				sccPassCount = 1;
				cout << sccPassCount << " passes: " << sccToString(SCCs[i]);
		}
		else {
			do {
				int first = database.getSize();
				for (unsigned int j : SCCs[i]) {
					headRelation = evalQuery(datalog.rules.at(j).getHead());
					evaluateRules(datalog.rules.at(j), headRelation);	
				} 
				int second = database.getSize();
				newTupleAdded = (second > first);
				sccPassCount++;
			} while (newTupleAdded);
			cout << sccPassCount << " passes: " << sccToString(SCCs[i]);
		}
	}
}

/*bool Interpreter::rulesLoop(DatalogProgram datalog) {

	Relation headRelation;

	int first = database.getSize();
	
	for (unsigned int i = 0; i < datalog.rules.size(); i++) {
		headRelation = evalQuery(datalog.rules.at(i).getHead());
		evaluateRules(datalog.rules.at(i), headRelation);
	}

int second = database.getSize();

return (second > first);
}*/

Relation Interpreter::evalQuery(Predicate query) {
	set<int> projectColumn;
	string schemeName = query.getName();
	Relation newRelation = database.getRelation(query.getName());
	set<string> firstVars;
	vector<int> columnsToKeep;
	Scheme renamedScheme;

	for (unsigned int i = 0; i < query.getParameters().size(); i++) {
		if (query.getParameters().at(i).getName()[0] == '\'') {
			newRelation = newRelation.select(i, query.getParameters().at(i).getName());
		}
		else {
			if (!firstVars.count(query.getParameters().at(i).getName())) {
				firstVars.insert(query.getParameters().at(i).getName());
				columnsToKeep.push_back(i);
				renamedScheme.push_back(query.getParameters().at(i).getName());
			}
			for (unsigned int j = i + 1; j < query.getParameters().size(); j++) {
				if (query.getParameters().at(i).getName() == query.getParameters().at(j).getName()) {
					newRelation = newRelation.select(i, j);
				}
			}
		}
	}

	newRelation = newRelation.project(columnsToKeep);
	newRelation = newRelation.rename(renamedScheme);

	return newRelation;
}

void Interpreter::evaluateRules(Rule rule, Relation headRelation) {
	Relation tmpRelation;
	Relation joinRelation;
	vector<Relation> rulesRelations;
	Scheme scheme;

	for (unsigned int j = 0; j < rule.getPredList().size(); j++) {
		if (j == 0) {
			joinRelation = evalQuery(rule.getPredList().at(j));
		}
		else {
			tmpRelation = evalQuery(rule.getPredList().at(j));
			joinRelation = joinRelation.join(tmpRelation);
		}
	}
	joinRelation = joinRelation.project(getColsToKeep(headRelation, joinRelation));

	joinRelation = joinRelation.rename(headRelation.getScheme());

	joinRelation.setName(headRelation.getName());

	cout << rule.toString() << endl;

	database.getRelation(joinRelation.getName()).rUnion(joinRelation);

}

vector<int> Interpreter::getColsToKeep(Relation r1, Relation r2) {
	vector<int> matchingColumns;
	for (unsigned int i = 0; i < r1.getScheme().size(); i++) {
		for (unsigned int j = 0; j < r2.getScheme().size(); j++) {
			if (r2.getScheme().at(j) == r1.getScheme().at(i)) {
				matchingColumns.push_back(j);
			}
		}
	}
	return matchingColumns;
}

Graph Interpreter::buildGraph(DatalogProgram datalog) {

	Graph newGraph(datalog.rules);

	for (unsigned int i = 0; i < datalog.rules.size(); i++) {
		Rule rule = datalog.rules.at(i);
		for (Predicate p : rule.getPredList()) {
			for (unsigned int j = 0; j < datalog.rules.size(); j++) {
				Rule rule2 = datalog.rules.at(j);
				if (p.getName() == rule2.getHead().getName()) {
					newGraph.addEdge(i, j);
				}
			}
		}
	}

	return newGraph;
}

string Interpreter::dependencyGraph(Graph newGraph) {
	stringstream ss;

	for (unsigned int i = 0; i < newGraph.forwardGraph.size(); i++) {
		ss << "R" << i << ":";
		for (unsigned int j : newGraph.forwardGraph[i].adjacencyList) {
			ss << "R" << j << ",";
		}
		if (newGraph.forwardGraph[i].adjacencyList.size() > 0) {
			ss.seekp(-1, ios_base::end);
		}
		ss << endl;
	}

	return ss.str();
}

bool Interpreter::headMatch(Rule rule) {
	for (unsigned int i = 0; i < rule.getPredList().size(); i++) {
		if (rule.getHead().getName() == rule.getPredList().at(i).getName()) {
			return true;
		}
	}
	return false;
}

string Interpreter::sccToString(set<int> SCC) {
	stringstream ss;

	for (unsigned int i : SCC) {
		ss << "R" << i << ",";
	}

	ss.seekp(-1, ios_base::end);
	ss << endl;

	return ss.str();
}
