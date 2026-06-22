# Guida Pratica: Backtracking - Cricca, Parentesi, Subset Sum

## Indice
1. [Panoramica del Progetto](#1-panoramica-del-progetto)
2. [Analisi cricca.cpp](#2-analisi-criccacpp)
3. [Analisi parentesi.cpp](#3-analisi-parentesicpp)
4. [Analisi main_subsetsum.cpp](#4-analisi-main_subsetsumcpp)
5. [Trace di Esecuzione](#5-trace-di-esecuzione)
6. [Adattamenti per l'Esame](#6-adattamenti-per-lesame)

---

## 1. Panoramica del Progetto

### 1.1 Struttura File

```
Pratica/
├── cricca/
│   ├── cricca.cpp              # Problema della cricca
│   ├── GrafoNonOrientato.h     # Dipendenza
│   └── Criccak.pdf             # Traccia
│
├── StringheParentesizzate/
│   ├── parentesi.cpp           # Stringhe ben parentesizzate
│   └── Stringhe ben parentesizzate.pdf
│
└── sommaSottoinsiemi/
    ├── main_subsetsum.cpp      # Subset Sum
    └── Esercitazione_Somma_sottoinsieme.pdf
```

### 1.2 Pattern Comune

Tutti e tre seguono lo stesso schema:

```cpp
bool/void solve(Solution& sol) {
    for (ogni scelta x) {
        if (canAdd(x, sol)) {
            add(x, sol);
            if (isComplete(sol)) { /* trovata! */ }
            else solve(sol);
            remove(x, sol);
        }
    }
}
```

---

## 2. Analisi cricca.cpp

### 2.1 Obiettivo

Trovare una **cricca** di dimensione esattamente `k` in un grafo non orientato.

### 2.2 Struttura Dati

```cpp
using Solution = vector<unsigned>;
// sol[i] = nodo i-esimo nella cricca

const unsigned MAX_VAL = 4;  // Nodo massimo (0..4 = 5 nodi)
const unsigned MIN_VAL = 0;
```

### 2.3 isComplete

```cpp
bool isComplete(Solution& sol, unsigned k) {
    return sol.size() == k;  // Cricca di dimensione k trovata?
}
```

### 2.4 canAdd - Cuore del Pruning

```cpp
bool canAdd(unsigned node, Solution& sol, const GrafoNonOrientato& Map) {
    cout << "provo con il nodo " << node << endl;
    unsigned size = sol.size();
    
    // Per ogni nodo già nella soluzione
    for (unsigned i = 0; i < size; i++)
        // Verifica che ci sia l'arco
        if (!Map(sol[i], node))
            return false;  // Manca un arco → non è cricca!
    
    return true;
}
```

**Invariante:** Se `canAdd` ritorna `true`, aggiungendo `node` a `sol` otteniamo ancora una cricca.

### 2.5 solve - Versione Iterativa

```cpp
bool solve(Solution& sol, const GrafoNonOrientato& Map, unsigned k) {
    unsigned x = MIN_VAL;
    bool stop = false, existsSolution = false;
    
    while (!stop) {
        if (x <= MAX_VAL) {
            if (canAdd(x, sol, Map)) {
                add(x, sol);
                
                if (isComplete(sol, k)) {
                    existsSolution = true;
                    stop = true;
                } else {
                    x = MIN_VAL;  // Riparti da nodo 0
                }
            } else {
                x = next(x);  // Prova prossimo nodo
            }
        } else {
            // Backtrack
            if (isEmpty(sol)) {
                existsSolution = false;
                stop = true;
            } else {
                remove(x, sol);
                x = next(x);
            }
        }
    }
    
    return existsSolution;
}
```

### 2.6 Esempio nel main

```cpp
GrafoNonOrientato Map(5);
Map(0,1,true);  // Arco 0-1
Map(0,2,true);  // Arco 0-2
Map(1,2,true);  // Arco 1-2  → {0,1,2} è una cricca!
Map(2,3,true);  // Arco 2-3
Map(3,4,true);  // Arco 3-4

Solution sol;
solve(sol, Map, 2);  // Trova cricca dim 2: es. {0,1}
solve(sol, Map, 4);  // Non esiste cricca dim 4
```

### 2.7 Bug/Limitazioni

1. **Non evita duplicati:** `x` riparte da `MIN_VAL` dopo ogni add, potrebbe provare nodi già usati
2. **Inefficiente:** Dovrebbe partire da `sol.back() + 1` per evitare ridondanze

```cpp
// Ottimizzazione suggerita:
x = sol.empty() ? MIN_VAL : sol.back() + 1;
```

---

## 3. Analisi parentesi.cpp

### 3.1 Obiettivo

Generare **tutte** le stringhe con `n` coppie di parentesi ben formate.

### 3.2 Struttura Dati

```cpp
struct Soluzione {
    vector<string> benFormate;  // Risultati
    string current;              // Stringa in costruzione
    int n;                       // Numero coppie

    Soluzione(int n_) : n(n_), current("") {}
};
```

### 3.3 canAdd - Regole di Bilanciamento

```cpp
bool canAdd(string par, Soluzione sol) {
    // Conta parentesi aperte
    int count_aperte = 0;
    for (int i = 0; i < sol.current.size(); i++)
        if (sol.current[i] == '(')
            count_aperte++;
    
    if (par == "(") {
        // Posso aggiungere "(" solo se ne ho meno di n
        if (count_aperte == sol.n)
            return false;
        else 
            return true;
    }
    
    // par == ")"
    // Posso aggiungere ")" solo se #"(" > #")"
    if (count_aperte > sol.current.size() - count_aperte)
        return true;
    else
        return false;
}
```

**Regole:**
1. Posso mettere `(` se ne ho meno di `n`
2. Posso mettere `)` se ho più `(` che `)`

### 3.4 solve - Trova Tutte le Soluzioni

```cpp
void solve(Soluzione& sol) {
    for (int i = 0; i < 2; i++) {  // 0="(", 1=")"
        if (canAdd(get(i), sol)) {
            add(get(i), sol);
            
            if (isComplete(sol))
                sol.benFormate.push_back(sol.current);  // Salva
            
            solve(sol);  // Continua comunque!
            
            remove(sol);  // Backtrack SEMPRE
        }
    }
}
```

**Differenza chiave:** Non ritorna `true` quando trova una soluzione, continua a cercare.

### 3.5 Funzioni Ausiliarie

```cpp
string get(int i) {
    return (i == 0) ? "(" : ")";
}

void add(string par, Soluzione& sol) {
    sol.current += par;
}

void remove(Soluzione& sol) {
    sol.current.pop_back();
}

bool isComplete(Soluzione sol) {
    return sol.current.size() == 2 * sol.n;
}
```

### 3.6 Esempio Esecuzione (n=2)

```
solve(""):
  i=0: canAdd("(")? n_aperte=0 < 2 → sì
       add → current="("
       solve("("):
         i=0: canAdd("(")? n_aperte=1 < 2 → sì
              add → current="(("
              solve("(("):
                i=0: canAdd("(")? n_aperte=2 == 2 → NO
                i=1: canAdd(")")? 2 > 0 → sì
                     add → current="(()"
                     solve("(()"):
                       i=0: canAdd("(")? 2 == 2 → NO
                       i=1: canAdd(")")? 2 > 1 → sì
                            add → current="(())"
                            isComplete? 4 == 4 → SALVA "(())"
                            solve non trova altro
                            remove → "(()".
                       remove → "((".
                     remove → "(("
              remove → "("
         i=1: canAdd(")")? 1 > 0 → sì
              add → current="()"
              solve("()"):
                i=0: canAdd("(")? 1 < 2 → sì
                     add → current="()("
                     solve("()("):
                       i=0: canAdd("(")? 2 == 2 → NO
                       i=1: canAdd(")")? 2 > 1 → sì
                            add → current="()()"
                            isComplete → SALVA "()()"
                            ...
                            
Risultato: ["(())", "()()"]
```

---

## 4. Analisi main_subsetsum.cpp

### 4.1 Obiettivo

Trovare un sottoinsieme di elementi la cui somma è esattamente `W`.

### 4.2 Struttura Dati

```cpp
struct Soluzione {
    vector<int> sol;       // Indici degli elementi scelti
    vector<int> elementi;  // Array originale
    int somma_target;      // W
    
    Soluzione(vector<int>& el, int st) : elementi(el), somma_target(st) {}
};
```

**Nota:** `sol` contiene **indici**, non valori!

### 4.3 isComplete

```cpp
bool isComplete(Soluzione& s) {
    int sum = 0;
    for (auto i : s.sol)
        sum += s.elementi[i];
    return sum == s.somma_target;
}
```

### 4.4 canAdd - Doppio Controllo

```cpp
bool canAdd(int x, Soluzione& s) {
    // 1. x già usato?
    for (auto y : s.sol)
        if (x == y)
            return false;
    
    // 2. Somma sfora?
    int sum = 0;
    for (auto i : s.sol)
        sum += s.elementi[i];
    
    if (sum + s.elementi[x] > s.somma_target)
        return false;
    
    return true;
}
```

**Pruning importante:** Se la somma supera il target, non ha senso continuare.

### 4.5 solve

```cpp
bool solve(Soluzione& s) {
    int x = 0;
    
    while (x < s.elementi.size()) {
        if (canAdd(x, s)) {
            add(x, s);
            
            if (isComplete(s))
                return true;
            else if (solve(s))
                return true;
            
            remove(x, s);
        }
        x++;
    }
    
    return false;
}
```

### 4.6 Input da Utente

```cpp
int main() {
    vector<int> elementi;
    cout << "Inserisci elementi:" << endl;
    int elem; cin >> elem;
    
    while (elem != -1) {
        elementi.push_back(elem);
        cin >> elem;
    }
    
    cout << "Inserisci target:" << endl;
    int somma_target; cin >> somma_target;
    
    Soluzione s(elementi, somma_target);
    
    if (solve(s))
        for (auto x : s.sol)
            cout << s.elementi[x] << " ";
    
    return 0;
}
```

**Input esempio:**
```
4 12 3 88 192 -1
19
```

**Output:** `4 12 3`

---

## 5. Trace di Esecuzione

### 5.1 Subset Sum: S={4,12,3}, W=19

```
solve([]):
  x=0: canAdd(0)? non usato, 4 <= 19 → sì
       add → sol=[0]  (somma=4)
       isComplete? 4 != 19
       solve([0]):
         x=0: canAdd(0)? già usato → NO
         x=1: canAdd(1)? non usato, 4+12=16 <= 19 → sì
              add → sol=[0,1]  (somma=16)
              isComplete? 16 != 19
              solve([0,1]):
                x=0: già usato → NO
                x=1: già usato → NO
                x=2: canAdd(2)? non usato, 16+3=19 <= 19 → sì
                     add → sol=[0,1,2]  (somma=19)
                     isComplete? 19 == 19 → TRUE!

Risultato: [0,1,2] → elementi: {4, 12, 3}
```

---

## 6. Adattamenti per l'Esame

### 6.1 Cricca: Leggere da File

```cpp
int main() {
    int N, M, k;
    cin >> N >> M >> k;
    
    GrafoNonOrientato G(N);
    
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        G(u, v, true);
    }
    
    Solution sol;
    if (solve(sol, G, k)) {
        cout << "Cricca trovata: ";
        for (auto node : sol)
            cout << node << " ";
    }
    
    return 0;
}
```

### 6.2 Cricca Massima (Variante)

```cpp
Solution best;  // Migliore trovata finora

void findMaxClique(Solution& sol, const GrafoNonOrientato& G) {
    // Aggiorna best se sol è più grande
    if (sol.size() > best.size())
        best = sol;
    
    for (unsigned x = (sol.empty() ? 0 : sol.back() + 1); x < G.n(); x++) {
        if (canAdd(x, sol, G)) {
            add(x, sol);
            findMaxClique(sol, G);
            remove(x, sol);
        }
    }
}
```

### 6.3 Subset Sum: Ottimizzazione

```cpp
// Evita ricalcolo somma
bool solve(Soluzione& s, int start, int somma_corrente) {
    if (somma_corrente == s.somma_target)
        return true;
    
    for (int x = start; x < s.elementi.size(); x++) {
        int nuova_somma = somma_corrente + s.elementi[x];
        
        if (nuova_somma <= s.somma_target) {
            add(x, s);
            if (solve(s, x + 1, nuova_somma))  // x+1 evita duplicati
                return true;
            remove(x, s);
        }
    }
    
    return false;
}

// Chiamata iniziale:
solve(s, 0, 0);
```

### 6.4 Parentesi: Conta Senza Generare

```cpp
// Numeri di Catalan
int catalan(int n) {
    if (n <= 1) return 1;
    
    int result = 0;
    for (int i = 0; i < n; i++)
        result += catalan(i) * catalan(n - 1 - i);
    
    return result;
}
```

---

## Appendice: Tabella Riassuntiva

| Problema | File | Tipo Output | Dominio Scelte |
|----------|------|-------------|----------------|
| Cricca | cricca.cpp | Una soluzione | Nodi 0..N-1 |
| Parentesi | parentesi.cpp | Tutte le soluzioni | {"(", ")"} |
| Subset Sum | main_subsetsum.cpp | Una soluzione | Indici 0..n-1 |

| Problema | canAdd controlla | Complessità |
|----------|------------------|-------------|
| Cricca | Connesso a tutti | O(2^n) |
| Parentesi | Bilanciamento | O(4^n / sqrt(n)) |
| Subset Sum | Non usato + non sfora | O(2^n) |
