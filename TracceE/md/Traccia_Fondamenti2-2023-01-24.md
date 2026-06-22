Fondamenti di Programmazione 2 Prova d’esame 24 Gennaio 2023 

## **Esercizio 1** 

Data la seguente porzione di programma rispondere alle domande corrispondenti: `#include<iostream>` **`using namespace`** `std; int main() { int v[] = {...la tua matricola...}; int *p1, *p2, a, b; a = v[0]; b = v[1]; p1 = &a; p2 = &b; p1 = p2; *p2 = v[2]; a = v[3];` _`// 1. Cosa stampa la seguente istruzione?`_ `cout << *p1 << *p2 << a << b << endl;` _`// 2. Data la seguente istruzione, indicare qual è // il modo corretto (A, B, C o D) di gestire la memoria dinamica`_ `int* q1 =` **`new`** `int(20);` _`// 2A:`_ **`delete`** `q1[0];` _`// 2B: Non c'è bisogno di alcuna delete // 2C:`_ **`for`** `(int i = 0; i < 20; ++i) {` **`delete`** `[] q1[i] }` **`delete`** `q1;` _`// 2D:`_ **`delete`** `q1; int *ptr = &v[0]; int *qtr = &v[3];` _`// 3. Cosa stampa la seguente istruzione?`_ `cout << qtr - ptr << endl;` _`// 4. Cosa stampa la seguente istruzione?`_ `int &f = v[2]; f = 7;` **`for`** `(int i = 0; i < 5; ++i) { cout << *(v+i); } cout << endl; }` 

## **Esercizio 2** 

Consideriamo la classe astratta `StatisticheVettore` che abbia la seguente interfaccia pubblica: 

```
classStatisticheVettore{
public:
```

```
virtualdoublecompute(constvector<int>&)=0;
```

```
}
```

Mediante l’uso dell’ereditarietà e opportuno overloading del metodo `double compute(const vector<int>&)` , implementare delle classi `MediaVettore` , `ModaVettore` e `MedianaVettore` che restituiscano rispettivamente la _media_ , la _moda_ e la _mediana_ del `vector<int>` parametro: 

- La media del vettore [ _x_ 1 _, ..., xn_ ] è definita come[[1]] 

   - _n_[[1]] � _ni_ =0 _[x][i]_ 

- La moda del vettore [ _x_ 1 _, ..., xn_ ] è definita come l’elemento che occorre più volte 

- Consideriamo il vettore _x_ = [ _x_ 1 _, ..., xn_ ]. Sia _y_ = [ _y_ 1 _, ..., yn_ ] il vettore che otteniamo ordinando in senso crescente il vettore _X_ . La mediana di _X_ è definita come _yk_ se _X_ ha un numero dispari di elementi, altrimenti come _[y][k]_[+] _[y][k]_[+][1] dove _k_ = _[n]_[intera!).] 2 2[(divisione] 

Realizzare un `main` che mostri l’applicazione del polimorfismo creando opportunamente un `vector` basato solo sulla classe `StatisticheVettore` , ma in cui il primo elemento si comporti come `MediaVettore` , il secondo elemento come `ModaVettore` e il terzo elemento come `MedianaVettore` . 

## **Esercizio 3** 

Sia _G_ un grafo orientato. Ad ogni nodo _v_ di _G_ è associato un numero intero _W_ ( _v_ ), detto _peso_ del nodo _v_ . Scrivere una funzione che preso in input un grafo orientato _G_ e un vettore di pesi _W_ per i suoi nodi restituisca `true` se e solo se è verificata la seguente proprietà, `false` altrimenti: 

_Per ogni nodo u di G, la somma dei pesi dei nodi verso i quali esiste un arco uscente da u è maggiore o uguale alla somma dei pesi dei nodi a partire dai quali esiste un arco entrante in u._ 

La funzione dovrà avere la seguente segnatura: 

```
boolesercizio(constGraph&g,constvector<int>&W);
```

Il grafo è rappresentato una classe `Graph` con la seguente interfaccia pubblica: 

```
classGraph{
public:
```

```
/*Restituisceilnumerodinodidelgrafo*/
/*Sipuòassumereinodisianonumeratida`0`a`n-1`*/
unsignedn()const;
```

```
/*Restituisceilnumerodiarchidelgrafo*/
unsignedm()const;
```

```
/*Restituisce`true`seesoloseesisteunarcoda`i`a`j`*/
booloperator()(unsignedi,unsignedj)const;
```

```
};
```

## **Esercizio 4** 

Scrivere una funzione che presi in input un numero naturale _n_ , una lista di insiemi ( _S_ 1 _, ..., Sm_ ), con _Si ⊆ {_ 0 _,_ 1 _,_ 2 _, ..., n −_ 1 _}_ e un intero _k_ , con 0 _< k < m_ , determini se esiste un insieme _H ⊆{_ 0 _,_ 1 _,_ 2 _, ..., n −_ 1 _}_ di cardinalità _k_ tale che per ogni insieme _Si_ nella lista esista almeno un elemento di _H_ contenuto in _Si_ . 

