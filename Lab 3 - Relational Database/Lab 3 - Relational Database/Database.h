#ifndef DATABASE_H
#define DATABASE_H

#include "Relation.h"
#include "DatalogProgram.h"
#include <map>

using namespace std;

class Database {

public:

	Database() {}

	Relation& getRelation(string name);

	map<string, Relation> relationList;

	int getSize();

};


#endif
