/*
 * grammarParser.h
 *
 *  Created on: Mar 17, 2016
 *      Author: frederick.doering
 */

#ifndef GRAMMARPARSER_H_
#define GRAMMARPARSER_H_

#include "Parser.h"

namespace metaParser {

class GrammarParser: public Parser {
public:
	GrammarParser(const char* grammarStr,int maxLength,GrammarParser* gramParser=nullptr);
	static GrammarParser* getDefaultParser();
	void setDefaultParser();
	~GrammarParser();
protected:

private:
	GrammarParser(ParseTree* grammarTree);//bootstrap
	static GrammarParser* defaultGrammarParser;
	static const char* const names[];
	static const unsigned int numNames=16;
};

} /* namespace metaParser */

#endif /* GRAMMARPARSER_H_ */
