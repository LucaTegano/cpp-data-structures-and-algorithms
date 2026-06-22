# Lezione: Il Problema delle N-Regine (Backtracking)

## Indice
1. [Introduzione al Problema](#1-introduzione-al-problema)
2. [Backtracking: Teoria](#2-backtracking-teoria)
3. [Rappresentazione della Soluzione](#3-rappresentazione-della-soluzione)
4. [Algoritmo Risolutivo](#4-algoritmo-risolutivo)
5. [Versione Iterativa vs Ricorsiva](#5-versione-iterativa-vs-ricorsiva)
6. [Ottimizzazioni e Pruning](#6-ottimizzazioni-e-pruning)
7. [Complessità Computazionale](#7-complessità-computazionale)
8. [Varianti del Problema](#8-varianti-del-problema)
9. [Errori Comuni](#9-errori-comuni)
10. [Esercizi Proposti](#10-esercizi-proposti)

---

## 1. Introduzione al Problema

### 1.1 Descrizione

Il **problema delle N-Regine** consiste nel posizionare N regine su una scacchiera N×N in modo che nessuna regina possa attaccarne un'altra.

**Regola degli scacchi:** Una regina può attaccare qualsiasi pezzo sulla stessa riga, colonna o diagonale.

```
┌─────────────────────────────────────────────────────────────┐
│ SOLUZIONE PER 4 REGINE                                       │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│     0   1   2   3                                            │
│   ┌───┬───┬───┬───┐                                          │
│ 0 │   │ Q │   │   │  Q in (0,1)                             │
│   ├───┼───┼───┼───┤                                          │
│ 1 │   │   │   │ Q │  Q in (1,3)                             │
│   ├───┼───┼───┼───┤                                          │
│ 2 │ Q │   │   │   │  Q in (2,0)                             │
│   ├───┼───┼───┼───┤                                          │
│ 3 │   │   │ Q │   │  Q in (3,2)                             │
│   └───┴───┴───┴───┘                                          │
│                                                              │
│ Nessuna regina attacca le altre:                            │
│ - Righe diverse: ✓ (0,1,2,3)                                │
│ - Colonne diverse: ✓ (1,3,0,2)                              │
│ - Diagonali diverse: ✓                                       │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

### 1.2 Vincoli del Problema

| Vincolo | Spiegazione |
|---------|-------------|
| Una regina per riga | Ogni riga deve contenere esattamente una regina |
| Una regina per colonna | Ogni colonna deve contenere esattamente una regina |
| Nessuna diagonale condivisa | Due regine non possono essere sulla stessa diagonale |

### 1.3 Numero di Soluzioni

| N | Soluzioni | Note |
|---|-----------|------|
| 1 | 1 | Banale |
| 2 | 0 | Impossibile |
| 3 | 0 | Impossibile |
| 4 | 2 | Prima soluzione non banale |
| 5 | 10 | |
| 6 | 4 | |
| 7 | 40 | |
| 8 | 92 | Problema classico degli scacchi |
| 12 | 14,200 | |
| 15 | 2,279,184 | |

---

## 2. Backtracking: Teoria

### 2.1 Cos'è il Backtracking?

Il **backtracking** è una tecnica algoritmica che esplora sistematicamente lo spazio delle soluzioni, "tornando indietro" quando si raggiunge un vicolo cieco.

```
┌─────────────────────────────────────────────────────────────┐
│ ALBERO DI RICERCA (N=4, parziale)                           │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│                         []                                   │
│           ┌──────┬──────┼──────┬──────┐                     │
│          [0]   [1]    [2]    [3]                            │
│           ↓     ↓      ↓      ↓                             │
│          ...   ...    ...    ...                            │
│                 │                                            │
│     ┌───┬───┬───┼───┐                                       │
│    [1,0][1,1][1,2][1,3]                                     │
│     ✗     ✗    ↓    ✗                                       │
│           Diag      Colonna                                  │
│                │                                             │
│         [1,2,0] → continua...                               │
│                                                              │
│ Legenda:                                                     │
│   [c₀, c₁, ...] = colonne delle regine nelle righe 0,1,...  │
│   ✗ = pruning (ramo tagliato)                               │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

### 2.2 Schema Generale del Backtracking

```
BACKTRACKING(soluzione_parziale):
    SE soluzione_parziale è completa:
        RITORNA soluzione_parziale
    
    PER OGNI scelta possibile:
        SE scelta è valida (pruning):
            Aggiungi scelta alla soluzione
            risultato = BACKTRACKING(soluzione_parziale)
            SE risultato è valido:
                RITORNA risultato
            Rimuovi scelta dalla soluzione (BACKTRACK!)
    
    RITORNA fallimento
```

### 2.3 Pattern Try-Check-Undo

```cpp
for (ogni scelta x) {
    if (canAdd(x, sol)) {      // CHECK: è valida?
        add(x, sol);            // TRY: prova la scelta
        
        if (isComplete(sol))
            return true;        // Soluzione trovata!
        
        if (solve(sol))
            return true;        // Ricorsione ha trovato
        
        remove(x, sol);         // UNDO: backtrack
    }
}
return false;  // Nessuna scelta valida
```

---

## 3. Rappresentazione della Soluzione

### 3.1 Rappresentazione Compatta

Invece di una matrice N×N, usiamo un **vettore di N elementi**:

```cpp
using Solution = vector<unsigned>;
// sol[i] = c significa: la regina della riga i è nella colonna c
```

**Vantaggi:**
- Spazio O(N) invece di O(N²)
- Una regina per riga è **garantita** dalla struttura
- Facilita il backtracking (push_back/pop_back)

### 3.2 Esempio

```
Scacchiera 4×4:          Vettore:
    0   1   2   3        sol = [1, 3, 0, 2]
  ┌───┬───┬───┬───┐
0 │   │ Q │   │   │      sol[0] = 1  →  Riga 0, Colonna 1
  ├───┼───┼───┼───┤
1 │   │   │   │ Q │      sol[1] = 3  →  Riga 1, Colonna 3
  ├───┼───┼───┼───┤
2 │ Q │   │   │   │      sol[2] = 0  →  Riga 2, Colonna 0
  ├───┼───┼───┼───┤
3 │   │   │ Q │   │      sol[3] = 2  →  Riga 3, Colonna 2
  └───┴───┴───┴───┘
```

### 3.3 Interpretazione Durante la Costruzione

```cpp
// sol.size() = numero di regine già posizionate
// sol.size() = prossima riga da riempire

sol = [1]         // 1 regina, prossima riga = 1
sol = [1, 3]      // 2 regine, prossima riga = 2
sol = [1, 3, 0]   // 3 regine, prossima riga = 3
sol = [1, 3, 0, 2] // 4 regine = COMPLETA!
```

---

## 4. Algoritmo Risolutivo

### 4.1 Funzione isComplete

```cpp
bool isComplete(const Solution& sol) {
    return sol.size() == regine;  // Tutte le N regine posizionate
}
```

### 4.2 Funzione canAdd (Pruning)

Questa è la funzione più importante: decide se possiamo mettere una regina in una certa colonna senza conflitti.

```cpp
bool canAdd(unsigned colonna, const Solution& sol) {
    unsigned rigaDaRiempire = sol.size();
    
    // Controlla ogni regina già posizionata
    for (unsigned i = 0; i < rigaDaRiempire; i++) {
        
        // 1. Stessa colonna?
        if (sol[i] == colonna) 
            return false;
        
        // 2. Stessa diagonale?
        // Due celle (r1,c1) e (r2,c2) sono sulla stessa diagonale se:
        // |r1 - r2| == |c1 - c2|
        if (abs((int)i - (int)rigaDaRiempire) == 
            abs((int)sol[i] - (int)colonna))
            return false;
    }
    
    return true;  // Nessun conflitto!
}
```

### 4.3 Verifica Diagonale: Spiegazione

```
Due celle sono sulla stessa diagonale se la distanza
orizzontale è uguale alla distanza verticale.

Esempio:
  Regina esistente: (0, 1)
  Nuova posizione:  (2, 3)
  
  |0 - 2| = 2  (distanza verticale)
  |1 - 3| = 2  (distanza orizzontale)
  
  2 == 2 → STESSA DIAGONALE! ✗

Visualizzazione:
    0   1   2   3
  ┌───┬───┬───┬───┐
0 │   │ Q │ ↘ │   │
  ├───┼───┼───┼───┤
1 │   │   │   │ ↘ │
  ├───┼───┼───┼───┤
2 │   │   │   │ ✗ │  ← Conflitto diagonale!
  └───┴───┴───┴───┘
```

### 4.4 Funzioni Ausiliarie

```cpp
void add(unsigned colonna, Solution& sol) {
    sol.push_back(colonna);  // Aggiungi regina
}

void remove(unsigned& colonna, Solution& sol) {
    colonna = sol.back();    // Ricorda quale colonna stiamo rimuovendo
    sol.pop_back();          // Rimuovi ultima regina
}

unsigned next(unsigned colonna) {
    return colonna + 1;      // Prossima colonna da provare
}
```

---

## 5. Versione Iterativa vs Ricorsiva

### 5.1 Versione Ricorsiva

```cpp
bool solverec(Solution& sol) {
    unsigned x = MIN_VAL;  // Parti dalla colonna 0
    
    while (x <= MAX_VAL) {
        if (canAdd(x, sol)) {
            add(x, sol);
            
            if (isComplete(sol)) 
                return true;
            
            if (solverec(sol))  // Ricorsione
                return true;
            
            remove(x, sol);     // Backtrack
        }
        x = next(x);
    }
    
    return false;  // Nessuna colonna valida
}
```

**Flusso:**
```
solverec([]):
  x=0: canAdd? sì → add → sol=[0]
    solverec([0]):
      x=0: canAdd? no (stessa colonna)
      x=1: canAdd? no (diagonale)
      x=2: canAdd? sì → add → sol=[0,2]
        solverec([0,2]):
          ... continua ...
```

### 5.2 Versione Iterativa

```cpp
bool solve(Solution& sol) {
    unsigned x = MIN_VAL;
    bool stop = false, existsSolution = false;
    
    while (!stop) {
        if (x <= MAX_VAL) {
            if (canAdd(x, sol)) {
                add(x, sol);
                
                if (isComplete(sol)) {
                    existsSolution = true;
                    stop = true;
                } else {
                    x = MIN_VAL;  // Ricomincia da colonna 0 per nuova riga
                }
            } else {
                x = next(x);  // Prova prossima colonna
            }
        } else {
            // Backtrack: ho finito le colonne
            if (isEmpty(sol)) {
                existsSolution = false;
                stop = true;
            } else {
                remove(x, sol);  // Rimuovi ultima regina
                x = next(x);     // Riprova dalla colonna successiva
            }
        }
    }
    
    return existsSolution;
}
```

### 5.3 Confronto

| Aspetto | Ricorsiva | Iterativa |
|---------|-----------|-----------|
| Leggibilità | Più chiara | Più complessa |
| Stack | Implicito (call stack) | Esplicito (vettore sol) |
| Rischio overflow | Sì, per N grande | No |
| Performance | Leggermente peggiore | Leggermente migliore |

---

## 6. Ottimizzazioni e Pruning

### 6.1 Pruning Automatico

La funzione `canAdd` implementa il **pruning**: quando restituisce `false`, l'intero sottoalbero viene ignorato.

```
Senza pruning:              Con pruning:
        []                        []
    /  |  |  \               /  |  |  \
  [0] [1] [2] [3]          [0] [1] [2] [3]
  /|\  /|\  /|\ /|\          ↓   ↓   ↓   ↓
 ... ... ... ...           [0,2][1,3][2,0][3,1]
                              ↓    ↓    ↓    ↓
8⁴ = 4096 nodi            Solo rami validi!
```

### 6.2 Ottimizzazione: Controllo Colonne O(1)

Usa un array booleano per tracciare le colonne occupate:

```cpp
bool colonneUsate[N] = {false};

bool canAddOptimized(unsigned colonna, const Solution& sol) {
    if (colonneUsate[colonna]) return false;
    
    // Controlla solo diagonali
    unsigned riga = sol.size();
    for (unsigned i = 0; i < riga; i++) {
        if (abs((int)i - (int)riga) == abs((int)sol[i] - (int)colonna))
            return false;
    }
    return true;
}

void addOptimized(unsigned colonna, Solution& sol) {
    colonneUsate[colonna] = true;
    sol.push_back(colonna);
}

void removeOptimized(Solution& sol) {
    unsigned colonna = sol.back();
    colonneUsate[colonna] = false;
    sol.pop_back();
}
```

### 6.3 Ottimizzazione: Controllo Diagonali O(1)

```cpp
// Ci sono 2N-1 diagonali in ogni direzione
bool diagPrincipale[2*N - 1] = {false};  // r - c + N - 1
bool diagSecondaria[2*N - 1] = {false};  // r + c

bool canAddUltraFast(unsigned col, const Solution& sol) {
    unsigned riga = sol.size();
    
    return !colonneUsate[col] 
        && !diagPrincipale[riga - col + N - 1]
        && !diagSecondaria[riga + col];
}
```

---

## 7. Complessità Computazionale

### 7.1 Caso Peggiore

- **Senza pruning:** O(N^N) - ogni riga ha N scelte
- **Con pruning:** Molto meglio in pratica, ma ancora esponenziale

### 7.2 Analisi dello Spazio

| Componente | Spazio |
|------------|--------|
| Vettore sol | O(N) |
| Stack ricorsivo | O(N) |
| Array ottimizzazione | O(N) |
| **Totale** | O(N) |

### 7.3 Numero di Nodi Visitati (Sperimentale)

| N | Nodi senza pruning | Nodi con pruning |
|---|-------------------|------------------|
| 4 | 256 | ~60 |
| 8 | 16,777,216 | ~15,000 |
| 12 | ~8.9 × 10¹² | ~850,000 |

---

## 8. Varianti del Problema

### 8.1 Trovare TUTTE le Soluzioni

```cpp
void findAll(Solution& sol, vector<Solution>& allSolutions) {
    unsigned x = MIN_VAL;
    
    while (x <= MAX_VAL) {
        if (canAdd(x, sol)) {
            add(x, sol);
            
            if (isComplete(sol)) {
                allSolutions.push_back(sol);  // Salva soluzione
                // NON ritornare! Continua a cercare
            } else {
                findAll(sol, allSolutions);
            }
            
            remove(x, sol);  // Backtrack SEMPRE
        }
        x = next(x);
    }
}
```

### 8.2 Contare le Soluzioni

```cpp
int countSolutions(Solution& sol) {
    if (isComplete(sol)) return 1;
    
    int count = 0;
    for (unsigned x = MIN_VAL; x <= MAX_VAL; x++) {
        if (canAdd(x, sol)) {
            add(x, sol);
            count += countSolutions(sol);
            remove(x, sol);
        }
    }
    return count;
}
```

### 8.3 N-Regine su Scacchiera Toroidale

La scacchiera "si avvolge" ai bordi (come Pac-Man).

---

## 9. Errori Comuni

### 9.1 Cast Mancante in abs()

```cpp
// ❌ SBAGLIATO: unsigned - unsigned può dare overflow
if (abs(i - rigaDaRiempire) == abs(sol[i] - colonna))

// ✅ CORRETTO: cast a int
if (abs((int)i - (int)rigaDaRiempire) == 
    abs((int)sol[i] - (int)colonna))
```

### 9.2 Dimenticare il Backtrack

```cpp
// ❌ SBAGLIATO: non rimuove se la ricorsione fallisce
if (canAdd(x, sol)) {
    add(x, sol);
    if (solve(sol)) return true;
    // Manca: remove(x, sol);
}

// ✅ CORRETTO
if (canAdd(x, sol)) {
    add(x, sol);
    if (solve(sol)) return true;
    remove(x, sol);  // FONDAMENTALE!
}
```

### 9.3 Ritornare Troppo Presto in findAll

```cpp
// ❌ SBAGLIATO: trova solo la prima soluzione
if (isComplete(sol)) {
    allSolutions.push_back(sol);
    return;  // SBAGLIATO!
}

// ✅ CORRETTO: non ritornare, continua il backtrack
if (isComplete(sol)) {
    allSolutions.push_back(sol);
    // NON ritornare, lascia che il loop faccia backtrack
}
```

### 9.4 Bug nel Codice Originale

```cpp
// Nel main.cpp, linea 102:
else if (solve(sol))  // ❌ Dovrebbe essere solverec!
    return true;

// Corretto:
else if (solverec(sol))
    return true;
```

---

## 10. Esercizi Proposti

### Esercizio 1: Conta Soluzioni
Modifica l'algoritmo per contare quante soluzioni esistono per N=8.

### Esercizio 2: Stampa Scacchiera
Scrivi una funzione che, data una soluzione, stampa la scacchiera in formato grafico.

```cpp
void stampaScacchiera(const Solution& sol);
// Output per [1,3,0,2]:
// . Q . .
// . . . Q
// Q . . .
// . . Q .
```

### Esercizio 3: N-Torri
Adatta l'algoritmo per il problema delle N-Torri (le torri attaccano solo in riga e colonna, non in diagonale).

### Esercizio 4: Prima Soluzione Lessicograficamente
Modifica l'algoritmo per trovare la soluzione "più piccola" in ordine lessicografico.

### Esercizio 5: Regine con Ostacoli
La scacchiera ha alcune celle "bloccate" dove non si può mettere una regina. Modifica `canAdd` per gestire questa variante.
