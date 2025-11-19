#include "dipendente.h"
#include <iostream>

int main()
{
    Dipendente d = Dipendente();
    Dipendente d2 = Dipendente("AAAA", "CICCIO", "Pasticcio", 3000);
    cout << d2 << d << endl;
    return 0;
}