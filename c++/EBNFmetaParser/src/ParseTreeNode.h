/*
 * ParseTreeNode.h
 *
 *  Created on: Mar 14, 2016
 *      Author: frederick.doering
 */

#ifndef PARSETREENODE_H_
#define PARSETREENODE_H_

class ParseTreeNode {
public:
	ParseTreeNode(int id=0,int start=0,ParseTreeNode * parent=nullptr, ParseTreeNode * firstChild=nullptr);
	ParseTreeNode(int id,int start,ParseTreeNode * parent, ParseTreeNode * firstChild, int end, ParseTreeNode * next=nullptr);
	~ParseTreeNode();
	ParseTreeNode* parent;
	ParseTreeNode* next;
	ParseTreeNode* firstChild;
	int metaidentifier;
	int textStart;
	int textEnd;
};

#endif /* PARSETREENODE_H_ */
