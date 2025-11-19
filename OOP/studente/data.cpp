#include "data.h"
#include <iostream>

using namespace std;

Data::Data() : giorno(1), mese(1), anno(2000) {}

Data::Data(unsigned g, unsigned m, unsigned a) : giorno(g), mese(m), anno(a) {}

void Data::leggi() {
    cout << "Inserisci data di nascita (giorno mese anno): ";
    cin >> giorno >> mese >> anno;
}

void Data::stampa() const {
    cout << giorno << "/" << mese << "/" << anno;
}

unsigned Data::getMese() const {
    return mese;
}

bool Data::piuGiovaneDi(const Data& altra) const {
    if (anno > altra.anno) return true;
    if (anno < altra.anno) return false;
    if (mese > altra.mese) return true;
    if (mese < altra.mese) return false;
    return giorno > altra.giorno;
}