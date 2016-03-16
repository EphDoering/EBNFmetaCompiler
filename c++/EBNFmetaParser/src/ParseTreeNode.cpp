/*
 * ParseTreeNode.cpp
 *
 *  Created on: Mar 14, 2016
 *      Author: frederick.doering
 */

#include "ParseTreeNode.h"

ParseTreeNode::ParseTreeNode(int id,int start,ParseTreeNode * parent,ParseTreeNode * firstChild):
parent(parent),next(nullptr),firstChild(firstChild),metaidentifier(id),textStart(start){
	//text end isn't set
}

ParseTreeNode::ParseTreeNode(int id,int start,ParseTreeNode * parent,ParseTreeNode * firstChild,int end,ParseTreeNode * next):
		parent(parent),next(next),firstChild(firstChild),metaidentifier(id),textStart(start),textEnd(end){
}

ParseTreeNode::~ParseTreeNode() {
	if(next) delete next;
	if(firstChild) delete firstChild;
}
