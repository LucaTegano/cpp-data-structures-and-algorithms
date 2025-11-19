#include <iostream>
using namespace std;

struct Insieme
{
    bool *elementi;
    int dimensione;
};

Insieme inizializza(int dim)
{
    Insieme s;
    s.dimensione = dim;
    s.elementi = new bool[dim]();
    return s;
}

void dealloca(Insieme &s)
{
    delete[] s.elementi;
    s.elementi = nullptr;
    s.dimensione = 0;
}

void stampa(const Insieme &s)
{
    cout << "{ ";
    for (int i = 0; i < s.dimensione; ++i)
    {
        if (s.elementi[i])
        {
            cout << i << " ";
        }
    }
    cout << "}" << endl;
}

void cambiaDimensioni(Insieme &s, int nuovaDimensione)
{
    bool *nuovoArray = new bool[nuovaDimensione]();

    int elementiDaCopiare = (s.dimensione < nuovaDimensione)
                                ? s.dimensione
                                : nuovaDimensione;

    for (int i = 0; i < elementiDaCopiare; ++i)
    {
        nuovoArray[i] = s.elementi[i];
    }

    delete[] s.elementi;
    s.elementi = nuovoArray;
    s.dimensione = nuovaDimensione;
}

void aggiungiElemento(Insieme &s, int k)
{
    if (k < 0)
        return;

    if (k >= s.dimensione)
    {
        cambiaDimensioni(s, k + 1);
    }

    s.elementi[k] = true;
}

Insieme unione(const Insieme &a, const Insieme &b)
{
    int nuovaDim = (a.dimensione > b.dimensione)
                       ? a.dimensione
                       : b.dimensione;

    Insieme risultato = inizializza(nuovaDim);

    for (int i = 0; i < nuovaDim; ++i)
    {
        bool inA = (i < a.dimensione) && a.elementi[i];
        bool inB = (i < b.dimensione) && b.elementi[i];
        risultato.elementi[i] = inA || inB;
    }
    return risultato;
}

Insieme intersezione(const Insieme &a, const Insieme &b)
{
    int nuovaDim = (a.dimensione < b.dimensione)
                       ? a.dimensione
                       : b.dimensione;

    Insieme risultato = inizializza(nuovaDim);

    for (int i = 0; i < nuovaDim; ++i)
    {
        risultato.elementi[i] = a.elementi[i] && b.elementi[i];
    }
    return risultato;
}

Insieme copia(const Insieme &originale)
{
    Insieme nuova = inizializza(originale.dimensione);
    for (int i = 0; i < originale.dimensione; ++i)
    {
        nuova.elementi[i] = originale.elementi[i];
    }
    return nuova;
}

int main()
{
    Insieme setA = inizializza(11);
    aggiungiElemento(setA, 2);
    aggiungiElemento(setA, 5);
    aggiungiElemento(setA, 7);
    cout << "A è : ";
    stampa(setA);

    Insieme setB = inizializza(7);
    aggiungiElemento(setB, 2);
    aggiungiElemento(setB, 5);
    aggiungiElemento(setB, 0);
    cout << "B è : ";
    stampa(setB);

    Insieme setUnione = unione(setA, setB);
    cout << "Unione(A, B): ";
    stampa(setUnione);

    Insieme setInter = intersezione(setA, setB);
    cout << "Intersezione(A, B): ";
    stampa(setInter);

    Insieme setCopia = copia(setA);
    cout << "Copia(A): ";
    stampa(setCopia);

    cout << "Aggiungo 9 ad A (resize auto):" << endl;
    aggiungiElemento(setA, 9);
    cout << "A: ";
    stampa(setA);

    cout << "Riduco A a dim 4:" << endl;
    cambiaDimensioni(setA, 4);
    cout << "A: ";
    stampa(setA);

    dealloca(setA);
    dealloca(setB);
    dealloca(setUnione);
    dealloca(setInter);
    dealloca(setCopia);

    return 0;
}