#ifndef LIBRO_H
#define LIBRO_H
#include "Pubblicazione.h"

class Libro : public Pubblicazione
{
private:
    int numeroPag;

public:
    Libro(unsigned int id, const string &titolo, const string &nomeAutore, int numeroPag) : Pubblicazione(id, titolo, nomeAutore), numeroPag(numeroPag) {};

    void setNumeroPagine(int numeroPag) { this->numeroPag = numeroPag }
};
#endif