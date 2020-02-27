#include "Graph.h"

vector<set<int>> Graph::getSCCList() {
	return SCCList;
}


void Graph::addEdge(int first, int second) {
	forwardGraph[first].addAdjNode(second);
	backwardGraph[second].addAdjNode(first);
}

Graph::Graph(vector<Rule> ruleList) {
	for (unsigned int i = 0; i < ruleList.size(); i++) {
		Node newNode(i);
		forwardGraph[i] = newNode;
		backwardGraph[i] = newNode;
	}
}

void Graph::fillStack() {
	for (unsigned int i = 0; i < backwardGraph.size(); i++) {
		if (!backwardGraph[i].visited) {
			dfsReverse(i);
		}
	}
}

void Graph::dfsReverse(int index) {
	Node& node = backwardGraph[index];
	node.visited = true;

	for (unsigned int i : node.adjacencyList) {
		if (!backwardGraph[i].visited) {
			dfsReverse(i);
		}
	}
	postorderNums.push(index);
}


void Graph::dfsForest() {
	for (unsigned int i = 0; i < backwardGraph.size(); i++) {
		if (!backwardGraph[i].visited) {
			dfsReverse(i);
		}
	}
}

void Graph::dfsReachable(int start) {
	Node& node = forwardGraph[start];
	node.visited = true;
	SCC.insert(start);
	
	for (unsigned int i : node.adjacencyList) {
		if (!forwardGraph[i].visited) {
			dfsReachable(i);
		}
	}
}
/*

	
Schemes:
Parent(a,c)
Sibling(a,c)
Ancestor(a,c)

Facts:
Parent('1','2').
Sibling('2','3').
Ancestor('3','2').
Ancestor('2','3').

Rules:
Sibling(x,y):-Parent(x,y),Ancestor(x,y).
Ancestor(y,x):-Sibling(y,x),Parent(y,x).
Parent(x,y):-Ancestor(x,y),Sibling(x,y).

Queries:
Parent(a,c)?



*/

void Graph::findSCC() {

	while (!postorderNums.empty()) {
		int pop = postorderNums.top();
		postorderNums.pop();
		if (!forwardGraph[pop].visited) {
			dfsReachable(pop);
			SCCList.push_back(SCC);
			SCC.clear();
		}
	}
}

