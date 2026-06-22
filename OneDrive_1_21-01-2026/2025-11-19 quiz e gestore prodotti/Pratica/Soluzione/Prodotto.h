#ifndef P_H
#define P_H
#include <iostream>
#include <string>
using namespace std;

class Prodotto {
protected:
    string nome;
    double prezzo;

public:
    Prodotto(string n, double p) : nome(n), prezzo(p) {}
    virtual ~Prodotto() {}

    virtual void stampa() const = 0;
    double getPrezzo() const { return prezzo; }
    string getNome() const { return nome; }
};
#endif
