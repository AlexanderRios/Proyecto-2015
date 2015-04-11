#ifndef _NODE_H
#define _NODE_H
#include "element.h"
using std::cout;
class Node
{
	private:
		Element *e;
		Node *fc;
		Node *ns;
	
	public:
		//CONSTRUCTORES
		Node(Element a);
		Node(Element a,Node *fc,Node *ns);
		Node(const Node& e);
		
		//CONSULTORES
		Element* element();
		string get_tagname_();
		Node *firstChild();
		Node *nextSibling();
		
		//MODIFICADORES
		void setElement(Element *a);
		void setFirstChild(Node *a);
		void setNextSibling(Node *a);
		Node operator =(const Node &a);
};

Node::Node(Element a)
{
	e=new Element(a);
	fc=NULL;
	ns=NULL;
}

Node::Node(Element a,Node *f,Node *n)
{
	e=new Element(a);
	fc=f;
	ns=n;
}

Node::Node(const Node& a)
{
	e=a.e;
	fc=a.fc;
	ns=a.ns;
}

Element* Node::element()
{
	return(e);
}

string Node::get_tagname_()
{
	return(e->tagName());	
}

Node* Node::firstChild()
{
	return(fc);
}

Node* Node::nextSibling()
{
	return(ns);
}

void Node::setElement(Element *a)
{
	e=a;
}

void Node::setFirstChild(Node *a)
{
	fc=a;
}
	
void Node::setNextSibling(Node *a)
{
	ns=a;
}

Node Node::operator =(const Node &a)
{
	e=a.e;
	fc=a.fc;
	ns=a.ns;
	return *(this);
}	
#endif

