#include "studente.h"
#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

Studente::Studente(int numEsami)
{
    voti.resize(numEsami, 0);
}

Studente::Studente(const Studente &altro)
{
    matricola = altro.matricola;
    dataNascita = altro.dataNascita;
    voti = altro.voti;
}

void Studente::setMatricola(unsigned m)
{
    matricola = m;
}

unsigned Studente::getMatricola() const
{
    return matricola;
}

void Studente::setDataNascita(const Data &d)
{
    dataNascita = d;
}

Data Studente::getDataNascita() const
{
    return dataNascita;
}

void Studente::setVoto(int esame, int voto)
{
    if (esame >= 0 && esame < voti.size())
    {
        voti[esame] = voto;
    }
}

int Studente::getVoto(int esame) const
{
    if (esame >= 0 && esame < voti.size())
    {
        return voti[esame];
    }
    return -1; // Invalid exam number
}

void Studente::leggiStudente()
{
    cout << "Inserisci matricola: ";
    cin >> matricola;
    dataNascita.leggi();
    cout << "Inserisci i voti (" << voti.size() << " esami, 0 per non sostenuto):" << endl;
    for (size_t i = 0; i < voti.size(); ++i)
    {
        cout << "Esame " << i + 1 << ": ";
        cin >> voti[i];
    }
}

void Studente::stampaStudente() const
{
    cout << "Matricola: " << matricola << endl;
    cout << "Data di nascita: ";
    dataNascita.stampa();
    cout << endl;
    cout << "Voti:" << endl;
    for (size_t i = 0; i < voti.size(); ++i)
    {
        if (voti[i] != 0)
        {
            cout << "Esame " << i + 1 << ": " << voti[i] << endl;
        }
    }
}

double Studente::getMedia() const
{
    double somma = 0;
    int count = 0;
    for (int voto : voti)
    {
        if (voto >= 18)
        {
            somma += voto;
            count++;
        }
    }
    return count > 0 ? somma / count : 0.0;
}

int Studente::getVotoMax() const
{
    int maxVoto = 0;
    for (int voto : voti)
    {
        if (voto > maxVoto)
        {
            maxVoto = voto;
        }
    }
    return maxVoto;
}

int Studente::getNumEsamiAllaLaurea() const
{
    int esamiPassati = 0;
    int numeroEsami = 23;
    for (int voto : voti)
    {
        if (voto >= 18)
        {
            esamiPassati++;
        }
    }
    return numeroEsami - esamiPassati;
}

bool Studente::studentePiuGiovaneDi(const Studente &S) const
{
    return dataNascita.piuGiovaneDi(S.dataNascita);
}

Studente &Studente::operator=(const Studente &altro)
{
    if (this != &altro)
    {
        matricola = altro.matricola;
        dataNascita = altro.dataNascita;
        voti = altro.voti;
    }
    return *this;
}