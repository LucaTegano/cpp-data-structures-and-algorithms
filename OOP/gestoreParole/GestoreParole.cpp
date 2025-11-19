#include "GestoreParole.h"
#include <iostream>

using namespace std;

void GestoreParole::leggi()
{
    string parola;
    cin >> parola;
    while (parola != "0")
    {
        parole.push_back(parola);
        cin >> parola;
    }
}

bool GestoreParole::ripetizione() const
{
    for (int i = 0; i < parole.size(); ++i)
    {
        for (int j = i + 1; j < parole.size(); ++j)
        {
            if (i != j && parole[i] == parole[j])
                return true;
        }
    }
    return false;
}

bool GestoreParole::esisteParola(string parola) const
{
    for (const auto &p : parole)
    {
        if (p == parola)
            return true;
    }
    return false;
}

bool GestoreParole::esisteParolaConIniziali(string iniziali) const
{
    for (int i = 0; i < parole.size(); ++i)
    {
        if (parole[i].find(iniziali) == 0)
            return true;
    }
    return false;
}

void GestoreParole::sostituisciIniziali(string iniziali)
{
    for (int i = 0; i < parole.size(); ++i)
    {
        if (parole[i].size() >= 5)
            parole[i].replace(0, 3, iniziali);
    }
}