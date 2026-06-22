#ifndef GA_H
#define GA_H

#include "Prodotto.h"
#include <vector>
class GestoreProdottiAlimentari {
    vector<Prodotto*> prodotti;

public:
    ~GestoreProdottiAlimentari() {
        for (auto p : prodotti)
            delete p;
    }

    void aggiungi(Prodotto* p) {
        prodotti.push_back(p);
    }

    void stampa() const {
        for (auto p : prodotti)
            p->stampa();
    }

    Prodotto* cerca(const string& nome) {
        for (auto p : prodotti)
            if (p->getNome() == nome)
                return p;
        return nullptr;
    }

    double totale() const {
        double sum = 0;
        for (auto p : prodotti)
            sum += p->getPrezzo();
        return sum;
    }
};

#endif
