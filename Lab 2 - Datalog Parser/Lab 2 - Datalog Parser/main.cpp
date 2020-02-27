#include <iostream>
#include <vector>
#include <fstream>
#include "Scanner.h"
#include "Parser.h"

using namespace std;


int main(int argc, char* argv[]) {

	Scanner * scanner = new Scanner();

	string file_name = argv[1];

	vector<Token> output;

	output = scanner->getTokens(file_name);

	Parser * parser = new Parser(output);

	bool toParse = parser->parse();

	if (toParse) {
		cout << parser->toString();
	}

	/*for (unsigned int i = 0; i < output.size(); i++) {
		Token token = output.at(i);
		cout << token.printString() << endl;
	}
	cout << "Total Tokens = " << output.size();*/

	delete scanner;
	delete parser;

	//system("pause");

	return 0;
};

