#include <iostream>
#include <vector>

using namespace std;

// Coordinate per le celle 9
struct Pos {
  int r, c;
};

// Conta bombe vicine (-1)
int countBombs(const vector<vector<int>> &pf, int r, int c, int n) {
  int cnt = 0;
  for (int i = r - 1; i <= r + 1; ++i) {
    for (int j = c - 1; j <= c + 1; ++j) {
      if (i >= 0 && i < n && j >= 0 && j < n) {
        if (pf[i][j] == -1)
          cnt++;
      }
    }
  }
  return cnt;
}

// Verifica validità finale
bool isValid(const vector<vector<int>> &pf,
             const vector<vector<int>> &original) {
  int n = pf.size();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      // Controlliamo solo le celle che NON sono bombe
      if (pf[i][j] != -1) {
        // Se la cella in origine era un numero fisso (0-8), deve matchare le
        // bombe vicine
        if (original[i][j] != 9) {
          if (countBombs(pf, i, j, n) != original[i][j])
            return false;
        }
        // Se era 9, assume semplicemente il valore delle bombe vicine (sempre
        // valido)
      }
    }
  }
  return true;
}

// Backtracking
bool solve(vector<vector<int>> &pf, const vector<vector<int>> &original,
           const vector<Pos> &unknowns, int idx, int k_missing) {

  // Base Case
  if (idx == unknowns.size()) {
    if (k_missing == 0)
      return isValid(pf, original);
    return false;
  }

  int r = unknowns[idx].r;
  int c = unknowns[idx].c;

  // Tentativo 1: Metto BOMBA (-1)
  if (k_missing > 0) {
    pf[r][c] = -1;
    if (solve(pf, original, unknowns, idx + 1, k_missing - 1))
      return true;
    pf[r][c] = 9; // Backtrack
  }

  // Tentativo 2: Metto NON-BOMBA (valore fittizio diverso da -1, es. -2)
  pf[r][c] = -2;
  if (solve(pf, original, unknowns, idx + 1, k_missing))
    return true;
  pf[r][c] = 9; // Backtrack

  return false;
}

// Funzione principale richiesta
bool minesweeper(vector<vector<int>> &pf, int k) {
  int n = pf.size();
  int bombs_present = 0;
  vector<Pos> unknowns;

  // Preprocessing
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (pf[i][j] == -1)
        bombs_present++;
      else if (pf[i][j] == 9)
        unknowns.push_back({i, j});
    }
  }

  if (bombs_present > k)
    return false;

  vector<vector<int>> original = pf;
  return solve(pf, original, unknowns, 0, k - bombs_present);
}

// Main di test minimale
int main() {
  // Esempio traccia
  vector<vector<int>> pf = {{-1, 1, 0}, {9, 2, 1}, {9, 9, 9}};
  int k = 2; // Test caso funzionante

  if (minesweeper(pf, k))
    cout << "True" << endl;
  else
    cout << "False" << endl;

  return 0;
}
