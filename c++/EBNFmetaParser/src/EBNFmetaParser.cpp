//============================================================================
// Name        : EBNFmetaParser.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "ParseTreeNode.h"
#include "ParseTree.h"

enum EBNFmID {
	SYNTAX,
	SYNTAX_RULE,
	DEFINITIONS_LIST,
	SINGLE_DEFINITION,
	TERM,
	EXCEPTION,
	FACTOR,
	PRIMARY,
	EMPTY,
	OPTIONAL_SEQUENCE,
	REPEATED_SEQUENCE,
	GROUPED_SEQUENCE,
	TERMINAL,
	META_IDENTIFIER,
	INTEGER,
	SPECIAL_SEQUENCE
};

const char* const EBNFnames[]={
	"SYNTAX",
	"SYNTAX RULE",
	"DEFINITIONS LIST",
	"SINGLE DEFINITION",
	"TERM",
	"EXCEPTION",
	"FACTOR",
	"PRIMARY",
	"EMPTY",
	"OPTIONAL SEQUENCE",
	"REPEATED SEQUENCE",
	"GROUPED SEQUENCE",
	"TERMINAL",
	"META IDENTIFIER",
	"INTEGER",
	"SPECIAL SEQUENCE"};

int main() {
	const char*	inputStr="FIRST = \"yay\"|SECOND,\"no yay\".\nSECOND = \"jk\".";
	/* the grammar string:
	 *
	 * FIRST = "yay"|SECOND,"no yay".
	 * SECOND = "jk".
	 *
	 *
	 * [{"n":"SYNTAX","v":"","c":[{"n":"SYNTAX_RULE","v":"","c":[{"n":"META_IDENTIFIER","v":"FIRST"},{"n":"not here","v":" = "},{"n":"DEFINITIONS_LIST","v":"","c":[{"n":"SINGLE_DEFINITION","v":"","c":[{"n":"PRIMARY","v":"","c":[{"n":"TERMINAL","v":"\"yay\""}]}]},{"n":"not here","v":"|"},{"n":"SINGLE_DEFINITION","v":"","c":[{"n":"PRIMARY","v":"","c":[{"n":"META_IDENTIFIER","v":"SECOND"}]},{"n":"not here","v":","},{"n":"PRIMARY","v":"","c":[{"n":"TERMINAL","v":"\"no yay\""}]}]}]},{"n":"not here","v":".↵"}]},{"n":"SYNTAX_RULE","v":"","c":[{"n":"META_IDENTIFIER","v":"SECOND"},{"n":"not here","v":" = "},{"n":"DEFINITIONS_LIST","v":"","c":[{"n":"SINGLE_DEFINITION","v":"","c":[{"n":"PRIMARY","v":"","c":[{"n":"TERMINAL","v":"\"jk\""}]}]}]},{"n":"not here","v":"."}]}]}]
	 *
	 * the JSON save representation used by http://jsfiddle.net/w5ten6y6/2/embedded/result/
	 * which was used to generate the code below.
	 */
	metaParser::ParseTreeNode* temp;
	{//block to limit the using namespace metaParser
	using namespace metaParser;
	temp=new ParseTreeNode(SYNTAX,inputStr+0,nullptr,
		    new ParseTreeNode(SYNTAX_RULE,inputStr+0,nullptr,
		       new ParseTreeNode(META_IDENTIFIER,inputStr+0,nullptr,nullptr,inputStr+5,
		       new ParseTreeNode(DEFINITIONS_LIST,inputStr+8,nullptr,
		          new ParseTreeNode(SINGLE_DEFINITION,inputStr+8,nullptr,
		             new ParseTreeNode(PRIMARY,inputStr+8,nullptr,
		                 new ParseTreeNode(TERMINAL,inputStr+8,nullptr,nullptr,inputStr+13),inputStr+13),inputStr+13,
		          new ParseTreeNode(SINGLE_DEFINITION,inputStr+14,nullptr,
		              new ParseTreeNode(PRIMARY,inputStr+14,nullptr,
		                 new ParseTreeNode(META_IDENTIFIER,inputStr+14,nullptr,nullptr,inputStr+20),inputStr+20,
		              new ParseTreeNode(PRIMARY,inputStr+21,nullptr,
		                  new ParseTreeNode(TERMINAL,inputStr+21,nullptr,nullptr,inputStr+29),inputStr+29)),inputStr+29)),inputStr+29)),inputStr+31,
		    new ParseTreeNode(SYNTAX_RULE,inputStr+31,nullptr,
		        new ParseTreeNode(META_IDENTIFIER,inputStr+31,nullptr,nullptr,inputStr+37,
		        new ParseTreeNode(DEFINITIONS_LIST,inputStr+40,nullptr,
		           new ParseTreeNode(SINGLE_DEFINITION,inputStr+40,nullptr,
		               new ParseTreeNode(PRIMARY,inputStr+40,nullptr,
		                   new ParseTreeNode(TERMINAL,inputStr+40,nullptr,nullptr,inputStr+44),inputStr+44),inputStr+44),inputStr+44)),inputStr+45)),inputStr+45);
	} /* namespace metaParser */


	metaParser::ParseTree myTree(EBNFnames,temp);
	temp=nullptr;//the ParseTree now owns the root treenode;

	//the magic of oop :)
	std::cout << myTree;
	return 0;
}
