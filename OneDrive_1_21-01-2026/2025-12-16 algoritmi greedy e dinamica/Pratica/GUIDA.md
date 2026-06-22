# Guida Pratica: Greedy e Programmazione Dinamica

## Indice
1. [Panoramica del Progetto](#1-panoramica-del-progetto)
2. [Analisi divcoins/main.cpp](#2-analisi-divcoinsmain.cpp)
3. [Analisi scheduling/main.cpp](#3-analisi-schedulingmaincpp)
4. [Analisi euristica cammino/main.cpp](#4-analisi-euristica-camminomaincpp)
5. [Trace di Esecuzione](#5-trace-di-esecuzione)
6. [Adattamenti per l'Esame](#6-adattamenti-per-lesame)

---

## 1. Panoramica del Progetto

### 1.1 Struttura File

```
Pratica/
├── 448 - divcoins (dinamica)/
│   ├── main.cpp                    # Partition problem con DP
│   └── Traccia/Esercitazione_Divcoins.pdf
│
├── scheduling (dinamica)/
│   ├── main.cpp                    # Weighted interval scheduling
│   └── Traccia/Traccia.pdf
│
└── 441 - euristica cammino minimo (golosa)/
    ├── main.cpp                    # Cammino minimo greedy
    ├── grafo.hpp
    ├── grafoPesato.hpp
    └── Traccia/...pdf
```

### 1.2 Tecniche Utilizzate

| File | Tecnica | Problema |
|------|---------|----------|
| divcoins | DP (Tabulation) | Partition Problem |
| scheduling | DP (Tabulation) | Weighted Interval Scheduling |
| euristica cammino | Greedy | Shortest Path (euristica) |

---

## 2. Analisi divcoins/main.cpp

### 2.1 Obiettivo

Dividere monete in due gruppi minimizzando `|somma_gruppo1 - somma_gruppo2|`.

### 2.2 Idea Chiave

Trovare un sottoinsieme con somma più vicina a `Totale/2`.

### 2.3 Codice Annotato

```cpp
int divCoins(const vector<int>& monete) {
    // 1. Calcola somma totale
    int tot = 0;
    for (int i : monete)
        tot += i;
    
    int target = tot / 2;
    
    // 2. Array DP: sommeParziali[k] = true se somma k è raggiungibile
    bool sommeParziali[target + 1] = {false};
    sommeParziali[0] = true;  // Somma 0 sempre possibile
    
    // 3. Per ogni moneta, aggiorna le somme raggiungibili
    for (int m : monete) {
        // IMPORTANTE: itera all'INDIETRO!
        for (int i = target - m; i >= 0; --i) {
            if (sommeParziali[i])
                sommeParziali[i + m] = true;
        }
    }
    
    // 4. Trova la somma più grande raggiungibile <= target
    for (int i = target; i >= 0; --i) {
        if (sommeParziali[i])
            return abs(i - (tot - i));
    }
    
    return -1;  // Non dovrebbe mai succedere
}
```

### 2.4 Perché All'Indietro?

```
Esempio: monete = [5], target = 10

Avanti (SBAGLIATO):
  i=0: sommeParziali[0+5] = true → [T,F,F,F,F,T,...]
  i=5: sommeParziali[5+5] = true → [T,F,F,F,F,T,...,T]
       Moneta usata 2 volte!

Indietro (CORRETTO):
  i=5: sommeParziali[5] = false → nulla
  i=0: sommeParziali[0+5] = true → [T,F,F,F,F,T]
       Moneta usata 1 volta!
```

### 2.5 Input/Output

```
Input: 1 6 11 5 -1
Output: Diff ottima: 1

Spiegazione:
  Totale = 23, target = 11
  Gruppo 1 = {11} = 11
  Gruppo 2 = {1,6,5} = 12
  Differenza = |11 - 12| = 1
```

---

## 3. Analisi scheduling/main.cpp

### 3.1 Obiettivo

Selezionare attività non sovrapposte massimizzando il valore totale.

### 3.2 Struttura Attività

```cpp
struct Attivita {
    int inizio;
    int fine;
    int valore;
    
    // Ordinamento per tempo di fine (cruciale!)
    bool operator<(const Attivita other) {
        return fine < other.fine;
    }
};
```

### 3.3 Algoritmo in Due Fasi

**Fase 1: Calcola p[]**
```cpp
// p[i] = indice dell'ultima attività compatibile con i
//        (che finisce prima che i inizi)
vector<int> p(attivita.size(), -1);

for (int i = 1; i < attivita.size(); ++i) {
    for (int j = i - 1; j >= 0; --j) {
        if (attivita[j].fine <= attivita[i].inizio) {
            p[i] = j;
            break;  // Prendi il più recente
        }
    }
}
```

**Fase 2: DP**
```cpp
vector<int> M(attivita.size());
M[0] = attivita[0].valore;

for (int i = 1; i < attivita.size(); ++i) {
    // Opzione 1: Non prendo attività i
    int non_prendo = M[i - 1];
    
    // Opzione 2: Prendo attività i
    int prendo = attivita[i].valore;
    if (p[i] != -1)
        prendo += M[p[i]];
    
    M[i] = max(non_prendo, prendo);
}

return M[M.size() - 1];
```

### 3.4 Ricorrenza

$$M[i] = \max(M[i-1], M[p[i]] + v_i)$$

Dove:
- $M[i-1]$ = valore massimo senza l'attività $i$
- $M[p[i]] + v_i$ = valore massimo includendo l'attività $i$

### 3.5 Esempio nel main

```cpp
vector<Attivita> attivita;
attivita.push_back(Attivita(3,8,5));   // [3,8] valore 5
attivita.push_back(Attivita(7,11,8));  // [7,11] valore 8
attivita.push_back(Attivita(0,6,3));   // [0,6] valore 3
attivita.push_back(Attivita(1,4,1));   // [1,4] valore 1
attivita.push_back(Attivita(3,5,2));   // [3,5] valore 2
attivita.push_back(Attivita(4,7,4));   // [4,7] valore 4
attivita.push_back(Attivita(5,9,6));   // [5,9] valore 6
attivita.push_back(Attivita(6,10,7));  // [6,10] valore 7

sort(attivita.begin(), attivita.end());  // Ordina per fine!
```

---

## 4. Analisi euristica cammino/main.cpp

### 4.1 Obiettivo

Trovare un cammino da i a j minimizzando il costo (euristica, non ottima).

### 4.2 Strategia Greedy

Ad ogni passo, scegli l'arco con costo minimo tra quelli uscenti dal nodo corrente.

### 4.3 Funzione di Scelta

```cpp
int sceltaGolosa(const GrafoPesato& g, int nodo_corrente, 
                  const vector<bool>& visitati) {
    int costo_min = INT16_MAX;
    int nodo_min = -1;
    
    for (int i = 0; i < g.n(); ++i) {
        // Condizioni: non visitato, esiste arco, costo minore
        if (!visitati[i] && g(nodo_corrente, i) && 
            g.w(nodo_corrente, i) < costo_min) {
            costo_min = g.w(nodo_corrente, i);
            nodo_min = i;
        }
    }
    
    return nodo_min;  // -1 se nessun vicino disponibile
}
```

### 4.4 Costruzione Cammino

```cpp
vector<int> calcolaCammino(const GrafoPesato& g, int i, int j) {
    vector<int> cammino = {i};
    vector<bool> visitati(g.n(), false);
    visitati[i] = true;
    
    int nodo_corrente = i;
    while (nodo_corrente != j) {
        int prossimo = sceltaGolosa(g, nodo_corrente, visitati);
        
        if (prossimo == -1)
            return vector<int>();  // Fallimento!
        
        cammino.push_back(prossimo);
        visitati[prossimo] = true;
        nodo_corrente = prossimo;
    }
    
    return cammino;
}
```

### 4.5 Esempi dal Codice

```cpp
// ESEMPIO: NON trova l'ottimo
GrafoPesato g(4);
g(0,1,true,7);
g(0,2,true,3);
g(2,3,true,10);
g(1,3,true,2);

// Da 0 a 3:
// Greedy: 0→2→3 (costo 3+10=13)
// Ottimo: 0→1→3 (costo 7+2=9)

// ESEMPIO: NON trova soluzione ammissibile
GrafoPesato g(4);
g(0,1,true,7);
g(0,2,true,3);
g(1,3,true,2);  // 2 non collegato a 3!

// Da 0 a 3:
// Greedy: 0→2→??? (2 non ha archi verso 3)
// Ma esiste: 0→1→3
```

---

## 5. Trace di Esecuzione

### 5.1 DivCoins con [1, 6, 11, 5]

```
tot = 23, target = 11

Iniziale: [T, F, F, F, F, F, F, F, F, F, F, F]
           0  1  2  3  4  5  6  7  8  9 10 11

Moneta m=1:
  i=10→0: se sommeParziali[i], metti T in [i+1]
  [T, T, F, F, F, F, F, F, F, F, F, F]
   0  1

Moneta m=6:
  i=5→0: [0] è T → [6] = T
         [1] è T → [7] = T
  [T, T, F, F, F, F, T, T, F, F, F, F]
   0  1              6  7

Moneta m=11:
  i=0: [0] è T → [11] = T
  [T, T, F, F, F, F, T, T, F, F, F, T]
   0  1              6  7           11

Moneta m=5:
  i=6→0: [0] è T → [5] = T
         [1] è T → [6] già T
         [6] è T → [11] già T
         [7] è T → fuori range
  [T, T, F, F, F, T, T, T, F, F, F, T]
   0  1           5  6  7           11

Ricerca: i=11 è T!
Risultato: |11 - 12| = 1
```

---

## 6. Adattamenti per l'Esame

### 6.1 DivCoins: Restituire i Gruppi

```cpp
pair<vector<int>, vector<int>> divCoinsConGruppi(const vector<int>& monete) {
    int tot = 0;
    for (int m : monete) tot += m;
    int target = tot / 2;
    
    // Usa vettore di set per tracciare quali monete formano ogni somma
    vector<set<int>> come(target + 1);
    come[0] = {};
    
    for (int idx = 0; idx < monete.size(); idx++) {
        int m = monete[idx];
        for (int i = target - m; i >= 0; --i) {
            if (!come[i].empty() || i == 0) {
                come[i + m] = come[i];
                come[i + m].insert(idx);
            }
        }
    }
    
    // Trova la migliore
    for (int i = target; i >= 0; --i) {
        if (!come[i].empty() || i == 0) {
            // Costruisci i due gruppi
            vector<int> g1, g2;
            for (int idx = 0; idx < monete.size(); idx++) {
                if (come[i].count(idx))
                    g1.push_back(monete[idx]);
                else
                    g2.push_back(monete[idx]);
            }
            return {g1, g2};
        }
    }
    
    return {{}, {}};
}
```

### 6.2 Scheduling: Restituire Attività Selezionate

```cpp
vector<int> scheduleConSelezione(const vector<Attivita>& attivita) {
    // ... calcola p[] e M[] come prima ...
    
    // Ricostruzione
    vector<int> selezionate;
    int i = attivita.size() - 1;
    
    while (i >= 0) {
        if (p[i] == -1) {
            if (attivita[i].valore >= M[i-1] || i == 0) {
                selezionate.push_back(i);
                break;
            } else {
                i--;
            }
        } else {
            if (M[p[i]] + attivita[i].valore >= M[i-1]) {
                selezionate.push_back(i);
                i = p[i];
            } else {
                i--;
            }
        }
    }
    
    reverse(selezionate.begin(), selezionate.end());
    return selezionate;
}
```

### 6.3 Cammino Minimo: Dijkstra

```cpp
vector<int> dijkstra(const GrafoPesato& g, int sorgente, int dest) {
    vector<int> dist(g.n(), INT_MAX);
    vector<int> pred(g.n(), -1);
    vector<bool> visitati(g.n(), false);
    
    dist[sorgente] = 0;
    
    for (int count = 0; count < g.n(); count++) {
        // Trova il nodo non visitato con distanza minima
        int u = -1;
        for (int i = 0; i < g.n(); i++) {
            if (!visitati[i] && (u == -1 || dist[i] < dist[u]))
                u = i;
        }
        
        if (dist[u] == INT_MAX) break;
        visitati[u] = true;
        
        // Rilassa gli archi
        for (int v = 0; v < g.n(); v++) {
            if (g(u, v) && dist[u] + g.w(u, v) < dist[v]) {
                dist[v] = dist[u] + g.w(u, v);
                pred[v] = u;
            }
        }
    }
    
    // Ricostruisci cammino
    vector<int> cammino;
    for (int v = dest; v != -1; v = pred[v])
        cammino.push_back(v);
    reverse(cammino.begin(), cammino.end());
    
    return cammino;
}
```

---

## Appendice: Tabella Complessità

| Problema | Tempo | Spazio | Ottimo? |
|----------|-------|--------|---------|
| DivCoins | O(n × sum) | O(sum) | Sì |
| Scheduling | O(n²) | O(n) | Sì |
| Euristica Cammino | O(V²) | O(V) | No |
| Dijkstra | O(V² o (V+E)log V) | O(V) | Sì |
