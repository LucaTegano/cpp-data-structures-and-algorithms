#ifndef PF_H
#define PF_H

#include "Prodotto.h"

class ProdottoFresco : public Prodotto {
public:
    ProdottoFresco(string n, double p) : Prodotto(n,p) {}

    void stampa() const override {
        cout << "Prodotto Fresco: " << nome << " | " << prezzo << "€\n";
    }
};
#endif
