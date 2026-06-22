// 4
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Struttura per rappresentare una cella della scacchiera
struct Cell {
  int x, y;
  vector<pair<int, int>> path; // Memorizza il percorso fatto per arrivare qui

  bool operator==(const Cell &other) const {
    return x == other.x && y == other.y;
  }
};

const int BOARD_SIZE = 8;

// Possibili mosse a "L" del cavallo
int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

// Funzione per verificare se una mossa è valida (dentro i bordi e non proibita)
bool isValid(int x, int y, const bool visited[BOARD_SIZE][BOARD_SIZE]) {
  return (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE &&
          !visited[x][y]);
}

void solveKnightPath(pair<int, int> start, pair<int, int> target,
                     const vector<pair<int, int>> &prohibitedVec) {
  // Matrice per tenere traccia dei nodi visitati
  bool visited[BOARD_SIZE][BOARD_SIZE] = {false};

  // Segniamo le celle proibite come già visitate
  for (const auto &p : prohibitedVec) {
    visited[p.first][p.second] = true;
  }

  // Coda per la BFS
  queue<Cell> q;

  // Controllo se partenza o destinazione sono proibite
  if (visited[start.first][start.second] ||
      visited[target.first][target.second]) {
    cout << "IMPOSSIBILE" << endl;
    return;
  }

  // EARLY EXIT: Controllo se siamo già a destinazione in partenza
  if (start == target) {
    cout << "(" << start.first << "," << start.second << ")" << endl;
    return;
  }

  // Inizializzazione BFS
  q.push({start.first, start.second, {start}});
  visited[start.first][start.second] = true;

  while (!q.empty()) {
    Cell current = q.front();
    q.pop();

    // Esplora tutte le 8 mosse possibili
    for (int i = 0; i < 8; ++i) {
      int nx = current.x + dx[i];
      int ny = current.y + dy[i];

      if (isValid(nx, ny, visited)) {
        vector<pair<int, int>> newPath = current.path;
        newPath.push_back({nx, ny});

        // EARLY EXIT: Controllo immediato se la nuova cella è il target
        if (nx == target.first && ny == target.second) {
          for (size_t j = 0; j < newPath.size(); ++j) {
            cout << "(" << newPath[j].first << "," << newPath[j].second << ")"
                 << (j == newPath.size() - 1 ? "" : " -> ");
          }
          cout << endl;
          return;
        }

        visited[nx][ny] = true;
        q.push({nx, ny, newPath});
      }
    }
  }

  cout << "IMPOSSIBILE" << endl;
}

int main() {
  pair<int, int> start = {4, 3};
  pair<int, int> target = {2, 2};
  vector<pair<int, int>> prohibited = {{3, 3}, {4, 4}};

  cout << "Ricerca cammino da (4,3) a (2,2):" << endl;
  solveKnightPath(start, target, prohibited);

  return 0;
}