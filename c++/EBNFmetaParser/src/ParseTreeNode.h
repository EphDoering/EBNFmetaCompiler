/*
 * ParseTreeNode.h
 *
 *  Created on: Mar 14, 2016
 *      Author: frederick.doering
 */

#ifndef PARSETREENODE_H_
#define PARSETREENODE_H_
#include <iostream>

class ParseTreeNode {
public:
	ParseTreeNode(int id=0,const char* start=0,ParseTreeNode * parent=nullptr, ParseTreeNode * firstChild=nullptr);
	ParseTreeNode(int id,const char* start,ParseTreeNode * parent, ParseTreeNode * firstChild, const char* end, ParseTreeNode * next=nullptr);
	~ParseTreeNode();
	void fixChildrenParentPointers();
	void fixDesendantParentPointers();
	ParseTreeNode* parent;
	ParseTreeNode* next;
	ParseTreeNode* firstChild;
	int metaidentifier;
	const char* textStart;
	const char* textEnd;
	static void printToWithPrefix(std::ostream& stream, ParseTreeNode* node,std::string & prefix, const char * const* names);
private:
	static void assignParent(ParseTreeNode* root,ParseTreeNode* parent,bool recurse);
};

#endif /* PARSETREENODE_H_ */
