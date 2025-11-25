#include "data.h"

// Costruttore di default
Data::Data() : giorno(1), mese(1), anno(2000) {}

// Costruttore con parametri
Data::Data(int g, int m, int a) : giorno(g), mese(m), anno(a) {}ß

// Setters
void Data::setGiorno(int g) {
    giorno = g;
}

void Data::setMese(int m) {
    mese = m;
}

void Data::setAnno(int a) {
    anno = a;
}

// Getters
int Data::getGiorno() const {
    return giorno;
}

int Data::getMese() const {
    return mese;
}

int Data::getAnno() const {
    return anno;
}

// Operatori di confronto
bool Data::operator<(const Data& other) const {
    if (anno != other.anno)
        return anno < other.anno;
    if (mese != other.mese)
        return mese < other.mese;
    return giorno < other.giorno;
}

bool Data::operator==(const Data& other) const {
    return giorno == other.giorno && mese == other.mese && anno == other.anno;
}

// Input/Output
ostream& operator<<(ostream& os, const Data& d) {
    os << d.giorno << "/" << d.mese << "/" << d.anno;
    return os;
}

istream& operator>>(istream& is, Data& d) {
    char slash;
    is >> d.giorno >> slash >> d.mese >> slash >> d.anno;
    return is;
}