#ifndef LIST_H
#define LIST_H

#include "node.h"
#include <iostream>
#include <cassert>
template <typename T>
class List
{
private:
   Node<T> *first;
   Node<T> *last;
public:
   List():first(nullptr),last(nullptr)
   {}
   ~List();
   void pushFront(const T&);
   bool popFront();
   void pushBack(const T&);
   bool popBack();
   bool find(const T&) const;
   bool empty() const
   {
      return first==nullptr;
   }
   Node<T>* front();
   void print() const;
   void remove(const T&); 
   void delNode(Node<T>* &); //date un'occhiata a questi altri due metodi 
   void remove_usando_del(const T&);  // <---

};
template <typename T>
List<T>::~List()
{

    while (first !=nullptr)
    {
       Node<T>* tmp = first;
       first=first->nextNode;
       delete tmp;  
       
    }
    
}


template <typename T>
void List<T>::pushFront(const T& v)
{
    Node<T> * tmp = new Node<T>(v);
    
    if (empty())
       first=last=tmp;
    else{
        tmp->nextNode =first;
        first =tmp;
    }
}



template <typename T>
bool List<T>::popFront()
{
   if (empty())
     return false;
   if (first==last)
       {
       delete first;
       first = last = nullptr;
       }
   else
      {
      Node<T> * tmp=first;
      first = first->nextNode;
      delete tmp;  
      }
   return true;
}
       
template <typename T>
void List<T>::print() const
{
   
   Node<T>* tmp= first;
   while (tmp!=nullptr)
   {  
       std::cout<<tmp->value<<std::endl;
       tmp=tmp->nextNode;
   }
}

template <typename T>
void List<T>::pushBack(const T& v)
{
    Node<T> * tmp = new Node<T>(v);
    
    if (empty())
       first=last=tmp;
    else{

        last->nextNode=tmp;
        last=tmp;
    }
}


template <typename T>
bool List<T>::popBack()
{
   if (empty())
     return false;
   if (first==last)
       {
       delete last;
       first = last = nullptr;
       }
   else
      {
      Node<T> * tmp=first;
      while (tmp->nextNode != last)
         tmp=tmp->nextNode;
      delete last;
      last=tmp;
      last->nextNode=nullptr;
      }

   return true;
}

template <typename T>
bool List<T>::find(const  T&value) const
{
    Node<T> * tmp=first;
    
    while(tmp!=nullptr)
    {
       if (tmp->value==value)
         return true;
       tmp=tmp->nextNode; 
    }
    return false;
}
template<typename T>
void List<T>::remove(const T&value)
{
    Node<T> * tmp=first;
    Node<T> * tmpsucc;
    if (empty())
       return;
    if (first->value==value)

        {
        
        first=first->nextNode;
        delete tmp;
        if (first==nullptr)
           last=nullptr;
        return; 
        }

    tmpsucc=tmp->nextNode; 
    while(tmpsucc!=nullptr)
      {
          if (tmpsucc->value==value)
               {
                  tmpsucc=tmpsucc->nextNode;
                  delete tmp->nextNode;
                  tmp->nextNode=tmpsucc;
                  if (tmpsucc == nullptr)
                     last=tmp;   
                  return;
               }
         tmp=tmp->nextNode;    
	 tmpsucc=tmpsucc->nextNode; 
          
      }
    
}

template <class T>
void List<T>::delNode(Node<T>* & pos) 
//N.B. dopo la cancellazione pos punta al nodo successivo a quello cancellato
{
      assert(first!=0);
	assert(pos!=0);
	if (pos==first) 
	{

		first=pos->nextNode;
		delete pos;
		pos=first;
                if (first==nullptr)
                   last=nullptr;  
	}
	else{

		Node<T> * prec=first;
		while(prec->nextNode!=pos) prec=prec->nextNode;
		Node<T> *tmp = pos;
		prec->nextNode = pos->nextNode;
		if (pos==last) last = prec;
		delete pos;
		pos=prec;
	}
}

template <class T>
void List<T>::remove_usando_del(const T&v)
{
    if(empty()) return;
    bool found=false;
	Node<int> * n;
	
	for (n=front(); n!=nullptr; n=n->nextNode)
		if (n->value==v) 
		{
			found=true;
			delNode(n); 

                        break;
		}
	
}

template <class T>
Node<T>* List<T>::front()
{
	return first;
}

#endif
