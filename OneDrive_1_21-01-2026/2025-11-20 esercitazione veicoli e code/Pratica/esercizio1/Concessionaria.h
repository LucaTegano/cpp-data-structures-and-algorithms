#ifndef CONCESSIONARIA_H
#define CONCESSIONARIA_H

#include "Veicolo.h"
#include "Automobile.h"
#include "Moto.h"
#include <vector>

using namespace std;


class Concessionaria {
    private:
        vector<Veicolo*> veicoli;

    public:
        Concessionaria(): veicoli({}) {}
        vector<Veicolo*> getVeicoli() const {return veicoli;}

        bool aggiungi(Veicolo* v);
        bool rimuovi(const string& targa);
};

#endif