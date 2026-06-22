# Documentazione Classi `Grafo` e `GrafoNonOrientato`

Questo documento fornisce una guida completa e dettagliata all'utilizzo delle classi `Grafo` (in `Grafo.h`) e `GrafoNonOrientato` (in `GrafoNonOrientato.h`), incluse spiegazioni teoriche, complessità computazionale ed esempi di codice pronti all'uso.

---

## Indice
1. [Classe `Grafo` (Grafo Orientato)](#classe-grafo-grafo-orientato)
    - [Costruttore](#1-costruttore-grafounsigned-n)
    - [Gestione Archi](#2-inserimentorimozione-arco-operatorunsigned-i-unsigned-j-bool-b)
    - [Verifica Connessioni](#3-verifica-esistenza-arco-operatorunsigned-i-unsigned-j-const)
    - [Metodi di Utilità](#4-metodi-di-utilità-n-m-svuota-stampa)
2. [Classe `GrafoNonOrientato` (Grafo Non Orientato)](#classe-grafononorientato)
    - [Differenze Principali](#differenze-rispetto-a-grafo)
    - [Esempi Specifici](#esempi-di-utilizzo-grafononorientato)

---

## Classe `Grafo` (Grafo Orientato)

La classe `Grafo` implementa un **grafo diretto** (o orientato) utilizzando una **matrice di adiacenza**.
In un grafo orientato, l'arco $(i, j)$ è distinto dall'arco $(j, i)$.

### 1. Costruttore: `Grafo(unsigned n)`

Inizializza un grafo con `n` nodi e 0 archi. La matrice di adiacenza viene allocata dinamicamente.

- **Parametri**: `n` (numero di nodi, deve essere >= 1).
- **Complessità**: $O(n^2)$ (inizializzazione della matrice a `false`).

**Esempio:**
```cpp
#include "Grafo.h"

// Crea un grafo orientato con 5 nodi (indici da 0 a 4)
Grafo g(5);
```

### 2. Inserimento/Rimozione Arco: `operator()(unsigned i, unsigned j, bool b)`

Aggiunge (`b=true`) o rimuove (`b=false`) un arco orientato che parte dal nodo `i` e arriva al nodo `j`.

- **Controllo errori**: Verifica tramite `assert` che gli indici `i` e `j` siano validi.
- **Aggiornamento conteggio**: Il numero di archi (`m`) viene aggiornato solo se l'operazione modifica effettivamente lo stato del grafo.
- **Complessità**: $O(1)$.

**Esempio:**
```cpp
// Aggiunge un arco diretto dal nodo 0 al nodo 1 (0 -> 1)
g(0, 1, true); 

// Aggiunge un arco dal nodo 1 al nodo 2 (1 -> 2)
g(1, 2, true);

// Rimuove l'arco dal nodo 0 al nodo 1
g(0, 1, false);

// Tentare di rimuovere un arco inesistente non fa nulla e non cambia il conteggio m()
g(3, 4, false); 
```

### 3. Verifica Esistenza Arco: `operator()(unsigned i, unsigned j) const`

Restituisce `true` se esiste l'arco diretto da `i` a `j`, altrimenti `false`.

- **Complessità**: $O(1)$.

**Esempio:**
```cpp
if (g(0, 1)) {
    cout << "Esiste un arco da 0 a 1" << endl;
} else {
    cout << "NON esiste un arco da 0 a 1" << endl;
}
```

### 4. Metodi di Utilità: `n()`, `m()`, `svuota()`, `stampa()`

#### `n() const`
Restituisce il numero di nodi del grafo.
- **Complessità**: $O(1)$.

#### `m() const`
Restituisce il numero di archi attualmente presenti.
- **Complessità**: $O(1)$.

#### `svuota()`
Rimuove tutti gli archi dal grafo, resettando la matrice a `false` e il conteggio archi a 0.
- **Complessità**: $O(n^2)$ (deve scorrere tutta la matrice).

#### `stampa()`
Stampa a video la matrice di adiacenza o la lista degli archi (a seconda dell'implementazione interna, qui stampa le coppie `(i j) = valore`).

**Esempio Completo:**
```cpp
Grafo g(3);
g(0, 1, true);
g(1, 2, true);

cout << "Nodi: " << g.n() << endl; // Output: 3
cout << "Archi: " << g.m() << endl; // Output: 2

g.stampa(); 
// Output atteso (format dipendente da implementazione):
// (0 0) = 0 (0 1) = 1 (0 2) = 0 ...

g.svuota();
cout << "Archi dopo svuota: " << g.m() << endl; // Output: 0
```

---

## Classe `GrafoNonOrientato`

Definita in `GrafoNonOrientato.h`, questa classe eredita da `Grafo`. Rappresenta un grafo dove le connessioni sono simmetriche: se esiste un collegamento tra A e B, esiste implicitamente anche tra B e A.

### Differenze Rispetto a `Grafo`

1.  **Simmetria**: L'inserimento di un arco $(i, j)$ inserisce automaticamente anche $(j, i)$.
2.  **Ereditarietà**: Utilizza l'ereditarietà `protected` o `public` (nell'implementazione corrente eredita `protected` ma espone i metodi necessari) per riutilizzare la struttura dati della classe base.

### Esempi di Utilizzo `GrafoNonOrientato`

#### 1. Costruttore
```cpp
#include "GrafoNonOrientato.h"

// Crea un grafo non orientato con 10 nodi
GrafoNonOrientato gno(10);
```

#### 2. Inserimento Arco Simmetrico
Quando si imposta a `true` l'arco tra `i` e `j`, la classe aggiorna entrambe le celle della matrice: `[i][j]` e `[j][i]`.

```cpp
// Collega il nodo 2 e il nodo 3
gno(2, 3, true); 

// Verifiche:
if (gno(2, 3) && gno(3, 2)) {
    cout << "Il collegamento è bidirezionale!" << endl;
}
```

#### 3. Conteggio Archi (`m()`)
**Nota Importante**: Nell'implementazione corrente, quando si aggiunge un arco non orientato `(u, v)`, la variabile membro `vm` (ereditata da `Grafo`) viene incrementata di 1, anche se fisicamente vengono settati due booleani nella matrice. Questo rappresenta correttamente il numero di "lati" del grafo non orientato.

```cpp
gno.svuota();
gno(0, 1, true); // Crea connessione 0-1 (e 1-0)
cout << "Numero archi: " << gno.m() << endl; // Stampa: 1
```

#### 4. Svuotamento
```cpp
gno.svuota(); // Rimuove tutte le connessioni e resetta m() a 0
```
