
#ifndef Computer_H_
#define Computer_H_

#include <iostream>
#include <string>

using namespace std;


enum Tipo { ULTRABOOK = 0, NETBOOK, NOTEBOOK };
#include <algorithm>
    

class Computer {
private:
    string nomeComputer;
    string produttore;
    int prezzo;
    Tipo tipo;
    string connessoA;
    
public:
    Computer(string _nomeComputer = "", string _produttore = "", int _prezzo = 0, Tipo _tipo = ULTRABOOK, string _connessoA = "") : nomeComputer(_nomeComputer), produttore(_produttore), prezzo(_prezzo), tipo(_tipo), connessoA(_connessoA) {}

    string getNomeComputer() const { return nomeComputer; }
    void setNomeComputer(string v) { nomeComputer = v; }

    string getProduttore() const { return produttore; }
    void setProduttore(string v) { produttore = v; }

    int getPrezzo() const { return prezzo; }
    void setPrezzo(int v) { prezzo = v; }

    Tipo getTipo() const { return tipo; }
    void setTipo(Tipo v) { tipo = v; }

    string getConnessoA() const { return connessoA; }
    void setConnessoA(string v) { connessoA = v; }

    

    bool operator==(const Computer& right) const { return nomeComputer == right.nomeComputer && produttore == right.produttore && prezzo == right.prezzo && tipo == right.tipo && connessoA == right.connessoA; }

friend ostream& operator<<(ostream& out, const Computer& x) { return out << "[" << x.nomeComputer << ", " << x.produttore << ", " << x.prezzo << ", " << x.tipo << ", " << x.connessoA << "]"; }
};

#endif
