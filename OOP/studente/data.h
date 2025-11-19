#ifndef DATA_H
#define DATA_H
#include <iostream>

class Data {
private:
    unsigned giorno;
    unsigned mese;
    unsigned anno;

public:
    Data();
    Data(unsigned g, unsigned m, unsigned a);
    void leggi();
    void stampa() const;
    unsigned getMese() const;
    bool piuGiovaneDi(const Data& altra) const;
};

#endif