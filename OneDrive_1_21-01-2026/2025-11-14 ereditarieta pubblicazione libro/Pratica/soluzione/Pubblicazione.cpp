/*
 * Created by Elena Mastria on 14/11/25.
 */
//

#include "Pubblicazione.h"

void Pubblicazione::setId(int id) {
    this->id = id;
}

void Pubblicazione::setTitolo(const string& titolo) {
    this->titolo = titolo;
}

void Pubblicazione::setAutore(const string& autore) {
    this->autore = autore;
}

void Pubblicazione::mostraDettagli() const {
    cout << "ID: " << id << endl;
    cout << "Titolo: " << titolo << endl;
    cout << "Autore: " << autore << endl;
}
