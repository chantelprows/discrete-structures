#include "Parameter.h"

Parameter::Parameter(string parameter) {
	this->parameter = parameter;
}

void Parameter::setName(string value) {
	parameter = value;
}

string Parameter::getName() {
	return parameter;
}