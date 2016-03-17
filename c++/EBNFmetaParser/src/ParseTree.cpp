/*
 * ParseTree.cpp
 *
 *  Created on: Mar 16, 2016
 *      Author: frederick.doering
 */

#include "ParseTree.h"

namespace metaParser {


ParseTree::ParseTree(const char* const * names,ParseTreeNode* root):
		root(root),
		names(names)
			{

}

ParseTree::~ParseTree() {
	if(root) delete root;
}

std::ostream& operator<<(std::ostream& os, const ParseTree& t){
	    std::string str("");
	    ParseTreeNode::printToWithPrefix(os,t.root,str,t.names);
	    return os;
	}
} /* namespace metaParser */
