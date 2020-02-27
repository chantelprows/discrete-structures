#include <iostream>
#include <vector>
#include <fstream>
#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"

using namespace std;


int main(int argc, char* argv[]) {

	Scanner * scanner = new Scanner();

	string file_name = argv[1];

	vector<Token> output;

	output = scanner->getTokens(file_name);

	Parser * parser = new Parser(output);

	DatalogProgram toParse = parser->parse();

	Interpreter * interpreter = new Interpreter(toParse);

	/*if (toParse) {
		cout << parser->toString();
	}

	for (unsigned int i = 0; i < output.size(); i++) {
		Token token = output.at(i);
		cout << token.printString() << endl;
	}
	cout << "Total Tokens = " << output.size();*/

	delete scanner;
	delete parser;
	delete interpreter;

	/*
	string SN = "SN";
	Scheme scheme;
	scheme.push_back("S");
	scheme.push_back("N");
	scheme.push_back("A");
	scheme.push_back("P");

	Tuple tuple;

	tuple.push_back("a");
	tuple.push_back("b");
	tuple.push_back("c");
	tuple.push_back("d");

	Relation * R1 = new Relation(SN, scheme);

	string AP = "AP";
	Scheme scheme2;
	scheme2.push_back("A");
	scheme2.push_back("B");
	scheme2.push_back("S");
	scheme2.push_back("P");

	Tuple tuple2;

	tuple2.push_back("c");
	tuple2.push_back("f");
	tuple2.push_back("a");
	tuple2.push_back("d");

	Relation * R2 = new Relation(AP, scheme2);

	R1->addTuple(tuple);

	R2->addTuple(tuple2);

	Relation newRelation = R1->join(*R2);
	*/

	system("pause");

	return 1;
};

