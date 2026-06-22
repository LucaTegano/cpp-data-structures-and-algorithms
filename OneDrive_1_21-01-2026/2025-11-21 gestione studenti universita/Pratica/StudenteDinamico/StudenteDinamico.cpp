/*
 * Created by Elena Mastria on 23/10/24.
 */
//

#include "StudenteDinamico.h"
#include <iostream>

using namespace std;

StudenteDinamico::StudenteDinamico(): matricola(0), dataDiNascita(), esamiSostenuti(0) {
    elencoEsami = new int[25];
    for (int i = 0; i < 25; ++i) {
        elencoEsami[i] = 0;
    }
}

StudenteDinamico::StudenteDinamico(const StudenteDinamico& oStudente): matricola(oStudente.matricola),
                                                                       dataDiNascita(oStudente.dataDiNascita),
                                                                       esamiSostenuti(oStudente.esamiSostenuti) {
    setElencoEsami(oStudente.getElencoEsami());
}

int StudenteDinamico::getMatricola() const {
    return matricola;
}

void StudenteDinamico::setMatricola(int matricola) {
    this->matricola = matricola;
}

const Data& StudenteDinamico::getDataDiNascita() const {
    return dataDiNascita;
}

void StudenteDinamico::setDataDiNascita(const Data& dataDiNascita) {
    this->dataDiNascita = dataDiNascita;
}

int StudenteDinamico::getEsamiSostenuti() const {
    return esamiSostenuti;
}

void StudenteDinamico::setEsamiSostenuti(int esamiSostenuti) {
    this->esamiSostenuti = esamiSostenuti;
}

const int* StudenteDinamico::getElencoEsami() const {
    return elencoEsami;
}


int StudenteDinamico::getEsame(int i) const {
    if (i > 0 && i < 25)
        return elencoEsami[i];
    cout << "ERRORE Esame inesistente" << endl;
    return -1;
}

void StudenteDinamico::setEsame(int i, int voto) {
    if (i > 0 && i < 25) {
        if (voto > 0 && voto < 30)
            elencoEsami[i] = voto;
        else cout << "ERRORE Esame Non Valido";
    } else
        cout << "ERRORE Esame inesistente" << endl;
}


void StudenteDinamico::setElencoEsami(const int* oElencoEsami) {
    if (elencoEsami != nullptr) {
        delete[] elencoEsami;
        elencoEsami = new int[25];
    }
    esamiSostenuti = 0;
    for (int i = 0; i < 25; ++i) {
        setEsame(i, oElencoEsami[i]);
        if (oElencoEsami[i] != 0)
            esamiSostenuti++;
    }

}





float StudenteDinamico::getMedia() const {
    float sommaVoti = 0;
    int n_esami = 0;
    for (int i = 0; i < 25; ++i)
        if (elencoEsami[i] != 0) {
            sommaVoti += elencoEsami[i];
            n_esami++;
        }

    if (n_esami != 0)
        return sommaVoti / n_esami;
    return 0;
}

int StudenteDinamico::getVotoMax() const {
    int max = 0;
    for (int i = 0; i < 25; ++i) {
        if (elencoEsami[i] > max)
            max = elencoEsami[i];
    }
    return max;
}

int StudenteDinamico::getNumEsamiAllaLaurea() const {
    int esamiSuperati = 0;
    for (int i = 0; i < 25; ++i) {
        if (elencoEsami[i] >= 18) {
            esamiSuperati++;
        }
    }
    return 25 - esamiSuperati;
}

bool StudenteDinamico::studentePiuGiovane(const StudenteDinamico& studente) const {

    return dataDiNascita<studente.dataDiNascita;
}

StudenteDinamico& StudenteDinamico::operator=(const StudenteDinamico& oStudente) {
    if (this == &oStudente)
        return *this;
    this->matricola = oStudente.matricola;
    this->dataDiNascita = oStudente.dataDiNascita;
    this->esamiSostenuti = oStudente.esamiSostenuti;
    setElencoEsami(oStudente.getElencoEsami());
    return *this;
}

bool StudenteDinamico::aggiungiEsame(int voto) {
    bool added = false;
    if (voto > 0 && voto <= 30)
        for (int i = 0; i < 25; ++i) {
            if (elencoEsami[i] == 0) {
                elencoEsami[i] = voto;
                added = true;
                esamiSostenuti++;
                break;
            }

        }
    return added;
}

StudenteDinamico::~StudenteDinamico() {
    delete[] elencoEsami;
}




ostream& operator<<(ostream& out, const StudenteDinamico& s) {
    out<<"Matricola: "<<s.matricola<<endl;
    out << "data di nascita:" << s.dataDiNascita<<endl;
    out << "numero esami sostenuti" << s.esamiSostenuti << endl;
    out << "con votazione" << endl;
    int esami = 0;
    for (int i = 0; i < 25; ++i) {
        if (s.elencoEsami[i] > 0) {
            esami++;
            out << esami << s.elencoEsami[i] << endl;
        }
    }
    out<<"media"<<s.getMedia();
    return out;
}

istream& operator>>(istream& in, StudenteDinamico& s) {

    cout << "inserisci la matricola" << endl;
    in >> s.matricola;
    cout << "inserisci la data di nascita" << endl;
    in>>s.dataDiNascita;
    cout << "inserisci il numero di esami sostenuti" << endl;
    in >> s.esamiSostenuti;
    for (int i = 0; i < s.esamiSostenuti; ++i) {
        cout << "inserisci il voto dell'esame " << i + 1 << endl;
        in >> s.elencoEsami[i];
    }
    cout << "ho letto il seguente studente" << endl;
    cout<<s;
    return in;
}
