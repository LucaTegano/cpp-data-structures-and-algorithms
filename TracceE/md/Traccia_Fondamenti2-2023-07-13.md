Fondamenti di Programmazione 2 (Corso di Laurea in Informatica) Esame del 13/7/2023 

## Esercizio 1 

Data la seguente porzione di programma rispondere alle domande corrispondenti: 

#include <iostream> 

using namespace std; 

int main() { 

int *m = new int[6]{.. la tua matricola ..}; 

## **// 1. Cosa stampa questa istruzione?** 

cout << *(m + 3)-2 <<endl; 

**// 2. La seguente istruzione è corretta? Se si, cosa stampa?** m[0]=m[1]==9; 

**// 3. Che valore viene stampato per la variabile somma?** 

int somma=0; for (int i = 0;i<6;i++){ if(i%2==0){ int &a = m[i]; a*=0; } somma += m[i]; 

} cout<<somma; 

cout << m[0] + m[1] + m[2] << endl; 

/ **/ 4.La seguente istruzione è corretta? Se si, cosa stampa?Se no, perchè?** 

delete[] m; 

cout << m[0] << endl; 

} 

## Esercizio 2 

Si consideri la seguente classe e completare: 

class Spedizione{ 

private: int codice; float valore; float peso; 

public: 

int getCodice() const; float getValore() const; float getPeso() const; 

_// da implementare_ **friend ostream& operator<<(ostream& os, const Spedizione& sp);** 

**bool operator==(const Spedizione&);** 

}; 

Implementare quindi la classe **CodaSpedizioni** che eredita opportunamente da list<Spedizione*>. Definire almeno i seguenti metodi: 

**void add(Spedizione*);** _//aggiunge la spedizione se non esiste già, quindi se codice, valore e peso sono tutti differenti. La funzione deve garantire che le spedizioni nella coda siano ordinate: si consideri prima il peso, a parità di peso il valore, a parità di valore il codice._ 

**Spedizione* next() const;** 

_//restituisce il prossimo elemento della coda, senza rimuoverlo_ **void remove();** 

_//rimuove il prossimo elemento nella coda_ **unsigned int size() const.** 

_//restituisce il numero di elementi nella coda_ 

Implementare **operator<<** e **operator==** per lla classe Spedizione. 

Fondamenti di Programmazione 2 (Corso di Laurea in Informatica) Esame del 13/7/2023 

## Esercizio 3 

Ogni espressione aritmetica può essere codificata da (almeno) un albero binario dove le foglie hanno come valore informativo numero intero e i nodi interni un operatore aritmetico tra “ `+”` (addizione), `“-”` (sottrazione), “ `/”` (divisione intera), e “ `*”` (moltiplicazione). 

Scrivere una funzione che presa in input un’espressione aritmetica, modellata da un’istanza di `AlberoB<std::string>` , restituisca il suo risultato (come `int` ). 

Si può assumere l’input sia valido (es. espressioni sintatticamente corrette, no divisioni per zero, …), ed è possibile utilizzare la funzione `int std::strtoi(std::string)` per convertire un’istanza di `std::string` nel corrispondente intero. 

L’albero in figura codifica l’espressione aritmetica `3+(4*5)` . La funzione dovrà restituire 23. NB: Nell’albero in input, i valori informativi dei nodi sono rispettivamente le stringhe `“+”, “3”, “*”, “4”, “5”` . ~~|~~ 

La ~~Pe~~ 

**NOTA:** La classe template `AlberoB<T>` possiede la seguente interfaccia pubblica, dove `t` è 

un’istanza della classe: 

- `t.radice() -` Restituisce il valore informativo della radice di `t.` 

- `t.nullo() -` Restituisce `true` se `t` è l’albero vuoto, `false` altrimenti. 

- `t.figlio(d) -` Restituisce il sottoalbero sinistro (se `d == SIN)` o destro (se `d == DES` ). 

## Esercizio 4 

Scrivere una funzione che presi in input un insieme finito di numeri interi 𝑆 _,_ degli insiemi finiti {𝐶 ,  𝐶 ,  ...,  𝐶 } _,_ con 𝐶 ⊂𝑆 , ed un intero _0 <_ 𝑘< 𝑛 , e restituisca true se e solo se è 1 2 𝑛 𝑖 possibile generare un insieme 𝑆* con almeno _k_ elementi tali che ciascun 𝑥 ∈𝑆* compaia in almeno _k_ tra gli insiemi {𝐶 ,  𝐶 ,  ...,  𝐶 } . 1 2 𝑛 

- Si può assumere che gli elementi di 𝑆 e degli insiemi {𝐶 ,  𝐶 ,  ...,  𝐶 } siano tutti distinti; 1 2 𝑛 

- Si può assumere che 𝑆 sia rappresentato come istanza di `std::vector<int>` ; 

- ● Si può assumere che 𝐶 sia rappresentato come istanza di `std::vector<std::vector<int>>` . 

