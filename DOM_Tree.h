#ifndef _DOM_Tree_H
#define _DOM_Tree_H
#include "Node.h"
using std::ostream;
class DOM_Tree
{
	private:
		Node *e;
		int cont;
	
	public:
		//CONSTRUCTORES
		DOM_Tree();
		DOM_Tree(Element a,list<DOM_Tree> l);
		
		//CONSULTORES
		Node* childNode(int p);
		DOM_Tree getElementByID(string id);
				
		//MODIFICADORES
		void appendChild(DOM_Tree h);
		void appendChild(DOM_Tree h,int p);
		void appendChild(string h);
		void appendChild(string h,int p);
		DOM_Tree crear_arbol(string &h);
		void removeChild(int p);
		void replaceChild(DOM_Tree h,int p);
		void replaceChild(string h,int p);
		void copiar(const DOM_Tree &d);
		Node* copiarNode(Node* ptr);
		DOM_Tree operator =(const DOM_Tree &a);
		friend std::ostream& operator<<(std::ostream& os, DOM_Tree &d);
		~DOM_Tree();
};

//CONSTRUCTORES
DOM_Tree::DOM_Tree()
{
	e=NULL;
	cont=-1;
}

DOM_Tree::DOM_Tree(Element a,list<DOM_Tree> l)
{
	e=new Node(a,NULL,NULL);
	Node *aux;
	cont=-1;
	if (!l.empty())
	{
		e->setFirstChild(l.front().e);
		l.pop_front();
		aux=e->firstChild();
		
		while (!l.empty())
		{
			aux->setNextSibling(l.front().e);
			aux=aux->nextSibling();
			l.pop_front();
		}
	}
}

//CONSULTORES
Node* DOM_Tree::childNode(int p)
{
	Node *aux;
	if (p==1)
		return(e->firstChild());
	else
	{
		aux=e->firstChild();
		for (int i = 0; i < p-1; i++)
			aux=aux->nextSibling();
		return(aux);
	}
}
	
DOM_Tree DOM_Tree::getElementByID(string id)
{
	DOM_Tree d,modi;
	Node *aux;
	list<string> l;
	int band=0;
	l=e->element()->attributeList();
	
	while (band==0 && !l.empty())
	{
		if (l.front()==id)
			band=1;
		l.pop_front();
	}
	
	if (band==1)
		return*(this);
	else
	{
		aux=e->firstChild();
		if (aux==NULL)
			return(d);
		else
		{
			while (aux!=NULL)
			{
				modi.e=aux;
				d=modi.getElementByID(id);
				
				if (d.e==NULL)
					aux=aux->nextSibling();
				else
				{
					aux=NULL;
					d.e->setNextSibling(NULL);
				}
			}
			return(d);
		}	
	}
}
	
		
//MODIFICADORES
void DOM_Tree::appendChild(DOM_Tree h)
{
	Node *aux;
	
	if (e==NULL)
		e=copiarNode(h.e);
	else
	{
		aux=e;
		while (aux->nextSibling()!=NULL)
			aux=aux->nextSibling();
		aux->setNextSibling(copiarNode(h.e));
	}
}

void DOM_Tree::appendChild(DOM_Tree h,int p)
{
	Node *aux,*aux2;
	aux=e;
	if(p==1)
	{
		e=copiarNode(h.e);
		e->setNextSibling(aux);
	}
	else
	{
		for (int i = 0; i < p-2; i++)
			aux=aux->nextSibling();
		
		aux2=aux->nextSibling();
		aux->setNextSibling(copiarNode(h.e));
		aux->nextSibling()->setNextSibling(aux2);
	}
}

void DOM_Tree::appendChild(string h)
{
	appendChild(crear_arbol(h));
}

void DOM_Tree::appendChild(string h,int p)
{
	appendChild(crear_arbol(h),p);
}

DOM_Tree DOM_Tree::crear_arbol(string &h)
{
	list<DOM_Tree> l;
	list<string> attr;
	string aux,aux2,aux3;
	int tam,i=0,band=0;
	h.erase(0,1);
	while (h[0]!='>')
	{
		aux=aux+h[0];
		h.erase(0,1);
	}
	h.erase(0,1);
	tam=aux.size();
	while (i<tam && band==0)
	{
		if (aux[i]==' ')
			band=1;
		i++;
	}
	if (band==1)
	{
		aux2=aux;
		aux2.erase(0,i);
		
		while (aux2.size()>0)
		{
			while (aux2[0]!=' ' && aux2.size()>0)
			{
				aux3=aux3+aux2[0];
				aux2.erase(0,1);
			}
			if(aux2.size()>0)
				aux2.erase(0,1);
			attr.push_back(aux3);
			aux3.clear();
		}
		aux.erase(i-1,aux.size());
	}
	Element elem(aux);
	elem.setAttributeList(attr);
	aux.clear();
	if(h[0]!='<')
	{
		while (h[0]!='<')
		{
			aux=aux+h[0];
			h.erase(0,1);
		}
		elem.setInnerHTML(aux);
	}
	while(h[0]=='<' && h[1]!='/')
	{		
		if(h[0]=='<' && h[1]!='/')
			l.push_back(crear_arbol(h));
		while (h[0]!='>')
			h.erase(0,1);
		h.erase(0,1);	
	}
	DOM_Tree d(elem,l);
	return(d);
}		
		
void DOM_Tree::removeChild(int p)
{
	Node *aux,*aux2;
	list<Node*> l;
	aux=e;
	if(p==1)
		e=aux->nextSibling();
	else
	{
		for (int i = 0; i < p-2; i++)
			aux=aux->nextSibling();
		
		aux2=aux->nextSibling();
		aux->setNextSibling(aux2->nextSibling());
		aux=aux2;
	}
	
	l.push_back(aux);
	while(!l.empty())
	{
		aux=l.front();
		l.pop_front();
		aux=aux->firstChild();
		if (aux!=NULL)
		{
			l.push_back(aux);
			aux=aux->nextSibling();
			while (aux!=NULL)
			{
				l.push_back(aux);
				aux=aux->nextSibling();
			}	
		}	
	}
}

void DOM_Tree::replaceChild(string h, int p)
{
	replaceChild(crear_arbol(h),p);
}
	
void DOM_Tree::replaceChild(DOM_Tree h, int p)
{
	Node *aux,*aux2;
	list<Node*> l;
	aux=e;
	if(p==1)
	{
		e=h.e;
		h.e->setNextSibling(aux->nextSibling());
	}
	else
	{
		for (int i = 0; i < p-2; i++)
			aux=aux->nextSibling();
		
		aux2=aux->nextSibling();
		aux->setNextSibling(h.e);
		h.e->setNextSibling(aux2->nextSibling());
		aux=aux2;
	}
	l.push_back(aux);
	while(!l.empty())
	{
		aux2=l.front();
		l.pop_front();
		aux2=aux2->firstChild();
		if (aux2!=NULL)
		{
			l.push_back(aux2);
			aux2=aux2->nextSibling();
			while (aux2!=NULL)
			{
				l.push_back(aux2);
				aux2=aux2->nextSibling();
			}	
		}	
	}	
}

DOM_Tree DOM_Tree::operator =(const DOM_Tree &a)
{
	e=a.e;
	return*(this);
}

Node* DOM_Tree::copiarNode(Node* ptr)
{
	Node *nvo;
	if(ptr==NULL)
			return NULL;
	else
	{
		nvo=new Node(*ptr->element(),copiarNode(ptr->firstChild()),copiarNode(ptr->nextSibling()));
		return nvo;
	}
}

void DOM_Tree::copiar(const DOM_Tree &d)
{
	if(d.e!=NULL)
		e=new Node(*d.e->element(),copiarNode(d.e->firstChild()),NULL);
	else
		e=NULL;
}

ostream& operator<<(std::ostream& os, DOM_Tree &d)
{
	if(d.e!=NULL)
	{
		list<string> l;
		DOM_Tree aux;
		if(d.cont==-1)
		{	os<<"<document>\n";
			d.cont++;
		}
		d.cont++;
		for (int i = 0; i < d.cont; i++)
			os<<"   ";
		
		os<<"<"<<d.e->get_tagname_();
		l=d.e->element()->attributeList();
		while (!l.empty())
		{
			os<<" "<<l.front();
			l.pop_front();
		}
		os<<">";
		os<<d.e->element()->innerHTML();
		aux.e=d.e->firstChild();
		aux.cont=d.cont;
		if(aux.e!=NULL)
		{
			os<<"\n";
			os<<aux;
			
			for (int i = 0; i < d.cont; i++)
				os<<"   ";
		}
		os<<"</"<<d.e->get_tagname_()<<">\n";
		aux.e=d.e->nextSibling();
		aux.cont--;
		d.cont--;
		if(aux.e!=NULL)
			os<<aux;
		aux.e=NULL;
		return os;
	}
	else
	{
		os<<"El arbol esta vacio";
		return os;
	}
	
}


DOM_Tree::~DOM_Tree()
{
	list<Node*> l;
	Node *aux,*aux2;
	
	if(e!=NULL)
	{
		l.push_back(e);
		while(!l.empty())
		{
			aux=l.front();
			aux2=aux->firstChild();
			l.pop_front();
			while (aux2!=NULL)
			{
				l.push_front(aux2);
				aux2=aux2->nextSibling();
			}
		}
	}
	e=NULL;
}

#endif
