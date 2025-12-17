#include <cassert>
#include <vector>
#include <iostream>
#include <list>
#include <queue>
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
    
    // Verifica se l'arco (i,j) kzesiste
    bool operator()(unsigned i, unsigned j) const {
        assert(i >= 0 && i < this->n() && j >= 0 && j < this->n());
        return this->archi[i][j];
    }
};

// DFS (Depth-First Search) - Visita in profondità
// s: nodo di partenza (corrente)
// g: il grafo
// visitati: vettore per tracciare i nodi già visitati
// Logica:
// 1. Marca s come visitato.
// 2. Itera su tutti i possibili nodi j (da 0 a n-1).
// 3. Se esiste un arco da s a j (g(s,j) è true) e j non è stato visitato...
// 4. ...chiama ricorsivamente dfs su j.
void dfs(const unsigned& s, const Grafo& g, vector<bool>& visitati) {
    visitati[s] = true;
    for (unsigned j = 0; j < g.n(); ++j)
        if (s != j && g(s,j) && !visitati[j])
            dfs(j, g, visitati);
}

// Calcola la chiusura transitiva del grafo
// Restituisce un nuovo grafo dove c'è un arco (i, j) se esiste un cammino da i a j nel grafo originale.
// Logica:
// 1. Per ogni nodo i del grafo...
// 2. Esegui una DFS partendo da i per scoprire tutti i nodi raggiungibili.
// 3. Per ogni nodo j raggiungibile (dove visitati[j] è true)...
// 4. Aggiungi un arco diretto (i, j) nel nuovo grafo gc.
Grafo chiusuraTransitiva(const Grafo& g) {
    Grafo gc(g.n());
    vector<bool> visitati(g.n());
    
    for (unsigned i=0; i<g.n(); i++) {
        visitati.assign(visitati.size(), false); // Reset visitati per ogni nodo di partenza
        dfs(i, g, visitati); // Trova tutti i nodi raggiungibili da i
        for (unsigned j=0; j<g.n(); j++)
            if (i!=j && visitati[j])
                gc(i,j, true); // Crea arco diretto se j è raggiungibile da i
    }
    return gc;
}

// BFS (Breadth-First Search) - Visita in ampiezza
// Restituisce un vettore 'p' dove p[v] è il "padre" di v nell'albero di visita (utile per ricostruire i cammini minimi in termini di numero di archi)
vector<int> bfs(const Grafo& g, const unsigned& s) {
    vector<bool> visitati(g.n(), false);
    vector<int> p(g.n(), -1); // p[i] conterrà l'indice del nodo che ci ha portato a i
    queue<unsigned> q;
    
    // Inizializzazione
    q.push(s);
    p[s] = s; // Il padre della sorgente è se stesso (convenzione)
    visitati[s] = true;
    
    while (!q.empty()) {
        unsigned u = q.front();
        q.pop();
        
        // Esplora i vicini di u
        for (unsigned v = 0; v < g.n(); ++v)
            if (g(u,v) && u != v && !visitati[v]) {
                q.push(v);       // Accoda v per visitarlo dopo
                p[v] = u;        // Salva u come padre di v
                visitati[v] = true;
            }
    }
    return p;
}

// Cerca un cammino da 's' a 't' usando DFS
// s: nodo corrente
// t: nodo target
// cammino: lista che accumula il percorso trovato (se esiste)
// Ritorna true se il cammino è stato trovato
bool trovaCammino(const Grafo& g, const int& s, const int& t, 
                  vector<bool>& visitati, list<int>& cammino) {
    if (s == t) {
        visitati[t] = true;
        return true; // Trovato!
    }
    
    visitati[s] = true;
    bool trovato = false;
    
    for (unsigned j=0; j<g.n() && !trovato; j++)
        if (g(s,j) && !visitati[j]) { // Se c'è arco e non già vistato...
            cammino.push_back(j); // ...prova ad andare in j
            trovato = trovaCammino(g, j, t, visitati, cammino); // Ricorsione
            if (!trovato) cammino.pop_back(); // Backtracking: se j non porta a t, torna indietro
        }
    
    return trovato;
}

int main() {
    int n, u, v;
    cout << "Inserisci numero nodi: ";
    if (!(cin >> n)) return 0;
    
    Grafo g(n);
    
    cout << "Inserisci archi (u v) - termina con EOF o input non valido:" << endl;
    while (cin >> u >> v) { // Loop di lettura robusto
        if (u >= 0 && u < n && v >= 0 && v < n)
             g(u, v, true);
        else 
             cout << "Arco non valido ignorato: " << u << " " << v << endl;
    }
    cin.clear(); // Pulisce lo stato di errore per eventuali input successivi

    vector<bool> visitati(g.n(), false);
    list<int> cammino;
    int s=0, t=n>2 ? 2 : n-1; // Default s=0, t=2 (o ultimo nodo se < 3)
    
    cout << "\nRicerca cammino da " << s << " a " << t << "..." << endl;
    if (trovaCammino(g, s, t, visitati, cammino)) {
        cout << "Cammino trovato: " << s << " ";
        while (!cammino.empty()) {
            cout << cammino.front() << " ";
            cammino.pop_front();
        }
        cout << endl;
    }
    else {
        cout << "Cammino non trovato" << endl;
    }
    
    return 0;
}
