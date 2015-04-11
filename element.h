#ifndef _ELEMENT_H
#define _ELEMENT_H
#include <iostream>
#include <list>

using std::list;
using std::string;

class Element
{
	private:
		string tagname;
		list<string> attrlist;
		string innerhtml;
	
	public:
		//CONSTRUCTORES
		Element(string e);
		Element(const Element& e);
		
		//CONSULTORES
		string tagName();
		list<string> attributeList();
		string innerHTML();
		
		//MODIFICADORES
		void setTagName(string e);
		void setAttributeList(list<string> e);
		void setInnerHTML(string e);
		Element operator =(const Element &e);

};

Element::Element(string e)
{
	tagname=e;
}

Element::Element(const Element& e)
{
	tagname=e.tagname;
	attrlist=e.attrlist;
	innerhtml=e.innerhtml;
}

string Element::tagName()
{
	return(tagname);
}

list<string> Element::attributeList()
{
	return(attrlist);
}

string Element::innerHTML()
{
	return(innerhtml);
}

void Element::setTagName(string e)
{
	tagname=e;
}

void Element::setAttributeList(list<string> e)
{
	attrlist.clear();
	while (!e.empty())
	{
		attrlist.push_back(e.front());
		e.pop_front();
	}
}
	
void Element::setInnerHTML(string e)
{
	innerhtml=e;
}

Element Element::operator =(const Element &e)
{
	tagname=e.tagname;
	attrlist=e.attrlist;
	innerhtml=e.innerhtml;
	return *(this);
}

	
#endif
