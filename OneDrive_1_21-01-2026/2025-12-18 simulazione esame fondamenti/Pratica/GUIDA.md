# Guida Pratica: Simulazione d'Esame - BFS e Backtracking Avanzato

## Indice
1. [Approfondimento Esercizio 2: Website BFS](#1-approfondimento-esercizio-2-website-bfs)
2. [Approfondimento Esercizio 3: Analisi Matrice Adiacenza](#2-approfondimento-esercizio-3-analisi-matrice-adiacenza)
3. [Approfondimento Esercizio 4: Cavallo sulla Scacchiera](#3-approfondimento-esercizio-4-cavallo-sulla-scacchiera)
4. [Pattern: Il Cavallo in Backtracking](#4-pattern-il-cavallo-in-backtracking)

---

## 1. Approfondimento Esercizio 2: Website BFS

### 1.1 Perché la BFS per livelli?
Se usassimo una BFS semplice, sapremmo che la pagina è raggiungibile ma non sapremmo a che distanza "minima". Processando i nodi a ondate (levelSize), garantiamo che `level` rifletta la distanza minima.

### 1.2 Importanza di `operator==`
In `Webpage.h`, l'operatore di uguaglianza è definito sul titolo:
```cpp
bool operator==(const Webpage& other) {
    return titolo == other.titolo;  
}
```
Questo permette a `std::find` di funzionare correttamente nel vettore `visitate`.

---

## 2. Approfondimento Esercizio 3: Analisi Matrice Adiacenza

### 2.1 Tabulazione dei Gradi
L'esercizio richiede di controllare una proprietà globale basata su gradi locali.
Il modo ottimale è:
```cpp
for (int i=0; i<n; ++i)
    for (int j=0; j<n; ++j)
        if (g(i, j)) {
            grado_uscente[i]++;
            grado_entrante[j]++;
        }
```
**Nota**: Per la matrice di adiacenza, scansionare per righe (`i` esterno, `j` interno) è fondamentale per le performance (cache locality).

---

## 3. Approfondimento Esercizio 4: Cavallo sulla Scacchiera

### 3.1 Rappresentazione delle Mosse
Il cavallo si muove di 2 celle in una direzione e 1 cella perpendicolare. Ci sono 8 combinazioni:
$(\pm 2, \pm 1)$ e $(\pm 1, \pm 2)$.

### 3.2 La funzione `remove` (Backtrack)
Nel backtracking del cavallo, quando si torna indietro non basta rimuovere la cella dalla `soluzione`, bisogna anche **ripristinare la `pos_corrente`**.
```cpp
void remove(Soluzione& sol) {
    sol.soluzione.pop_back();
    if (sol.soluzione.empty())
        sol.pos_corrente = sol.pos_iniziale;
    else
        sol.pos_corrente = sol.soluzione.back(); // La pos precedente è l'ultima rimasta
}
```

---

## 4. Pattern: Il Cavallo in Backtracking

### 4.1 Trace di esempio (Scacchiera 8x8)
Partenza: (0,0), Destinazione: (2,1)

**Esecuzione:**
1.  **Stato**: `pos = (0,0)`, `sol = []`.
2.  **Mossa 1**: Provo `{-2, -1}` → Fuori dai bordi ✗.
3.  ... molte mosse falliscono ...
4.  **Mossa 7**: Provo `{2, 1}` → `canAdd`?
    -   Bordi: (2,1) è in [0,7]? Sì.
    -   Proibite: (2,1) è nella lista? No.
    -   Già visitate: No.
    -   **Add**: `pos = (2,1)`, `sol = [(2,1)]`.
5.  **Check Completion**: `pos (2,1) == dest (2,1)`? **SÌ**.
6.  **Esito**: Successo in una sola mossa!

### 4.2 Ottimizzazione: Euristica di Warnsdorff
Se dovessimo visitare **tutta** la scacchiera (Knight's Tour), l'ordine delle mosse conta. L'euristica suggerisce di scegliere sempre la mossa che porta alla cella con il minor numero di mosse successive disponibili.
