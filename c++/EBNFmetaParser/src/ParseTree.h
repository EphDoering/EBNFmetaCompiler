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

namespace metaParser {

class ParseTree {
public:
	ParseTree(const char* const * names,ParseTreeNode* root=nullptr);
	~ParseTree();

	friend std::ostream& operator<<(std::ostream& os, const ParseTree* t);
private:
	ParseTreeNode* root;
	const char * const* names;
};

} /* namespace metaParser */
#endif /* PARSETREE_H_ */
