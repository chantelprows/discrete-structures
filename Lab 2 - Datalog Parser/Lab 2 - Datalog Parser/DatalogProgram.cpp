#include "DatalogProgram.h"

string DatalogProgram::toString() {
	stringstream ss;


	ss << "Schemes(" << schemes.size() << "):" << endl;
	for (unsigned int i = 0; i < schemes.size(); i++) {
		ss << "  " << schemes.at(i).toString() << endl;
	}

	ss << "Facts(" << facts.size() << "):" << endl;
	for (unsigned int i = 0; i < facts.size(); i++) {
		ss << "  " << facts.at(i).toString() << "." << endl;
	}

	ss << "Rules(" << rules.size() << "):" << endl;
	for (unsigned int i = 0; i < rules.size(); i++) {
		ss << "  " << rules.at(i).toString() << endl;
	}

	ss << "Queries(" << queries.size() << "):" << endl;
	for (unsigned int i = 0; i < queries.size(); i++) {
		ss << "  " << queries.at(i).toString() << "?" << endl;
	}
	

	ss << "Domain(" << domain.size() << "):" << endl;
	for (string word : domain) {
		ss << "  " << word << endl;
	}

	return ss.str();

}
