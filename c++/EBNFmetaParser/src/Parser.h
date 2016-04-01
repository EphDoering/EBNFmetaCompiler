/*
 * Parser.h
 *
 *  Created on: Mar 17, 2016
 *      Author: frederick.doering
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "ParseTree.h"
#include "EBNFmetaNames.h"
#include "StateTransition.h"

#include <string>
#include <map>

namespace metaParser {

class GrammarParser;

class Parser {
public:
	Parser(const char* const * names,unsigned int numNames,const char* grammar,int maxLength, GrammarParser* grammarParser=nullptr);

	ParseTree* parse(const char* strWithinGrammar,int maxLength,State startState=0);
	~Parser();
protected:
	//only for grammar parser bootstrap
	Parser(const char* const * names,unsigned int numNames,ParseTree* parsedGrammar);

private:
	const char* const* names;
	int numNames;

	State maxState;
	State maxRecordedState;
	State minTerminableState;
	bool nullTerminable;
	StateTransition** stateTransitionMatrix; //array of StateTransitionPointers
};

} /* namespace metaParser */

#endif /* PARSER_H_ */
