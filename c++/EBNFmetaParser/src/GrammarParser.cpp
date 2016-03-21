/*
 * GrammarParser.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: frederick.doering
 */

#include "GrammarParser.h"

namespace metaParser {

GrammarParser::GrammarParser(const char* grammarStr,int maxLength,GrammarParser* gramParser):
		Parser(names,numNames,grammarStr,maxLength,gramParser) {

}

GrammarParser* GrammarParser::getDefaultParser() {
	if(!defaultGrammarParser){
		//TODO turn into a minimally working EBNF grammar
		//currently not a grammar parsing grammar, but it needs to be, to work.
		const char*	inputStr="FIRST = \"yay\"|SECOND,\"no yay\".\nSECOND = \"jk\".";
		ParseTreeNode* root=
			new ParseTreeNode(SYNTAX,inputStr+0,nullptr,
				new ParseTreeNode(SYNTAXRULE,inputStr+0,nullptr,
				   new ParseTreeNode(METAIDENTIFIER,inputStr+0,nullptr,nullptr,inputStr+5,
				   new ParseTreeNode(DEFINITIONSLIST,inputStr+8,nullptr,
					  new ParseTreeNode(SINGLEDEFINITION,inputStr+8,nullptr,
						 new ParseTreeNode(PRIMARY,inputStr+8,nullptr,
							 new ParseTreeNode(TERMINAL,inputStr+8,nullptr,nullptr,inputStr+13),inputStr+13),inputStr+13,
					  new ParseTreeNode(SINGLEDEFINITION,inputStr+14,nullptr,
						  new ParseTreeNode(PRIMARY,inputStr+14,nullptr,
							 new ParseTreeNode(METAIDENTIFIER,inputStr+14,nullptr,nullptr,inputStr+20),inputStr+20,
						  new ParseTreeNode(PRIMARY,inputStr+21,nullptr,
							  new ParseTreeNode(TERMINAL,inputStr+21,nullptr,nullptr,inputStr+29),inputStr+29)),inputStr+29)),inputStr+29)),inputStr+31,
				new ParseTreeNode(SYNTAXRULE,inputStr+31,nullptr,
					new ParseTreeNode(METAIDENTIFIER,inputStr+31,nullptr,nullptr,inputStr+37,
					new ParseTreeNode(DEFINITIONSLIST,inputStr+40,nullptr,
					   new ParseTreeNode(SINGLEDEFINITION,inputStr+40,nullptr,
						   new ParseTreeNode(PRIMARY,inputStr+40,nullptr,
							   new ParseTreeNode(TERMINAL,inputStr+40,nullptr,nullptr,inputStr+44),inputStr+44),inputStr+44),inputStr+44)),inputStr+45)),inputStr+45)
			;
		root->fixDesendantParentPointers();
		defaultGrammarParser = new GrammarParser(new ParseTree(names,root));

		//Upgrade default parser
		//GrammarParser* old=defaultGrammarParser;
		//defaultGrammarParser=new GrammarParser("UpgradeString1"); TODO turn into more useful grammar
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

GrammarParser::GrammarParser(ParseTree* grammarTree):Parser(names,NUM_EBNFmID,grammarTree) {

}


} /* namespace metaParser */


#define EBNFMETANAMES_VAR const char* const GrammarParser::names[]
#include "EBNFmetaNames.h"
#undef EBNFMETANAMES_VAR
