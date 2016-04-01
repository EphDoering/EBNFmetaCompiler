/*
 * STOL.cpp
 *
 *  Created on: Mar 30, 2016
 *      Author: frederick.doering
 */

#include "STOL.h"

namespace metaParser {

STOL::STOL():transitions() {
	// TODO Auto-generated constructor stub

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

} /* namespace metaParser */
