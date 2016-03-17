/*
 * GrammarParser.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: frederick.doering
 */

#include "GrammarParser.h"

namespace metaParser {

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


GrammarParser::GrammarParser(const char* grammarStr,GrammarParser* gramParser):
		Parser(names,numNames,grammarStr,gramParser) {

}

GrammarParser* GrammarParser::getDefaultParser() {
	if(!defaultGrammarParser){

		//currently not a grammar parsing grammar, but it needs to be to work.
		const char*	inputStr="FIRST = \"yay\"|SECOND,\"no yay\".\nSECOND = \"jk\".";
		ParseTree* temp =new ParseTree(names,
			new ParseTreeNode(SYNTAX,inputStr+0,nullptr,
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
							   new ParseTreeNode(TERMINAL,inputStr+40,nullptr,nullptr,inputStr+44),inputStr+44),inputStr+44),inputStr+44)),inputStr+45)),inputStr+45)
			);
		defaultGrammarParser = new GrammarParser(temp);
		delete temp;

		//Upgrade default parser
		//GrammarParser* old=defaultGrammarParser;
		//defaultGrammarParser=new GrammarParser("UpgradeString1");
		//delete old;
		//repeat

	}
	return defaultGrammarParser;
}

void GrammarParser::setDefaultParser() {
}

GrammarParser::~GrammarParser() {
	// TODO Auto-generated destructor stub
}

GrammarParser* GrammarParser::defaultGrammarParser=nullptr;
const char* const GrammarParser::names[]={
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

GrammarParser::GrammarParser(ParseTree* grammarTree):Parser(names,numNames,grammarTree) {

}


} /* namespace metaParser */
