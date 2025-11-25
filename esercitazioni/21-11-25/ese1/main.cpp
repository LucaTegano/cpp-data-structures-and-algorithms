#include <iostream>
#include <vector>
#include <map>
#include "studente.h"

using namespace std;

int main() {
    int N;
    cout << "Inserisci il numero di studenti: ";
    cin >> N;

    if (N <= 0) {
        cout << "Numero di studenti non valido." << endl;
        return 1;
    }

    // Allocazione array di N studenti
    // Usiamo un array dinamico di puntatori o un array dinamico di oggetti?
    // "letto in input un array di N studenti" -> array di oggetti.
    StudenteDinamico* studenti = new StudenteDinamico[N];

    // Input studenti
    for (int i = 0; i < N; ++i) {
        cout << "\n--- Studente " << i + 1 << " ---" << endl;
        cin >> studenti[i];
    }

    // 1. Media generale degli studenti
    double sommaMedie = 0;
    for (int i = 0; i < N; ++i) {
        sommaMedie += studenti[i].getMedia();
    }
    double mediaGenerale = sommaMedie / N;
    cout << "\nMedia generale degli studenti: " << mediaGenerale << endl;

    // 2. Lo studente più brillante (media migliore)
    int indiceMigliore = 0;
    double maxMedia = -1;
    for (int i = 0; i < N; ++i) {
        double media = studenti[i].getMedia();
        if (media > maxMedia) {
            maxMedia = media;
            indiceMigliore = i;
        }
    }
    cout << "Studente più brillante: " << studenti[indiceMigliore].getMatricola() 
              << " con media " << maxMedia << endl;

    // 3. Il voto più alto più frequente
    map<int, int> frequenzaVotoMax;
    for (int i = 0; i < N; ++i) {
        int votoMax = studenti[i].getVotoMax();
        frequenzaVotoMax[votoMax]++;
    }

    int votoPiuFrequente = -1;
    int maxFrequenza = -1;
    for (auto const& [voto, frequenza] : frequenzaVotoMax) {
        if (frequenza > maxFrequenza) {
            maxFrequenza = frequenza;
            votoPiuFrequente = voto;
        }
    }
    cout << "Voto più alto più frequente: " << votoPiuFrequente 
              << " (frequenza: " << maxFrequenza << ")" << endl;

    // 4. Il mese in cui sono nati meno studenti
    map<int, int> frequenzaMesi;
    // Inizializza tutti i mesi a 0
    for (int m = 1; m <= 12; ++m) {
        frequenzaMesi[m] = 0;
    }

    for (int i = 0; i < N; ++i) {
        int mese = studenti[i].getNascita().getMese();
        if (mese >= 1 && mese <= 12) {
            frequenzaMesi[mese]++;
        }
    }

    int meseMenoStudenti = 1;
    int minFrequenza = N + 1; // Valore più alto possibile iniziale
    
    for (int m = 1; m <= 12; ++m) {
        if (frequenzaMesi[m] < minFrequenza) {
            minFrequenza = frequenzaMesi[m];
            meseMenoStudenti = m;
        }
    }
    
    // Potrebbero esserci più mesi con lo stesso minimo, ne stampiamo uno o tutti?
    // Il testo dice "Il mese", singolare. Stampiamo il primo trovato (o logica a scelta).
    cout << "Mese con meno nati: " << meseMenoStudenti 
              << " (nati: " << minFrequenza << ")" << endl;


    // Pulizia memoria
    delete[] studenti;

    return 0;
}
