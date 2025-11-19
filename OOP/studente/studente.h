#ifndef STUDENTE_H
#define STUDENTE_H

#include <iostream>
#include <vector>
#include <string>
#include "data.h"

using namespace std;

class Studente {
private:
    unsigned matricola;
    Data dataNascita;
    vector<int> voti;

public:
    Studente(int numEsami = 25);
    Studente(const Studente& altro);

    void setMatricola(unsigned m);
    unsigned getMatricola() const;

    void setDataNascita(const Data& d);
    Data getDataNascita() const;

    void setVoto(int esame, int voto);
    int getVoto(int esame) const;

    void leggiStudente();
    void stampaStudente() const;

    double getMedia() const;
    int getVotoMax() const;
    int getNumEsamiAllaLaurea() const;

    bool studentePiuGiovaneDi(const Studente& S) const;

    Studente& operator=(const Studente& altro);
};

#endif