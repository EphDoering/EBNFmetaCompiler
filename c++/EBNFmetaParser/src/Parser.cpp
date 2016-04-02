/*
 * Parser.cpp
 *
 *  Created on: Mar 17, 2016
 *      Author: frederick.doering
 */
#include <string>

#include "Parser.h"
#include "GrammarParser.h"
#include "STOL.h"

#include <set>
#include <vector>
#include <limits>

namespace metaParser {


const State DONE=-1;
const int EOFbyte = -1;
const int maxStackDepth=0x7FFFFF;

Parser::Parser(const char* const * names, unsigned int numNames,
		const char* grammar,int maxLength, GrammarParser* grammarParser)
	:names(names),
	 numNames(numNames),
	 nullTerminable(true){
	if(!grammarParser)
		grammarParser=GrammarParser::getDefaultParser();
	ParseTree* grammarTree=grammarParser->parse(grammar, maxLength);

	finishConstruction(STOL(grammarTree,names,numNames,grammarParser));

	delete grammarTree;
}

//only for bootstrapped grammar parser
Parser::Parser(const char* const * names, unsigned int numNames, ParseTree* parsedGrammar)
	:names(names),
	 numNames(numNames),
	 nullTerminable(true){
	finishConstruction(STOL(parsedGrammar,names,numNames));
}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
	if(stateTransitionMatrix)
		delete[] stateTransitionMatrix;
}

ParseTree* Parser::parse(const char* strWithinGrammar,int maxLength,State startState) {
	//TODO Part 3: Use the state table to parse the incoming string


	//temporary fix: return a nearly empty parsed tree:
	int i=0;
	while(i<maxLength && strWithinGrammar[i])
		i++;
	//temporary development shim: parse one string manually:
	if(i==45){
		const char* temp="FIRST = \"yay\"|SECOND,\"no yay\".\nSECOND = \"jk\".";
		/* the grammar string:
		 *
		 * FIRST = "yay"|SECOND,"no yay".
		 * SECOND = "jk".
		 *
		 *
		 * [{"n":"SYNTAX","v":"","c":[{"n":"SYNTAXRULE","v":"","c":[{"n":"METAIDENTIFIER","v":"FIRST"},{"n":"not here","v":" = "},{"n":"DEFINITIONSLIST","v":"","c":[{"n":"SINGLEDEFINITION","v":"","c":[{"n":"PRIMARY","v":"","c":[{"n":"TERMINAL","v":"\"yay\""}]}]},{"n":"not here","v":"|"},{"n":"SINGLEDEFINITION","v":"","c":[{"n":"PRIMARY","v":"","c":[{"n":"METAIDENTIFIER","v":"SECOND"}]},{"n":"not here","v":","},{"n":"PRIMARY","v":"","c":[{"n":"TERMINAL","v":"\"no yay\""}]}]}]},{"n":"not here","v":".\u21b5"}]},{"n":"SYNTAXRULE","v":"","c":[{"n":"METAIDENTIFIER","v":"SECOND"},{"n":"not here","v":" = "},{"n":"DEFINITIONSLIST","v":"","c":[{"n":"SINGLEDEFINITION","v":"","c":[{"n":"PRIMARY","v":"","c":[{"n":"TERMINAL","v":"\"jk\""}]}]}]},{"n":"not here","v":"."}]}]}]
		 *
		 * the JSON save representation used by http://jsfiddle.net/w5ten6y6/2/embedded/result/
		 * which was used to generate the code below.
		 */
		bool same=true;
		while(i--&&same){
			same=temp[i]==strWithinGrammar[i];
		}
		if(same){
			ParseTreeNode* root=
				new ParseTreeNode(SYNTAX,strWithinGrammar+0,nullptr,
					new ParseTreeNode(SYNTAXRULE,strWithinGrammar+0,nullptr,
					   new ParseTreeNode(METAIDENTIFIER,strWithinGrammar+0,nullptr,nullptr,strWithinGrammar+5,
					   new ParseTreeNode(DEFINITIONSLIST,strWithinGrammar+8,nullptr,
						  new ParseTreeNode(SINGLEDEFINITION,strWithinGrammar+8,nullptr,
							 new ParseTreeNode(PRIMARY,strWithinGrammar+8,nullptr,
								 new ParseTreeNode(TERMINAL,strWithinGrammar+8,nullptr,nullptr,strWithinGrammar+13),strWithinGrammar+13),strWithinGrammar+13,
						  new ParseTreeNode(SINGLEDEFINITION,strWithinGrammar+14,nullptr,
							  new ParseTreeNode(PRIMARY,strWithinGrammar+14,nullptr,
								 new ParseTreeNode(METAIDENTIFIER,strWithinGrammar+14,nullptr,nullptr,strWithinGrammar+20),strWithinGrammar+20,
							  new ParseTreeNode(PRIMARY,strWithinGrammar+21,nullptr,
								  new ParseTreeNode(TERMINAL,strWithinGrammar+21,nullptr,nullptr,strWithinGrammar+29),strWithinGrammar+29)),strWithinGrammar+29)),strWithinGrammar+29)),strWithinGrammar+31,
					new ParseTreeNode(SYNTAXRULE,strWithinGrammar+31,nullptr,
						new ParseTreeNode(METAIDENTIFIER,strWithinGrammar+31,nullptr,nullptr,strWithinGrammar+37,
						new ParseTreeNode(DEFINITIONSLIST,strWithinGrammar+40,nullptr,
						   new ParseTreeNode(SINGLEDEFINITION,strWithinGrammar+40,nullptr,
							   new ParseTreeNode(PRIMARY,strWithinGrammar+40,nullptr,
								   new ParseTreeNode(TERMINAL,strWithinGrammar+40,nullptr,nullptr,strWithinGrammar+44),strWithinGrammar+44),strWithinGrammar+44),strWithinGrammar+44)),strWithinGrammar+45)),strWithinGrammar+45);
			root->fixDesendantParentPointers();
			return new ParseTree(names,root);
		}
		i=45;
	}
	else if(i==8){
		const char* temp="jkno yay";
		bool same=true;
		while(i--&&same){
			same=temp[i]==strWithinGrammar[i];
		}
		if(same){
			ParseTreeNode* root=
					new ParseTreeNode(0,strWithinGrammar+0,nullptr,
						new ParseTreeNode(1,strWithinGrammar+0,nullptr,nullptr,strWithinGrammar+2),strWithinGrammar+8);
			root->fixDesendantParentPointers();
			return new ParseTree(names,root);
		}
		i=8;
	}
	return new ParseTree(names,new ParseTreeNode(0,strWithinGrammar,nullptr,nullptr,strWithinGrammar+i));

	ParseTree* returnTree=new ParseTree(names,nullptr);

	ParseTreeNode** next=&returnTree->root;
	ParseTreeNode* parent=nullptr;

	std::vector<State> stateStack;
	unsigned int recordAgainAt=maxStackDepth;
	std::vector<unsigned int> countStack;

	const char* pos=strWithinGrammar;
	const char* end=strWithinGrammar+maxLength;
	int currentByte=*pos;

	State s;

	StateTransition init(T_DESEND,startState,DONE);

	StateTransition* nextTransition= &init;

	while(nextTransition && pos<end){
		s=nextTransition->to;
		switch(nextTransition->type){
			case T_CONSUME:
				pos++;
				if(pos==end){
					goto endOfString;
				}
				currentByte=*pos;
				break;
			case T_DIRECT:
				break;
			case T_DESEND:
				stateStack.push_back(nextTransition->desend.exitTo);
				if(stateStack.size()<recordAgainAt){
					if(s<maxRecordedState){
						parent=*next=new ParseTreeNode(s,pos,parent);
						next=&(*next)->firstChild;
					}else {
						recordAgainAt=stateStack.size();
					}
				}
				break;
			case T_ASCEND:
				if(stateStack.size()<=recordAgainAt){
					recordAgainAt=maxStackDepth;
					parent->textEnd=pos;
					next=&parent->next;
					parent=parent->parent;
				}
				if(stateStack.size()==0){
					return returnTree;
				}
				s=stateStack.back();
				stateStack.pop_back();
				break;
			case T_START_COUNTER:
				countStack.push_back(nextTransition->startCount.count-1);
				stateStack.push_back(nextTransition->startCount.exitTo);
				break;
			case T_COUNT:
				if(!(--countStack.back())){
					countStack.pop_back();
					s=stateStack.back();
					stateStack.pop_back();
				}
				break;
			case T_EXCEPT:
			case T_ERROR:
				//TODO Debug ERROR
				break;
		}
		while(s==-1){

		}
		nextTransition=stateTransitionMatrix[(s<<8)+currentByte];
	}
	if(!currentByte && nullTerminable){
endOfString:
		int left=stateStack.size();
		while(left--){
			if(stateStack[i]<minTerminableState){
				break;
			}
			parent->textEnd=pos;
			parent=parent->parent;
			stateStack.pop_back();
		}
	}

	if(stateStack.size()){
	//we errored so wrap the root in an error node
		returnTree->root=new ParseTreeNode(-1,strWithinGrammar,nullptr,returnTree->root,pos);
	}
	return returnTree;
}

void Parser::finishConstruction(const STOL& stol) {
	maxRecordedState=numNames;
	maxState=stol.getMaxState();
	minTerminableState=0;
	stateTransitionMatrix=nullptr;
}

} /* namespace metaParser */

