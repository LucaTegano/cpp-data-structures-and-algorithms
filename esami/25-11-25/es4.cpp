#include "../prof/Grafo.h"
#include <iostream>
#include <vector>

using namespace std;

// Funzione di backtracking semplificata al massimo
bool backtracking(const Grafo &G, const vector<bool> &fazioni, unsigned k,
                  unsigned start_idx, const vector<unsigned> &T_cities,
                  vector<unsigned> &selected) {
  // Se abbiamo selezionato esattamente k soldati, verifichiamo la copertura
  if (selected.size() == k) {
    for (unsigned i = 0; i < G.n(); ++i) {
      if (!fazioni[i]) { // città F
        bool coperto = false;
        for (unsigned s : selected) {
          if (G(s, i)) {
            coperto = true;
            break;
          }
        }
        if (!coperto) {
          return false; // Se anche una sola città F non è coperta, la soluzione
                        // non è valida
        }
      }
    }
    return true;
  }

  // Genera tutte le combinazioni di città T di dimensione k
  for (unsigned i = start_idx; i < T_cities.size(); ++i) {
    selected.push_back(T_cities[i]);
    if (backtracking(G, fazioni, k, i + 1, T_cities, selected)) {
      return true;
    }
    selected.pop_back(); // Backtrack
  }

  return false;
}

// Funzione principale per l'Esercizio 4
void trova_sistemazione(const Grafo &G, const vector<bool> &fazioni,
                        unsigned k) {
  vector<unsigned> T_cities;
  for (unsigned i = 0; i < G.n(); ++i) {
    if (fazioni[i]) {
      T_cities.push_back(i);
    }
  }

  vector<unsigned> selected;
  if (backtracking(G, fazioni, k, 0, T_cities, selected)) {
    for (unsigned i = 0; i < selected.size(); ++i) {
      cout << selected[i];
    }
    cout << endl;
  } else {
    cout << "IMPOSSIBILE" << endl;
  }
}

int main() {
  cout << "=== Avvio dei Test per l'Esercizio 4 (Medievale Semplificato) ==="
       << endl;

  // --- TEST 1: Grafo dell'esempio della traccia ---
  // n = 6 città
  // Fazione T (true): {0, 2, 4}
  // Fazione F (false): {1, 3, 5}
  Grafo g1(6);
  vector<bool> fazioni1 = {true,  false, true,
                           false, true,  false}; // 0:T, 1:F, 2:T, 3:F, 4:T, 5:F

  g1(1, 2, true);
  g1(2, 1, true);
  g1(1, 4, true);
  g1(4, 1, true);
  g1(3, 4, true);
  g1(4, 3, true);
  g1(5, 2, true);
  g1(2, 5, true);

  cout << "Test 1 (k=2): ";
  trova_sistemazione(g1, fazioni1, 2); // Atteso: 2 4

  cout << "Test 2 (k=1, impossibile): ";
  trova_sistemazione(g1, fazioni1, 1); // Atteso: IMPOSSIBILE

  return 0;
}
