/*
 * Parser.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: frederick.doering
 */

#include "Parser.h"
#include "GrammarParser.h"

namespace metaParser {

enum EBNFmID {//TODO: move this somewhere sensible
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

Parser::Parser(const char* const * names, unsigned int numNames,
		const char* grammar, GrammarParser* grammarParser)
	:names(names),
	 numNames(numNames) {
	if(!grammarParser)
		grammarParser=GrammarParser::getDefaultParser();
	ParseTree* temp=grammarParser->parse(grammar);
	continueInitFromGrammarTree(temp);
	delete temp;
}


Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

ParseTree* Parser::parse(const char* strWithinGrammar) {
	//TODO
	//Part 3: Use the state table to parse the incoming string
}

//only for bootstrapped grammar parser
Parser::Parser(const char* const * names, unsigned int numNames,
		ParseTree* parsedGrammar)
	:names(names),
	 numNames(numNames){
	continueInitFromGrammarTree(parsedGrammar);
}

void Parser::continueInitFromGrammarTree(ParseTree* parsedGrammar) {
	maxState=0;
	/*TODO
	 * Part 1: Create a state transition options list (STOL)
	 * 		Step a: get the string names of all the META IDENTIFIERs by looking at the first node in each SYNTAX RULE
	 * 		Step b: Assign entry states to each META IDENTIFIER starting with the ones in the "names" list
	 * 		Step c: for each SYNTAX RULE call updateSTOL on the DEFINITIONS LIST
	 * 		 	with the corresponding entry state and either -1 or -2 as the exit state depending on if you want to record
	 *
	 * Part 2: Generate a state transition table
	 * 		Step a: find the conditions for all state transition options
	 * 		Step b: find intersecting conditions and generate superStates with corresponding reformers.
	 * 		Step c: edit the STOL to reflect the superStates
	 * 		Step d: renumber the states to remove unreached states and shrink the domain.
	 * 		Step e: tabulate the now unambiguous STOL.
	 */
}

void Parser::updateSTOL(State entryState,ParseTreeNode* node,State exitState){
	switch(node->metaidentifier){
	case DEFINITIONS_LIST:
		node= node->firstChild;
		while(node){
			updateSTOL(entryState,node,exitState);
			node=node->next;
		}
		break;
	case SINGLE_DEFINITION:
		node=node->firstChild;
		while(node->next){
			State addedState=++maxState;
			updateSTOL(entryState,node,addedState);
			entryState=addedState;
			node=node->next;
		}
		updateSTOL(entryState,node,exitState);
		break;
	case TERM://TODO
	case EXCEPTION://TODO
	case FACTOR://TODO
		break;
	case PRIMARY:
		updateSTOL(entryState,node->firstChild,exitState);
		break;
	case EMPTY:
		//TODO
		//Create a direct state transition and add it as an option to entry state
		//addOption(entryState,StateTransition(T_DIRECT,exitState));
		break;
	case OPTIONAL_SEQUENCE:
		//TODO
	case REPEATED_SEQUENCE:
		//TODO
	case GROUPED_SEQUENCE:
		//TODO
	case TERMINAL:
		//TODO: Create  length-1 states and for each add a T_CONSUME linking them together
		break;
	case META_IDENTIFIER:
		//TODO
		//find the entry state for the corresponding META IDENTIFIER
		//Create a descend state transition and add it as an option to entry state
		//addOption(entryState,StateTransition(T_DECEND,metaEntry,exitState));
		break;
	case INTEGER://probably will never get to...
	case SPECIAL_SEQUENCE://no idea if we'll ever be able to deal with these.
	default:
		throw 50;
	}
}

} /* namespace metaParser */




