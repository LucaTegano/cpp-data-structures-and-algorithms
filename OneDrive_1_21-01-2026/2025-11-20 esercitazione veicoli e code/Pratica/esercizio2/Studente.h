#ifndef STUDENTE_H
#define STUDENTE_H

#include <iostream>

using namespace std;


class Studente {
    private:
        unsigned matricola;
        float isee;
        float media;
    
    public:
        Studente() = default;
        Studente(unsigned m, unsigned i, unsigned me): matricola(m), isee(i), media(me) {}

        unsigned getMatricola() const {return matricola;}
        float getIsee() const {return isee;}
        float getMedia() const {return media;}
    
    friend ostream& operator<<(ostream& os, const Studente& s) {
        os << "matricola: " << s.matricola << endl
            << "ISEE: " << s.isee << endl
            << "media: " << s.media << endl;
        return os;
    }

};


#endif