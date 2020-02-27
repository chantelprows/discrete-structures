#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>

using namespace std;

class Parameter {

public:

	Parameter() {}

	Parameter(string parameter);

	~Parameter() {}

	void setName(string value);

	string getName();


private:

	string parameter;

};

#endif