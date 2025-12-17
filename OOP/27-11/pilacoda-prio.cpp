#include<iostream>
#include<list>
#include<cassert>

using namespace std;

template<typename T>
class Stack{
private:
   list<T> S;
public:
    void push(T el){S.push_back(el);}
    void pop(){assert(!S.empty()); S.pop_back();}
    bool empty(){return S.empty();}
    size_t size(){return S.size();}
    T top () {return S.back();}
};

template<typename T>
class Queue{
private:
   list<T> S;
public:
    void enqueue(T el){S.push_back(el);}
    void dequeue(){assert(!S.empty()); S.pop_front();}
    bool empty(){return S.empty();}
    size_t size(){return S.size();}
    T front () {return S.front();}
};

//classe coda ereditando la lista
template<typename T>
class QueueINH:protected list<T>{
public:
    void enqueue(T el){this->push_back(el);}
    void dequeue(){assert(!empty()); list<T>::pop_front();}
    
    //bool empty(){return empty();}
    using  list<T>::empty;
    size_t size(){return list<T>::size();}
    T front () {return list<T>::front();}
};

template<typename T>
class QueueINHwithPriority:public QueueINH<T>{
public:
    void enqueue(T el){
        typename list<T>::iterator it=this->begin();
        while(it!=this->end()&&el<=(*it))
        {
               it++;
        }
        this->insert(it,el);
}    


};


                
int main()
{
   Stack<int> H;
   if (!H.empty())
     H.pop();
   QueueINHwithPriority<int>  Q;
   Q.enqueue(3);
   Q.enqueue(2);
   Q.enqueue(4);
   cout<<Q.front()<<" "<<endl;
   Q.dequeue();
   cout<<Q.front()<<" "<<endl;
   Q.dequeue();
   cout<<Q.front()<<" "<<endl;
      
   if(Q.empty())
      cout<<"coda vuota"<<endl;
 }
    

/*
 * La classe `QueueINHwithPriority` è una coda con priorità implementata ereditando dalla classe `QueueINH<T>`.
 * A differenza di una coda FIFO (First-In, First-Out) tradizionale, una coda con priorità ordina i suoi elementi
 * in base a un criterio di priorità. In questo caso, gli elementi vengono inseriti in ordine crescente (o decrescente,
 * a seconda dell'operatore di confronto '<='), in modo che l'elemento con la priorità più alta (il più piccolo
 * in questa implementazione) sia sempre in testa alla coda.
 *
 * Metodo `enqueue(T el)`:
 * Questo metodo inserisce un elemento `el` nella coda mantenendo l'ordine di priorità.
 * 1. Viene inizializzato un iteratore `it` all'inizio della lista interna (ereditata).
 * 2. L'iteratore scorre la lista finché non trova una posizione in cui `el` non è più minore o uguale all'elemento corrente (`*it`).
 *    Questo significa che `el` deve essere inserito prima di `*it` (o alla fine se `el` è il più grande).
 *    La condizione `el <= (*it)` implica che gli elementi sono mantenuti in ordine non decrescente.
 *    Se `el` è minore o uguale a `*it`, l'iteratore avanza, cercando la posizione corretta.
 * 3. Una volta trovata la posizione (o raggiunta la fine della lista), `el` viene inserito in quella posizione usando `this->insert(it, el)`.
 *
 * Effetto:
 * - Il metodo `front()` della coda restituirà sempre l'elemento con la priorità più alta (il valore più piccolo in questa implementazione).
 * - Il metodo `dequeue()` rimuoverà sempre l'elemento con la priorità più alta.
 *
 * Questo trasforma la coda in una min-priority queue, dove gli elementi vengono estratti in ordine ascendente.
 */
