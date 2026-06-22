#include "CodaEreditaria.h"

using namespace std;


int main() {
    CodaEreditaria c;

    Studente s1(1001, 15000, 29.5);
    Studente s2(1002, 12000, 27.0);
    Studente s3(1003, 18000, 25.0);
    Studente s4(1004, 14000, 30.0);
    Studente s5(1005, 16000, 28.0);
    Studente s6(1006, 11000, 26.5);
    Studente s7(1007, 20000, 24.0);
    Studente s8(1008, 17000, 29.0);
    Studente s9(1009, 13000, 27.5);
    Studente s10(1010, 19000, 22.0);

    c.aggiungi(s1);
    c.aggiungi(s2);
    c.aggiungi(s3);
    c.aggiungi(s4);
    c.aggiungi(s5);
    c.aggiungi(s6);
    c.aggiungi(s7);
    c.aggiungi(s8);
    c.aggiungi(s9);
    c.aggiungi(s10);

    cout << c;

    cout << "--------------------" << endl;
    cout << "Studente in testa: " << c.prossimo() << endl;
    c.rimuovi();
    cout << "Studente in testa (dopo rimozione del primo): " << c.prossimo() << endl;
    cout << "Dimensione coda prioritaria: " << c.size() << endl;

    return 0;
}