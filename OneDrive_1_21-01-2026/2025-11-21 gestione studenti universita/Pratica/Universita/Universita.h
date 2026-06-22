#ifndef UNIVERSITA_H
#define UNIVERSITA_H

#include "StudenteDinamico.h"
#include <iostream>
#include <string>

using namespace std;

class Universita {
private:
    string nome;
    StudenteDinamico* studenti; 
    int numeroStudenti; // Numero attuale di studenti (size)
    int capacity;       // Dimensione fisica dell'array allocato

    // Metodo helper privato per gestire il raddoppio
    void ridimensiona(int nuovaCapacity);

public:
    Universita();
    Universita(string nome);
    Universita(const Universita& other);
    ~Universita();

    Universita& operator=(const Universita& other);

    void aggiungiStudente(const StudenteDinamico& s);
    bool rimuoviStudente(int matricola);
    int cercaStudente(int matricola) const;

    StudenteDinamico& getStudente(int matricola);
    void setStudente(int matricola, const StudenteDinamico& s);
    
    string getNome() const { return nome; }
    int getNumeroStudenti() const { return numeroStudenti; }
    int getCapacity() const { return capacity; }

    StudenteDinamico migliorStudente() const;

    friend ostream& operator<<(ostream& out, const Universita& u);
};

#endif