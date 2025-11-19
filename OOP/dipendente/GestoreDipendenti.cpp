#include "GestoreDipendenti.h"
#include "dipendente.h"
#include <iostream>
#include <vector>

using namespace std;

bool GestoreDipendenti::aggiungiDipendente(const Dipendente &d)
{
    if (esisteDipendente(d.getId()))
    {
        return false;
    }
    dipendenti.push_back(d);
    return true;
}

bool GestoreDipendenti::esisteDipendente(const string &id) const
{
    for (const auto &d : dipendenti)
    {
        if (d.getId() == id)
            return true;
    }
    return false;
}

void GestoreDipendenti::rimuoviDipendente(const string &id)
{
    for (auto it = dipendenti.begin(); it != dipendenti.end(); ++it)
    {
        if (it->getId() == id)
        {
            dipendenti.erase(it);
            return;
        }
    }
}

void GestoreDipendenti::stampa() const
{
    for (const auto &d : dipendenti)
    {
        cout << d << endl;
    }
}

float GestoreDipendenti::calcolaCostoDipendenti() const
{
    float totale = 0;
    for (const auto &d : dipendenti)
    {
        totale += d.getStipendio();
    }
    return totale;
}

ostream &operator<<(ostream &os, const GestoreDipendenti &gd)
{
    for (const auto &d : gd.dipendenti)
    {
        os << d << endl;
    }
    return os;
}
