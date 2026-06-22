# Guida Pratica: Il Problema delle N-Regine

## Indice
1. [Panoramica del Progetto](#1-panoramica-del-progetto)
2. [Analisi del Codice](#2-analisi-del-codice)
3. [Trace di Esecuzione Completa](#3-trace-di-esecuzione-completa)
4. [Debugging e Output](#4-debugging-e-output)
5. [Bug e Correzioni](#5-bug-e-correzioni)
6. [Modifiche per l'Esame](#6-modifiche-per-lesame)

---

## 1. Panoramica del Progetto

### 1.1 Struttura File

```
Pratica/
├── main.cpp        # Implementazione completa con versione iterativa e ricorsiva
└── NRegine.pdf     # Traccia dell'esercizio
```

### 1.2 Costanti e Tipi

```cpp
const unsigned regine = 4;          // Numero di regine (e dimensione scacchiera)
const unsigned MAX_VAL = regine - 1; // Colonna massima (3 per N=4)
const unsigned MIN_VAL = 0;          // Colonna minima

using Solution = vector<unsigned>;   // sol[i] = colonna della regina nella riga i
```

### 1.3 Rappresentazione della Soluzione

```
Soluzione: sol = [1, 3, 0, 2]

Interpretazione:
  sol[0] = 1  →  Regina riga 0 in colonna 1
  sol[1] = 3  →  Regina riga 1 in colonna 3
  sol[2] = 0  →  Regina riga 2 in colonna 0
  sol[3] = 2  →  Regina riga 3 in colonna 2

Scacchiera:
    0   1   2   3
  ┌───┬───┬───┬───┐
0 │   │ Q │   │   │
  ├───┼───┼───┼───┤
1 │   │   │   │ Q │
  ├───┼───┼───┼───┤
2 │ Q │   │   │   │
  ├───┼───┼───┼───┤
3 │   │   │ Q │   │
  └───┴───┴───┴───┘
```

---

## 2. Analisi del Codice

### 2.1 isComplete - Verifica Completezza

```cpp
bool isComplete(const Solution& sol) {
    cout << "Verifico se la soluzione è completa:" << (sol.size() == regine) << endl;
    return sol.size() == regine;
}
```

- **Quando è completa?** Quando abbiamo posizionato tutte le N regine
- `sol.size()` = numero di righe già riempite

### 2.2 add - Aggiungi Regina

```cpp
void add(unsigned colonna, Solution& sol) {
    cout << "Aggiorno la soluzione corrente. Aggiungo la regina " 
         << sol.size() << " alla colonna: " << colonna << endl;
    sol.push_back(colonna);
}
```

- Aggiunge la colonna in fondo al vettore
- La riga è implicita: `sol.size()` prima del push

### 2.3 canAdd - Verifica Validità (CRUCIALE)

```cpp
bool canAdd(unsigned colonna, const Solution& sol) {
    unsigned rigaDaRiempire = sol.size();  // Prossima riga

    cout << "nella riga " << rigaDaRiempire 
         << " provo con la regina in colonna" << colonna << endl;
    
    // Per ogni regina già posizionata
    for (unsigned i = 0; i < rigaDaRiempire; i++) {
        
        // 1. Stessa colonna?
        if (sol[i] == colonna) {
            cout << "non posso procedere perchè c'è già la regina" 
                 << i << " su questa colonna" << endl;
            return false;
        }
        
        // 2. Stessa diagonale?
        // |riga1 - riga2| == |colonna1 - colonna2|
        if (std::abs(static_cast<int>(i) - static_cast<int>(rigaDaRiempire))
            == std::abs(static_cast<int>(sol[i]) - static_cast<int>(colonna))) {
            cout << "non posso procedere perchè c'è già la regina" 
                 << i << " su questa diagonale" << endl;
            return false;
        }
    }
    
    cout << "ok, posso aggiungerla" << endl;
    return true;
}
```

**Spiegazione verifica diagonale:**

```
Regina in (i, sol[i]) e nuova regina in (rigaDaRiempire, colonna)

Stessa diagonale ↔ distanza verticale = distanza orizzontale

|i - rigaDaRiempire| == |sol[i] - colonna|

Esempio:
  Regina esistente: (0, 0)
  Provo:            (1, 1)
  
  |0 - 1| = 1
  |0 - 1| = 1
  1 == 1 → DIAGONALE! ✗
```

### 2.4 remove - Rimuovi Ultima Regina (Backtrack)

```cpp
void remove(unsigned& colonna, Solution& sol) {
    colonna = sol.back();  // Salva la colonna rimossa (per continuare da lì)
    sol.pop_back();
    cout << "rimuovo la regina nella colonna " << colonna 
         << " della riga " << sol.size() << endl;
}
```

**Nota:** `colonna` è passato per riferimento perché serve sapere quale colonna è stata rimossa per provare la successiva.

### 2.5 next - Prossima Colonna

```cpp
unsigned next(unsigned colonna) {
    cout << "provo con la colonna " << colonna + 1 << endl;
    return colonna + 1;
}
```

### 2.6 solve - Versione Iterativa

```cpp
bool solve(Solution& sol) {
    unsigned x = MIN_VAL;  // Colonna corrente
    bool stop = false, existsSolution = false;
    
    while (!stop) {
        if (x <= MAX_VAL) {
            // Ho ancora colonne da provare
            if (canAdd(x, sol)) {
                add(x, sol);
                
                if (isComplete(sol)) {
                    existsSolution = true;
                    stop = true;
                } else {
                    x = MIN_VAL;  // Nuova riga, riparti da colonna 0
                }
            } else {
                x = next(x);  // Prova prossima colonna
            }
        } else {
            // Finite le colonne → backtrack
            if (isEmpty(sol)) {
                existsSolution = false;
                stop = true;
            } else {
                remove(x, sol);  // Rimuovi ultima regina
                x = next(x);     // Prova colonna successiva
            }
        }
    }
    
    return existsSolution;
}
```

**Diagramma di flusso:**
```
┌─────────────────────────────────────────────────────────────┐
│                    SOLVE ITERATIVO                           │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│                 ┌──────────────┐                            │
│                 │ x = MIN_VAL  │                            │
│                 └──────┬───────┘                            │
│                        ↓                                     │
│             ┌──────────────────────┐                        │
│             │    x <= MAX_VAL?     │                        │
│             └──────┬───────┬───────┘                        │
│                  Sì│       │No                              │
│                    ↓       ↓                                │
│         ┌──────────────┐ ┌──────────────┐                   │
│         │ canAdd(x)?   │ │ sol vuota?   │                   │
│         └──┬───────┬───┘ └──┬───────┬───┘                   │
│          Sì│       │No    Sì│       │No                     │
│            ↓       ↓        ↓       ↓                       │
│     ┌──────────┐ ┌────┐ ┌──────┐ ┌────────┐                │
│     │ add(x)   │ │x++ │ │STOP  │ │remove()│                │
│     └────┬─────┘ └──┬─┘ │false │ │ x++    │                │
│          ↓          │   └──────┘ └────┬───┘                │
│   ┌────────────┐    │                 │                     │
│   │isComplete? │    │                 │                     │
│   └──┬─────┬───┘    │                 │                     │
│    Sì│     │No      │                 │                     │
│      ↓     ↓        │                 │                     │
│ ┌──────┐ ┌────┐     │                 │                     │
│ │STOP  │ │x=0 │     │                 │                     │
│ │true  │ └──┬─┘     │                 │                     │
│ └──────┘    │       │                 │                     │
│             └───────┴─────────────────┘                     │
│                    (loop)                                    │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

### 2.7 solverec - Versione Ricorsiva

```cpp
bool solverec(Solution& sol) {
    unsigned x = MIN_VAL;
    
    while (x <= MAX_VAL) {
        if (canAdd(x, sol)) {
            add(x, sol);
            
            if (isComplete(sol)) 
                return true;
            else if (solve(sol))  // ⚠️ BUG: dovrebbe essere solverec!
                return true;
            
            remove(x, sol);
        }
        x = next(x);
    }
    
    return false;
}
```

---

## 3. Trace di Esecuzione Completa

### 3.1 Esecuzione per N=4

```
solve([]):
  x=0: canAdd(0, [])? ok → add → sol=[0]
  
  solve([0]):
    x=0: canAdd(0, [0])? NO (colonna 0 usata)
    x=1: canAdd(1, [0])? NO (diagonale con riga 0)
    x=2: canAdd(2, [0])? ok → add → sol=[0,2]
    
    solve([0,2]):
      x=0: canAdd(0, [0,2])? NO (colonna 0 usata)
      x=1: canAdd(1, [0,2])? NO (diagonale con riga 1)
      x=2: canAdd(2, [0,2])? NO (colonna 2 usata)
      x=3: canAdd(3, [0,2])? NO (diagonale con riga 1)
      x>MAX → backtrack
    
    remove → sol=[0], x=3
    x=3: canAdd(3, [0])? ok → add → sol=[0,3]
    
    solve([0,3]):
      x=0: canAdd(0, [0,3])? NO (colonna)
      x=1: canAdd(1, [0,3])? ok → add → sol=[0,3,1]
      
      solve([0,3,1]):
        x=0: canAdd(0, [0,3,1])? NO (colonna)
        x=1: canAdd(1, [0,3,1])? NO (colonna)
        x=2: canAdd(2, [0,3,1])? NO (diagonale con riga 2)
        x=3: canAdd(3, [0,3,1])? NO (colonna)
        x>MAX → backtrack
      
      remove → sol=[0,3], x=2
      x=2: canAdd(2, [0,3])? NO (diagonale)
      x=3: canAdd(3, [0,3])? NO (colonna)
      x>MAX → backtrack
    
    remove → sol=[0], x>MAX → backtrack
  
  remove → sol=[], x=1
  x=1: canAdd(1, [])? ok → add → sol=[1]
  
  solve([1]):
    x=0: canAdd(0, [1])? NO (diagonale)
    x=1: canAdd(1, [1])? NO (colonna)
    x=2: canAdd(2, [1])? NO (diagonale)
    x=3: canAdd(3, [1])? ok → add → sol=[1,3]
    
    solve([1,3]):
      x=0: canAdd(0, [1,3])? ok → add → sol=[1,3,0]
      
      solve([1,3,0]):
        x=0: NO, x=1: NO, x=2: ok → add → sol=[1,3,0,2]
        
        isComplete([1,3,0,2])? YES! SOLUZIONE TROVATA!

Risultato: [1, 3, 0, 2]
```

### 3.2 Visualizzazione della Soluzione

```
    0   1   2   3
  ┌───┬───┬───┬───┐
0 │   │ Q │   │   │   ← sol[0] = 1
  ├───┼───┼───┼───┤
1 │   │   │   │ Q │   ← sol[1] = 3
  ├───┼───┼───┼───┤
2 │ Q │   │   │   │   ← sol[2] = 0
  ├───┼───┼───┼───┤
3 │   │   │ Q │   │   ← sol[3] = 2
  └───┴───┴───┴───┘

Verifica:
- Righe: tutte diverse ✓ (per costruzione)
- Colonne: 1,3,0,2 tutte diverse ✓
- Diagonali: nessuna condivisa ✓
```

---

## 4. Debugging e Output

### 4.1 Capire l'Output

Il codice stampa messaggi dettagliati. Esempio:

```
nella riga 0 provo con la regina in colonna0
ok, posso aggiungerla
Aggiorno la soluzione corrente. Aggiungo la regina 0 alla colonna: 0
Verifico se la soluzione è completa:0
nella riga 1 provo con la regina in colonna0
non posso procedere perchè c'è già la regina0 su questa colonna
provo con la colonna 1
nella riga 1 provo con la regina in colonna1
non posso procedere perchè c'è già la regina0 su questa diagonale
...
```

### 4.2 Interpretazione

| Messaggio | Significato |
|-----------|-------------|
| "provo con la regina in colonna X" | Tentativo di inserimento |
| "già la regina Y su questa colonna" | Conflitto colonna |
| "già la regina Y su questa diagonale" | Conflitto diagonale |
| "ok, posso aggiungerla" | Nessun conflitto |
| "Aggiungo la regina N alla colonna X" | Inserimento effettuato |
| "rimuovo la regina nella colonna X" | Backtrack |

---

## 5. Bug e Correzioni

### 5.1 Bug 1: Chiamata Errata nella Ricorsione

```cpp
// ❌ SBAGLIATO (linea 102)
else if (solve(sol))  // Chiama la versione iterativa!
    return true;

// ✅ CORRETTO
else if (solverec(sol))  // Deve chiamare se stessa
    return true;
```

### 5.2 Bug 2: Stampa Errata nel main

```cpp
// ❌ SBAGLIATO (linee 127-128)
if (solverec(solrec)) {
    for (int i = 0; i < sol.size(); i++)  // Usa 'sol' invece di 'solrec'!
        cout << i << " , " << sol[i] << endl;
}

// ✅ CORRETTO
if (solverec(solrec)) {
    for (int i = 0; i < solrec.size(); i++)  // Usa 'solrec'
        cout << i << " , " << solrec[i] << endl;
}
```

---

## 6. Modifiche per l'Esame

### 6.1 Trovare TUTTE le Soluzioni

```cpp
void findAllSolutions(Solution& sol, vector<Solution>& allSolutions) {
    unsigned x = MIN_VAL;
    
    while (x <= MAX_VAL) {
        if (canAdd(x, sol)) {
            add(x, sol);
            
            if (isComplete(sol)) {
                allSolutions.push_back(sol);  // Salva
                // NON ritornare! Continua
            } else {
                findAllSolutions(sol, allSolutions);
            }
            
            remove(x, sol);  // Backtrack SEMPRE
        }
        x = next(x);
    }
}

// Uso:
Solution sol;
vector<Solution> tutte;
findAllSolutions(sol, tutte);
cout << "Trovate " << tutte.size() << " soluzioni" << endl;
```

### 6.2 Contare le Soluzioni

```cpp
int countSolutions(Solution& sol) {
    if (isComplete(sol)) 
        return 1;
    
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

### 6.3 Stampa Scacchiera Grafica

```cpp
void stampaScacchiera(const Solution& sol) {
    unsigned n = sol.size();
    for (unsigned r = 0; r < n; r++) {
        for (unsigned c = 0; c < n; c++) {
            if (sol[r] == c)
                cout << "Q ";
            else
                cout << ". ";
        }
        cout << endl;
    }
}
```

### 6.4 Versione con Ottimizzazione O(1)

```cpp
vector<bool> colonneUsate(regine, false);
vector<bool> diag1(2*regine - 1, false);  // r - c + N - 1
vector<bool> diag2(2*regine - 1, false);  // r + c

bool canAddFast(unsigned col, const Solution& sol) {
    unsigned riga = sol.size();
    return !colonneUsate[col] 
        && !diag1[riga - col + regine - 1]
        && !diag2[riga + col];
}

void addFast(unsigned col, Solution& sol) {
    unsigned riga = sol.size();
    colonneUsate[col] = true;
    diag1[riga - col + regine - 1] = true;
    diag2[riga + col] = true;
    sol.push_back(col);
}

void removeFast(Solution& sol) {
    unsigned col = sol.back();
    unsigned riga = sol.size() - 1;
    colonneUsate[col] = false;
    diag1[riga - col + regine - 1] = false;
    diag2[riga + col] = false;
    sol.pop_back();
}
```

---

## Appendice: Riassunto Pattern Backtracking

```cpp
// Template generico backtracking
bool backtrack(Solution& sol) {
    if (isComplete(sol))
        return true;  // Oppure: salva soluzione e continua
    
    for (ogni scelta x nel dominio) {
        if (canAdd(x, sol)) {      // Pruning
            add(x, sol);            // Applica scelta
            
            if (backtrack(sol))
                return true;
            
            remove(x, sol);         // Annulla scelta (backtrack)
        }
    }
    
    return false;  // Nessuna soluzione trovata
}
```
