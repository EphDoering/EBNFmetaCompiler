//============================================================================
// Name        : EBNFmetaParser.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Parser.h"


int main() {
	const char*	grammarStr="FIRST = \"yay\"|SECOND,\"no yay\".\nSECOND = \"jk\".";

	const char* names[]={"FIRST","SECOND"};

	metaParser::Parser myFirstParser(names,2,grammarStr,45);

	const char* inputStr="jkno yay";
	metaParser::ParseTree* myTree=myFirstParser.parse(inputStr,8);

	//the magic of oop :)
	std::cout << myTree;

	delete myTree;

	return 0;
}
