# Lezione: Algoritmi Greedy e Programmazione Dinamica

## Indice
1. [Introduzione: Greedy vs Dinamica](#1-introduzione-greedy-vs-dinamica)
2. [DivCoins: Partizionamento con DP](#2-divcoins-partizionamento-con-dp)
3. [Weighted Interval Scheduling: DP](#3-weighted-interval-scheduling-dp)
4. [Cammino Minimo: Euristica Greedy](#4-cammino-minimo-euristica-greedy)
5. [Confronto delle Tecniche](#5-confronto-delle-tecniche)
6. [Complessità Computazionale](#6-complessità-computazionale)
7. [Errori Comuni](#7-errori-comuni)
8. [Esercizi Proposti](#8-esercizi-proposti)

---

## 1. Introduzione: Greedy vs Dinamica

### 1.1 Algoritmi Greedy

Un algoritmo **greedy** (goloso) fa la scelta localmente ottimale ad ogni passo, sperando di ottenere l'ottimo globale.

**Caratteristiche:**
- Semplice e veloce
- Non sempre ottimale
- Nessun backtracking

### 1.2 Programmazione Dinamica

La **programmazione dinamica** (DP) risolve problemi scomponendoli in sottoproblemi sovrapposti, memorizzando i risultati.

**Caratteristiche:**
- Più complessa ma garantisce l'ottimo
- Usa memoization o tabulation
- Richiede sottostruttura ottima

### 1.3 Quando Usare Quale?

| Criterio | Greedy | Dinamica |
|----------|--------|----------|
| Ottimalità | Non garantita | Garantita |
| Velocità | O(n log n) tipico | O(n²) o pseudo-polinomiale |
| Complessità impl. | Bassa | Media/Alta |
| Sottostruttura | Greedy choice | Ottima |

---

## 2. DivCoins: Partizionamento con DP

### 2.1 Problema

Dividere un insieme di monete in due gruppi minimizzando la differenza tra le somme.

**Input:** `monete = [1, 6, 11, 5]`
**Output:** Differenza minima = 1 (gruppi: {1,5,6}=12 e {11}=11)

### 2.2 Riduzione a Subset Sum

Il problema è equivalente a trovare un sottoinsieme con somma più vicina possibile a `Totale/2`.

```
Totale = 1 + 6 + 11 + 5 = 23
Target = 23 / 2 = 11

Se trovo sottoinsieme con somma S:
  Gruppo 1 = S
  Gruppo 2 = 23 - S
  Differenza = |S - (23 - S)| = |2S - 23|

Più S è vicino a 11, minore è la differenza.
```

### 2.3 Algoritmo DP

```cpp
int divCoins(const vector<int>& monete) {
    // Calcola il totale
    int tot = 0;
    for (int m : monete)
        tot += m;
    
    int target = tot / 2;
    
    // sommeParziali[k] = true se esiste sottoinsieme con somma k
    bool sommeParziali[target + 1] = {false};
    sommeParziali[0] = true;  // Somma 0 sempre possibile (insieme vuoto)
    
    // Per ogni moneta
    for (int m : monete) {
        // Itera ALL'INDIETRO per non usare la stessa moneta più volte
        for (int i = target - m; i >= 0; --i) {
            if (sommeParziali[i])
                sommeParziali[i + m] = true;
        }
    }
    
    // Trova la somma più grande possibile <= target
    for (int i = target; i >= 0; --i) {
        if (sommeParziali[i])
            return abs(i - (tot - i));  // Differenza tra i due gruppi
    }
    
    return -1;
}
```

### 2.4 Perché Iterare all'Indietro?

```
Supponi monete = [5], target = 10

Iterando IN AVANTI:
  i=0: sommeParziali[0]=true → sommeParziali[5]=true
  i=5: sommeParziali[5]=true → sommeParziali[10]=true  ← SBAGLIATO!
  
  Abbiamo usato la moneta 5 due volte!

Iterando ALL'INDIETRO:
  i=5: sommeParziali[5]=false → nulla
  i=0: sommeParziali[0]=true → sommeParziali[5]=true
  
  La moneta è usata una sola volta!
```

### 2.5 Trace di Esecuzione

```
monete = [1, 6, 11, 5]
tot = 23, target = 11

Iniziale: sommeParziali = [T, F, F, F, F, F, F, F, F, F, F, F]
                           0  1  2  3  4  5  6  7  8  9 10 11

Dopo m=1:  [T, T, F, F, F, F, F, F, F, F, F, F]
            0  1

Dopo m=6:  [T, T, F, F, F, F, T, T, F, F, F, F]
            0  1              6  7

Dopo m=11: [T, T, F, F, F, F, T, T, F, F, F, T]
            0  1              6  7            11

Dopo m=5:  [T, T, F, F, F, T, T, T, F, F, F, T]
            0  1           5  6  7            11

Risultato: i=11 è true
           Differenza = |11 - 12| = 1
```

---

## 3. Weighted Interval Scheduling: DP

### 3.1 Problema

Date n attività con (inizio, fine, valore), selezionare attività non sovrapposte massimizzando il valore totale.

### 3.2 Struttura Dati

```cpp
struct Attivita {
    int inizio;
    int fine;
    int valore;
    
    bool operator<(const Attivita other) {
        return fine < other.fine;  // Ordina per tempo di fine
    }
};
```

### 3.3 Algoritmo

**Passo 1:** Ordina attività per tempo di fine crescente

**Passo 2:** Per ogni attività i, calcola p[i] = ultima attività compatibile (che finisce prima che i inizi)

**Passo 3:** Ricorrenza DP:
```
M[i] = max(M[i-1],                    // Non prendo l'attività i
           M[p[i]] + valore[i])       // Prendo l'attività i
```

### 3.4 Implementazione

```cpp
int schedule(const vector<Attivita>& attivita) {
    // Attività già ordinata per fine crescente
    
    // 1. Calcola P (precedenti compatibili)
    vector<int> p(attivita.size(), -1);
    for (int i = 1; i < attivita.size(); ++i) {
        for (int j = i - 1; j >= 0; --j) {
            if (attivita[j].fine <= attivita[i].inizio) {
                p[i] = j;
                break;  // Prendi il più recente compatibile
            }
        }
    }
    
    // 2. DP
    vector<int> M(attivita.size());
    M[0] = attivita[0].valore;
    
    for (int i = 1; i < attivita.size(); ++i) {
        int non_prendo = M[i-1];
        int prendo = attivita[i].valore;
        
        if (p[i] != -1)
            prendo += M[p[i]];
        
        M[i] = max(non_prendo, prendo);
    }
    
    return M[M.size() - 1];
}
```

### 3.5 Esempio

```
Attività (ordinate per fine):
  i=0: [1,4] v=1
  i=1: [3,5] v=2
  i=2: [0,6] v=3
  i=3: [3,8] v=5
  i=4: [5,9] v=6
  i=5: [6,10] v=7
  i=6: [7,11] v=8

Calcolo p[]:
  p[0] = -1 (nessuna attività finisce prima di t=1)
  p[1] = -1 (nessuna finisce prima di t=3)
  p[2] = -1
  p[3] = 0  (attività 0 finisce a t=4 <= inizio 3? NO)
            (attività 0 finisce a t=4, inizio di 3 è t=3: 4 > 3)
            ... cerchiamo meglio
  ...

DP:
  M[0] = 1
  M[1] = max(M[0], v[1] + 0) = max(1, 2) = 2
  ...
```

---

## 4. Cammino Minimo: Euristica Greedy

### 4.1 Definizione
Il problema del cammino minimo richiede di trovare la sequenza di archi tra due nodi che minimizza la somma dei pesi.

### 4.2 L'ADT GrafoPesato
Per gestire i pesi, estendiamo la classe `Grafo` aggiungendo una matrice di pesi:
- `std::vector<std::vector<int>> pesi`: memorizza il costo dell'arco $(i, j)$.
- `g.w(i, j)`: restituisce il peso dell'arco.

### 4.3 Approccio Greedy (Euristica)
Ad ogni passo, scegli l'arco con peso minimo tra quelli disponibili.

```cpp
int sceltaGolosa(const GrafoPesato& g, int nodo_corrente, 
                  const vector<bool>& visitati) {
    int costo_min = INT_MAX;
    int nodo_min = -1;
    
    for (int i = 0; i < g.n(); ++i) {
        if (!visitati[i] && g(nodo_corrente, i) && 
            g.w(nodo_corrente, i) < costo_min) {
            costo_min = g.w(nodo_corrente, i);
            nodo_min = i;
        }
    }
    
    return nodo_min;
}

vector<int> calcolaCammino(const GrafoPesato& g, int i, int j) {
    vector<int> cammino = {i};
    vector<bool> visitati(g.n(), false);
    visitati[i] = true;
    
    int nodo_corrente = i;
    while (nodo_corrente != j) {
        int prossimo = sceltaGolosa(g, nodo_corrente, visitati);
        
        if (prossimo == -1)
            return vector<int>();  // Nessun cammino trovato
        
        cammino.push_back(prossimo);
        visitati[prossimo] = true;
        nodo_corrente = prossimo;
    }
    
    return cammino;
}
```

### 4.3 Limiti dell'Euristica Greedy

**NON garantisce:**
1. **Soluzione ottima**
2. **Soluzione ammissibile** (potrebbe non trovare un cammino esistente)

```
Esempio: Non trova l'ottimo
    0 ─(7)─ 1
    │       │
   (3)     (2)
    │       │
    2 ─(10)─ 3

Da 0 a 3:
  Greedy: 0 →(3)→ 2 →(10)→ 3  Costo = 13
  Ottimo: 0 →(7)→ 1 →(2)→ 3   Costo = 9

Esempio: Non trova soluzione
    0 ─(7)─ 1
    │       │
   (3)     (2)
    │       │
    2       3

Da 0 a 3:
  Greedy: 0 →(3)→ 2 → ???  (2 non è connesso a 3!)
  Ma esiste: 0 →(7)→ 1 →(2)→ 3
```

### 4.4 Quando Funziona?

L'euristica greedy per cammino minimo funziona solo in casi speciali. Per la soluzione ottima, usare **Dijkstra** (che è comunque greedy ma con una strategia diversa).

---

## 5. Confronto delle Tecniche

### 5.1 Tabella Riassuntiva

| Problema | Tecnica | Ottimalità | Complessità |
|----------|---------|------------|-------------|
| DivCoins | DP | Sì | O(n × sum) |
| Interval Scheduling | DP | Sì | O(n²) |
| Cammino Minimo (euristica) | Greedy | No | O(n²) |
| Cammino Minimo (Dijkstra) | Greedy | Sì | O((V+E) log V) |

### 5.2 Proprietà Richieste

| Tecnica | Proprietà Richiesta |
|---------|---------------------|
| Greedy | Greedy Choice Property |
| DP | Optimal Substructure + Overlapping Subproblems |

### 5.3 Greedy Choice Property

> Posso raggiungere l'ottimo globale facendo scelte localmente ottime, senza mai doverle riconsiderare.

**Vale per:** Dijkstra (archi non negativi), Interval Scheduling (non pesato), Huffman

**Non vale per:** Cammino minimo generico, Partition Problem, 0/1 Knapsack

---

## 6. Complessità Computazionale

### 6.1 DivCoins

- **Tempo:** O(n × target) = O(n × sum/2) - Pseudo-polinomiale
- **Spazio:** O(target)

### 6.2 Interval Scheduling

- **Tempo:** O(n²) per calcolare p[], O(n) per DP → O(n²)
- **Spazio:** O(n)

Ottimizzazione: Con binary search, p[] si calcola in O(n log n)

### 6.3 Euristica Cammino Minimo

- **Tempo:** O(V²) per ogni arco
- **Spazio:** O(V)

---

## 7. Errori Comuni

### 7.1 DivCoins: Iterazione in Avanti

```cpp
// ❌ SBAGLIATO: usa la stessa moneta più volte
for (int i = 0; i <= target - m; ++i)
    if (sommeParziali[i])
        sommeParziali[i + m] = true;

// ✅ CORRETTO: itera all'indietro
for (int i = target - m; i >= 0; --i)
    if (sommeParziali[i])
        sommeParziali[i + m] = true;
```

### 7.2 Scheduling: Non Ordinare

```cpp
// ❌ Algoritmo non funziona senza ordinamento
schedule(attivita);  // attivita non ordinato!

// ✅ Prima ordinare
sort(attivita.begin(), attivita.end());
schedule(attivita);
```

### 7.3 Greedy: Assumere Ottimalità

```cpp
// ❌ SBAGLIATO: assumere che greedy sia ottimo
cout << "Cammino ottimo: " << cammino << endl;

// ✅ CORRETTO: è solo un'euristica
cout << "Cammino trovato (non necessariamente ottimo): " << cammino << endl;
```

---

## 8. Esercizi Proposti

### Esercizio 1: DivCoins con Ricostruzione
Modifica DivCoins per restituire anche quali monete vanno in quale gruppo.

### Esercizio 2: Interval Scheduling Non Pesato
Implementa la versione greedy (ordina per fine, prendi il primo disponibile).

### Esercizio 3: 0/1 Knapsack
Implementa lo zaino 0/1 con programmazione dinamica.

### Esercizio 4: Dijkstra
Implementa l'algoritmo di Dijkstra per cammini minimi.

### Esercizio 5: Confronto Empirico
Esegui l'euristica greedy e confronta con Dijkstra su vari grafi. Conta quando trova l'ottimo.
