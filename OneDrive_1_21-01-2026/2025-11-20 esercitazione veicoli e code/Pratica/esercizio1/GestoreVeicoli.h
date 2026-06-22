#ifndef GESTORE_VEICOLI_H
#define GESTORE_VEICOLI_H

#include <vector>
#include "Veicolo.h"
#include "Automobile.h"
#include "Moto.h"

using namespace std;


class GestoreVeicoli {
    private: 
        vector<Veicolo*> veicoli;

        void aggiungiVeicolo(Veicolo* v) {
            // controlla che non esista già un veicolo con la stessa targa di v
            for (Veicolo* ptr : veicoli)
                if (ptr->getTarga() == v->getTarga()) {
                    cout << "Impossibile aggiungere veicolo: targa già esistente" << endl;
                    return;
                }
                    
            veicoli.push_back(v);
            cout << "veicolo aggiunto correttamente" << endl;
            return;
        }

        void clear() {
            while (!veicoli.empty()) {
                delete veicoli.back();  // libera la memoria
                veicoli.pop_back();     // elimina il ptr nel vector
            }            
        }

    public:
        GestoreVeicoli() {}
        
        void aggiungiAutomobile(string t, float p, string c, string n) {
            Veicolo* a = new Automobile(t, p, c, n);
            aggiungiVeicolo(a);
        }

        void aggiungiMoto(string t, float p, string c, string n) {
            Veicolo* m = new Moto(t, p, c, n);
            aggiungiVeicolo(m);
        }

        vector<Veicolo*> getVeicoli() const {
            return veicoli;
        }

        Veicolo* getVeicolo(const string& targa) const {
            for (Veicolo* v : veicoli)
                if (targa == v->getTarga())
                    return v;
            return NULL;
        }

        ~GestoreVeicoli() {
            clear();
        }

        GestoreVeicoli& operator=(const GestoreVeicoli& other) {
            if (this != &other) {
                clear();  // reset del vector di veicoli per sicurezza
                for (Veicolo* v : other.veicoli)
                    this -> veicoli.push_back(v->clone());
            }
            return *this;
        }

        GestoreVeicoli(const GestoreVeicoli& other) {
            for (Veicolo* v : other.veicoli)
                this->veicoli.push_back(v->clone());  // copia profonda di ogni veicolo
        }

};


#endif