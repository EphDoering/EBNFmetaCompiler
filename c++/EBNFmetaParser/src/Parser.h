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


namespace metaParser {

typedef int State;
enum TransitionType {
	T_CONSUME,
	T_DIRECT,
	T_DESEND,
	T_ASCEND,
	T_START_COUNTER,
	T_COUNT,
	T_EXCEPT,
	T_ERROR
};

class GrammarParser;

class Parser {
public:
	Parser(const char* const * names,unsigned int numNames,const char* grammar,int maxLength, GrammarParser* grammarParser=nullptr);

	ParseTree* parse(const char* strWithinGrammar,int maxLength);
	~Parser();
protected:
	//only for grammar parser bootstrap
	Parser(const char* const * names,unsigned int numNames,ParseTree* parsedGrammar);

private:
	const char* const* names;
	int numNames;
	void continueInitFromGrammarTree(ParseTree* parsedGrammar);
	void updateSTOL(State entryState, ParseTreeNode* node, State exitState);
	State maxState;
};

} /* namespace metaParser */

#endif /* PARSER_H_ */
