/*
 * STOL.h
 *
 *  Created on: Mar 30, 2016
 *      Author: frederick.doering
 */

#ifndef STOL_H_
#define STOL_H_

#include <map>
#include <set>
#include <vector>
#include <string>

#include "StateTransition.h"
#include "ParseTree.h"



namespace metaParser {

class GrammarParser;

typedef int MetaID;

class STOL {
public:
	STOL(ParseTree* parsedGrammar,const char* const * names,unsigned int numNames,GrammarParser* grammarParser=nullptr);
	~STOL();
	void insert(State s, StateTransition* st);

	State getMaxState() const {
		return maxState;
	}

private:
	std::set<StateTransition*,StateTransitionCompare> transitions;
	std::vector<std::set<StateTransition*>> stol;

	State maxState;
	std::map<std::string,MetaID> metaIDs;
	std::set<MetaID> metaIdsNeedingProcessed;
	std::set<MetaID> processedMetaIds;
	std::map<MetaID,ParseTreeNode*> unprocessedSyntaxRules;
    bool queueNewLookups;

	MetaID getIdentifier(ParseTreeNode * metaIdentifier);
	MetaID getIdentifier(const std::string& name);

	void updateSTOL(State entryState, ParseTreeNode* node, State exitState);
};

} /* namespace metaParser */

#endif /* STOL_H_ */
