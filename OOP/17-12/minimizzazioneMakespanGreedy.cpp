#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;

// Algoritmo greedy LPT (Longest Processing Time first)
// 1. Ordina i job in ordine decrescente di durata
// 2. Assegna ogni job alla macchina con il carico minore
int MinMakespan(vector<int> jobs, int m) {
    // Ordina i job in ordine decrescente (i più lunghi prima)
    sort(jobs.begin(), jobs.end(), greater<int>());
    
    // Min-heap per tenere traccia del carico di ogni macchina
    // La macchina con il minor carico sarà sempre in cima
    priority_queue<int, vector<int>, greater<int>> carichi;
    
    // Inizializza tutte le macchine con carico 0
    for (int i = 0; i < m; ++i) {
        carichi.push(0);
    }
    
    // Assegna ogni job alla macchina con il carico minore
    for (int i = 0; i < jobs.size(); ++i) {
        // Prendi la macchina con il carico minimo
        int minCarico = carichi.top();
        carichi.pop();
        
        // Assegna il job corrente a questa macchina
        // Il nuovo carico sarà il vecchio carico + durata del job
        carichi.push(minCarico + jobs[i]);
    }
    
    // Il makespan è il massimo tra tutti i carichi
    // Estrai tutti i carichi per trovare il massimo
    int makespan = 0;
    while (!carichi.empty()) {
        makespan = carichi.top();  // L'ultimo estratto sarà il più grande
        carichi.pop();
    }
    
    return makespan;
}

int main() {
    int m;
    vector<int> jobs;
    
    // Leggi i job separati da virgola (es: 62,14,75,72,83)
    cout << "jobs: ";
    string line;
    getline(cin, line);
    
    // Parsing dei job separati da virgola
    stringstream ss(line);
    int job;
    while (ss >> job) {
        jobs.push_back(job);
        if (ss.peek() == ',') ss.ignore();
    }
    
    // Leggi il numero di macchine
    cout << "macchine: ";
    cin >> m;
    
    // Calcola e stampa il makespan minimo
    int risultato = MinMakespan(jobs, m);
    cout << "Makespan minimo (greedy LPT): " << risultato << endl;
    
    return 0;
}