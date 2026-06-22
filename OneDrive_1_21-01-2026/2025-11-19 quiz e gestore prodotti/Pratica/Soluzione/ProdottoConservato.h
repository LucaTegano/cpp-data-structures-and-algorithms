#ifndef PC_H
#define PC_H

#include "Prodotto.h"
class ProdottoConservato : public Prodotto {
public:
    ProdottoConservato(string n, double p) : Prodotto(n,p) {}

    void stampa() const override {
        cout << "Prodotto Conservato: " << nome << " | " << prezzo << "€\n";
    }
};
#endif
