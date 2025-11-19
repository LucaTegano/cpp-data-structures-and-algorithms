#include "Pubblicazione.h"

void Pubblicazione::setId(unsigned int id)
{
    this->id = id;
}
void Pubblicazione::setTitolo(const string &titolo)
{
    this->titolo = titolo;
}

void Pubblicazione::setNomeAutore(const string &nomeAutore)
{
    this->nomeAutore = nomeAutore;
}

void Pubblicazione::mostraDettagli() const
{
    cout << "ID:" << this->id << "Titolo " << this->titolo << " nome " << this->nomeAutore;
}