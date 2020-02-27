#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "Rule.h"
#include <map>
#include <stack>
#include <set>
#include <vector>

using namespace std;

class Graph {

public:

	Graph() {};
	Graph(vector<Rule> ruleList);
	map<int, Node> forwardGraph;
	map<int, Node> backwardGraph;
	void fillStack();
	void addEdge(int first, int second);
	void dfsReverse(int index);
	void dfsForest();
	void dfsReachable(int start);
	stack<int> postorderNums;
	void findSCC();
	vector<set<int>> getSCCList();
	vector<set<int>> SCCList;
	set<int> stronglyConComs;
	set<int> SCC;

};


#endif
