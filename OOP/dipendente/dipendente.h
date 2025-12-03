#ifndef DIPENDENTE_H
#define DIPENDENTE_H
#include <iostream>
#include <string>

using  namespace std;

class Dipendente
{
private:
    string id;
    string nome;
    string cognome;
    float stipendio;

public:
    // Dipendente() = default;
    Dipendente() : id(""), nome(""), cognome(""), stipendio(0.0) {};
    Dipendente(string i, string n, string c, float s) : id(i), nome(n), cognome(c), stipendio(s) {};

    // getter
    string getId() const { return id; }
    string getNome() const { return nome; }
    string getCognome() const { return cognome; }
    float getStipendio() const { return stipendio; }
    // setter
    void setId(const string &i) { id = i; }
    void setNome(const string &n) { nome = n; }
    void setCognome(const string &c) { cognome = c; }
    void setStipendio(float s) { stipendio = s; }

    friend ostream &operator<<(ostream &os, const Dipendente &d)
    {
        os << "ID: " << d.id << ", Nome: " << d.nome << ", Cognome: " << d.cognome << ", Stipendio: " << d.stipendio;
        return os;
    }
};
#endif