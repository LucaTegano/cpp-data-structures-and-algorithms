/*
 * Created by Elena Mastria on 14/11/25.
 */
//

#ifndef LIBRERIADIGITALE_LIBRO_H
#define LIBRERIADIGITALE_LIBRO_H

#include "Pubblicazione.h"

class Libro: public Pubblicazione {
    private:
        int numeroPagine;

    public:
        Libro(int id, const string& titolo, const string& autore, int numeroPagine)
            : Pubblicazione(id, titolo, autore), numeroPagine(numeroPagine) {
        }

        void setNumeroPagine(int numeroPagine) { this->numeroPagine = numeroPagine; }

        void mostraDettagli() const {
            Pubblicazione::mostraDettagli();
            cout << "Numero di pagine: " << numeroPagine << endl;
        }
};


#endif //LIBRERIADIGITALE_LIBRO_H
