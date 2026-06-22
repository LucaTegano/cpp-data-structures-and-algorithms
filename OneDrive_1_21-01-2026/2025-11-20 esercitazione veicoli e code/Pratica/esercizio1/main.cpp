#include "Concessionaria.h"
#include "GestoreVeicoli.h"
#include <iostream>
#include <string>

using namespace std;


void stampaMenu() {
    cout << "1. Aggiungi un'automobile al gestore veicoli" << endl
        << "2. Aggiungi una moto al gestore veicoli" << endl
        << "3. Aggiungi un veicolo del gestore veicoli alla concessionaria" << endl
        << "4. Rimuovi un veicolo dalla concessionaria" << endl
        << "5. Stampa il prezzo scontato di un veicolo nel gestore veicoli" << endl
        << "6. Stampa tutti i veicoli nella concessionaria" << endl
        << "9. Esci" << endl
        << ">> ";
}


void leggiVeicolo(string& t, float& p, string& c, string& n) {
    cout << "Inserisci la targa, il prezzo, la casa di produzione e il nome del veicolo separati da spazio: ";
    cin >> t >> p >> c >> n;
}


int main() {
    GestoreVeicoli g;
    Concessionaria c;
   
    stampaMenu();
    int choice;
    cin >> choice;

    while (choice != 9) {

        switch (choice) {

            case 1: {
                string t, c, n;
                float p;
                leggiVeicolo(t, p, c, n);
                g.aggiungiAutomobile(t, p, c, n);
                break;
            }

            case 2: {
                string t, c, n;
                float p;
                leggiVeicolo(t, p, c, n);
                g.aggiungiMoto(t, p, c, n);
                break;
            }

            case 3: {
                string t;
                cout << "inserisci la targa >> ";
                cin >> t;
                Veicolo* v = g.getVeicolo(t);
                if (v != NULL)
                    c.aggiungi(v);
                else
                    cout << "Veicolo inesistente nel gestore veicoli" << endl;
                break;                
            }

            case 4: {
                string t;
                cout << "inserisci la targa >> ";
                cin >> t;
                if (c.rimuovi(t))
                    cout << "Veicolo rimosso con successo" << endl;
                else 
                    cout << "Impossibile rimuovere il veicolo: targa inesistente" << endl;
                break;
            }

            case 5: {
                string t;
                cout << "inserisci la targa >> ";
                cin >> t;
                Veicolo* v = g.getVeicolo(t);
                if (v==NULL)
                    cout << "Veicolo inesistente" << endl;
                else
                    cout << "Il prezzo scontato è: €" << v->getPrezzo() << endl;
                break;
            }

            case 6: {
                for (Veicolo* v : c.getVeicoli())
                    cout << *v;
                break;
            }

            default: {
                cout << "Opzione non valida" << endl;
                break;
            }
        }

        stampaMenu();
        cin >> choice;
    }

    return 0;
}