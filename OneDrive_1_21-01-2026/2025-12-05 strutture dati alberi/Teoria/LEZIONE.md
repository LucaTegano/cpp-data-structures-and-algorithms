# Lezione: Strutture Dati - Alberi Binari

## Indice
1. [Introduzione agli Alberi](#1-introduzione-agli-alberi)
2. [Alberi Binari: Definizione e Proprietà](#2-alberi-binari-definizione-e-proprietà)
3. [Rappresentazione in Memoria](#3-rappresentazione-in-memoria)
4. [La Classe Template AlberoB](#4-la-classe-template-alberob)
5. [Visite degli Alberi](#5-visite-degli-alberi)
6. [Algoritmi Ricorsivi sugli Alberi](#6-algoritmi-ricorsivi-sugli-alberi)
7. [Heap e Alberi Completi](#7-heap-e-alberi-completi)
8. [Complessità Computazionale](#8-complessità-computazionale)
9. [Errori Comuni](#9-errori-comuni)
10. [Esercizi Proposti](#10-esercizi-proposti)

---

## 1. Introduzione agli Alberi

### 1.1 Cos'è un Albero?

Un **albero** è una struttura dati gerarchica non lineare composta da **nodi** collegati da **archi**. Ha una struttura ricorsiva: ogni sottoalbero è a sua volta un albero.

```
                    ┌───┐
                    │ A │ ← Radice (root)
                    └─┬─┘
           ┌─────────┼─────────┐
         ┌─┴─┐     ┌─┴─┐     ┌─┴─┐
         │ B │     │ C │     │ D │ ← Nodi interni
         └─┬─┘     └───┘     └─┬─┘
        ┌──┴──┐              ┌─┴─┐
      ┌─┴─┐ ┌─┴─┐          ┌─┴─┐
      │ E │ │ F │          │ G │ ← Foglie (leaves)
      └───┘ └───┘          └───┘
```

### 1.2 Terminologia

| Termine | Definizione |
|---------|-------------|
| **Radice** | Unico nodo senza padre |
| **Foglia** | Nodo senza figli |
| **Nodo interno** | Nodo con almeno un figlio |
| **Padre** | Nodo direttamente sopra |
| **Figlio** | Nodo direttamente sotto |
| **Fratelli** | Nodi con lo stesso padre |
| **Antenato** | Nodo sul cammino verso la radice |
| **Discendente** | Nodo nel sottoalbero |
| **Profondità** | Distanza dalla radice (radice = 0 o 1) |
| **Altezza** | Massima profondità delle foglie |
| **Livello k** | Tutti i nodi a profondità k |
| **Sottoalbero** | Nodo + tutti i suoi discendenti |

### 1.3 Perché Usare gli Alberi?

| Struttura | Ricerca | Inserimento | Ordinata? | Uso tipico |
|-----------|---------|-------------|-----------|------------|
| Array | O(n) / O(log n) | O(n) | Opzionale | Accesso diretto |
| Lista | O(n) | O(1) | No | Inserimenti frequenti |
| **Albero BST** | O(log n) avg | O(log n) avg | Sì | Ricerca + ordine |
| **Heap** | O(1) min/max | O(log n) | Parziale | Code priorità |
| Hash Table | O(1) avg | O(1) avg | No | Lookup veloce |

---

## 2. Alberi Binari: Definizione e Proprietà

### 2.1 Definizione

Un **albero binario** è un albero in cui ogni nodo ha **al massimo 2 figli**, chiamati figlio sinistro e figlio destro.

```
Albero Binario:                    NON Binario (ternario):
       ┌───┐                            ┌───┐
       │ A │                            │ A │
       └─┬─┘                            └─┬─┘
      ┌──┴──┐                      ┌─────┼─────┐
    ┌─┴─┐ ┌─┴─┐                  ┌─┴─┐ ┌─┴─┐ ┌─┴─┐
    │ B │ │ C │                  │ B │ │ C │ │ D │
    └───┘ └───┘                  └───┘ └───┘ └───┘
```

### 2.2 Proprietà Matematiche

Per un albero binario con **n nodi** e **altezza h**:

| Proprietà | Formula | Note |
|-----------|---------|------|
| Nodi massimi | 2^(h+1) - 1 | Albero completo |
| Nodi minimi | h + 1 | Albero degenere (lista) |
| Foglie massime | 2^h | Ultimo livello pieno |
| Altezza minima | ⌊log₂(n)⌋ | Albero bilanciato |
| Altezza massima | n - 1 | Albero degenere |

### 2.3 Tipi di Alberi Binari

```
┌─────────────────────────────────────────────────────────────┐
│ ALBERO BINARIO COMPLETO                                      │
│ Tutti i livelli pieni tranne l'ultimo, riempito da sinistra │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│              ┌───┐                                           │
│              │ 1 │                                           │
│              └─┬─┘                                           │
│           ┌───┴───┐                                          │
│         ┌─┴─┐   ┌─┴─┐                                        │
│         │ 2 │   │ 3 │                                        │
│         └─┬─┘   └─┬─┘                                        │
│        ┌──┴─┐   ┌─┘                                          │
│      ┌─┴─┐┌─┴─┐┌─┴─┐                                         │
│      │ 4 ││ 5 ││ 6 │  ← Ultimo livello parziale, da sinistra │
│      └───┘└───┘└───┘                                         │
│                                                              │
└─────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────┐
│ ALBERO BINARIO PIENO (Full)                                  │
│ Ogni nodo ha 0 o 2 figli (mai 1 solo)                       │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│              ┌───┐                                           │
│              │ 1 │                                           │
│              └─┬─┘                                           │
│           ┌───┴───┐                                          │
│         ┌─┴─┐   ┌─┴─┐                                        │
│         │ 2 │   │ 3 │  ← Ogni nodo ha 0 o 2 figli            │
│         └─┬─┘   └───┘                                        │
│        ┌──┴──┐                                               │
│      ┌─┴─┐ ┌─┴─┐                                             │
│      │ 4 │ │ 5 │                                             │
│      └───┘ └───┘                                             │
│                                                              │
└─────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────┐
│ ALBERO BINARIO PERFETTO                                      │
│ Tutti i livelli completamente pieni                          │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│              ┌───┐                                           │
│              │ 1 │                                           │
│              └─┬─┘                                           │
│           ┌───┴───┐                                          │
│         ┌─┴─┐   ┌─┴─┐                                        │
│         │ 2 │   │ 3 │                                        │
│         └─┬─┘   └─┬─┘                                        │
│        ┌──┴──┐ ┌──┴──┐                                       │
│      ┌─┴─┐┌─┴─┐┌─┴─┐┌─┴─┐                                    │
│      │ 4 ││ 5 ││ 6 ││ 7 │  ← Tutti i livelli pieni          │
│      └───┘└───┘└───┘└───┘    n = 2^(h+1) - 1 = 7             │
│                                                              │
└─────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────┐
│ ALBERO DEGENERE (Degenerate/Skewed)                          │
│ Ogni nodo ha al massimo 1 figlio → equivalente a lista      │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│   ┌───┐                                                      │
│   │ 1 │                                                      │
│   └─┬─┘                                                      │
│     └─┐                                                      │
│     ┌─┴─┐                                                    │
│     │ 2 │         Altezza = n - 1                            │
│     └─┬─┘         Ricerca = O(n)                             │
│       └─┐         Spreco di struttura!                       │
│       ┌─┴─┐                                                  │
│       │ 3 │                                                  │
│       └───┘                                                  │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

---

## 3. Rappresentazione in Memoria

### 3.1 Rappresentazione con Puntatori (Dinamica)

Ogni nodo contiene il dato e puntatori ai figli (e opzionalmente al padre).

```cpp
template <class T>
struct SNodo {
    T vinfo;                    // Dato
    SNodo* ppadre;              // Puntatore al padre
    SNodo* pfiglio[2];          // pfiglio[0]=SIN, pfiglio[1]=DES
    
    SNodo(const T& inf) : vinfo(inf) {
        ppadre = pfiglio[SIN] = pfiglio[DES] = nullptr;
    }
    
    ~SNodo() {
        delete pfiglio[SIN];    // Distruzione ricorsiva!
        delete pfiglio[DES];
    }
};
```

```
Memoria:
┌──────────────────────────────────────────────────────────────┐
│                                                               │
│  ┌─────────────────┐                                          │
│  │ SNodo: 7        │ ← Radice                                 │
│  │ padre: nullptr  │                                          │
│  │ SIN: ─────────────┐                                        │
│  │ DES: ───────────────────┐                                  │
│  └─────────────────┘       │                                  │
│           │                │                                  │
│           ▼                ▼                                  │
│  ┌─────────────────┐  ┌─────────────────┐                     │
│  │ SNodo: 3        │  │ SNodo: 9        │                     │
│  │ padre: ↑        │  │ padre: ↑        │                     │
│  │ SIN: nullptr    │  │ SIN: nullptr    │                     │
│  │ DES: nullptr    │  │ DES: nullptr    │                     │
│  └─────────────────┘  └─────────────────┘                     │
│                                                               │
└──────────────────────────────────────────────────────────────┘
```

### 3.2 Rappresentazione Implicita (Array)

Per alberi **completi**, si può usare un array senza puntatori:

```
Albero:              Array: [7, 3, 9, 1, 5, 8, 10]
       7                    indice:  0  1  2  3  4  5  6
      / \
     3   9           Formule:
    / \ / \          - Figlio SX di i:  2*i + 1
   1  5 8  10        - Figlio DX di i:  2*i + 2
                     - Padre di i:      (i-1) / 2
```

**Vantaggi:** Nessun overhead di puntatori, cache-friendly
**Svantaggi:** Spreco di spazio per alberi non completi

---

## 4. La Classe Template AlberoB

### 4.1 Struttura Generale

```cpp
enum Direzione { SIN=0, DES=1 };  // Indici per i figli

template <class T>
class AlberoB {
protected:
    SNodo<T>* pradice;  // Puntatore alla radice
    
public:
    // Costruttori
    AlberoB();              // Albero vuoto
    AlberoB(const T& a);    // Albero con solo radice
    
    // Query
    bool nullo() const;     // true se vuoto
    bool foglia() const;    // true se radice senza figli
    const T& radice() const; // Valore della radice
    
    // Navigazione
    AlberoB<T> figlio(Direzione d) const;  // Sottoalbero figlio
    AlberoB<T> padre() const;               // Albero padre
    
    // Modifica
    void insFiglio(Direzione d, AlberoB& AC);  // Inserisce sottoalbero
    AlberoB<T> estraiFiglio(Direzione d);      // Estrae sottoalbero
    void modRadice(const T& a);                 // Modifica valore radice
    
    // Memoria
    AlberoB<T> copia() const;   // Deep copy
    void svuota();              // Dealloca tutti i nodi
    void annulla();             // Solo puntatore a null (no delete)
};
```

### 4.2 Costruttori

```cpp
// Costruttore vuoto
AlberoB() : pradice(0) {}

// Costruttore con radice
AlberoB(const T& a) {
    pradice = new SNodo<T>(a);
}

// Esempio di utilizzo:
AlberoB<int> vuoto;         // Albero vuoto
AlberoB<int> radice(7);     // Albero con solo nodo 7
```

### 4.3 Navigazione: figlio() e padre()

```cpp
AlberoB<T> figlio(Direzione d) const {
    assert(!nullo());           // Precondizione: albero non vuoto
    AlberoB<T> AC;
    AC.pradice = pradice->pfiglio[d];
    return AC;
}

AlberoB<T> padre() const {
    assert(!nullo());
    AlberoB<T> AC;
    AC.pradice = pradice->ppadre;
    return AC;
}
```

**Attenzione:** Questi metodi ritornano **viste** sullo stesso albero, NON copie!

```
Originale:         figlio(SIN) ritorna:
    ┌─7─┐              ┌─3─┐
   /     \             └───┘ ← Stesso nodo in memoria!
 ┌─3─┐ ┌─9─┐                   pradice punta allo stesso SNodo
 └───┘ └───┘
```

### 4.4 Inserimento: insFiglio()

```cpp
void insFiglio(Direzione d, AlberoB& AC) {
    assert(!nullo());           // Devo avere una radice
    assert(figlio(d).nullo()); // La posizione deve essere libera
    
    if (!AC.nullo()) {
        pradice->pfiglio[d] = AC.pradice;  // Collega figlio
        AC.pradice->ppadre = pradice;       // Collega padre
    }
}
```

**Esempio:**
```cpp
AlberoB<int> a(7);     // Radice 7
AlberoB<int> sx(3);    // Futuro figlio sinistro
AlberoB<int> dx(9);    // Futuro figlio destro

a.insFiglio(SIN, sx);  // 7 -> 3 (sinistro)
a.insFiglio(DES, dx);  // 7 -> 9 (destro)

// Risultato:
//     7
//    / \
//   3   9
```

### 4.5 Deep Copy: copia()

```cpp
AlberoB<T> copia() const {
    if (nullo()) return AlberoB<T>();  // Caso base
    
    AlberoB<T> AC(radice());           // Copia radice
    AlberoB<T> fs = figlio(SIN).copia();  // Copia ricorsiva SX
    AlberoB<T> fd = figlio(DES).copia();  // Copia ricorsiva DX
    AC.insFiglio(SIN, fs);
    AC.insFiglio(DES, fd);
    return AC;
}
```

### 4.6 Distruzione: svuota() vs annulla()

```cpp
void svuota() { 
    delete pradice;  // Chiama ~SNodo() → cancellazione ricorsiva!
    pradice = 0; 
}

void annulla() { 
    pradice = 0;     // Solo azzera il puntatore, NON dealloca
}
```

**Quando usare quale?**
- `svuota()`: Quando sei l'unico proprietario dell'albero
- `annulla()`: Quando l'albero è condiviso o gestito altrove

---

## 5. Visite degli Alberi

### 5.1 Visite in Profondità (DFS)

```cpp
// PREORDER: Radice - Sinistro - Destro
void preorder(const AlberoB<int>& a) {
    if (a.nullo()) return;
    cout << a.radice() << " ";   // Prima la radice
    preorder(a.figlio(SIN));      // Poi sinistro
    preorder(a.figlio(DES));      // Poi destro
}

// INORDER: Sinistro - Radice - Destro
void inorder(const AlberoB<int>& a) {
    if (a.nullo()) return;
    inorder(a.figlio(SIN));       // Prima sinistro
    cout << a.radice() << " ";   // Poi radice
    inorder(a.figlio(DES));       // Poi destro
}

// POSTORDER: Sinistro - Destro - Radice
void postorder(const AlberoB<int>& a) {
    if (a.nullo()) return;
    postorder(a.figlio(SIN));     // Prima sinistro
    postorder(a.figlio(DES));     // Poi destro
    cout << a.radice() << " ";   // Poi radice
}
```

**Esempio:**
```
        1
       / \
      2   3
     / \
    4   5

Preorder:   1, 2, 4, 5, 3
Inorder:    4, 2, 5, 1, 3
Postorder:  4, 5, 2, 3, 1
```

### 5.2 Visita in Ampiezza (BFS)

```cpp
void bfs(const AlberoB<int>& a) {
    if (a.nullo()) return;
    
    queue<AlberoB<int>> q;
    q.push(a);
    
    while (!q.empty()) {
        AlberoB<int> curr = q.front();
        q.pop();
        
        cout << curr.radice() << " ";
        
        if (!curr.figlio(SIN).nullo())
            q.push(curr.figlio(SIN));
        if (!curr.figlio(DES).nullo())
            q.push(curr.figlio(DES));
    }
}

// Risultato: 1, 2, 3, 4, 5 (livello per livello)
```

### 5.3 Confronto Visite

| Visita | Ordine | Uso tipico | Implementazione |
|--------|--------|------------|-----------------|
| Preorder | R-S-D | Serializzazione, copia | Ricorsione/Stack |
| Inorder | S-R-D | BST: ordine crescente | Ricorsione/Stack |
| Postorder | S-D-R | Calcolo altezza, delete | Ricorsione/Stack |
| BFS | Per livelli | Shortest path, livelli | Coda |

---

## 6. Algoritmi Ricorsivi sugli Alberi

### 6.1 Pattern Generale

```cpp
TipoRitorno funzione(const AlberoB<T>& a, parametri...) {
    // 1. CASO BASE: albero vuoto
    if (a.nullo()) 
        return valoreBase;
    
    // 2. CASO BASE OPZIONALE: foglia
    if (a.foglia()) 
        return elaboraFoglia(a.radice());
    
    // 3. CONTROLLO NODO CORRENTE (se serve)
    if (!proprietàLocale(a.radice()))
        return fallimento;
    
    // 4. PASSO RICORSIVO
    return combina(
        funzione(a.figlio(SIN), parametriModificati),
        funzione(a.figlio(DES), parametriModificati)
    );
}
```

### 6.2 Altezza dell'Albero

```cpp
int altezza(const AlberoB<int>& a) {
    if (a.nullo()) return -1;  // Convenzione: vuoto ha altezza -1
    
    return 1 + max(altezza(a.figlio(SIN)), 
                   altezza(a.figlio(DES)));
}
```

### 6.3 Conteggio Nodi

```cpp
int contaNodi(const AlberoB<int>& a) {
    if (a.nullo()) return 0;
    
    return 1 + contaNodi(a.figlio(SIN)) + contaNodi(a.figlio(DES));
}
```

### 6.4 Somma Valori

```cpp
int somma(const AlberoB<int>& a) {
    if (a.nullo()) return 0;
    
    return a.radice() + somma(a.figlio(SIN)) + somma(a.figlio(DES));
}
```

### 6.5 Verifica Proprietà: isHeap

```cpp
// Max-Heap: ogni nodo >= figli
bool isHeap(const AlberoB<int>& a) {
    if (a.nullo() || a.foglia())
        return true;
    
    // Controlla figlio destro
    if (!a.figlio(DES).nullo() && a.radice() < a.figlio(DES).radice())
        return false;
    
    // Controlla figlio sinistro
    if (!a.figlio(SIN).nullo() && a.radice() < a.figlio(SIN).radice())
        return false;
    
    // Ricorsione
    return isHeap(a.figlio(SIN)) && isHeap(a.figlio(DES));
}
```

### 6.6 Proprietà con Accumulatore: sommaPath

```cpp
// Ogni path radice-foglia forma un numero: 1-2-3 = 123
// Ritorna la somma di tutti questi numeri
int sommaPath(const AlberoB<int>& a) {
    return sommaPath(a, 0);  // Wrapper
}

int sommaPath(const AlberoB<int>& a, int somma_corrente) {
    if (a.nullo()) return 0;
    
    // Costruisci il numero "shiftando" a sinistra
    int nuova_somma = somma_corrente * 10 + a.radice();
    
    if (a.foglia())
        return nuova_somma;  // Ho completato un path
    
    return sommaPath(a.figlio(SIN), nuova_somma) +
           sommaPath(a.figlio(DES), nuova_somma);
}
```

**Trace:**
```
        2
       / \
      3   4
         /
        5

sommaPath(2, 0):
  nuova = 0*10 + 2 = 2
  
  sommaPath(3, 2):
    nuova = 2*10 + 3 = 23
    foglia → return 23
    
  sommaPath(4, 2):
    nuova = 2*10 + 4 = 24
    
    sommaPath(5, 24):
      nuova = 24*10 + 5 = 245
      foglia → return 245

Risultato: 23 + 245 = 268
```

### 6.7 Proprietà con Livello: pariEDispari

```cpp
// Livello pari → valore pari, livello dispari → valore dispari
bool pariEDispari(const AlberoB<int>& a) {
    return pariEDispari(a, 1);  // Radice al livello 1
}

bool pariEDispari(const AlberoB<int>& a, int livello) {
    if (a.nullo()) return true;
    
    // Controllo locale
    if ((livello % 2 == 0 && a.radice() % 2 != 0) ||
        (livello % 2 == 1 && a.radice() % 2 == 0))
        return false;
    
    return pariEDispari(a.figlio(SIN), livello + 1) &&
           pariEDispari(a.figlio(DES), livello + 1);
}
```

---

## 7. Heap e Alberi Completi

### 7.1 Definizione di Heap

Un **heap binario** è un albero binario completo che soddisfa la proprietà heap:
- **Max-Heap:** ogni nodo ≥ tutti i suoi discendenti
- **Min-Heap:** ogni nodo ≤ tutti i suoi discendenti

```
Max-Heap:            Min-Heap:
     100                  1
    /   \               /   \
   19    36            2     3
  /  \   /            / \   /
 17   3 25           5   6 4
```

### 7.2 Rappresentazione Array

Gli heap usano la rappresentazione implicita in array:

```cpp
// Heap: [100, 19, 36, 17, 3, 25]
//        0    1   2   3  4   5

int parent(int i) { return (i - 1) / 2; }
int left(int i)   { return 2 * i + 1; }
int right(int i)  { return 2 * i + 2; }
```

### 7.3 Costruzione da Array: vecToAlbero

```cpp
AlberoB<int> vecToAlbero(vector<int> vettore) {
    if (vettore.empty()) return AlberoB<int>();
    
    AlberoB<int> albero(vettore[0]);
    vector<AlberoB<int>> alberi;
    alberi.push_back(albero);
    
    for (int i = 1; i < vettore.size(); i++) {
        AlberoB<int> nuovo(vettore[i]);
        alberi.push_back(nuovo);
        
        int padre = (i - 1) / 2;
        if (i % 2 == 1)  // Figlio sinistro (indice dispari)
            alberi[padre].insFiglio(SIN, nuovo);
        else              // Figlio destro (indice pari)
            alberi[padre].insFiglio(DES, nuovo);
    }
    
    return albero;
}
```

---

## 8. Complessità Computazionale

### 8.1 Operazioni su AlberoB

| Operazione | Complessità | Note |
|------------|-------------|------|
| `nullo()` | O(1) | Controllo puntatore |
| `foglia()` | O(1) | Controllo figli |
| `radice()` | O(1) | Accesso diretto |
| `figlio(d)` | O(1) | Crea wrapper |
| `insFiglio()` | O(1) | Solo puntatori |
| `copia()` | O(n) | Visita tutti i nodi |
| `svuota()` | O(n) | Dealloca tutti i nodi |

### 8.2 Algoritmi Ricorsivi

| Algoritmo | Complessità | Spazio Stack |
|-----------|-------------|--------------|
| Altezza | O(n) | O(h) |
| Conta nodi | O(n) | O(h) |
| Somma | O(n) | O(h) |
| isHeap | O(n) | O(h) |
| copia | O(n) | O(h) |
| BFS | O(n) | O(w) dove w = larghezza max |

### 8.3 Ricorsione vs Iterazione

```
Ricorsione (stack):         Iterazione (coda per BFS):
┌───────────────────┐       ┌───────────────────┐
│ Spazio: O(altezza)│       │ Spazio: O(larghezza)│
│ Per alberi        │       │ Per alberi          │
│ bilanciati: O(log n)│     │ completi: O(n/2)    │
│ Per alberi        │       │ = O(n)              │
│ degeneri: O(n)    │       │                     │
└───────────────────┘       └───────────────────┘
```

---

## 9. Errori Comuni

### 9.1 Non Controllare nullo()

```cpp
// ❌ SBAGLIATO - crash se albero vuoto
int somma(const AlberoB<int>& a) {
    return a.radice() + somma(a.figlio(SIN)) + somma(a.figlio(DES));
}

// ✅ CORRETTO
int somma(const AlberoB<int>& a) {
    if (a.nullo()) return 0;  // Caso base!
    return a.radice() + somma(a.figlio(SIN)) + somma(a.figlio(DES));
}
```

### 9.2 Confondere Vista con Copia

```cpp
AlberoB<int> albero(10);
AlberoB<int> sx = albero.figlio(SIN);  // Vista, non copia!

// Se modifichi sx.insFiglio(), modifichi anche albero!

// Per copia indipendente:
AlberoB<int> sx_copia = albero.figlio(SIN).copia();
```

### 9.3 Memory Leak con annulla()

```cpp
AlberoB<int> a(10);
AlberoB<int> sx(5);
a.insFiglio(SIN, sx);

a.annulla();  // ⚠️ Memory leak! I nodi esistono ancora!

// Corretto:
a.svuota();   // Dealloca tutti i nodi
```

### 9.4 Distruzione Doppia

```cpp
AlberoB<int> a(10);
AlberoB<int> b = a.figlio(SIN);  // Vista sullo stesso nodo

a.svuota();  // Dealloca tutto
b.svuota();  // ⚠️ Double free! b.pradice punta a memoria già liberata
```

### 9.5 Ritorno per Valore vs Riferimento

```cpp
// Il metodo radice() ritorna const T&
const T& radice() const { return pradice->vinfo; }

// Posso usarlo così:
int x = a.radice();  // Copia del valore
const int& y = a.radice();  // Riferimento (più efficiente per oggetti grandi)
```

---

## 10. Esercizi Proposti

### Esercizio 1: Conta Foglie
```cpp
int contaFoglie(const AlberoB<int>& a);
// Ritorna il numero di foglie nell'albero
```

### Esercizio 2: Profondità Nodo
```cpp
int profondita(const AlberoB<int>& a, int valore);
// Ritorna la profondità del primo nodo con quel valore, -1 se non esiste
```

### Esercizio 3: Albero Specchiato
```cpp
AlberoB<int> specchia(const AlberoB<int>& a);
// Ritorna una copia dell'albero con sinistro e destro scambiati
```

### Esercizio 4: Cammino Massimo
```cpp
int camminoMax(const AlberoB<int>& a);
// Ritorna la somma massima di un cammino radice-foglia
```

### Esercizio 5: Albero BST Valido
```cpp
bool isBST(const AlberoB<int>& a);
// Ritorna true se l'albero è un BST valido
// Hint: passa min e max ammessi come parametri
```

### Esercizio 6: Livello con Somma Massima
```cpp
int livelloMaxSomma(const AlberoB<int>& a);
// Ritorna il numero del livello con somma massima (usa BFS)
```
