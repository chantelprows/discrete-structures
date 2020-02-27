#include "Node.h"

Node::Node() {
	visited = false;
}

Node::Node(int index) {
	nodeNum = index;
}

void Node::addAdjNode(int index) {
	adjacencyList.insert(index);
}