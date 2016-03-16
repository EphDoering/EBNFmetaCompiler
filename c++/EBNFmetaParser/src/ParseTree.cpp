/*
 * ParseTree.cpp
 *
 *  Created on: Mar 16, 2016
 *      Author: frederick.doering
 */

#include "ParseTree.h"


ParseTree::ParseTree(const char* str):str(str),root(nullptr) {
}


ParseTree::ParseTree(const char* str, ParseTreeNode* root,
		const char* const * names):
		str(str),
		root(root),
		names(names)
			{

}

ParseTree::~ParseTree() {
	if(root) delete root;
}

namespace ParseTree{
std::ostream& operator<<(std::ostream& os, ParseTree& t){
    std::string str("");
    ParseTreeNode::printToWithPrefix(os,t.root,str,t.names);
    return os;
}

}
