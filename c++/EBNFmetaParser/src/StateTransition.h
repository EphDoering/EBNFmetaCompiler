/*
 * StateTransition.h
 *
 *  Created on: Mar 23, 2016
 *      Author: frederick.doering
 */

#ifndef STATETRANSITION_H_
#define STATETRANSITION_H_

namespace metaParser {

typedef int State;
enum StateTransitionType{
	T_CONSUME,
	T_DIRECT,
	T_DESEND,
	T_ASCEND,
	T_START_COUNTER,
	T_EXCEPT,
	T_ERROR
};

struct StateTransitionDataConsume{
	StateTransitionDataConsume(char byte):byte(byte){};
	char byte;
};

struct StateTransitionDataDesend{
	State exitTo;
};

struct StateTransitionDataStartCounter{
	StateTransitionDataStartCounter(unsigned int count,State exitTo):count(count),exitTo(exitTo){};
	unsigned int count;
	State exitTo;
};

struct StateTransitionDataExcept{
	State exception;
};


struct StateTransition {
	StateTransition(StateTransitionType type,State to):type(type),to(to),desend(){};
	StateTransition(StateTransitionType type,State to,State s):type(type),to(to),desend(){
		switch(type){
		case T_DESEND:
				desend.exitTo=s;
			break;
		case T_EXCEPT:
				except.exception=s;
			break;
		}
	};
	StateTransition(StateTransitionType type,State to,char byte):type(type),to(to),consume(byte){};
	StateTransition(StateTransitionType type,State to,unsigned int count,State exitTo):type(type),to(to),startCount(count,exitTo){};
	StateTransitionType type;
	State to;
	union {
		StateTransitionDataConsume consume;
		StateTransitionDataDesend desend;
		StateTransitionDataStartCounter startCount;
		StateTransitionDataExcept except;
	};
};

} /* namespace metaParser */

#endif /* STATETRANSITION_H_ */
