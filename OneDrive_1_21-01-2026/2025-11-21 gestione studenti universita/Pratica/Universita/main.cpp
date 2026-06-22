#include <iostream>
#include "Universita.h"
#include "StudenteDinamico.h"

using namespace std;

int main() {
    // Capacity iniziale impostata a 5 dal costruttore
    Universita uni("Tech University");
    
    cout << "Stato Iniziale -> Studenti: " << uni.getNumeroStudenti() 
         << ", Capacity: " << uni.getCapacity() << endl;

    // Aggiungiamo 6 studenti per forzare il raddoppio (da 5 a 10)
    for(int i = 0; i < 6; i++) {
        StudenteDinamico s;
        s.setMatricola(100 + i);
        uni.aggiungiStudente(s);
        
        cout << "Aggiunto studente " << 100+i 
             << " | Size: " << uni.getNumeroStudenti() 
             << " | Capacity: " << uni.getCapacity() << endl;
    }

    // Rimuoviamo uno studente (la capacity NON deve diminuire)
    cout << "\nRimozione studente matricola 100..." << endl;
    uni.rimuoviStudente(100);
    
    cout << "Stato dopo rimozione -> Size: " << uni.getNumeroStudenti() 
         << " | Capacity: " << uni.getCapacity() << endl;

    return 0;
}