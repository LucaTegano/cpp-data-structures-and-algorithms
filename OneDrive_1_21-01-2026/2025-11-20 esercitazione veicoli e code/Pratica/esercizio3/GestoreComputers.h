
#ifndef GestoreComputers_H
#define GestoreComputers_H

#include "Computer.h"

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

/*

Questa classe contiene un vector di computers. Ogni computer e` caratterizzato dalle seguenti informazioni:

    - nomeComputer: il nome di un computer (string);

    - produttore: il nome del produttore che ha prodotto il computer (string);

    - prezzo: il prezzo del computer (int);

    - tipo: il tipo del computer (un enumerativo con 3 possibili valori: ULTRABOOK, NETBOOK, NOTEBOOK);

    - connessoA: il computer con cui e' connesso in rete, stringa vuota se non esiste (string).
    
    Implementare nel file GestoreComputers.cpp i metodi della classe GestoreComputer.
    
*/
class GestoreComputers   // questa riga e` corretta NON MODIFICARE
{
private:
    vector<Computer> computers;

public:
    // DESCRIZIONE NEL FILE .cpp
    int metodo1();

    // DESCRIZIONE NEL FILE .cpp
    int metodo2();

    // DESCRIZIONE NEL FILE .cpp
    int metodo3();

    // DESCRIZIONE NEL FILE .cpp
    int metodo4();

    
    
    inline bool aggiungi(Computer c) {computers.push_back(c); return true;}
    
    
    inline vector<Computer>& getContent() { return computers; }
};
#endif
