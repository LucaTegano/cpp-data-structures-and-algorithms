#include "Concessionaria.h"
#include <iostream>

using namespace std;


bool Concessionaria::aggiungi(Veicolo* v) {
    for (int i=0; i<veicoli.size(); ++i)
        if (veicoli[i]->getTarga() == v->getTarga()) {
            cout << "Impossibile aggiungere veicolo: esiste già un altro veicolo con questa targa nella concessionaria." << endl;
            return false;
        }
    veicoli.push_back(v);
    cout << "Veicolo aggiunto con successo!" << endl;
    return true;
}


bool Concessionaria::rimuovi(const string& targa) {
    for (auto it=veicoli.begin(); it!=veicoli.end(); ++it) 
        if ((*it)->getTarga() == targa) {
            veicoli.erase(it);  
            return true;
        }
    return false;
}


