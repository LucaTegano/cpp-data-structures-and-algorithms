# Lezione: Simulazione Esame - BFS su Grafi Reali, Proprietà di Rete e Cammino del Cavallo

## Indice
1. [Introduzione](#1-introduzione)
2. [Esercizio 2: Navigazione Web (BFS per Livelli)](#2-esercizio-2-navigazione-web-bfs-per-livelli)
3. [Esercizio 3: Analisi Strutturale di un Grafo](#3-esercizio-3-analisi-strutturale-di-un-grafo)
4. [Esercizio 4: Il Cammino del Cavallo (Backtracking)](#4-esercizio-4-il-cammino-del-cavallo-backtracking)
5. [Sintesi delle Tecniche d'Esame](#5-sintesi-delle-tecniche-desame)

---

## 1. Introduzione
Questa simulazione mette alla prova la capacità di modellare problemi reali (pagine web, scacchiere) utilizzando strutture dati classiche (grafi, code) e algoritmi di esplorazione (BFS, Backtracking).

---

## 2. Esercizio 2: Navigazione Web (BFS per Livelli)

### 2.1 Modellazione
Un sito web è modellato come un **grafo orientato** dove:
- **Nodi**: Oggetti `Webpage` (titolo, testo, lista di link).
- **Archi**: I puntatori `Webpage*` contenuti nel vettore `link`.

### 2.2 Algoritmo: BFS a Livelli
A differenza della BFS standard che trova solo la raggiungibilità, la **BFS per livelli** permette di calcolare la distanza minima (numero di click) dalla homepage.

**Pattern Chiave:**
```cpp
while (!queue.empty()) {
    int levelSize = queue.size(); // Blocca il numero di nodi al livello attuale
    for (int i = 0; i < levelSize; i++) {
        // Processa nodo...
        // Aggiungi figli alla coda...
    }
    level++; // Incrementa solo dopo aver svuotato l'intero livello
}
```

### 2.3 Gestione dei Cicli
In un sito web, la pagina A può puntare a B e B tornare ad A. È indispensabile un contenitore dei `visitati` per evitare loop infiniti.

---

## 3. Esercizio 3: Analisi Strutturale di un Grafo

### 3.1 Requisiti del Problema
Si deve verificare se un grafo $G$ soddisfa tre proprietà:
1. **Assenza di Autoarchi**: $i \neq j$ per ogni arco $(i, j)$.
2. **Parità degli Archi**: $|E|$ deve essere pari.
3. **Soglia di Grado**: Il grado uscente di ogni nodo deve essere $\le$ al numero di nodi con grado entrante $\le 1$.

### 3.2 Implementazione Efficiente
Invece di ricalcolare i gradi più volte, si esegue una **scansione singola** della matrice di adiacenza $O(N^2)$:
- Si popolano due array: `grado_entrante[N]` e `grado_uscente[N]`.
- Si conta il numero totale di archi.

Successivamente si verificano le proprietà in tempo $O(N)$.

---

## 4. Esercizio 4: Il Cammino del Cavallo (Backtracking)

### 4.1 Il Problema
Muovere un cavallo da una posizione $A$ a una $B$ su una scacchiera $8 \times 8$ evitando:
1. Celle "proibite" (ostacoli).
2. Celle già visitate (per evitare cicli).
3. Uscita dai bordi.

### 4.2 Modellazione del Cavallo
Le mosse del cavallo sono fisse (forma a "L"). Si rappresentano come un vettore di coppie:
```cpp
mosse = {{-2,-1}, {-2,1}, {-1,-2}, {-1,2}, {1,-2}, {1,2}, {2,-1}, {2,1}};
```

### 4.3 Logica del Backtracking
- **Stato**: `pos_corrente` + `soluzione` (vettore di celle visitate).
- **canAdd**: Verifica limiti scacchiera, ostacoli e duplicati.
- **isComplete**: `pos_corrente == destinazione`.

---

## 5. Sintesi delle Tecniche d'Esame

### 5.1 Confronto BFS vs Backtracking
| Caratteristica | BFS (Es. 2) | Backtracking (Es. 4) |
|------------|-------------|-------------------|
| **Scopo** | Cammino minimo, livelli | Esistenza di un cammino, tutte le soluzioni |
| **Struttura** | Coda (FIFO) | Pila / Ricorsione (LIFO) |
| **Memoria** | $O(V)$ per la coda | $O(N)$ per lo stack ricorsivo |
| **Ottimalità** | Garantisce il cammino minimo | Non garantisce l'ottimo (salvo varianti) |

### 5.2 Suggerimenti per la Prova
1. **Unsigned vs Signed**: Nel calcolo delle mosse (Es. 4), attenzione alle sottrazioni su `unsigned`. `0 - 2` diventa un numero enorme (overflow), il che è utile per il controllo bordi (`> 7`).
2. **Puntatori**: In `Webpage`, i link sono puntatori. Assicurarsi che gli oggetti puntati esistano sempre.
3. **Efficienza**: In `Website::find_webpage`, usare un `std::set` o un array di `bool` per i visitati è più veloce di `std::find` su un `vector`.
