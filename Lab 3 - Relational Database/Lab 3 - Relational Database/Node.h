#ifndef NODE_H
#define NODE_H

#include <set>

using namespace std;

class Node {

public:

	Node();
	Node(int index);
	void addAdjNode(int index);
	bool visited;
	set<int> adjacencyList;
	int nodeNum;

};




#endif
