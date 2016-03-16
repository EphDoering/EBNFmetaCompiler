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
	"SYNTAX_RULE",
	"DEFINITIONS_LIST",
	"SINGLE_DEFINITION",
	"TERM",
	"EXCEPTION",
	"FACTOR",
	"PRIMARY",
	"EMPTY",
	"OPTIONAL_SEQUENCE",
	"REPEATED_SEQUENCE",
	"GROUPED_SEQUENCE",
	"TERMINAL",
	"META_IDENTIFIER",
	"INTEGER",
	"SPECIAL_SEQUENCE"};

/*
void printSubTree(ParseTreeNode* root,std::string prefix, const char* str){
	if(root){
		std::cout<< prefix << (root->next?"+-":"`-") << (root->firstChild?"+-":"--") << EBNFnames[root->metaidentifier];
		if(root->firstChild){
			std::cout << std::endl;
			prefix.append(root->next?"| ":"  ");
			printSubTree(root->firstChild,prefix,str);
			prefix.resize(prefix.size()-2);
		}else{
			std::cout<< "\t\t(";
			int start=root->textStart;
			while(start<root->textEnd)
				std::cout << str[start++];
			std::cout<< ")" << std::endl;
		}
		printSubTree(root->next,prefix,str);
	}
}

void printTree(ParseTreeNode* root,const char* str){
	printSubTree(root,std::string(""),str);
}
*/

int main() {
	const char*	inputStr="FIRST = \"yay\"|SECOND,\"no yay\".\nSECOND = \"jk\".";
	/*
	 * FIRST = "yay"|SECOND,"no yay".
	 * SECOND = "jk".
	 * [{"n":"SYNTAX","v":"","c":[{"n":"SYNTAX_RULE","v":"","c":[{"n":"META_IDENTIFIER","v":"FIRST"},{"n":"not here","v":" = "},{"n":"DEFINITIONS_LIST","v":"","c":[{"n":"SINGLE_DEFINITION","v":"","c":[{"n":"PRIMARY","v":"","c":[{"n":"TERMINAL","v":"\"yay\""}]}]},{"n":"not here","v":"|"},{"n":"SINGLE_DEFINITION","v":"","c":[{"n":"PRIMARY","v":"","c":[{"n":"META_IDENTIFIER","v":"SECOND"}]},{"n":"not here","v":","},{"n":"PRIMARY","v":"","c":[{"n":"TERMINAL","v":"\"no yay\""}]}]}]},{"n":"not here","v":".↵"}]},{"n":"SYNTAX_RULE","v":"","c":[{"n":"META_IDENTIFIER","v":"SECOND"},{"n":"not here","v":" = "},{"n":"DEFINITIONS_LIST","v":"","c":[{"n":"SINGLE_DEFINITION","v":"","c":[{"n":"PRIMARY","v":"","c":[{"n":"TERMINAL","v":"\"jk\""}]}]}]},{"n":"not here","v":"."}]}]}]
	 */
	ParseTreeNode* temp=new ParseTreeNode(SYNTAX,inputStr+0,nullptr,
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
	ParseTree myTree(inputStr,temp,EBNFnames);
	temp=nullptr;
	std::cout << myTree;
	return 0;
}
