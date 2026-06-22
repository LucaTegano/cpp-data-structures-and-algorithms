# Lezione: Problemi di Backtracking - Cricca, Parentesi, Subset Sum

## Indice
1. [Introduzione al Backtracking](#1-introduzione-al-backtracking)
2. [Problema della Cricca (Clique)](#2-problema-della-cricca-clique)
3. [Stringhe Ben Parentesizzate](#3-stringhe-ben-parentesizzate)
4. [Subset Sum (Somma Sottoinsiemi)](#4-subset-sum-somma-sottoinsiemi)
5. [Pattern Comune del Backtracking](#5-pattern-comune-del-backtracking)
6. [Complessità Computazionale](#6-complessità-computazionale)
7. [Errori Comuni](#7-errori-comuni)
8. [Esercizi Proposti](#8-esercizi-proposti)

---

## 1. Introduzione al Backtracking

### 1.1 Caratteristiche dei Problemi

Questi tre problemi condividono caratteristiche comuni:
- **Spazio di ricerca esponenziale**: tutte le combinazioni/permutazioni
- **Soluzione incrementale**: costruita passo dopo passo
- **Pruning**: taglio di rami non promettenti

### 1.2 Schema Generale

```cpp
bool/void backtrack(Solution& sol, ...) {
    if (isComplete(sol)) {
        // Trovata soluzione
        return true;  // oppure salva e continua
    }
    
    for (ogni scelta x) {
        if (canAdd(x, sol)) {      // Pruning
            add(x, sol);
            
            if (backtrack(sol))    // Ricorsione
                return true;
            
            remove(x, sol);        // Backtrack
        }
    }
    
    return false;
}
```

---

## 2. Problema della Cricca (Clique)

### 2.1 Definizione

Una **cricca** (clique) in un grafo non orientato è un sottoinsieme di nodi in cui ogni coppia è connessa da un arco. In altre parole, è un **sottografo completo**.

```
┌─────────────────────────────────────────────────────────────┐
│ GRAFO CON CRICCA DI DIMENSIONE 3                            │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│       0 ━━━━━━ 1                                            │
│       ┃ ╲      ┃                                            │
│       ┃   ╲    ┃         Cricca: {0, 1, 2}                  │
│       ┃     ╲  ┃         Tutti connessi tra loro:           │
│       2 ━━━━━━ 3 ─── 4   0-1 ✓, 0-2 ✓, 1-2 ✓                │
│                                                              │
│   Linee spesse = archi della cricca                         │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

### 2.2 Problema

**Input:** Grafo G = (V, E) e intero k
**Output:** Esiste una cricca di dimensione k? Se sì, quale?

### 2.3 Complessità

Il problema della cricca è **NP-Completo**. Non esiste algoritmo polinomiale noto.

### 2.4 Soluzione con Backtracking

```cpp
using Solution = vector<unsigned>;

bool isComplete(Solution& sol, unsigned k) {
    return sol.size() == k;
}

bool canAdd(unsigned node, Solution& sol, const GrafoNonOrientato& G) {
    // Il nuovo nodo deve essere connesso a TUTTI i nodi già nella soluzione
    for (unsigned i = 0; i < sol.size(); i++)
        if (!G(sol[i], node))
            return false;
    return true;
}

void add(unsigned node, Solution& sol) {
    sol.push_back(node);
}

void remove(unsigned& node, Solution& sol) {
    node = sol.back();
    sol.pop_back();
}

bool solve(Solution& sol, const GrafoNonOrientato& G, unsigned k) {
    unsigned x = 0;  // Nodo corrente
    
    while (x <= MAX_VAL) {
        if (canAdd(x, sol, G)) {
            add(x, sol);
            
            if (isComplete(sol, k))
                return true;
            else if (solve(sol, G, k))
                return true;
            
            remove(x, sol);
        }
        x++;
    }
    
    return false;
}
```

### 2.5 Invariante Fondamentale

> **Ad ogni passo, `sol` è sempre una cricca.**

Questo è garantito da `canAdd`: aggiungiamo un nodo solo se è connesso a tutti quelli già presenti.

### 2.6 Esempio di Esecuzione

```
Grafo:
  0 ── 1
  │ ╲  │
  │  ╲ │
  2 ── 3 ── 4

Archi: (0,1), (0,2), (0,3), (1,2), (2,3), (3,4)

Cerco cricca di dimensione 3:

solve([]):
  x=0: canAdd(0, [])? sì → add → sol=[0]
    solve([0]):
      x=0: già in sol (ma non controlliamo questo, quindi canAdd sì...)
           [BUG POTENZIALE - vedi ottimizzazioni]
      x=1: canAdd(1, [0])? G(0,1)=true → sì → add → sol=[0,1]
        solve([0,1]):
          x=0: già usato
          x=1: già usato
          x=2: canAdd(2, [0,1])? G(0,2)=true, G(1,2)=true → sì!
               add → sol=[0,1,2]
               isComplete? 3==3 → true!
               
Risultato: Cricca {0, 1, 2}
```

---

## 3. Stringhe Ben Parentesizzate

### 3.1 Definizione

Una stringa è **ben parentesizzata** se:
- Ogni "(" ha una corrispondente ")"
- In ogni prefisso, #"(" ≥ #")"

### 3.2 Esempi

| n | Stringhe ben parentesizzate |
|---|---------------------------|
| 1 | "()" |
| 2 | "()()", "(())" |
| 3 | "()()()", "()(())", "(())()", "(()())", "((()))" |

### 3.3 Modello di Soluzione

```cpp
struct Soluzione {
    vector<string> benFormate;  // Tutte le soluzioni trovate
    string current;              // Stringa in costruzione
    int n;                       // Numero di coppie di parentesi
    
    Soluzione(int n_) : n(n_), current("") {}
};
```

### 3.4 Funzioni Chiave

```cpp
bool isComplete(Soluzione sol) {
    return sol.current.size() == 2 * sol.n;
}

bool canAdd(string par, Soluzione sol) {
    // Conta le parentesi aperte
    int count_aperte = 0;
    for (int i = 0; i < sol.current.size(); i++)
        if (sol.current[i] == '(')
            count_aperte++;
    
    if (par == "(") {
        // Posso aggiungere "(" solo se non ho già n "("
        return count_aperte < sol.n;
    }
    
    // par == ")"
    // Posso aggiungere ")" solo se #"(" > #")"
    int count_chiuse = sol.current.size() - count_aperte;
    return count_aperte > count_chiuse;
}

void add(string par, Soluzione& sol) {
    sol.current += par;
}

void remove(Soluzione& sol) {
    sol.current.pop_back();
}
```

### 3.5 Algoritmo (Trova TUTTE le Soluzioni)

```cpp
void solve(Soluzione& sol) {
    for (int i = 0; i < 2; i++) {  // 0 = "(", 1 = ")"
        string par = (i == 0) ? "(" : ")";
        
        if (canAdd(par, sol)) {
            add(par, sol);
            
            if (isComplete(sol))
                sol.benFormate.push_back(sol.current);
            else
                solve(sol);
            
            remove(sol);  // Backtrack SEMPRE
        }
    }
}
```

### 3.6 Albero di Ricerca (n=2)

```
                    ""
                  /    \
                "("    ")" ← Pruning (non può iniziare con ")")
               /    \
            "(("    "()"
            /  \      |
         "(()" "(())" "()("
           |     ✓      |
         "(())"       "()()"
           ✓            ✓

Soluzioni: "(())", "()()"
```

---

## 4. Subset Sum (Somma Sottoinsiemi)

### 4.1 Definizione

**Input:** Insieme S di numeri interi, valore target W
**Output:** Esiste un sottoinsieme di S la cui somma è esattamente W?

### 4.2 Esempio

```
S = {4, 12, 3, 88, 192}
W = 19

Soluzione: {4, 12, 3} → 4 + 12 + 3 = 19 ✓
```

### 4.3 Modello di Soluzione

```cpp
struct Soluzione {
    vector<int> sol;       // Indici degli elementi selezionati
    vector<int> elementi;  // Array originale
    int somma_target;      // W
    
    Soluzione(vector<int>& el, int st) : elementi(el), somma_target(st) {}
};
```

### 4.4 Funzioni Chiave

```cpp
bool isComplete(Soluzione& s) {
    int sum = 0;
    for (auto i : s.sol)
        sum += s.elementi[i];
    return sum == s.somma_target;
}

bool canAdd(int x, Soluzione& s) {
    // x già usato?
    for (auto y : s.sol)
        if (x == y) return false;
    
    // Somma sfora?
    int sum = 0;
    for (auto i : s.sol)
        sum += s.elementi[i];
    
    if (sum + s.elementi[x] > s.somma_target)
        return false;
    
    return true;
}

void add(int x, Soluzione& s) {
    s.sol.push_back(x);
}

void remove(int x, Soluzione& s) {
    s.sol.pop_back();
}
```

### 4.5 Algoritmo

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

### 4.6 Ottimizzazioni

1. **Evitare ricalcolo somma:** Passa la somma corrente come parametro
2. **Evitare duplicati:** Parti da `x+1` invece che da `0`

```cpp
// Versione ottimizzata
bool solve(Soluzione& s, int start, int somma_corrente) {
    for (int x = start; x < s.elementi.size(); x++) {
        int nuova_somma = somma_corrente + s.elementi[x];
        
        if (nuova_somma > s.somma_target)
            continue;  // Pruning
        
        add(x, s);
        
        if (nuova_somma == s.somma_target)
            return true;
        else if (solve(s, x + 1, nuova_somma))
            return true;
        
        remove(x, s);
    }
    
    return false;
}
```

---

## 5. Pattern Comune del Backtracking

### 5.1 Confronto dei Tre Problemi

| Aspetto | Cricca | Parentesi | Subset Sum |
|---------|--------|-----------|------------|
| Dominio scelte | Nodi del grafo | {`(`, `)`} | Indici array |
| isComplete | size == k | size == 2n | somma == W |
| canAdd | Connesso a tutti | Bilanciamento parentesi | Non usato + non sfora |
| Tipo soluzione | Una sola | Tutte | Una sola |
| Pruning | Archi mancanti | Sbilanciamento | Somma > target |

### 5.2 Template Generico

```cpp
struct Soluzione {
    // Dati specifici del problema
};

bool isComplete(Soluzione& sol);
bool canAdd(Scelta x, Soluzione& sol);
void add(Scelta x, Soluzione& sol);
void remove(Scelta x, Soluzione& sol);

bool/void backtrack(Soluzione& sol) {
    if (isComplete(sol)) {
        return true;  // o salva soluzione
    }
    
    for (ogni scelta x nel dominio) {
        if (canAdd(x, sol)) {
            add(x, sol);
            
            if (backtrack(sol))  // se cerchi UNA soluzione
                return true;
            // oppure: backtrack(sol);  // se cerchi TUTTE
            
            remove(x, sol);
        }
    }
    
    return false;
}
```

---

## 6. Complessità Computazionale

### 6.1 Caso Peggiore

| Problema | Complessità | Note |
|----------|-------------|------|
| Cricca | O(2^n) | NP-Completo |
| Parentesi | O(Catalan(n)) | Esponenziale ma strutturato |
| Subset Sum | O(2^n) | NP-Completo |

### 6.2 Effetto del Pruning

Il pruning riduce drasticamente i nodi visitati in pratica:

```
Senza pruning:         Con pruning:
      O                      O
    / | \                   /|\
   O  O  O               O  X  O     X = ramo tagliato
  /|\ ...               /|\
 O O O                 O X O

Nodi: 2^n            Nodi: molto meno (dipende dall'istanza)
```

### 6.3 Numeri di Catalan

Per le parentesi ben formate, il numero di soluzioni è il **numero di Catalan**:

$$C_n = \frac{1}{n+1}\binom{2n}{n}$$

| n | C_n |
|---|-----|
| 1 | 1 |
| 2 | 2 |
| 3 | 5 |
| 4 | 14 |
| 5 | 42 |
| 10 | 16,796 |

---

## 7. Errori Comuni

### 7.1 Cricca: Manca Controllo Duplicati

```cpp
// ❌ Potrebbe aggiungere lo stesso nodo due volte
bool canAdd(unsigned node, Solution& sol, ...) {
    for (unsigned i = 0; i < sol.size(); i++)
        if (!G(sol[i], node))
            return false;
    return true;
}

// ✅ Aggiungere controllo duplicati
bool canAdd(unsigned node, Solution& sol, ...) {
    for (unsigned i = 0; i < sol.size(); i++) {
        if (sol[i] == node) return false;  // Già presente!
        if (!G(sol[i], node)) return false;
    }
    return true;
}
```

### 7.2 Parentesi: Passaggio per Valore

```cpp
// ❌ SBAGLIATO: sol passata per valore
bool canAdd(string par, Soluzione sol) {  // Copia!
    // Funziona ma inefficiente
}

// ✅ CORRETTO: passare per riferimento const
bool canAdd(string par, const Soluzione& sol) {
    // Evita la copia
}
```

### 7.3 Subset Sum: Dimenticare di Avanzare

```cpp
// ❌ Loop infinito
while (x < elementi.size()) {
    if (canAdd(x, s)) {
        add(x, s);
        if (solve(s)) return true;
        remove(x, s);
        // Manca x++!
    }
    // Manca x++ nel caso canAdd fallisca!
}

// ✅ CORRETTO
while (x < elementi.size()) {
    if (canAdd(x, s)) {
        add(x, s);
        if (solve(s)) return true;
        remove(x, s);
    }
    x++;  // Sempre avanzare!
}
```

---

## 8. Esercizi Proposti

### Esercizio 1: Cricca Massima
Trova la cricca più grande nel grafo (non di dimensione fissa k).

### Esercizio 2: Conta Stringhe Parentesizzate
Conta il numero di stringhe ben parentesizzate senza generarle tutte.

### Esercizio 3: Subset Sum - Tutte le Soluzioni
Trova tutti i sottoinsiemi che sommano a W.

### Esercizio 4: Subset Sum con Elementi Negativi
Gestisci il caso in cui gli elementi possono essere negativi.

### Esercizio 5: Parentesi Multiple
Genera stringhe con più tipi di parentesi: `()`, `[]`, `{}`

```
n=1 per tipo → "([]{})", "([{}])", ...
```
