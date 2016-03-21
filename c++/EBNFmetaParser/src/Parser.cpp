/*
 * Parser.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: frederick.doering
 */
#include <string>

#include "Parser.h"
#include "GrammarParser.h"

namespace metaParser {

Parser::Parser(const char* const * names, unsigned int numNames,
		const char* grammar,int maxLength, GrammarParser* grammarParser)
	:names(names),
	 numNames(numNames) {
	if(!grammarParser)
		grammarParser=GrammarParser::getDefaultParser();
	ParseTree* temp=grammarParser->parse(grammar, maxLength);
	continueInitFromGrammarTree(temp);
	delete temp;
}


Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

ParseTree* Parser::parse(const char* strWithinGrammar,int maxLength) {
	//TODO Part 3: Use the state table to parse the incoming string


	//temporary fix: return a nearly empty parsed tree:
	int i=0;
	while(i<maxLength && strWithinGrammar[i])
		i++;
	return new ParseTree(names,new ParseTreeNode(0,strWithinGrammar,nullptr,nullptr,strWithinGrammar+i));
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
	/*TODO continueInitFromGrammarTree body
	 * Part 1: Create a state transition options list (STOL)
	 * 		Step a: Create an empty set of METAIDENTIFIER names.
	 * 		Step b: Create a map of METAIDENTIFIER NAMES to numbers
	 * 		Step c: add the METAIDENTIFIER for the first rule to the map.
	 * 		Step d: for each SYNTAX RULE
	 * 					IF the corresponding METAIDENTIFIER is in the map and not in the set
	 * 						call updateSTOL with the corresponding, entry state,  DEFINITIONSLIST, and
	 * 							either -1 or -2 as the exit state depending on if you want to record
	 * 						add it to the set
	 * 		Step e: repeat d until nothing was added to the set.
	 * 		Step f: for each METAIDENTIFIER in the map, that's not in the set
	 * 					search the parent grammar tree for a matching SYNTAXRULE
	 * 					if found
	 * 						call updateSTOL with the corresponding, entry state,  DEFINITIONSLIST, and
	 * 							either -1 or -2 as the exit state depending on if you want to record
	 * 						add it to the set
	 * 		Step g: repeat d-f until nothing is added in step f
	 * 		Step h: If there is anything in the map that's not in the set error with Undefined METAIDENTIFIERs
	 *
	 * Part 2: Generate a state transition table
	 * 		Step a: find the conditions for all state transition options
	 * 		Step b: find intersecting conditions and generate superStates with corresponding reformers.
	 * 		Step c: edit the STOL to reflect the superStates
	 * 		Step d: renumber the states to remove unnecessary states and shrink the domain.
	 * 		Step e: tabulate the now unambiguous STOL.
	 */
}

void Parser::updateSTOL(State entryState,ParseTreeNode* node,State exitState){
	switch(node->metaidentifier){
	case DEFINITIONSLIST:
		node= node->firstChild;
		while(node){
			updateSTOL(entryState,node,exitState);
			node=node->next;
		}
		break;
	case SINGLEDEFINITION:
		node=node->firstChild;
		while(node->next){
			State addedState=++maxState;
			updateSTOL(entryState,node,addedState);
			entryState=addedState;
			node=node->next;
		}
		updateSTOL(entryState,node,exitState);
		break;
	case TERM://TODO check for exception
	case EXCEPTION://TODO check for regular grammar
	case FACTOR://FIXME check for multiplier
	case PRIMARY:
		updateSTOL(entryState,node->firstChild,exitState);
		break;
	case EMPTY:
		//TODO Empty updateSTOL
		//Create a direct state transition and add it as an option to entry state
		//addOption(entryState,StateTransition(T_DIRECT,exitState));
		break;
	case OPTIONALSEQUENCE:
		//TODO OPTIONALSEQUENCE updateSTOL
	case REPEATEDSEQUENCE:
		//TODO REPEATEDSEQUENCE updateSTOL
	case GROUPEDSEQUENCE:
		//TODO GROUPEDSEQUENCE updateSTOL
	case TERMINAL:
		/*TODO: TERMINAL updateSTOL
		 *
		 *check if it has a subnode with quote character lengths otherwise assume 1
		 *check Create  length-(2*quotelength)-1 states and for each add a T_CONSUME linking them together
		 */
		break;
	case METAIDENTIFIER:
		//TODO METAIDENTIFIER updateSTOL
		//check the map for the corresponding META IDENTIFIER, if it's not there, add it as ++maxState.
		//Create a descend state transition and add it as an option to entry state
		//addOption(entryState,StateTransition(T_DECEND,metaEntry,exitState));
		break;
	case INTEGER://probably will never get to...
	case SPECIALSEQUENCE://no idea if we'll ever be able to deal with these.
	default:
		throw 50;
	}
}

} /* namespace metaParser */




