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
		default:
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

struct StateTransitionCompare{
	bool operator() (const StateTransition* lhs, const StateTransition* rhs) const{
		int diff=lhs->type-rhs->type;
		if(!diff){
			diff=lhs->to-rhs->to;
			if(!diff){
				switch(lhs->type){
					case T_CONSUME:
						diff=lhs->consume.byte-rhs->consume.byte;
						break;
					case T_DIRECT:
						diff=0;
						break;
					case T_DESEND:
						diff=lhs->desend.exitTo-rhs->desend.exitTo;
						break;
					case T_ASCEND:
						diff=0;
						break;
					case T_START_COUNTER:
						diff=lhs->startCount.exitTo-rhs->startCount.exitTo;
						if(!diff)
							diff=lhs->startCount.count-rhs->startCount.count;
						break;
					case T_EXCEPT:
						diff=lhs->except.exception-rhs->except.exception;
						break;
					case T_ERROR:
						diff=0;
				}
			}
		}
		return diff<0;
	}
};

} /* namespace metaParser */

#endif /* STATETRANSITION_H_ */
