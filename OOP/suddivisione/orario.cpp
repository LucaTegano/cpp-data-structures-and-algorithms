#include "orario.h"
unsigned Orario::convertiInSecondi() const { return ore * 3600 + minuti * 60 + secondi; }
ostream &operator<<(ostream &os, const Orario &o)
{
    os << o.ore << ":" << o.minuti << ":" << o.secondi;
    return os;
}
