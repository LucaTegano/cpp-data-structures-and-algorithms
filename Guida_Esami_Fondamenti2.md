# Guida Completa alla Risoluzione delle Tracce d'Esame di Fondamenti 2

Questa guida contiene l'analisi approfondita e l'implementazione in C++ di tutti gli **Esercizi 3** (Strutture dati non lineari: Alberi e Grafi) e **Esercizi 4** (Algoritmi combinatori e Backtracking) tratti da **12 appelli d'esame** (dal 2022 al 2026).

---

## 1. Definizione Classi di Supporto (Mock API)

Per rendere i codici d'esame auto-consistenti e comprensibili, definiamo le interfacce delle classi di supporto utilizzate nei vari appelli.

### A. Rappresentazione dei Grafi

```cpp
#include <vector>

// Usato negli esami con grafi semplici non pesati (es. 2026-01-22, 2025-11-25, 2025-06-13, 2023-09-14)
class Grafo {
private:
    unsigned num_nodi;
    std::vector<std::vector<bool>> adj;
public:
    Grafo(unsigned n) : num_nodi(n), adj(n, std::vector<bool>(n, false)) {}
    unsigned n() const { return num_nodi; }
    unsigned m() const {
        unsigned count = 0;
        for (unsigned i = 0; i < num_nodi; ++i)
            for (unsigned j = 0; j < num_nodi; ++j)
                if (adj[i][j]) count++;
        return count;
    }
    bool operator()(unsigned i, unsigned j) const { return adj[i][j]; }
    void aggiungiArco(unsigned i, unsigned j) { adj[i][j] = true; }
};

// Usato negli esami con grafi pesati (es. 2022-09-09)
class GrafoPesato {
private:
    unsigned num_nodi;
    std::vector<std::vector<float>> adj;
    std::vector<float> depositi;
public:
    GrafoPesato(unsigned n) : num_nodi(n), adj(n, std::vector<float>(n, 0.0f)), depositi(n, 0.0f) {}
    unsigned n() const { return num_nodi; }
    unsigned m() const {
        unsigned count = 0;
        for (unsigned i = 0; i < num_nodi; ++i)
            for (unsigned j = 0; j < num_nodi; ++j)
                if (adj[i][j] > 0) count++;
        return count;
    }
    float operator()(unsigned i, unsigned j) const { return adj[i][j]; }
    float dep(unsigned i) const { return depositi[i]; }
    void setDep(unsigned i, float val) { depositi[i] = val; }
    void aggiungiArco(unsigned i, unsigned j, float w) { adj[i][j] = w; }
};
```

### B. Rappresentazione degli Alberi Binari

```cpp
#include <memory>

const int SIN = 0;
const int DES = 1;

template <typename T>
class NodeB {
public:
    T info;
    std::shared_ptr<NodeB<T>> left;
    std::shared_ptr<NodeB<T>> right;
    NodeB(T val) : info(val), left(nullptr), right(nullptr) {}
};

template <typename T>
class AlberoB {
private:
    std::shared_ptr<NodeB<T>> rad;
public:
    AlberoB() : rad(nullptr) {}
    AlberoB(std::shared_ptr<NodeB<T>> r) : rad(r) {}
    
    T radice() const { return rad->info; }
    AlberoB<T> figlio(int dir) const {
        if (rad == nullptr) return AlberoB<T>();
        return AlberoB<T>(dir == SIN ? rad->left : rad->right);
    }
    bool nullo() const { return rad == nullptr; }
    bool foglia() const {
        if (rad == nullptr) return false;
        return rad->left == nullptr && rad->right == nullptr;
    }
    void modRadice(const T& a) {
        if (rad != nullptr) rad->info = a;
    }
};
```

---

## 2. Analisi e Codici Risolutivi per ciascun Appello

### Appello 1: 17 Febbraio 2026

*   **Esercizio 3 (Somma per Livelli Crescente):**
    *   *LeetCode mapping:* Variante di [102. Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/) (Medium).
    *   *Logica:* Si calcola la somma dei nodi di ciascun livello dell'albero tramite una BFS ed una struttura ad accumulo. Successivamente si verifica se il vettore delle somme è strettamente crescente.
    ```cpp
    #include <vector>
    #include <queue>

    bool esercizio3_2026_02_17(const AlberoB<int>& tree) {
        if (tree.nullo()) return true;

        std::vector<int> somme_livelli;
        std::queue<std::pair<AlberoB<int>, int>> q;
        q.push({tree, 0});

        while (!q.empty()) {
            auto [curr_tree, livello] = q.front();
            q.pop();

            if (somme_livelli.size() <= (size_t)livello) {
                somme_livelli.push_back(0);
            }

            somme_livelli[livello] += curr_tree.radice();

            if (!curr_tree.figlio(SIN).nullo()) {
                q.push({curr_tree.figlio(SIN), livello + 1});
            }
            if (!curr_tree.figlio(DES).nullo()) {
                q.push({curr_tree.figlio(DES), livello + 1});
            }
        }

        for (size_t i = 0; i < somme_livelli.size() - 1; ++i) {
            if (somme_livelli[i] >= somme_livelli[i + 1]) {
                return false;
            }
        }
        return true;
    }
    ```

*   **Esercizio 4 (Regolo di Golomb):**
    *   *LeetCode mapping:* N/A (Problema combinatorio NP-completo).
    *   *Logica:* Backtracking incrementale. Si posizionano le tacche da $0$ a $l$. Per ogni nuova tacca posizionata, si verifica che la distanza tra questa e tutte le tacche precedenti non sia già stata utilizzata.
    ```cpp
    #include <iostream>
    #include <vector>

    bool checkDistanze(const std::vector<unsigned>& regolo, unsigned nuova_tacca, std::vector<bool>& distanze_usate) {
        for (unsigned tacca : regolo) {
            unsigned d = nuova_tacca - tacca;
            if (distanze_usate[d]) {
                return false;
            }
        }
        return true;
    }

    bool risolviGolomb(unsigned o, unsigned l, std::vector<unsigned>& regolo, 
                       std::vector<bool>& distanze_usate, unsigned idx_tacca, unsigned start_val) {
        if (regolo.size() == o) {
            return regolo.back() == l;
        }
        if (!regolo.empty() && regolo.back() > l) {
            return false;
        }

        if (regolo.size() == o - 1) {
            if (checkDistanze(regolo, l, distanze_usate)) {
                std::vector<unsigned> nuove_distanze;
                for (unsigned tacca : regolo) {
                    unsigned d = l - tacca;
                    distanze_usate[d] = true;
                    nuove_distanze.push_back(d);
                }
                regolo.push_back(l);

                if (risolviGolomb(o, l, regolo, distanze_usate, idx_tacca + 1, l)) {
                    return true;
                }

                regolo.pop_back();
                for (unsigned d : nuove_distanze) {
                    distanze_usate[d] = false;
                }
            }
            return false;
        }

        for (unsigned val = start_val + 1; val < l; ++val) {
            if (checkDistanze(regolo, val, distanze_usate)) {
                std::vector<unsigned> nuove_distanze;
                for (unsigned tacca : regolo) {
                    unsigned d = val - tacca;
                    distanze_usate[d] = true;
                    nuove_distanze.push_back(d);
                }
                regolo.push_back(val);

                if (risolviGolomb(o, l, regolo, distanze_usate, idx_tacca + 1, val)) {
                    return true;
                }

                regolo.pop_back();
                for (unsigned d : nuove_distanze) {
                    distanze_usate[d] = false;
                }
            }
        }
        return false;
    }

    void esercizio4_2026_02_17(unsigned o, unsigned l) {
        if (o < 2) {
            std::cout << "IMPOSSIBILE" << std::endl;
            return;
        }
        std::vector<unsigned> regolo;
        regolo.push_back(0); 
        std::vector<bool> distanze_usate(l + 1, false);

        if (risolviGolomb(o, l, regolo, distanze_usate, 1, 0)) {
            for (unsigned val : regolo) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "IMPOSSIBILE" << std::endl;
        }
    }
    ```

---

### Appello 2: 22 Gennaio 2026

*   **Esercizio 3 (Doppia Raggiungibilità):**
    *   *LeetCode mapping:* Variante di [1971. Find if Path Exists in Graph](https://leetcode.com/problems/find-if-path-exists-in-graph/) (Easy).
    *   *Logica:* Si effettuano due DFS ricorsive distinte. La prima controlla se esiste un cammino da $s$ a $t$, la seconda se esiste un cammino da $t$ a $s$.
    ```cpp
    #include <vector>

    bool dfs_raggiungibile(const Grafo& g, int attuale, int destinazione, std::vector<bool>& visitato) {
        if (attuale == destinazione) return true;
        visitato[attuale] = true;
        for (int vicino = 0; vicino < (int)g.n(); ++vicino) {
            if (g(attuale, vicino) && !visitato[vicino]) {
                if (dfs_raggiungibile(g, vicino, destinazione, visitato)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool esercizio3_2026_01_22(const Grafo& g, int s, int t) {
        std::vector<bool> visitato1(g.n(), false);
        bool da_s_a_t = dfs_raggiungibile(g, s, t, visitato1);

        std::vector<bool> visitato2(g.n(), false);
        bool da_t_a_s = dfs_raggiungibile(g, t, s, visitato2);

        return da_s_a_t && da_t_a_s;
    }
    ```

*   **Esercizio 4 (Colorazione Grafi con Vincolo di Somma):**
    *   *LeetCode mapping:* N/A (Constraint Satisfaction Problem).
    *   *Logica:* Backtracking per assegnare valori $0..n-1$ a ciascun nodo. Ad ogni assegnamento si verifica:
        1. Non adiacenza mod 3 con nodi già colorati.
        2. $v[x] \neq x$.
        3. Pruning: se la somma parziale supera $k$, interrompiamo.
    ```cpp
    #include <vector>
    #include <iostream>
    #include <numeric>

    bool is_valid_color(const Grafo& g, const std::vector<int>& v, int curr_node, int val) {
        if (val == curr_node) return false;
        for (int vicino = 0; vicino < (int)g.n(); ++vicino) {
            if (g(curr_node, vicino) && v[vicino] != -1) {
                if (val % 3 == v[vicino] % 3) {
                    return false;
                }
            }
        }
        return true;
    }

    bool solve_coloring(const Grafo& g, std::vector<int>& v, int curr_node, int target_sum, int current_sum) {
        int n = g.n();
        if (curr_node == n) {
            return current_sum == target_sum;
        }
        if (current_sum > target_sum) {
            return false;
        }
        int nodi_rimanenti = n - curr_node;
        if (current_sum + nodi_rimanenti * (n - 1) < target_sum) {
            return false;
        }

        for (int val = 0; val < n; ++val) {
            if (is_valid_color(g, v, curr_node, val)) {
                v[curr_node] = val;
                if (solve_coloring(g, v, curr_node + 1, target_sum, current_sum + val)) {
                    return true;
                }
                v[curr_node] = -1; // backtrack
            }
        }
        return false;
    }

    void esercizio4_2026_01_22(const Grafo& g, int k) {
        int n = g.n();
        std::vector<int> v(n, -1);
        if (solve_coloring(g, v, 0, k, 0)) {
            for (int val : v) std::cout << val << " ";
            std::cout << std::endl;
        } else {
            std::cout << "IMPOSSIBILE" << std::endl;
        }
    }
    ```

---

### Appello 3: 25 Novembre 2025

*   **Esercizio 3 (Trova Ciclo Semplice da x):**
    *   *LeetCode mapping:* Variante di [802. Find Eventual Safe States](https://leetcode.com/problems/find-eventual-safe-states/) (Medium).
    *   *Logica:* Si implementa una DFS che parte dai vicini di $x$. L'obiettivo è raggiungere un qualsiasi nodo $y$ tale che esista l'arco diretto $(y, x)$, mantenendo il cammino semplice (tramite un array `visited`).
    ```cpp
    #include <vector>

    bool dfs_cerca_ciclo(const Grafo& g, int curr, int target, std::vector<bool>& visited) {
        for (int vicino = 0; vicino < (int)g.n(); ++vicino) {
            if (g(curr, vicino)) {
                if (vicino == target) return true;
                if (!visited[vicino]) {
                    visited[vicino] = true;
                    if (dfs_cerca_ciclo(g, vicino, target, visited)) {
                        return true;
                    }
                    visited[vicino] = false; // backtrack
                }
            }
        }
        return false;
    }

    bool esercizio3_2025_11_25(const Grafo& g, int x) {
        // Verifica se x ha archi in ingresso
        bool ha_in = false;
        for (int i = 0; i < (int)g.n(); ++i) {
            if (g(i, x)) { ha_in = true; break; }
        }
        if (!ha_in) return false;

        std::vector<bool> visited(g.n(), false);
        visited[x] = true;
        return dfs_cerca_ciclo(g, x, x, visited);
    }
    ```

*   **Esercizio 4 (Piazzamento Soldati - Dominating Set):**
    *   *LeetCode mapping:* Variante di [1125. Smallest Sufficient Team](https://leetcode.com/problems/smallest-sufficient-team/) (Hard).
    *   *Logica:* Dobbiamo scegliere un sottoinsieme di città di taglia $k$ tra quelle controllate dalla fazione $T$ (dove `fazione[i] == true`) in modo che ogni città della fazione $F$ (`fazione[j] == false`) sia adiacente ad almeno una città con un soldato.
    ```cpp
    #include <vector>
    #include <iostream>

    bool controlla_sorveglianza(const Grafo& G, const std::vector<bool>& fazione, const std::vector<int>& soldati) {
        int n = G.n();
        for (int i = 0; i < n; ++i) {
            if (!fazione[i]) { // Città F
                bool protetta = false;
                for (int s : soldati) {
                    if (G(s, i) || G(i, s) || s == i) {
                        protetta = true;
                        break;
                    }
                }
                if (!protetta) return false;
            }
        }
        return true;
    }

    bool soldati_backtrack(int citta_idx, int k, const Grafo& G, const std::vector<bool>& fazione, std::vector<int>& soldati) {
        if (soldati.size() == (size_t)k) {
            return controlla_sorveglianza(G, fazione, soldati);
        }
        if (citta_idx == (int)G.n()) {
            return false;
        }

        if (fazione[citta_idx]) {
            soldati.push_back(citta_idx);
            if (soldati_backtrack(citta_idx + 1, k, G, fazione, soldati)) {
                return true;
            }
            soldati.pop_back(); // backtrack
        }

        if (soldati_backtrack(citta_idx + 1, k, G, fazione, soldati)) {
            return true;
        }
        return false;
    }

    void esercizio4_2025_11_25(const Grafo& G, const std::vector<bool>& fazione, int k) {
        std::vector<int> soldati;
        if (soldati_backtrack(0, k, G, fazione, soldati)) {
            for (int s : soldati) std::cout << s << " ";
            std::cout << std::endl;
        } else {
            std::cout << "IMPOSSIBILE" << std::endl;
        }
    }
    ```

---

### Appello 4: 16 Settembre 2025

*   **Esercizio 3 (Nodi Sovrapponibili):**
    *   *LeetCode mapping:* N/A (Easy).
    *   *Logica:* Si analizza ogni coppia di nodi $i, j$ e si verifica se per tutti i nodi del grafo hanno la stessa relazione di arco sia entrante che uscente.
    ```cpp
    #include <vector>

    std::vector<std::pair<int, int>> esercizio3_2025_09_16(const Grafo& g) {
        int n = g.n();
        std::vector<std::pair<int, int>> ris;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                bool sovrapponibili = true;
                for (int k = 0; k < n; ++k) {
                    if (g(i, k) != g(j, k) || g(k, i) != g(k, j)) {
                        sovrapponibili = false;
                        break;
                    }
                }
                if (sovrapponibili) {
                    ris.push_back({i, j});
                }
            }
        }
        return ris;
    }
    ```

*   **Esercizio 4 (Regine e Alfieri):**
    *   *LeetCode mapping:* Variante avanzata di [51. N-Queens](https://leetcode.com/problems/n-queens/) (Hard).
    *   *Logica:* Backtracking per posizionare $k$ regine sulla scacchiera $n \times n$. Bisogna controllare le minacce reciproche regina-regina e regina-alfiere, e infine verificare che tutti gli alfieri siano minacciati da almeno una regina.
    ```cpp
    #include <vector>
    #include <iostream>
    #include <cmath>

    bool alfiere_minaccia_cella(unsigned r, unsigned c, const std::vector<std::pair<unsigned, unsigned>>& alfieri) {
        for (const auto& a : alfieri) {
            if (std::abs((int)r - (int)a.first) == std::abs((int)c - (int)a.second)) {
                return true;
            }
        }
        return false;
    }

    bool regina_minaccia_cella(unsigned r, unsigned c, const std::vector<std::pair<unsigned, unsigned>>& regine) {
        for (const auto& q : regine) {
            if (r == q.first || c == q.second || std::abs((int)r - (int)q.first) == std::abs((int)c - (int)q.second)) {
                return true;
            }
        }
        return false;
    }

    bool verifica_alfieri_coperti(const std::vector<std::pair<unsigned, unsigned>>& alfieri, const std::vector<std::pair<unsigned, unsigned>>& regine) {
        for (const auto& a : alfieri) {
            bool minacciato = false;
            for (const auto& q : regine) {
                if (a.first == q.first || a.second == q.second || std::abs((int)a.first - (int)q.first) == std::abs((int)a.second - (int)q.second)) {
                    minacciato = true;
                    break;
                }
            }
            if (!minacciato) return false;
        }
        return true;
    }

    bool posiziona_regine(int r, int c, int n, int k, std::vector<std::pair<unsigned, unsigned>>& regine, const std::vector<std::pair<unsigned, unsigned>>& alfieri) {
        if (regine.size() == (size_t)k) {
            return verifica_alfieri_coperti(alfieri, regine);
        }

        for (int i = r; i < n; ++i) {
            int start_col = (i == r) ? c : 0;
            for (int j = start_col; j < n; ++j) {
                // Controlla se occupato da un alfiere
                bool occupato = false;
                for (const auto& a : alfieri) {
                    if (a.first == (unsigned)i && a.second == (unsigned)j) { occupato = true; break; }
                }
                if (occupato) continue;

                if (!regina_minaccia_cella(i, j, regine) && !alfiere_minaccia_cella(i, j, alfieri)) {
                    regine.push_back({i, j});
                    int next_col = (j + 1 < n) ? j + 1 : 0;
                    int next_row = (next_col == 0) ? i + 1 : i;
                    if (posiziona_regine(next_row, next_col, n, k, regine, alfieri)) {
                        return true;
                    }
                    regine.pop_back(); // backtrack
                }
            }
        }
        return false;
    }

    void esercizio4_2025_09_16(int n, const std::vector<std::pair<unsigned, unsigned>>& alfieri, int k) {
        std::vector<std::pair<unsigned, unsigned>> regine;
        if (posiziona_regine(0, 0, n, k, regine, alfieri)) {
            for (const auto& q : regine) std::cout << "(" << q.first << "," << q.second << ") ";
            std::cout << std::endl;
        } else {
            std::cout << "IMPOSSIBILE" << std::endl;
        }
    }
    ```

---

### Appello 5: 10 Luglio 2025

*   **Esercizio 3 (Cammino $c \to v \to b$):**
    *   *LeetCode mapping:* Variante di [864. Shortest Path to Get All Keys](https://leetcode.com/problems/shortest-path-to-get-all-keys/) (Medium).
    *   *Logica:* Il cammino minimo in un grafo non pesato si trova con una BFS. Si eseguono due BFS: da $c$ a $v$, e da $v$ a $b$. Si concatenano i percorsi risultanti.
    ```cpp
    #include <vector>
    #include <queue>
    #include <algorithm>

    std::vector<unsigned> BFS_singola(const Grafo& g, unsigned sorgente, unsigned destinazione) {
        unsigned n = g.n();
        std::vector<int> padre(n, -1);
        std::vector<bool> visitato(n, false);
        std::queue<unsigned> q;

        visitato[sorgente] = true;
        q.push(sorgente);

        bool trovato = false;
        while(!q.empty()) {
            unsigned u = q.front();
            q.pop();
            if (u == destinazione) { trovato = true; break; }
            for (unsigned v = 0; v < n; ++v) {
                if (g(u, v) && !visitato[v]) {
                    visitato[v] = true;
                    padre[v] = u;
                    q.push(v);
                }
            }
        }

        std::vector<unsigned> percorso;
        if (trovato) {
            int curr = destinazione;
            while(curr != -1) {
                percorso.push_back(curr);
                curr = padre[curr];
            }
            std::reverse(percorso.begin(), percorso.end());
        }
        return percorso;
    }

    std::vector<unsigned> esercizio3_2025_07_10(const Grafo& g, unsigned c, unsigned b, unsigned v) {
        std::vector<unsigned> p1 = BFS_singola(g, c, v);
        if (p1.empty() && c != v) return {};
        
        std::vector<unsigned> p2 = BFS_singola(g, v, b);
        if (p2.empty() && v != b) return {};

        std::vector<unsigned> cammino_finale = p1;
        if (!p2.empty()) {
            cammino_finale.insert(cammino_finale.end(), p2.begin() + 1, p2.end());
        }
        return cammino_finale;
    }
    ```

*   **Esercizio 4 (Dormitorio):**
    *   *LeetCode mapping:* N/A (Problema CSP / Assegnamento).
    *   *Logica:* Assegnamento ricorsivo studente per studente. Per ogni studente si prova l'inserimento in una delle stanze del dormitorio disponibili, verificando: capienza massima (`(stanza_id % 6) + 1`), incompatibilità con studenti già assegnati alla stanza e che a fine processo nessuna stanza sia rimasta vuota.
    ```cpp
    #include <vector>
    #include <string>
    #include <algorithm>

    struct Dormitorio {
        std::vector<std::string> studenti;
        std::vector<std::pair<std::string, std::string>> inc;
        std::vector<std::pair<unsigned, std::vector<std::string>>> stanze;
    };

    bool compatibile(const std::string& s, const std::vector<std::string>& occupanti, const std::vector<std::pair<std::string, std::string>>& inc) {
        for (const auto& occ : occupanti) {
            for (const auto& p : inc) {
                if ((p.first == s && p.second == occ) || (p.first == occ && p.second == s)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool alloca_studenti(int std_idx, Dormitorio& d) {
        if (stud_idx == (int)d.studenti.size()) {
            // Vincolo: nessuna stanza deve restare vuota
            for (const auto& stanza : d.stanze) {
                if (stanza.second.empty()) return false;
            }
            return true;
        }

        const std::string& studente = d.studenti[stud_idx];
        for (auto& stanza : d.stanze) {
            unsigned capienza = (stanza.first % 6) + 1;
            if (stanza.second.size() < capienza && compatibile(studente, stanza.second, d.inc)) {
                stanza.second.push_back(studente);
                if (alloca_studenti(stud_idx + 1, d)) {
                    return true;
                }
                stanza.second.pop_back(); // backtrack
            }
        }
        return false;
    }

    bool esercizio4_2025_07_10(Dormitorio& d) {
        for (auto& stanza : d.stanze) {
            stanza.second.clear();
        }
        return alloca_studenti(0, d);
    }
    ```

---

### Appello 6: 13 Giugno 2025

*   **Esercizio 3 (Spremi):**
    *   *LeetCode mapping:* Variante di [116. Populating Next Right Pointers in Each Node](https://leetcode.com/problems/populating-next-right-pointers-in-each-node/) (Medium).
    *   *Logica:* Visita DFS post-order modificata. Ogni nodo non foglia sposta il proprio valore sui figli (dividendo / 2). Il valore accumulato da figli nulli viene depositato in un accumulatore globale passato per riferimento.
    ```cpp
    float spremi_ricorsivo(AlberoB<float>& tree, float valore_ereditato, float& acc) {
        if (tree.nullo()) {
            acc += valore_ereditato;
            return 0.0f;
        }

        float valore_corrente = tree.radice();
        if (tree.foglia()) {
            tree.modRadice(valore_corrente + valore_ereditato);
            return 0.0f;
        }

        float totale_da_distribuire = valore_corrente + valore_ereditato;
        float meta = totale_da_distribuire / 2.0f;
        tree.modRadice(0.0f);

        AlberoB<float> sin = tree.figlio(SIN);
        AlberoB<float> des = tree.figlio(DES);

        spremi_ricorsivo(sin, meta, acc);
        spremi_ricorsivo(des, meta, acc);

        return acc;
    }

    float spremi_2025_06_13(AlberoB<float>& tree) {
        float acc = 0.0f;
        spremi_ricorsivo(tree, 0.0f, acc);
        return acc;
    }
    ```

*   **Esercizio 4 (Ciclo Hamiltoniano):**
    *   *LeetCode mapping:* N/A (Problema NP-completo classico).
    *   *Logica:* Ricerca esaustiva tramite DFS. Si tracciano i nodi visitati e la lunghezza del cammino. Al raggiungimento di $n$ nodi, si controlla se esiste un arco diretto per tornare al punto di partenza.
    ```cpp
    #include <vector>
    #include <iostream>

    bool trova_hamiltoniano(const Grafo& g, int start, int curr, int count, std::vector<int>& path, std::vector<bool>& visited) {
        int n = g.n();
        if (count == n) {
            return g(curr, start);
        }

        for (int vicino = 0; vicino < n; ++vicino) {
            if (g(curr, vicino) && !visited[vicino]) {
                visited[vicino] = true;
                path.push_back(vicino);
                if (trova_hamiltoniano(g, start, vicino, count + 1, path, visited)) {
                    return true;
                }
                path.pop_back();
                visited[vicino] = false; // backtrack
            }
        }
        return false;
    }

    void esercizio4_2025_06_13(const Grafo& g) {
        int n = g.n();
        std::vector<int> path;
        std::vector<bool> visited(n, false);

        for (int start = 0; start < n; ++start) {
            path.clear();
            std::fill(visited.begin(), visited.end(), false);
            visited[start] = true;
            path.push_back(start);

            if (trova_hamiltoniano(g, start, start, 1, path, visited)) {
                for (int node : path) std::cout << node << " ";
                std::cout << std::endl;
                return;
            }
        }
        std::cout << "Impossibile" << std::endl;
    }
    ```

---

### Appello 7: 14 Settembre 2023

*   **Esercizio 3 (Nodi Equidistanti $u$ e $v$):**
    *   *LeetCode mapping:* Variante di [863. All Nodes Distance K in Binary Tree](https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/) (Medium).
    *   *Logica:* Si calcolano le distanze da $u$ a tutti gli altri nodi tramite una BFS sul grafo diretto originale, e le distanze da ciascun nodo a $v$ eseguendo una BFS a partire da $v$ sul grafo trasposto.
    ```cpp
    #include <vector>
    #include <queue>

    std::vector<int> bfs_distanze_uscita(const Grafo& g, int sorgente) {
        int n = g.n();
        std::vector<int> dist(n, -1);
        std::queue<int> q;
        dist[sorgente] = 0;
        q.push(sorgente);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < n; ++v) {
                if (g(u, v) && dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return dist;
    }

    std::vector<int> bfs_distanze_entrata(const Grafo& g, int destinazione) {
        int n = g.n();
        std::vector<int> dist(n, -1);
        std::queue<int> q;
        dist[destinazione] = 0;
        q.push(destinazione);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < n; ++v) {
                if (g(v, u) && dist[v] == -1) { // Arco entrante in u
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return dist;
    }

    std::vector<int> esercizio3_2023_09_14(const Grafo& g, int u, int v) {
        std::vector<int> dist_da_u = bfs_distanze_uscita(g, u);
        std::vector<int> dist_a_v = bfs_distanze_entrata(g, v);
        std::vector<int> ris;
        for (int x = 0; x < (int)g.n(); ++x) {
            if (dist_da_u[x] != -1 && dist_a_v[x] != -1 && dist_da_u[x] == dist_a_v[x]) {
                ris.push_back(x);
            }
        }
        return ris;
    }
    ```

*   **Esercizio 4 (1-in-3 SAT):**
    *   *LeetCode mapping:* N/A (Problema NP-completo di soddisfacibilità booleana).
    *   *Logica:* Backtracking per assegnare $1$ (True) o $0$ (False) alle variabili. Per ogni assegnamento si verifica che nessuna terna contenga più di un valore $1$, ed al termine che ogni terna contenga esattamente un $1$.
    ```cpp
    #include <vector>

    bool check_terne(const std::vector<std::vector<int>>& terne, const std::vector<int>& var) {
        for (const auto& t : terne) {
            int true_cnt = 0;
            int assigned_cnt = 0;
            for (int v_idx : t) {
                if (var[v_idx] != -1) {
                    assigned_cnt++;
                    if (var[v_idx] == 1) true_cnt++;
                }
            }
            if (true_cnt > 1) return false;
            if (assigned_cnt == 3 && true_cnt == 0) return false;
        }
        return true;
    }

    bool sat_ricorsivo(int var_idx, int n, const std::vector<std::vector<int>>& terne, std::vector<int>& var) {
        if (var_idx == n + 1) return true;

        var[var_idx] = 1;
        if (check_terne(terne, var) && sat_ricorsivo(var_idx + 1, n, terne, var)) {
            return true;
        }

        var[var_idx] = 0;
        if (check_terne(terne, var) && sat_ricorsivo(var_idx + 1, n, terne, var)) {
            return true;
        }

        var[var_idx] = -1; // backtrack
        return false;
    }

    std::vector<int> esercizio4_2023_09_14(const std::vector<std::vector<int>>& terne, int n) {
        std::vector<int> var(n + 1, -1);
        if (sat_ricorsivo(1, n, terne, var)) {
            std::vector<int> ris;
            for (int i = 1; i <= n; ++i) {
                if (var[i] == 1) ris.push_back(i);
            }
            return ris;
        }
        return {};
    }
    ```

---

### Appello 8: 13 Luglio 2023

*   **Esercizio 3 (Valutazione Espressione):**
    *   *LeetCode mapping:* Variante di [150. Evaluate Reverse Polish Notation](https://leetcode.com/problems/evaluate-reverse-polish-notation/) (Medium).
    *   *Logica:* Traversata post-order ricorsiva. Se il nodo è una foglia, restituisce il suo valore convertito in intero; altrimenti valuta ricorsivamente i sottoalberi sinistro e destro ed applica l'operatore.
    ```cpp
    #include <string>

    int esercizio3_2023_07_13(const AlberoB<std::string>& expr) {
        if (expr.nullo()) return 0;
        if (expr.foglia()) {
            return std::stoi(expr.radice());
        }

        int val_sin = esercizio3_2023_07_13(expr.figlio(SIN));
        int val_des = esercizio3_2023_07_13(expr.figlio(DES));
        std::string op = expr.radice();

        if (op == "+") return val_sin + val_des;
        if (op == "-") return val_sin - val_des;
        if (op == "*") return val_sin * val_des;
        if (op == "/") return val_sin / val_des;

        return 0;
    }
    ```

*   **Esercizio 4 (Generazione Sottoinsieme Frequente):**
    *   *LeetCode mapping:* N/A (Easy/Medium).
    *   *Logica:* Algoritmo greedy polinomiale. Si contano le occorrenze di ciascun elemento di $S$ nella lista di insiemi $C$. Se almeno $k$ elementi compaiono ciascuno in almeno $k$ insiemi, la condizione è verificata.
    ```cpp
    #include <vector>
    #include <algorithm>

    bool esercizio4_2023_07_13(const std::vector<int>& S, const std::vector<std::vector<int>>& C, int k) {
        std::vector<int> S_star;
        for (int x : S) {
            int occorrenze = 0;
            for (const auto& insieme : C) {
                if (std::find(insieme.begin(), insieme.end(), x) != insieme.end()) {
                    occorrenze++;
                }
            }
            if (occorrenze >= k) {
                S_star.push_back(x);
            }
        }
        return S_star.size() >= (size_t)k;
    }
    ```

---

### Appello 9: 15 Giugno 2023

*   **Esercizio 3 (Ottimizzazione Locale su Archi):**
    *   *LeetCode mapping:* N/A (Easy).
    *   *Logica:* Si calcola il grado di tutti i nodi. Si itera su tutti gli archi del grafo calcolando il punteggio dato da $(W(u) \cdot W(v)) / (deg(u) + deg(v))$ e si restituisce quello con il valore massimo.
    ```cpp
    struct Arco2023 { unsigned u, v; };

    int get_deg_simple(const Grafo& G, unsigned node) {
        int d = 0;
        for (unsigned i = 0; i < G.n(); ++i) {
            if (G(node, i) || G(i, node)) d++;
        }
        return d;
    }

    Arco2023 esercizio3_2023_06_15(const Grafo& G, const std::vector<float>& W) {
        int n = G.n();
        std::vector<int> deg(n, 0);
        for (int i = 0; i < n; ++i) {
            deg[i] = get_deg_simple(G, i);
        }

        Arco2023 ris = {0, 0};
        float max_p = -1.0f;
        bool found = false;

        for (int u = 0; u < n; ++u) {
            for (int v = u + 1; v < n; ++v) {
                if (G(u, v) || G(v, u)) {
                    float p = (W[u] * W[v]) / (deg[u] + deg[v]);
                    if (!found || p > max_p) {
                        max_p = p;
                        ris = {(unsigned)u, (unsigned)v};
                        found = true;
                    }
                }
            }
        }
        return ris;
    }
    ```

*   **Esercizio 4 (Cammino Semplice di Lunghezza Esatta $k$):**
    *   *LeetCode mapping:* Variante di [797. All Paths From Source to Target](https://leetcode.com/problems/all-paths-from-source-to-target/) (Medium/Hard).
    *   *Logica:* Esplorazione DFS con backtracking. Partendo dal nodo $0$, si esplorano i vicini incrementando il contatore dei passi, tracciando i nodi visitati. Se a profondità $k$ ci troviamo in $n-1$, il cammino è valido.
    ```cpp
    #include <vector>

    bool dfs_lunghezza_k(const Grafo& G, int curr, int target, int k, int passi, std::vector<bool>& visited) {
        if (passi == k) {
            return curr == target;
        }
        if (curr == target) return false;

        for (int vicino = 0; vicino < (int)G.n(); ++vicino) {
            if (G(curr, vicino) && !visited[vicino]) {
                visited[vicino] = true;
                if (dfs_lunghezza_k(G, vicino, target, k, passi + 1, visited)) {
                    return true;
                }
                visited[vicino] = false; // backtrack
            }
        }
        return false;
    }

    bool esercizio4_2023_06_15(const Grafo& G, int k) {
        int n = G.n();
        std::vector<bool> visited(n, false);
        visited[0] = true;
        return dfs_lunghezza_k(G, 0, n - 1, k, 0, visited);
    }
    ```

---

### Appello 10: 14 Febbraio 2023

*   **Esercizio 3 (Cammino da Radice a Foglia con Somma Zero):**
    *   *LeetCode mapping:* Variante di [112. Path Sum](https://leetcode.com/problems/path-sum/) (Easy).
    *   *Logica:* Si effettua una DFS ricorsiva sull'albero. Durante la discesa si accumula il valore dei nodi. Giunti ad un nodo foglia, si controlla se la somma accumulata è pari a $0$.
    ```cpp
    bool dfs_somma_zero(const AlberoB<int>& t, int somma_corr) {
        if (t.nullo()) return false;
        int nuova_somma = somma_corr + t.radice();
        if (t.foglia()) {
            return nuova_somma == 0;
        }
        return dfs_somma_zero(t.figlio(SIN), nuova_somma) || dfs_somma_zero(t.figlio(DES), nuova_somma);
    }

    bool esercizio3_2023_02_14(const AlberoB<int>& T) {
        return dfs_somma_zero(T, 0);
    }
    ```

*   **Esercizio 4 (Selezione Nodi con Vincolo di Grado):**
    *   *LeetCode mapping:* Variante del problema NP-completo *Vertex Cover* (Hard).
    *   *Logica:* Si seleziona un sottoinsieme di nodi $W$ di taglia esatta $k$ tramite backtracking. Si verifica ad ogni passo che la somma dei gradi dei nodi selezionati rimanga $\le n$, ed al termine che ogni arco sia coperto da esattamente uno dei due estremi in $W$.
    ```cpp
    #include <vector>

    int calcola_grado_nodo(const Grafo& G, int node) {
        int deg = 0;
        for (unsigned i = 0; i < G.n(); ++i) {
            if (G(node, i) || G(i, node)) deg++;
        }
        return deg;
    }

    bool verifica_archi_coperti_esclusivi(const Grafo& G, const std::vector<bool>& W) {
        int n = G.n();
        for (int u = 0; u < n; ++u) {
            for (int v = u + 1; v < n; ++v) {
                if (G(u, v)) {
                    if (W[u] == W[v]) return false; // Devono essere uno sì e uno no
                }
            }
        }
        return true;
    }

    bool seleziona_nodi(const Grafo& G, int node_idx, int k, int selezionati, std::vector<bool>& W, int somma_gradi) {
        int n = G.n();
        if (selezionati == k) {
            if (somma_gradi <= n) {
                return verifica_archi_coperti_esclusivi(G, W);
            }
            return false;
        }
        if (node_idx == n || somma_gradi > n) {
            return false;
        }

        W[node_idx] = true;
        int deg = calcola_grado_nodo(G, node_idx);
        if (seleziona_nodi(G, node_idx + 1, k, selezionati + 1, W, somma_gradi + deg)) {
            return true;
        }
        W[node_idx] = false; // backtrack

        if (seleziona_nodi(G, node_idx + 1, k, selezionati, W, somma_gradi)) {
            return true;
        }
        return false;
    }

    bool esercizio4_2023_02_14(const Grafo& G, int k) {
        std::vector<bool> W(G.n(), false);
        return seleziona_nodi(G, 0, k, 0, W, 0);
    }
    ```

---

### Appello 11: 24 Gennaio 2023

*   **Esercizio 3 (Verifica Somma Pesi Vicinato):**
    *   *LeetCode mapping:* N/A (Easy).
    *   *Logica:* Semplice scansione di tutti i nodi del grafo. Per ogni nodo $u$, si calcola la somma dei pesi dei nodi con archi uscenti da $u$ e quella dei nodi con archi entranti in $u$, confrontandole.
    ```cpp
    #include <vector>

    bool esercizio3_2023_01_24(const Grafo& g, const std::vector<int>& W) {
        int n = g.n();
        for (int u = 0; u < n; ++u) {
            int sum_out = 0;
            int sum_in = 0;
            for (int v = 0; v < n; ++v) {
                if (g(u, v)) sum_out += W[v];
                if (g(v, u)) sum_in += W[v];
            }
            if (sum_out < sum_in) {
                return false;
            }
        }
        return true;
    }
    ```

*   **Esercizio 4 (Hitting Set):**
    *   *LeetCode mapping:* N/A (Problema NP-completo classico).
    *   *Logica:* Si generano i sottoinsiemi $H \subseteq \{0..n-1\}$ di cardinalità $k$ tramite backtracking. Per ogni sottoinsieme generato, si verifica che contenga almeno un elemento appartenente a ciascuno degli insiemi $S_i$ forniti in input.
    ```cpp
    #include <vector>

    bool hs_ricorsivo(int valore, int n, int k, const std::vector<std::vector<int>>& S, std::vector<int>& H, std::vector<int>& coperture) {
        if (H.size() == (size_t)k) {
            for (int c : coperture) {
                if (c == 0) return false;
            }
            return true;
        }
        if (valore == n) return false;

        // Includi 'valore' nel Hitting Set H
        H.push_back(valore);
        std::vector<int> indici_aggiornati;
        for (size_t i = 0; i < S.size(); ++i) {
            for (int elem : S[i]) {
                if (elem == valore) {
                    coperture[i]++;
                    indici_aggiornati.push_back(i);
                    break;
                }
            }
        }

        if (hs_ricorsivo(valore + 1, n, k, S, H, coperture)) {
            return true;
        }

        // Backtrack
        H.pop_back();
        for (int idx : indici_aggiornati) {
            coperture[idx]--;
        }

        // Prova a non includere 'valore'
        if (hs_ricorsivo(valore + 1, n, k, S, H, coperture)) {
            return true;
        }
        return false;
    }

    bool esercizio4_2023_01_24(int n, const std::vector<std::vector<int>>& S, int k) {
        std::vector<int> H;
        std::vector<int> coperture(S.size(), 0);
        return hs_ricorsivo(0, n, k, S, H, coperture);
    }
    ```

---

### Appello 12: 9 Settembre 2022

*   **Esercizio 3 (Verifica Depositi ed Archi Pesati):**
    *   *LeetCode mapping:* N/A (Easy).
    *   *Logica:* Per ogni nodo $v$, si calcola la somma dei pesi degli archi entranti e si verifica che sia minore del suo deposito. Si controlla inoltre che il deposito di ciascun nodo sorgente che punta a $v$ sia maggiore o uguale del deposito di $v$.
    ```cpp
    bool esercizio3_2022_09_09(const GrafoPesato& g) {
        int n = g.n();
        for (int v = 0; v < n; ++v) {
            float somma_in = 0.0f;
            bool ha_in = false;
            for (int u = 0; u < n; ++u) {
                float w = g(u, v);
                if (w > 0) {
                    ha_in = true;
                    somma_in += w;
                    if (g.dep(u) < g.dep(v)) {
                        return false;
                    }
                }
            }
            if (ha_in && somma_in >= g.dep(v)) {
                return false;
            }
        }
        return true;
    }
    ```

*   **Esercizio 4 (Sottoinsieme Disgiunto in Transazioni):**
    *   *LeetCode mapping:* Variante del problema NP-completo *Independent Set* (Hard).
    *   *Logica:* Si costruisce una matrice di incompatibilità/conflitto tra gli elementi di $V$ (conflitto se co-occorrono in almeno una transazione). Tramite backtracking si seleziona un sottoinsieme di dimensione $k$ privo di elementi in conflitto.
    ```cpp
    #include <vector>
    #include <string>
    #include <algorithm>

    bool ha_conflitti(int elem_idx, const std::vector<int>& W, const std::vector<std::vector<bool>>& conflict) {
        for (int scelto : W) {
            if (conflict[elem_idx][scelto]) return true;
        }
        return false;
    }

    bool trova_insieme_indipendente(int idx, int k, const std::vector<std::string>& V, std::vector<int>& W, const std::vector<std::vector<bool>>& conflict) {
        if (W.size() == (size_t)k) return true;
        if (idx == (int)V.size()) return false;

        // Includi V[idx] se possibile
        if (!ha_conflitti(idx, W, conflict)) {
            W.push_back(idx);
            if (trova_insieme_indipendente(idx + 1, k, V, W, conflict)) {
                return true;
            }
            W.pop_back(); // backtrack
        }

        // Escludi V[idx]
        if (trova_insieme_indipendente(idx + 1, k, V, W, conflict)) {
            return true;
        }
        return false;
    }

    bool esercizio4_2022_09_09(const std::vector<std::string>& V, const std::vector<std::vector<std::string>>& T, int k) {
        int n = V.size();
        std::vector<std::vector<bool>> conflict(n, std::vector<bool>(n, false));

        // Costruzione della matrice di conflitto
        for (const auto& trans : T) {
            for (size_t i = 0; i < trans.size(); ++i) {
                auto it1 = std::find(V.begin(), V.end(), trans[i]);
                if (it1 == V.end()) continue;
                int idx1 = std::distance(V.begin(), it1);

                for (size_t j = i + 1; j < trans.size(); ++j) {
                    auto it2 = std::find(V.begin(), V.end(), trans[j]);
                    if (it2 == V.end()) continue;
                    int idx2 = std::distance(V.begin(), it2);

                    conflict[idx1][idx2] = true;
                    conflict[idx2][idx1] = true;
                }
            }
        }

        std::vector<int> W;
        return trova_insieme_indipendente(0, k, V, W, conflict);
    }
    ```
