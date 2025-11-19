/*
Su una scacchiera 8x8, il cavallo è un pezzo che si muove ad “L”, spostandosi sempre di una cella in orizzontale e di 2 in verticale o viceversa, in qualsiasi direzione. I movimenti del cavallo possono
essere codificati dalle seguenti coppie di interi: (-2,-1), (-2,+1), (-1,-2), (-1,+2),
(+1,-2), (+1,+2), (+2, -1), (+2,+1)
Ad esempio, se siamo nella cella di riga 4 e colonna 3, seguendo il primo movimento della lista
finiremo sulla cella (2,2), mentre seguendo il secondo movimento arriveremo in (2,4) e così
via.
Scrivere un programma che prenda in input:
1. la posizione iniziale di un cavallo su scacchiera 8x8 (pair<unsigned,unsigned>)
2. un insieme di caselle proibite (vector<pair<unsigned,unsigned> >)
3. una casella di destinazione (pair<unsigned,unsigned>)
Il programma deve determinare se è possibile far arrivare il cavallo dalla sua posizione iniziale alla
destinazione, considerando che esso non può fermarsi sulle caselle proibite (ma può attraversarle
all’interno di una singola mossa). Naturalmente, non è ammesso che il cavallo si muova al di fuori
della scacchiera. Inoltre, non è possibile che il percorso del cavallo preveda di passare sulla stessa
casella più di una volta. Se esiste una soluzione dovrà stampare in output l’insieme delle caselle da
attraversare per arrivare a destinazione, altrimenti dovrà stampare “IMPOSSIBILE”.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

// Definizione per comodità
using Coordinate = pair<unsigned, unsigned>;

// Funzione per verificare se una coordinata è all'interno della scacchiera 8x8
bool isInside(int r, int c)
{
    return (r >= 0 && r < 8 && c >= 0 && c < 8);
}

// Funzione principale per risolvere il problema
void trovaPercorsoCavallo(Coordinate start, vector<Coordinate> forbidden, Coordinate target)
{

    // Matrici per tenere traccia dei visitati e delle celle proibite
    bool visited[8][8] = {false};
    bool isForbidden[8][8] = {false};

    // Matrice per ricostruire il percorso: parent[r][c] contiene la cella da cui siamo arrivati
    Coordinate parent[8][8];

    // Segniamo le celle proibite sulla griglia
    for (const auto &p : forbidden)
    {
        if (isInside(p.first, p.second))
        {
            isForbidden[p.first][p.second] = true;
        }
    }

    // Se la destinazione o la partenza sono proibite, è impossibile (a meno che start non sia l'eccezione, ma di solito non può starci)
    if (isForbidden[target.first][target.second] || isForbidden[start.first][start.second])
    {
        cout << "IMPOSSIBILE" << endl;
        return;
    }

    // Possibili movimenti del cavallo (delta riga, delta colonna)
    int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};

    // Coda per la BFS
    queue<Coordinate> q;

    // Inizializzazione
    q.push(start);
    visited[start.first][start.second] = true;

    bool found = false;

    while (!q.empty())
    {
        Coordinate curr = q.front();
        q.pop();

        // Se siamo arrivati a destinazione
        if (curr.first == target.first && curr.second == target.second)
        {
            found = true;
            break;
        }

        // Proviamo tutti e 8 i movimenti
        for (int i = 0; i < 8; i++)
        {
            // Usiamo int per gestire potenziali indici negativi prima del controllo
            int next_r = static_cast<int>(curr.first) + dr[i];
            int next_c = static_cast<int>(curr.second) + dc[i];

            // Controlliamo se la nuova posizione è valida
            if (isInside(next_r, next_c))
            {
                // Se non è proibita e non è stata ancora visitata
                if (!isForbidden[next_r][next_c] && !visited[next_r][next_c])
                {
                    visited[next_r][next_c] = true;
                    parent[next_r][next_c] = {curr.first, curr.second}; // Salviamo da dove veniamo
                    q.push({(unsigned)next_r, (unsigned)next_c});
                }
            }
        }
    }

    if (found)
    {
        // Ricostruzione del percorso andando a ritroso dal target allo start
        vector<Coordinate> path;
        Coordinate curr = target;
        path.push_back(curr);

        while (curr != start)
        {
            curr = parent[curr.first][curr.second];
            path.push_back(curr);
        }

        // Il percorso è stato ricostruito al contrario, quindi lo invertiamo
        reverse(path.begin(), path.end());

        // Stampa del risultato
        cout << "Percorso trovato:" << endl;
        for (size_t i = 0; i < path.size(); i++)
        {
            cout << "(" << path[i].first << ", " << path[i].second << ")";
            if (i < path.size() - 1)
                cout << " -> ";
        }
        cout << endl;
    }
    else
    {
        cout << "IMPOSSIBILE" << endl;
    }
}

int main()
{
    // Esempio di utilizzo (Input Hardcoded per dimostrazione)

    // 1. Posizione iniziale (Riga 0, Colonna 0)
    Coordinate start = {0, 0};

    // 2. Insieme di caselle proibite
    // Mettiamo degli ostacoli che bloccano i primi salti ovvi
    vector<Coordinate> forbidden;
    forbidden.push_back({1, 2});
    forbidden.push_back({2, 1});

    // 3. Casella di destinazione (Riga 4, Colonna 4)
    Coordinate dest = {4, 4};

    cout << "Start: (" << start.first << "," << start.second << ")" << endl;
    cout << "Dest:  (" << dest.first << "," << dest.second << ")" << endl;
    cout << "Ostacoli: ";
    for (auto p : forbidden)
        cout << "(" << p.first << "," << p.second << ") ";
    cout << endl
         << "----------------" << endl;

    trovaPercorsoCavallo(start, forbidden, dest);

    // Test 2: Caso impossibile
    cout << endl
         << "--- Test Caso Impossibile ---" << endl;
    Coordinate dest_imp = {1, 2}; // Questa è una casella proibita
    trovaPercorsoCavallo(start, forbidden, dest_imp);

    return 0;
}