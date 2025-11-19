#include "telefonata.h"
int main()
{
    Orario in(2, 3, 45);
    Orario fin(2, 3, 46 + 5);
    Telefonata t(in, fin, 98412345);
    cout << in << endl;
    cout << "Durata chiamata: " << t.durata() << " secondi" << endl;
}