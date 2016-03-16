/*
 * ParseTree.h
 *
 *  Created on: Mar 16, 2016
 *      Author: frederick.doering
 */

#ifndef PARSETREE_H_
#define PARSETREE_H_

#include <vector>
#include <string>

#include "ParseTreeNode.h"

class ParseTree {
public:
	ParseTree(const char* str);//parser needs to be included
	ParseTree(const char* str, ParseTreeNode* root,const char* const* names);
	~ParseTree();

	friend std::ostream& operator<<(std::ostream& os, const ParseTree& s);
private:
	const char* str;
	ParseTreeNode* root;
	const char * const* names;
};

#endif /* PARSETREE_H_ */
