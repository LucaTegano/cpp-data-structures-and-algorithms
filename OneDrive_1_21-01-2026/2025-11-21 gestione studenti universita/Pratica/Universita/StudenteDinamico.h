/*
 * Created by Elena Mastria on 23/10/24.
 */
//

#ifndef UNTITLED_STUDENTEDINAMICO_H
#define UNTITLED_STUDENTEDINAMICO_H


#include "Data.h"
#include <iostream>
using namespace std;
class StudenteDinamico {
    private:
        int matricola;
        Data dataDiNascita;
        int esamiSostenuti;
        int* elencoEsami;
    public:
        StudenteDinamico();

        StudenteDinamico(const StudenteDinamico& oStudente);

        ~StudenteDinamico();

        int getMatricola() const;

        void setMatricola(int matricola);

        const Data& getDataDiNascita() const;

        void setDataDiNascita(const Data& dataDiNascita);

        int getEsamiSostenuti() const;

        void setEsamiSostenuti(int esamiSostenuti);

        int getEsame(int i) const;

        void setEsame(int i, int voto);

        const int* getElencoEsami() const;

        void setElencoEsami(const int* oElencoEsami);

        float getMedia() const;

        int getVotoMax() const;

        int getNumEsamiAllaLaurea() const;

        bool studentePiuGiovane(const StudenteDinamico& studente) const;

        StudenteDinamico& operator=(const StudenteDinamico& oStudente);

        bool aggiungiEsame(int voto);
        friend ostream& operator<< (ostream& out, const StudenteDinamico& s);
        friend istream & operator>> (istream & in, StudenteDinamico& s);


};


#endif //UNTITLED_STUDENTEDINAMICO_H
