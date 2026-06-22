# Esempi Code Snippet per `Grafo` e `GrafoNonOrientato`

Questo documento contiene esempi di utilizzo per ogni funzione pubblica definita nelle classi `Grafo` (in `Grafo.h`) e `GrafoNonOrientato` (in `GrafoNonOrientato.h`).

## Classe `Grafo` (Grafo Orientato)

### 1. Costruttore: `Grafo(unsigned n)`
Inizializza un grafo con `n` nodi e 0 archi.
```cpp
// Crea un grafo orientato con 5 nodi (indici 0-4)
Grafo g(5);
```

### 2. Inserimento/Rimozione Arco: `operator()(unsigned i, unsigned j, bool b)`
Aggiunge (`b=true`) o rimuove (`b=false`) un arco orientato da `i` a `j`.
```cpp
// Aggiunge un arco dal nodo 0 al nodo 1
g(0, 1, true); 

// Rimuove l'arco dal nodo 0 al nodo 1
g(0, 1, false);
```

### 3. Verifica Esistenza Arco: `operator()(unsigned i, unsigned j) const`
Restituisce `true` se esiste l'arco da `i` a `j`, altrimenti `false`.
```cpp
if (g(0, 1)) {
    cout << "Esiste un arco da 0 a 1" << endl;
} else {
    cout << "NON esiste un arco da 0 a 1" << endl;
}
```

### 4. Numero di Nodi: `n() const`
Restituisce il numero di nodi del grafo.
```cpp
unsigned numeroNodi = g.n();
cout << "Nodi: " << numeroNodi << endl; // Stampa: Nodi: 5
```

### 5. Numero di Archi: `m() const`
Restituisce il numero di archi attualmente presenti.
```cpp
g(0, 1, true);
g(1, 2, true);
cout << "Archi: " << g.m() << endl; // Stampa: Archi: 2
```

### 6. Svuota: `svuota()`
Rimuove tutti gli archi dal grafo.
```cpp
g.svuota();
cout << "Archi dopo svuota: " << g.m() << endl; // Stampa: Archi dopo svuota: 0
```

### 7. Stampa: `stampa()`
Stampa a video la matrice di adiacenza (formato semplice).
```cpp
g.stampa();
// Output tipico: (0 0) = 0 (0 1) = 1 ...
```

---

## Classe `GrafoNonOrientato`

### 1. Costruttore: `GrafoNonOrientato(unsigned n)`
Inizializza un grafo non orientato con `n` nodi.
```cpp
// Crea un grafo non orientato con 10 nodi
GrafoNonOrientato gno(10);
```

### 2. Inserimento/Rimozione Arco: `operator()(unsigned i, unsigned j, bool b)`
Aggiunge o rimuove un arco **in entrambe le direzioni** (i->j e j->i).
```cpp
// Aggiunge arco tra nodo 2 e nodo 3 (e implicitamente 3->2)
gno(2, 3, true); 

// Verifica immediata:
// gno(2, 3) è true
// gno(3, 2) è true
```

### 3. Verifica Esistenza Arco: `operator()(unsigned i, unsigned j) const`
Verifica se esiste la connessione tra `i` e `j`. Funziona come per `Grafo`.
```cpp
bool connessi = gno(2, 3);
if (connessi) {
    cout << "Il nodo 2 e il nodo 3 sono collegati." << endl;
} else {
    cout << "NESSUN collegamento tra 2 e 3." << endl;
}
```

### 4. Metodi `n()`, `m()`, `svuota()`, `stampa()`
Questi metodi funzionano esattamente come nella classe base `Grafo`, ma operano nel contesto non orientato.

**Esempio `m()` (Conteggio Archi):**
Nota sull'implementazione: Quando aggiungi un arco non orientato (i,j), la variabile `vm` viene incrementata di 1.
```cpp
gno.svuota();
gno(0, 1, true); // Inserisce (0,1) e (1,0)
cout << "Archi: " << gno.m() << endl; // Stampa: Archi: 1
```

**Esempio `svuota()`:**
```cpp
gno.svuota(); // Rimuove tutte le connessioni simmetriche
```
