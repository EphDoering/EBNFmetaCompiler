/*
 * ParseTreeNode.cpp
 *
 *  Created on: Mar 14, 2016
 *      Author: frederick.doering
 */

#include "ParseTreeNode.h"

namespace metaParser {

ParseTreeNode::ParseTreeNode(int id,const char* start,ParseTreeNode * parent,ParseTreeNode * firstChild):
parent(parent),next(nullptr),firstChild(firstChild),metaidentifier(id),textStart(start){
	//text end isn't set
}

ParseTreeNode::ParseTreeNode(int id,const char* start,ParseTreeNode * parent,ParseTreeNode * firstChild,const char* end,ParseTreeNode * next):
		parent(parent),next(next),firstChild(firstChild),metaidentifier(id),textStart(start),textEnd(end){
}

ParseTreeNode::~ParseTreeNode() {
	if(next) delete next;
	if(firstChild) delete firstChild;
}

void ParseTreeNode::fixChildrenParentPointers(){
	assignParent(this->firstChild,this,false);
}

void ParseTreeNode::fixDesendantParentPointers(){
	assignParent(this->firstChild,this,true);
}

void ParseTreeNode::assignParent(ParseTreeNode* root, ParseTreeNode* parent, bool recurse){
	if(root){
		root->parent=parent;
		assignParent(root->next,parent,recurse);
		if(recurse){
			assignParent(root->firstChild,root,recurse);
		}
	}
}

void ParseTreeNode::printToWithPrefix(std::ostream& stream, ParseTreeNode* node,std::string& prefix, const char * const* names) {
	if(node){
			stream<< prefix << (node->next?"+-":"`-") << (node->firstChild?"+-":"--") << names[node->metaidentifier];
			if(node->firstChild){
				stream << std::endl;
				prefix.append(node->next?"| ":"  ");
				printToWithPrefix(stream,node->firstChild,prefix,names);
				prefix.resize(prefix.size()-2);
			}else{
				stream << "\t\t(";
				const char* start=node->textStart;
				while(start<node->textEnd){
					stream << start[0];
					start++;
				}
				stream << ")" << std::endl;
			}
			printToWithPrefix(stream,node->next,prefix,names);
		}
}

} /* namespace metaParser */
