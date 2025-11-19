#ifndef GESTOREDIPENDENTI_H
#define GESTOREDIPENDENTI_H
#include <vector>
#include "dipendente.h"
#include <iostream>

class GestoreDipendenti
{
private:
    vector<Dipendente> dipendenti;

public:
    bool aggiungiDipendente(const Dipendente &d);
    bool esisteDipendente(const string &id) const;
    void rimuoviDipendente(const string &id);
    void stampa() const;
    float calcolaCostoDipendenti() const;

    friend ostream &operator<<(ostream &os, const GestoreDipendenti &gd);
};
#endif