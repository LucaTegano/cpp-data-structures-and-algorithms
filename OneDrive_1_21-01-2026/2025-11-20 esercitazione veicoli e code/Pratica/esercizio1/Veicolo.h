#ifndef VEICOLO_H
#define VEICOLO_H

#include <string>
#include <iostream>

using namespace std;


class Veicolo {
    private:
        string targa;
        float prezzo;
        string casa_produttrice;
        string nome;

    public:
        Veicolo() = default;
        Veicolo(string t, float p, string c, string n): targa(t), prezzo(p), casa_produttrice(c), nome(n) {}
        virtual ~Veicolo() {} 
        
        string getTarga() const {return targa;}
        virtual float getPrezzo() const {return prezzo;}
        string getCasaProduttrice() const {return casa_produttrice;}
        string getNome() const {return nome;}   

        virtual Veicolo* clone() {
            return new Veicolo(*this);
        }

    friend ostream& operator<<(ostream& os, const Veicolo& v) {
        os << v.targa << ' ' << v.getPrezzo() << "€ " << v.casa_produttrice << ' ' << v.nome << endl;
        return os;
    }    
};

#endif