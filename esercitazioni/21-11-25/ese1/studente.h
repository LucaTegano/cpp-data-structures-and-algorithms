#ifndef STUDENTE_H
#define STUDENTE_H

#include "data.h"
#include <iostream>

using namespace std;

class StudenteDinamico {
private:
    int matricola;
    Data nascita;
    int* voti; // Array dinamico di 25 interi

public:
    // Costruttori e Distruttore
    StudenteDinamico();
    StudenteDinamico(const StudenteDinamico& other);
    ~StudenteDinamico();

    // Operatore di assegnamento
    StudenteDinamico& operator=(const StudenteDinamico& other);

    // Setters
    void setMatricola(int m);
    void setNascita(const Data& d);
    void setVoto(int indice, int voto);

    // Getters
    int getMatricola() const;
    Data getNascita() const;
    int getVoto(int indice) const;

    // Metodi richiesti
    double getMedia() const;
    int getVotoMax() const;
    int getNumEsamiAllaLaurea() const;
    bool studentePiuGiovaneDi(const StudenteDinamico& S) const;

    // Input/Output
    friend ostream& operator<<(ostream& os, const StudenteDinamico& s);
    friend istream& operator>>(istream& is, StudenteDinamico& s);
};

#endif // STUDENTE_H