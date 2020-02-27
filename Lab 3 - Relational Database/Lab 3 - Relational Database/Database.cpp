#include "Database.h"

Relation& Database::getRelation(string name) {
	return relationList[name];
}

int Database::getSize() {
	int total = 0;
	for (auto i : relationList) {
		total = total + i.second.getTupleList().size();
	}
	return total;
}
