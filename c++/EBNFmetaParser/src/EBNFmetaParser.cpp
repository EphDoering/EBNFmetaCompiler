//============================================================================
// Name        : EBNFmetaParser.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "ParseTreeNode.h"

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

void assignParent(ParseTreeNode* root, ParseTreeNode* parent, bool recurse){
	if(root){
		root->parent=parent;
		assignParent(root->next,parent,recurse);
		if(recurse){
			assignParent(root->firstChild,root,recurse);
		}
	}
}

void fixParents(ParseTreeNode* root, bool recurse){
	assignParent(root->firstChild,root,recurse);
}

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


int main() {
	const char*	inputStr="FIRST = \"yay\"|SECOND,\"no yay\".\nSECOND = \"jk\".";
	/*
	 * FIRST = "yay"|SECOND,"no yay".
	 * SECOND = "jk".
	 * [{"n":"SYNTAX","v":"","c":[{"n":"SYNTAX_RULE","v":"","c":[{"n":"META_IDENTIFIER","v":"FIRST"},{"n":"not here","v":" = "},{"n":"DEFINITIONS_LIST","v":"","c":[{"n":"SINGLE_DEFINITION","v":"","c":[{"n":"PRIMARY","v":"","c":[{"n":"TERMINAL","v":"\"yay\""}]}]},{"n":"not here","v":"|"},{"n":"SINGLE_DEFINITION","v":"","c":[{"n":"PRIMARY","v":"","c":[{"n":"META_IDENTIFIER","v":"SECOND"}]},{"n":"not here","v":","},{"n":"PRIMARY","v":"","c":[{"n":"TERMINAL","v":"\"no yay\""}]}]}]},{"n":"not here","v":".↵"}]},{"n":"SYNTAX_RULE","v":"","c":[{"n":"META_IDENTIFIER","v":"SECOND"},{"n":"not here","v":" = "},{"n":"DEFINITIONS_LIST","v":"","c":[{"n":"SINGLE_DEFINITION","v":"","c":[{"n":"PRIMARY","v":"","c":[{"n":"TERMINAL","v":"\"jk\""}]}]}]},{"n":"not here","v":"."}]}]}]
	 */
	ParseTreeNode myTree(SYNTAX,0,nullptr,
		    new ParseTreeNode(SYNTAX_RULE,0,nullptr,
		       new ParseTreeNode(META_IDENTIFIER,0,nullptr,nullptr,5,
		       new ParseTreeNode(DEFINITIONS_LIST,8,nullptr,
		          new ParseTreeNode(SINGLE_DEFINITION,8,nullptr,
		             new ParseTreeNode(PRIMARY,8,nullptr,
		                 new ParseTreeNode(TERMINAL,8,nullptr,nullptr,13),13),13,
		          new ParseTreeNode(SINGLE_DEFINITION,14,nullptr,
		              new ParseTreeNode(PRIMARY,14,nullptr,
		                 new ParseTreeNode(META_IDENTIFIER,14,nullptr,nullptr,20),20,
		              new ParseTreeNode(PRIMARY,21,nullptr,
		                  new ParseTreeNode(TERMINAL,21,nullptr,nullptr,29),29)),29)),29)),31,
		    new ParseTreeNode(SYNTAX_RULE,31,nullptr,
		        new ParseTreeNode(META_IDENTIFIER,31,nullptr,nullptr,37,
		        new ParseTreeNode(DEFINITIONS_LIST,40,nullptr,
		           new ParseTreeNode(SINGLE_DEFINITION,40,nullptr,
		               new ParseTreeNode(PRIMARY,40,nullptr,
		                   new ParseTreeNode(TERMINAL,40,nullptr,nullptr,44),44),44),44)),45)),45);
	fixParents(&myTree,true);
	printTree(&myTree,inputStr);
	return 0;
}
