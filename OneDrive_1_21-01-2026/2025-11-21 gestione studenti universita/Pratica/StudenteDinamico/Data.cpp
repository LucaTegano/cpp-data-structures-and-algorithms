/*
 * Created by Elena Mastria on 23/10/24.
 */
//

#include "Data.h"
#include <iostream>
#include <cassert>

using namespace std;

Data::Data(int giorno, int mese, int anno): giorno(giorno), mese(mese), anno(anno) {}

Data::Data(): giorno(0), mese(0), anno(0) {}

int Data::getGiorno() const {
    return giorno;
}

void Data::setGiorno(int giorno) {
    this->giorno = giorno;
}

int Data::getMese() const {
    return mese;
}

void Data::setMese(int mese) {
    assert(mese >= 1 && mese <= 12);
    this->mese = mese;
}

int Data::getAnno() const {
    return anno;
}

void Data::setAnno(int anno) {
    this->anno = anno;
}

Data::Data(Data const& oData): anno(oData.anno), mese(oData.mese), giorno(oData.giorno) {
}

Data& Data::operator=(const Data& oData) {
    if (this == &oData)
        return *this;
    setGiorno(oData.giorno);
    setMese(oData.mese);
    setAnno(oData.anno);
    return *this;
}
ostream& operator<<(ostream& out, const Data& s) {
    out << s.giorno << "/" << s.mese << "/" << s.giorno << endl;
    return out;
}

istream& operator>>(istream& in, Data& s) {
    cout << "inserisci il giorno" << endl;
    in >> s.giorno;
    cout << "inserisci il mese" << endl;
    in >> s.mese;
    cout << "inserisci l'anno" << endl;
    in >> s.anno;
    cout<<s;
    return in;
}

bool Data::operator<(const Data& data) const {
    if (this->anno < data.anno) return true;
    if (this->anno == data.anno) {
        if (this->mese < data.mese) {
            return true;
        } else if (this->mese == data.mese && this->giorno < data.giorno) return true;
    }
    return false;
}

