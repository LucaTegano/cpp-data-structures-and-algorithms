#ifndef ORARIO_H
#define ORARIO_H
#include <iostream>
using namespace std;
class Orario
{
private:
    unsigned ore, minuti, secondi;

public:
    Orario(unsigned o = 0, unsigned min = 0, unsigned sec = 0) : ore(o), minuti(min), secondi(sec) {}
    unsigned convertiInSecondi() const;
    friend ostream &operator<<(ostream &os, const Orario &o);
};
#endif