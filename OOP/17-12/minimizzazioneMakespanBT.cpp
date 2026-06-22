#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <queue>

using namespace std;

/**
 * Problema della Minimizzazione del Makespan
 * Risoluzione tramite Backtracking con potatura.
 */

int bestMakespan = numeric_limits<int>::max();

/**
 * Calcola un limite superiore iniziale usando l'algoritmo greedy LPT
 * (Longest Processing Time). Questo aiuta a potare i rami della ricorsione
 * più velocemente.
 */
int calcolaGreedyLPT(vector<int> jobs, int m) {
    if (jobs.empty()) return 0;
    sort(jobs.begin(), jobs.end(), greater<int>());
    priority_queue<int, vector<int>, greater<int>> carichi;
    for (int i = 0; i < m; ++i) carichi.push(0);
    for (int job : jobs) {
        int minCarico = carichi.top();
        carichi.pop();
        carichi.push(minCarico + job);
    }
    int makespan = 0;
    while (!carichi.empty()) {
        makespan = carichi.top();
        carichi.pop();
    }
    return makespan;
}

/**
 * Funzione ricorsiva di backtracking.
 * @param jobs Vettore delle durate dei job (ordinato decrescente)
 * @param carichi Vettore che contiene il carico attuale di ogni macchina
 * @param jobIdx Indice del job corrente da assegnare
 * @param currentMax Carico massimo attuale tra tutte le macchine
 */
void backtrace(const vector<int>& jobs, vector<int>& carichi, int jobIdx, int currentMax) {
    // Caso base: tutti i job sono stati assegnati
    if (jobIdx == jobs.size()) {
        if (currentMax < bestMakespan) {
            bestMakespan = currentMax;
        }
        return;
    }

    // Potatura Bound: se il carico massimo attuale è già >= al migliore trovato, non continuare
    if (currentMax >= bestMakespan) return;

    // Tentativo di assegnamento del job corrente a ciascuna macchina
    // Ottimizzazione: Usiamo 'seenLoad' per evitare assegnamenti simmetrici (macchine con stesso carico)
    vector<int> seenLoads;

    for (int i = 0; i < carichi.size(); ++i) {
        // Simmetria: se abbiamo già provato ad assegnare questo job a una macchina con questo carico, saltiamo
        bool giaProvato = false;
        for (int load : seenLoads) {
            if (load == carichi[i]) {
                giaProvato = true;
                break;
            }
        }
        if (giaProvato) continue;
        seenLoads.push_back(carichi[i]);

        // Assegna il job alla macchina i
        carichi[i] += jobs[jobIdx];
        int newMax = max(currentMax, carichi[i]);
        
        // Ricorsione
        backtrace(jobs, carichi, jobIdx + 1, newMax);
        
        // Backtrack
        carichi[i] -= jobs[jobIdx];

        // Se abbiamo trovato un makespan uguale al limite inferiore teorico, possiamo fermarci (opzionale)
        // int lowerBound = ... 
    }
}

int main() {
    int m;
    vector<int> jobs;
    
    cout << "jobs (separati da virgola, es: 1,5,6,4,2): ";
    string line;
    getline(cin, line);
    
    stringstream ss(line);
    string val;
    while (getline(ss, val, ',')) {
        try {
            jobs.push_back(stoi(val));
        } catch (...) {
            // Ignora valori non validi o spazi
        }
    }
    
    cout << "numero macchine (m): ";
    cin >> m;

    if (jobs.empty() || m <= 0) {
        cout << "Dati non validi." << endl;
        return 0;
    }

    // Ordinamento LPT (Longest Processing Time) - Fondamentale per il backtracking
    sort(jobs.begin(), jobs.end(), greater<int>());

    // Inizializza il bestMakespan con l'euristica greedy
    bestMakespan = calcolaGreedyLPT(jobs, m);
    
    vector<int> carichi(m, 0);
    backtrace(jobs, carichi, 0, 0);

    cout << "Makespan minimo (Backtracking): " << bestMakespan << endl;
    
    return 0;
}
