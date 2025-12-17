#include <cassert>
#include <vector>
#include <iostream>
#include <list>

using namespace std;
using boolVec = vector<bool>;

class Grafo {
protected:
    unsigned vn = 0, vm = 0; // vn: Numero di nodi (Vertex Number), vm: Numero di archi (Vertex Matches/Edges)
    vector<boolVec> archi; // Matrice di adiacenza: archi[i][j] è true se esiste un arco da i a j
    
    // Inizializza il grafo con n nodi
    // Ridimensiona la matrice di adiacenza per essere n x n
    // Inizialmente non ci sono archi (tutti false)
    void init(unsigned n) {
        this->vn = n;
        this->vm = 0;
        this->archi = vector<boolVec>(n);
        for (unsigned i = 0; i < n; i++)
            this->archi[i] = boolVec(n, false);
    }

public:
    Grafo(unsigned n) {
        assert(n >= 1);
        this->init(n);
    }
    
    // Inserisce o elimina l'arco (i,j)
    void operator()(unsigned i, unsigned j, bool b) {
        assert(i >= 0 && i < this->n() && j >= 0 && j < this->n());
        bool esisteArco = this->archi[i][j];
        if ((!esisteArco && b) || (esisteArco && !b)) {
            this->archi[i][j] = b;
            if (b) vm++;
            else vm--;
        }
    }
    
    void svuota() {
        for (unsigned i = 0; i < this->n(); i++)
            for (unsigned j = 0; j < this->n(); j++)
                archi[i][j] = false;
        vm = 0;
    }
    
    unsigned n() const { return vn; }
    unsigned m() const { return vm; }
    
    // Verifica se l'arco (i,j) esiste
    bool operator()(unsigned i, unsigned j) const {
        assert(i >= 0 && i < this->n() && j >= 0 && j < this->n());
        return this->archi[i][j];
    }
};

// Backtracking per trovare una cricca di dimensione k
// startNode: nodo da cui iniziare a cercare per evitare duplicati e loop
// k: dimensione target
// cricca: nodi correntemente nella cricca
bool trovaCricca(const Grafo& g, unsigned startNode, int k, vector<int>& cricca) {
    // Caso base: se la cricca ha raggiunto dimensione k, abbiamo finito
    if (cricca.size() == k) {
        return true;
    }

    // Prova ad aggiungere nodi da startNode in poi
    for (unsigned i = startNode; i < g.n(); i++) {
        // Verifica se 'i' può essere aggiunto alla cricca corrente.
        // Deve essere collegato a tutti i nodi già presenti.
        bool connessoATutti = true;
        for (int v : cricca) {
            // Controllo entrambe le direzioni per sicurezza su grafo non orientato,
            // (anche se basterebbe una se la matrice fosse simmetrica).
            if (!g(i, v) && !g(v, i)) { 
                connessoATutti = false;
                break;
            }
        }

        if (connessoATutti) {
            // Aggiungi i alla cricca
            cricca.push_back(i);

            // Ricorsione: cerca il prossimo nodo partendo da i+1
            if (trovaCricca(g, i + 1, k, cricca)) {
                return true;
            }

            // Backtracking: rimuovi i e continua a cercare altri nodi
            cricca.pop_back();
        }
    }

    return false;
}

int main() {
    int n, u, v;
    cout << "Inserisci numero nodi: ";
    if (!(cin >> n)) return 0;
    
    Grafo g(n);
    
    cout << "Inserisci archi (u v) - termina con EOF o input non valido:" << endl;
    // Input loop: legge coppie di nodi fino a input non valido (o EOF)
    while (cin >> u >> v) {
        if (u >= 0 && u < n && v >= 0 && v < n) {
             g(u, v, true);
             g(v, u, true); // Per grafo non orientato, aggiungiamo entrambi
        }
        else 
             cout << "Arco non valido ignorato: " << u << " " << v << endl;
    }
    cin.clear(); // Resetta lo stato dello stream per leggere K
    // Ignora il resto della linea o il token che ha causato l'errore (es. 'q' o 'end')
    while (cin.peek() != EOF && !isdigit(cin.peek())) cin.ignore();
    
    int k;
    cout << "Inserisci dimensione K della cricca da trovare: ";
    if (!(cin >> k)) {
        cout << "Input non valido per K" << endl;
        return 0;
    }

    vector<int> cricca;
    cricca.reserve(k);

    cout << "Ricerca cricca di dimensione " << k << "..." << endl;
    
    if (trovaCricca(g, 0, k, cricca)) {
        cout << "Cricca trovata: ";
        for (int nodo : cricca) {
            cout << nodo << " ";
        }
        cout << endl;
    } else {
        cout << "Nessuna cricca di dimensione " << k << " trovata." << endl;
    }
    
    return 0;
}
