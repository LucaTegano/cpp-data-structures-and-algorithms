#include "telefonata.h"

Telefonata::Telefonata(const Orario &o1, const Orario &o2, unsigned nc) : inizio(o1), fine(o2), numeroChiamato(nc) {};
unsigned Telefonata::durata() const
{
    return fine.convertiInSecondi() - inizio.convertiInSecondi();
}