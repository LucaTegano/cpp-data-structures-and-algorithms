#ifndef NODE_H
#define NODE_H

template <typename T>
class List;

template <typename T>
class Node
{
   friend class List<T>;
   private:
     T value;
     Node<T> * nextNode;
  public:
     Node(const T& v):value(v),nextNode(nullptr)
     {}  
};

#endif
