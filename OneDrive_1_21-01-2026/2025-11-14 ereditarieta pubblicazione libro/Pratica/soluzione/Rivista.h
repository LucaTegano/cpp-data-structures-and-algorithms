/*
 * Created by Elena Mastria on 14/11/25.
 */
//

#ifndef LIBRERIADIGITALE_RIVISTA_H
#define LIBRERIADIGITALE_RIVISTA_H

#include "Pubblicazione.h"

class Rivista: protected Pubblicazione {
    private:
        int numeroEdizione;

    public:
        Rivista(int id, const string& titolo, const string& autore, int numeroEdizione)
            : Pubblicazione(id, titolo, autore), numeroEdizione(numeroEdizione) {
        }

        void setTitolo(const string& nuovoTitolo) { Pubblicazione::setTitolo(nuovoTitolo); }
        void setAutore(const string& nuovoAutore) { Pubblicazione::setAutore(nuovoAutore); }
        void setId(int nuovoId) { Pubblicazione::setId(nuovoId); }
        void setNumeroEdizione(int nuovoNumeroEdizione) { numeroEdizione = nuovoNumeroEdizione; }

        void mostraDettagli() const {
            cout << "ID: " << id << endl;
            cout << "Titolo: " << titolo << endl;
            cout << "Autore: " << autore << endl;
            cout << "Numero di edizione: " << numeroEdizione << endl;
        }
};


#endif //LIBRERIADIGITALE_RIVISTA_H
