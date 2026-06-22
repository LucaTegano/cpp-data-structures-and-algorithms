/*
 * Created by Elena Mastria on 14/11/25.
 */
//

#ifndef LIBRERIADIGITALE_DOCUMENTORISERVATO_H
#define LIBRERIADIGITALE_DOCUMENTORISERVATO_H

#include "Pubblicazione.h"
class DocumentoRiservato : private Pubblicazione {
    private:
        string pin;

        // Controllo interno PIN
        bool checkPin(const string& inseritoPin) const {
            if (inseritoPin != pin) {
                cout << "PIN errato. Operazione negata." << endl;
                return false;
            }
            return true;
        }

    public:
        DocumentoRiservato(int id, const string& titolo, const string& autore, const string& pin)
            : Pubblicazione(id, titolo, autore), pin(pin) {}

        // Mostra dettagli solo con PIN corretto
        void mostraDettagli(const string& inseritoPin) const {
            if (checkPin(inseritoPin)) {
                cout << "ID: " << id << endl;
                cout << "Titolo: " << titolo << endl;
                cout << "Autore: " << autore << endl;
            }
        }

        // Setter che richiedono PIN
        void setTitolo(const string& inseritoPin, const string& nuovoTitolo) {
            if (checkPin(inseritoPin)) Pubblicazione::setTitolo(nuovoTitolo);
        }

        void setAutore(const string& inseritoPin, const string& nuovoAutore) {
            if (checkPin(inseritoPin)) Pubblicazione::setAutore(nuovoAutore);
        }

        void setId(const string& inseritoPin, int nuovoId) {
            if (checkPin(inseritoPin)) Pubblicazione::setId(nuovoId);
        }

        void setPin(const string& nuovoPin) { pin = nuovoPin; }
};


#endif //LIBRERIADIGITALE_DOCUMENTORISERVATO_H