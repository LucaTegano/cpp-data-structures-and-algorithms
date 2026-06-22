
#include "GestoreComputers.h"
#include <algorithm>

/*
Calcolare il massimo delle medie dei prezzi dei computers prodotti da ogni produttore.

Utilizzare la divisione intera.

Se non sono presenti computers, restituire -1.
            
*/
int GestoreComputers::metodo1() {
    if (computers.empty())
        return -1;

    vector<string> produttori;
    for (auto c : computers)
        produttori.push_back(c.getProduttore());

    int max_media = -1;
    for (string p : produttori) {
        int avg = 0;
        int count = 0;
        for (auto c : computers) {
            if (c.getProduttore() == p) {
                count++;
                avg += c.getPrezzo();
            }
        }
        avg /= count;
        if (max_media < avg)
            max_media = avg;
    }

    return max_media;
}

/*
Determinare la mediana dei computers ottenuta considerando la seguente relazione d'ordine:

Un computer C1 precede un computer C2 se il prezzo di C1 e' minore del prezzo di C2 e a parita' di prezzo, il tipo di C1 precede il tipo di C2 (ULTRABOOK precede NETBOOK precede NOTEBOOK).

Restituire il prezzo del computer che si trova in corrispondenza della mediana.

Nel caso in cui non ci siano computers presenti nel gestore, restituire -1.

NOTA BENE: calcolare mediana nel seguente modo: dopo aver ordinato gli oggetti si prende quello presente nel mezzo (utilizzare la divisione intera). 
            
*/
bool compare(const Computer& c1, const Computer& c2) {
    if (c1.getPrezzo() != c2.getPrezzo())
        return (c1.getPrezzo() < c2.getPrezzo());
    return c1.getTipo() < c2.getTipo();
}

int GestoreComputers::metodo2() {
    if (computers.empty())
        return -1;
    
    vector<Computer> tmp = getContent();
    sort(tmp.begin(), tmp.end(), compare);
    unsigned median_index = tmp.size() / 2;
    return tmp[median_index].getPrezzo();
}

/*
Siano P1 e P2 produttori distinti tali per cui la somma dei prezzi di tutti i prodotti di P1 meno la somma dei prezzi di tutti i prodotti di P2 e' minima rispetto ad ogni altra coppia di produttori.
Determinare la posizione del primo produttore tra P1 e P2 in ordine di occorrenza nell'elenco.

Se non sono presenti computers o e' presente un solo produttore, restituire -1.

NOTA BENE: nel caso ci siano piu' coppie di produttori distinti che verificano la condizione, considerare il primo produttore in ordine di occorrenza nell'elenco che si trova in una di queste coppie.
            
*/
int GestoreComputers::metodo3() {
    if (computers.empty())
        return -1;
    
    vector<string> produttori;
    for (Computer c : computers)
        if (find(produttori.begin(), produttori.end(), c.getProduttore()) == produttori.end()) 
            produttori.push_back(c.getProduttore());

    if (produttori.size() == 1)
        return -1;

    int min = INT16_MAX;
    int max = INT16_MIN;
    string produttoreMin, produttoreMax;

    // considero sempre produttoreMin - produttoreMax per ottenere la diff minima (vado in negativo)
    for (string p : produttori) {
        int somma = 0;
        for (Computer c : computers) 
            if (c.getProduttore() == p)
                somma += c.getPrezzo();
        
        if (somma < min) {
            min = somma;
            produttoreMin = p;
        }
        if (somma > max) {
            max = somma;
            produttoreMax = p;
        }
    }

    // cerchiamo la prima occorrenza di P1 o P2
    int pos = 0;
	for (auto c : computers) {
		if(c.getProduttore() == produttoreMin || c.getProduttore() == produttoreMax)
			break;
		pos++;
	}
	return pos;
}

/*
Data la seguente definizione:
Un computer C1 e' connesso con un Computer C2 se:
- C1 e' connesso con C2, oppure
- C1 e' connesso con C3 e C3 e' connesso con C2.

Il metodo deve restituire il numero massimo di computer connessi tra loro.

Nel caso in cui non ci siano computers restituisce -1.
            
*/
bool esiste(const vector<string>& v, const string& nome) {
    return find(v.begin(), v.end(), nome) != v.end();
}

int GestoreComputers::metodo4() {
    if (computers.empty())
        return -1;
    
    vector<string> nomi;
    for (Computer c : computers)
        if (find(computers.begin(), computers.end(), c.getNomeComputer()) == computers.end())
            nomi.push_back(c.getNomeComputer());
    
    int max = INT16_MIN; 
    for (Computer starter : computers) {
        vector<string> visitati;
        vector<string> daVisitare;
        daVisitare.push_back(starter.getNomeComputer());

        while (!daVisitare.empty()) {
            string computerCorrente = daVisitare.back();
            daVisitare.pop_back();
            visitati.push_back(computerCorrente);

            for (auto c : computers) 
                if (c.getNomeComputer() == computerCorrente) {
                    string c1 = c.getConnessoA();
                    if (!esiste(visitati, c1) && !esiste(daVisitare, c1))
                        daVisitare.push_back(c1);
                }
        }
        if (visitati.size() > max)
            max = visitati.size();
    }

    return max;
}


