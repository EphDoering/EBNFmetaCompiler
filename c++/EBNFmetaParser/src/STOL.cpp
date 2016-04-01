/*
 * STOL.cpp
 *
 *  Created on: Mar 30, 2016
 *      Author: frederick.doering
 */

#include "STOL.h"

#include "EBNFmetaNames.h"
#include "GrammarParser.h"

namespace metaParser {

STOL::STOL(ParseTree* parsedGrammar,const char* const * names,unsigned int numNames,GrammarParser* grammarParser):transitions(),metaIDs() {

	//fill metaIDs with the names we're returning.
	if(grammarParser){
		ParseTree* tempMetaTree;
		for(unsigned int i=0;i<numNames;i++){
			tempMetaTree=grammarParser->parse(names[i],-1,METAIDENTIFIER);
			getIdentifier(tempMetaTree->root);
			delete tempMetaTree;
		}
	}else{
		for(unsigned int i=0;i<numNames;i++){
			getIdentifier(names[i]);
		}
	}

	//grab all the syntax rules by MetaId
	ParseTreeNode* syntaxRule=parsedGrammar->root->firstChild;
	while(syntaxRule){
		unprocessedSyntaxRules.insert(std::pair<MetaID,ParseTreeNode*>(getIdentifier(syntaxRule->firstChild),syntaxRule->firstChild->next));
		syntaxRule=syntaxRule->next;
	}


	while(metaIdsNeedingProcessed.size()){
		auto nextID=metaIdsNeedingProcessed.begin();
		auto nextSyntaxRule=unprocessedSyntaxRules.find(*nextID);
		processedMetaIds.insert(*nextID);
		metaIdsNeedingProcessed.erase(nextID);
		if(nextSyntaxRule==unprocessedSyntaxRules.end()){
			//TODO fetch the rule from the built in types
			throw 50;
		}else{
			updateSTOL(nextSyntaxRule->first,nextSyntaxRule->second,-1);
			unprocessedSyntaxRules.erase(nextSyntaxRule);
		}
	}

	//TODO Part 2: Generate a state transition table
	//	 * 		Step a: find the conditions for all state transition options
	//	 * 		Step b: find intersecting conditions and generate superStates with corresponding reformers.
	//	 * 		Step c: edit the STOL to reflect the superStates
	//	 * 		Step d: renumber the states to remove unnecessary states and shrink the domain.
	//	 * 		Step e: tabulate the now unambiguous STOL.
}

STOL::~STOL() {
	// TODO Auto-generated destructor stub
	for(auto i: transitions){
		delete i;
	}
}

void STOL::insert(State s, StateTransition* st) { //this will eventually delete every st passed to it.
	//make sure it's unique across all states.
	auto insertRet=transitions.insert(st);
	if(!insertRet.second){
		delete st;
		st=*insertRet.first;
	}//now we have only the one copy of that particular state transition
	stol[s].insert(st);
}


void STOL::updateSTOL(State entryState,ParseTreeNode* node,State exitState){
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
		insert(entryState,new StateTransition(T_DIRECT,exitState));
		break;
	case OPTIONALSEQUENCE:
		//TODO OPTIONALSEQUENCE updateSTOL
	case REPEATEDSEQUENCE:
		//TODO REPEATEDSEQUENCE updateSTOL
	case GROUPEDSEQUENCE:
		//TODO GROUPEDSEQUENCE updateSTOL
	case TERMINAL:
		{
			int quoteCharBytes;
			if(node->firstChild && (node->firstChild->metaidentifier==FIRSTQUOTESYMBOL ||  node->firstChild->metaidentifier==SECONDQUOTESYMBOL)){
				quoteCharBytes=node->firstChild->textEnd-node->firstChild->textStart;
			}else{
				quoteCharBytes=1;
			}
			const char* pos=node->textStart+quoteCharBytes;
			const char* end=node->textEnd-quoteCharBytes;
			State newState;
			if(pos<end){
				end--;
				while(pos<end){
					newState=++maxState;
					insert(entryState,new StateTransition(T_CONSUME,newState,*pos));
					entryState=newState;
					pos++;
				}
				insert(entryState,new StateTransition(T_CONSUME,exitState,*pos));
			}else{
				insert(entryState,new StateTransition(T_DIRECT,exitState));
			}
		}
		break;
	case METAIDENTIFIER:
		insert(entryState,new StateTransition(T_DESEND,getIdentifier(node),exitState));
		break;
	case INTEGER://probably will never get to...
	case SPECIALSEQUENCE://no idea if we'll ever be able to deal with these.
	default:
		throw 50;
	}
}

MetaID STOL::getIdentifier(ParseTreeNode* metaIdentifier) {
	std::string key;
	ParseTreeNode* node=metaIdentifier->firstChild;
	while(node){
		key.push_back(*node->textStart);
		node=node->next;
	}
	return getIdentifier(key);
}


MetaID STOL::getIdentifier(const std::string& name) {
	auto ret=metaIDs.insert(std::pair<std::string,State>(name,maxState+1));
	if(ret.second){
		maxState++;
	}
	return (*ret.first).second;
}



} /* namespace metaParser */
