/*
 * STOL.h
 *
 *  Created on: Mar 30, 2016
 *      Author: frederick.doering
 */

#ifndef STOL_H_
#define STOL_H_

#include <set>
#include <vector>

#include "StateTransition.h"

namespace metaParser {

class STOL {
public:
	STOL();
	~STOL();
	void insert(State s, StateTransition* st);
private:
	std::set<StateTransition*,StateTransitionCompare> transitions;
	std::vector<std::set<StateTransition*>> stol;
};

} /* namespace metaParser */

#endif /* STOL_H_ */
