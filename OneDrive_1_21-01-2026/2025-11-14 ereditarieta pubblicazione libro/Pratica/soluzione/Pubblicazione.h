/*
 * Created by Elena Mastria on 14/11/25.
 */
//

#ifndef LIBRERIADIGITALE_PUBBLICAZIONE_H
#define LIBRERIADIGITALE_PUBBLICAZIONE_H

#include <iostream>
#include <string>

using namespace std;

class Pubblicazione {
    protected:
        int id;
        string titolo;
        string autore;

    public:
        Pubblicazione(int id, const string& titolo, const string& autore)
            : id(id), titolo(titolo), autore(autore) {
        }

        void setId(int id);
        void setTitolo(const string& titolo);
        void setAutore(const string& autore);

        void mostraDettagli() const;
};


#endif //LIBRERIADIGITALE_PUBBLICAZIONE_H
