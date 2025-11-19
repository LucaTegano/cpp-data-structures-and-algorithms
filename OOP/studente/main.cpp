#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include "studente.h"

using namespace std;

int main() {
    int n;
    cout << "Quanti studenti vuoi inserire? ";
    cin >> n;

    vector<Studente> studenti(n);
    for (int i = 0; i < n; ++i) {
        cout << "\n--- Inserimento Studente " << i + 1 << " ---" << endl;
        studenti[i].leggiStudente();
    }

    // Stampa esami mancanti per ogni studente
    cout << "\n--- Esami Mancanti ---" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Studente " << studenti[i].getMatricola() << ": " << studenti[i].getNumEsamiAllaLaurea() << " esami mancanti" << endl;
    }

    // Media generale
    double mediaGenerale = 0;
    int studentiConVoti = 0;
    for (const auto& s : studenti) {
        if (s.getMedia() > 0) {
            mediaGenerale += s.getMedia();
            studentiConVoti++;
        }
    }
    if (studentiConVoti > 0) {
        mediaGenerale /= studentiConVoti;
    }
    cout << "\n--- Risultati ---" << endl;
    cout << "Media generale degli studenti: " << mediaGenerale << endl;

    // Studente più brillante
    if (n > 0) {
        int brillanteIndex = -1;
        double maxMedia = -1.0;
        for (int i = 0; i < n; ++i) {
            if (studenti[i].getMedia() > maxMedia) {
                maxMedia = studenti[i].getMedia();
                brillanteIndex = i;
            }
        }
        if(brillanteIndex != -1){
            cout << "Studente piu' brillante (matricola): " << studenti[brillanteIndex].getMatricola() << endl;
        } else {
            cout << "Nessuno studente con esami superati." << endl;
        }
    }

    // Voto più alto più frequente
    map<int, int> frequenzaVotiAlti;
    for (const auto& s : studenti) {
        int votoMax = s.getVotoMax();
        if (votoMax > 0) {
            frequenzaVotiAlti[votoMax]++;
        }
    }

    if (!frequenzaVotiAlti.empty()) {
        int votoPiuFrequente = 0;
        int maxFreq = 0;
        for (const auto& pair : frequenzaVotiAlti) {
            if (pair.second > maxFreq) {
                maxFreq = pair.second;
                votoPiuFrequente = pair.first;
            }
        }
        cout << "Voto piu' alto piu' frequente: " << votoPiuFrequente << endl;
    } else {
        cout << "Nessun voto massimo trovato." << endl;
    }


    // Mese con meno nati
    if (n > 0) {
        map<unsigned, int> nascitePerMese;
        for (int i = 1; i <= 12; ++i) {
            nascitePerMese[i] = 0;
        }
        for (const auto& s : studenti) {
            nascitePerMese[s.getDataNascita().getMese()]++;
        }

        unsigned meseMenoNati = 0;
        int minNati = n + 1;
        for (const auto& pair : nascitePerMese) {
            if (pair.second < minNati) {
                minNati = pair.second;
                meseMenoNati = pair.first;
            }
        }
        cout << "Mese con meno studenti nati: " << meseMenoNati << endl;
    }

    return 0;
}