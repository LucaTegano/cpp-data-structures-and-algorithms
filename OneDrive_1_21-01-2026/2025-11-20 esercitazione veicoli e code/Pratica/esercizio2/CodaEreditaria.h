#ifndef CODA_EREDITARIA_H
#define CODA_EREDITARIA_H

#include "Studente.h"
#include <vector>

using namespace std;


class CodaEreditaria: private vector<Studente> {  // tutto ciò che in vector è public, protected o private ora diventa private
    public:
        void aggiungi(const Studente& s);
        Studente prossimo() const;
        void rimuovi();
        unsigned int size() const;

    friend ostream& operator<<(ostream& os, const CodaEreditaria& c) {
        for (auto it=c.begin(); it!=c.end(); ++it) {
            os << "Matricola: " << it->getMatricola() << endl
                << "ISEE: " << it->getIsee() << endl
                << "Media: " << it->getMedia() << endl
                << "-------------" << endl;
        }
        return os;
    }

};


#endif