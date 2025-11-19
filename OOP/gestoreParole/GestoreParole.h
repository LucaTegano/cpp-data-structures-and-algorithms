#ifndef GESTORE_PAROLE_H
#define GESTORE_PAROLE_H
#include <string>
#include <vector>

using namespace std;

class GestoreParole
{
private:
    vector<string> parole;

public:
    GestoreParole() = default;
    GestoreParole(vector<string> p) : parole(p) {}

    void leggi();
    bool ripetizione() const;
    bool esisteParola(string parola) const;
    bool esisteParolaConIniziali(string iniziali) const;
    void sostituisciIniziali(string iniziali);
};
#endif