#ifndef TELEFONATA_H
#define TELEFONATA_H
#include "orario.h"
class Telefonata
{
private:
    Orario inizio, fine;
    unsigned numeroChiamato;

public:
    Telefonata(const Orario &inizio, const Orario &fine, unsigned numeroChiamato);
    unsigned durata() const;
};
#endif