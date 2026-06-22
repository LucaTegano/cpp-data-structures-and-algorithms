Fondamenti di Programmazione 2 Prova d’esame 14 Febbraio 2023 

## **Esercizio 1** 

Data la seguente porzione di programma rispondere alle domande corrispondenti: 

```
#include<iostream>
usingnamespacestd;
intmain(){
intv[]={...latuamatricola...};
int*x=v+2;
int*y=v+4;
*(x+1)=*x;
*(y+1)=*y;
//A:Cosastampalaseguenteistruzione?
for(inti=0;i<6;++i)cout<<v[i];
cout<<endl;
//B:Cosastampalaseguenteistruzione?
cout<<(y-x)+(*y+*x)<<endl;
int*p,*q=newint[10];
//C:Qualèilmodocorrettodideallocarelamemoriadinamica?
/*1*/for(inti=0;i<10;++i){deleteq[i];deletep[i];}
/*2*/delete[]q;delete[]p;
/*3*/deletep;deleteq;
/*4*/delete[]q;
int&a=v[1];
intb=v[0];
b=*y;
a=*y;
//D:Cosastampalaseguenteistruzione?
for(inti=0;i<6;++i)cout<<v[i];
cout<<endl;
}
```

## **Esercizio 2** 

Consideriamo la seguente classe `Prodotto` , che si può supporre essere implementata: 

```
classProdotto{
public:
Prodotto(string,int);
Prodotto(constProdotto&);
stringget_nome()const;
doubleget_prezzo()const;
booloperator==(constProdotto&);
private:
stringnome;
doubleprezzo;
```

## `};` 

Completare opportunamente l’implementazione della classe `ListaDellaSpesa` , inserendo la parte dati necessaria, e completando i metodi sotto riportati. La classe deve permettere di tenere traccia di quali prodotti, e in quali quantità, vogliamo acquistare quando andiamo a fare la spesa. 

```
classListaDellaSpesa{
public:
```

```
/*InserisceilProdotto`p`nellalistadellaspesa,conquantità`q`.
Segiàpresente,incrementalaquantità.*/
voidinserisci(constProdotto&p,intq);
/*Rimuoveilprodotto`p`dallalistadellaspesa.
Restituisce`true`se`p`erapresente,`false`altrimenti.*/
boolrimuovi(constProdotto&p);
/*Restituisceilcostototaledellalistadellaspesa.
Ilcostodiunprodottonellalistaècalcolato
comeilprezzodelprodottomoltiplicatolasuaquantità
nellalista.*/
virtualdoubletotale()const;
```

```
};
```

Successivamente, sfruttare l’ereditarietà per implementare una classe `ListaDellaSpesaScontata` , il cui metodo `totale` applicherà uno sconto del 75% ad ogni `Prodotto` che viene acquistato con quantità maggiore di 5. 

## **Esercizio 3** 

Scrivere una funzione che, preso in input un albero binario interi, restituisca `true` se e solo se esiste almeno un nodo foglia _x_ tale che la somma dei valori informativi dei nodi sul percorso dalla radice di _T_ a _x_ è pari a zero, `false` altrimenti. 

## **Esercizio 4** 

Scrivere una funzione che preso in input un grafo non orientato _G_ e un intero positivo _k_ restituisca `true` se e solo se è possibile scegliere un insieme di nodi _W_ in modo che siano verificate le seguenti condizioni: 

   - _W_ contenga esattamente _k_ nodi; 

   - per ogni arco ( _u, v_ ) di _G_ , è vero che almeno uno dei nodi _u_ , _v_ è stato incluso in _W_ - ma non entrambi; 

   - la somma del _grado_ dei nodi inclusi in _W_ è minore o uguale a _n_ , dove _n_ è il numero di nodi di _G_ 

- Per grado di un nodo _v_ si intende il numero di archi incidenti in _v_ . 

