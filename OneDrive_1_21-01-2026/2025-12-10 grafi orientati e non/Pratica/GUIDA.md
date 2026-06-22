# Guida Pratica: Grafi Orientati e Non Orientati

## Indice
1. [Panoramica del Progetto](#1-panoramica-del-progetto)
2. [Analisi di Grafo.h](#2-analisi-di-grafoh)
3. [Analisi di GrafoNonOrientato.h](#3-analisi-di-grafononorientatoh)
4. [Esercizi Risolti: main.cpp](#4-esercizi-risolti-maincpp)
5. [Trace di Esecuzione](#5-trace-di-esecuzione)
6. [Pattern Ricorrenti](#6-pattern-ricorrenti)

---

## 1. Panoramica del Progetto

### 1.1 Struttura File

```
Pratica/
├── Grafo.h              # Classe Grafo (orientato) con matrice di adiacenza
├── GrafoNonOrientato.h  # Classe derivata per grafi non orientati
└── main.cpp             # 8 esercizi risolti sui grafi
```

### 1.2 Gerarchia delle Classi

```
┌─────────────────────────────────────────────────────────────┐
│                         Grafo                                │
│ (Grafo Orientato - arco (i,j) ≠ (j,i))                      │
├─────────────────────────────────────────────────────────────┤
│ protected:                                                   │
│   unsigned vn, vm                                            │
│   vector<vector<bool>> archi                                 │
│ public:                                                      │
│   Grafo(unsigned n)                                          │
│   void operator()(i, j, bool)  // inserisci/rimuovi arco    │
│   bool operator()(i, j) const  // verifica arco             │
│   unsigned n(), m()                                          │
│   void svuota(), stampa()                                    │
└─────────────────────────────────────────────────────────────┘
                              ▲
                              │ protected inheritance
                              │
┌─────────────────────────────────────────────────────────────┐
│                    GrafoNonOrientato                         │
│ (arco (i,j) == (j,i) - matrice simmetrica)                  │
├─────────────────────────────────────────────────────────────┤
│ public:                                                      │
│   void operator()(i, j, bool) // ridefinito per simmetria   │
│   // Espone n(), m(), operator()const, svuota(), stampa()   │
└─────────────────────────────────────────────────────────────┘
```

---

## 2. Analisi di Grafo.h

### 2.1 Struttura Dati

```cpp
using boolVec = std::vector<bool>;  // Alias per leggibilità

class Grafo {
protected:
    unsigned vn = 0, vm = 0;        // Numero nodi e archi
    std::vector<boolVec> archi;     // Matrice di adiacenza n×n
    
    // Inizializzazione matrice
    void init(unsigned n) {
        this->vn = n;
        this->vm = 0;
        this->archi = std::vector<boolVec>(n);
        for (unsigned i = 0; i < n; i++)
            this->archi[i] = boolVec(n, false);  // Tutto false
    }
};
```

**Visualizzazione memoria:**
```
Grafo g(4) con archi: 0→1, 0→2, 2→3

archi = vector<vector<bool>>:
┌─────────────────────────────────────┐
│ archi[0] = [false, true, true, false]   │  0 → 1, 0 → 2
│ archi[1] = [false, false, false, false] │
│ archi[2] = [false, false, false, true]  │  2 → 3
│ archi[3] = [false, false, false, false] │
└─────────────────────────────────────┘

Rappresentazione grafica:
    0 ───► 1
    │
    ▼
    2 ───► 3
```

### 2.2 Costruttore

```cpp
Grafo(unsigned n) {
    assert(n >= 1);      // Almeno un nodo
    this->init(n);       // Inizializza matrice n×n
}
```

**Complessità:** O(n²) per allocare e inizializzare la matrice.

### 2.3 operator() - Modifica Archi

```cpp
void operator()(unsigned i, unsigned j, bool b) {
    assert(i >= 0 && i < this->n() && j >= 0 && j < this->n());
    
    bool esisteArco = this->archi[i][j];
    
    // Aggiorna solo se lo stato cambia
    if ((!esisteArco && b) || (esisteArco && !b)) {
        this->archi[i][j] = b;
        if (b) vm++;     // Nuovo arco
        else vm--;       // Arco rimosso
    }
}
```

**Logica della condizione:**
```
esisteArco | b (voglio inserire?) | Azione
-----------|---------------------|------------------
   false   |       true          | Inserisci, vm++
   false   |       false         | Nulla (già assente)
   true    |       true          | Nulla (già presente)
   true    |       false         | Rimuovi, vm--
```

**Uso:**
```cpp
Grafo g(5);
g(0, 1, true);   // Inserisce arco 0 → 1
g(0, 1, true);   // Nulla (già esiste)
g(0, 1, false);  // Rimuove arco 0 → 1
```

### 2.4 operator() - Verifica Archi

```cpp
bool operator()(unsigned i, unsigned j) const {
    assert(i >= 0 && i < this->n() && j >= 0 && j < this->n());
    return this->archi[i][j];
}
```

**Uso:**
```cpp
if (g(0, 1)) {
    cout << "Esiste arco da 0 a 1" << endl;
}
```

### 2.5 Altri Metodi

```cpp
unsigned n() const { return vn; }  // Numero nodi
unsigned m() const { return vm; }  // Numero archi

void svuota() {
    for (unsigned i = 0; i < this->n(); i++)
        for (unsigned j = 0; j < this->n(); j++)
            archi[i][j] = false;
    vm = 0;
}

void stampa() {
    for (unsigned i = 0; i < this->n(); i++)
        for (unsigned j = 0; j < this->n(); j++)
            cout << "(" << i << " " << j << ") = " << archi[i][j] << " ";
}
```

---

## 3. Analisi di GrafoNonOrientato.h

### 3.1 Ereditarietà Protetta

```cpp
class GrafoNonOrientato : protected Grafo {
    // 'protected' significa:
    // - Membri pubblici di Grafo diventano protetti qui
    // - Dall'esterno, GrafoNonOrientato non è un Grafo
    // - Internamente può accedere ai membri protetti di Grafo
```

### 3.2 Ridefinizione di operator()

```cpp
void operator()(unsigned i, unsigned j, bool b) {
    assert(i >= 0 && i < this->n() && j >= 0 && j < this->n());
    
    bool esisteArco = this->archi[i][j];
    if ((!esisteArco && b) || (esisteArco && !b)) {
        this->archi[i][j] = b;    // Arco i → j
        this->archi[j][i] = b;    // Arco j → i (SIMMETRIA!)
        if (b) vm++;
        else vm--;
    }
}
```

**Differenza chiave:**
```cpp
// Grafo orientato:
this->archi[i][j] = b;  // Solo direzione i → j

// Grafo non orientato:
this->archi[i][j] = b;  // Direzione i → j
this->archi[j][i] = b;  // E anche j → i
```

### 3.3 Esposizione Metodi

```cpp
// I metodi della classe base sono resi pubblici esplicitamente
unsigned n() const { return Grafo::n(); }
unsigned m() const { return Grafo::m(); }

bool operator()(unsigned i, unsigned j) const {
    return Grafo::operator()(i, j);
}

void svuota() { Grafo::svuota(); }
void stampa() { Grafo::stampa(); }
```

---

## 4. Esercizi Risolti: main.cpp

### 4.1 stampaGrafo

```cpp
void stampaGrafo(const Grafo& g) {
    cout << "Numero nodi: " << g.n() << endl;
    cout << "Numero archi: " << g.m() << endl;
    
    for (int i = 0; i < g.n(); i++)
        for (int j = 0; j < g.n(); j++)
            if (g(i, j))
                cout << "Arco: " << i << " -> " << j << endl;
}
```

**Complessità:** O(n²) - scorre tutta la matrice.

---

### 4.2 getNodoConGradoMassimo

**Problema:** Trovare il nodo con il maggior numero di archi incidenti.

```cpp
int getNodoConGradoMassimo(const GrafoNonOrientato& g) {
    int grado_max = -1;
    int nodo_con_grado_max = -1;
    
    for (int nodo = 0; nodo < g.n(); nodo++) {
        // Conta gli archi incidenti al nodo
        int grado = 0;
        for (int i = 0; i < g.n(); i++)
            if (g(nodo, i) && i != nodo)  // Escludi self-loop
                grado++;
        
        // Aggiorna massimo
        if (grado > grado_max) {
            grado_max = grado;
            nodo_con_grado_max = nodo;
        }
    }
    
    return nodo_con_grado_max;
}
```

**Trace:**
```
Grafo:
  0 ── 1 ── 2
  │    │
  3 ── 4

Gradi:
  nodo 0: vicini {1, 3} → grado = 2
  nodo 1: vicini {0, 2, 4} → grado = 3  ← MASSIMO
  nodo 2: vicini {1} → grado = 1
  nodo 3: vicini {0, 4} → grado = 2
  nodo 4: vicini {1, 3} → grado = 2

Risultato: nodo 1 con grado 3
```

**Complessità:** O(n²)

---

### 4.3 stessoNumeroNodiStessoGrado

**Problema:** Verificare se due grafi hanno la stessa distribuzione di gradi.

```cpp
bool stessoNumeroNodiStessoGrado(const GrafoNonOrientato& g1, 
                                  const GrafoNonOrientato& g2) {
    if (g1.n() != g2.n()) return false;
    
    // Array di conteggio: num_nodi_per_grado[k] = quanti nodi hanno grado k
    int num_nodi_per_grado[g1.n()];
    fill(num_nodi_per_grado, num_nodi_per_grado + g1.n(), 0);
    
    // Incrementa per G1
    for (int nodo = 0; nodo < g1.n(); nodo++) {
        int grado = 0;
        for (int j = 0; j < g1.n(); j++)
            if (g1(nodo, j)) grado++;
        num_nodi_per_grado[grado]++;
    }
    
    // Decrementa per G2
    for (int nodo = 0; nodo < g2.n(); nodo++) {
        int grado = 0;
        for (int j = 0; j < g2.n(); j++)
            if (g2(nodo, j)) grado++;
        num_nodi_per_grado[grado]--;
    }
    
    // Se tutto a zero, stessa distribuzione
    for (int i = 0; i < g1.n(); i++)
        if (num_nodi_per_grado[i] != 0)
            return false;
    
    return true;
}
```

**Esempio:**
```
G1:        G2:
0 ─ 1      0 ─ 1
│   │      │   │
2 ─ 3      2   3

G1 gradi: 0→2, 1→2, 2→2, 3→2 → tutti grado 2
G2 gradi: 0→2, 1→2, 2→1, 3→1 → due grado 2, due grado 1

num_nodi_per_grado dopo G1: [0, 0, 4, ...]  (4 nodi con grado 2)
num_nodi_per_grado dopo G2: [0, -2, 2, ...] (non zero!)

Risultato: false (distribuzioni diverse)
```

---

### 4.4 almenoUnNodoAdiacenteATutti

**Problema:** Verificare se esiste un nodo "universale" collegato a tutti gli altri.

```cpp
bool almenoUnNodoAdiacenteATutti(const GrafoNonOrientato& g) {
    for (int nodo = 0; nodo < g.n(); nodo++) {
        bool adiacenteATutti = true;
        
        for (int i = 0; i < g.n() && adiacenteATutti; i++)
            if (!g(nodo, i) && i != nodo)  // Non connesso e non è se stesso
                adiacenteATutti = false;
        
        if (adiacenteATutti)
            return true;  // Trovato!
    }
    return false;
}
```

**Ottimizzazione:** Il ciclo interno si ferma appena trova un nodo non connesso.

---

### 4.5 getCoppiaConPiuAdiacenti

**Problema:** Trovare la coppia (i, j) con il maggior numero di vicini comuni.

```cpp
CoppiaNodi getCoppiaConPiuAdiacenti(const GrafoNonOrientato& g) {
    CoppiaNodi coppiaPiuAdiacenti;
    int max_num_adiacenti = -1;
    
    // Per ogni coppia (nodo_1, nodo_2) con nodo_1 < nodo_2
    for (int nodo_1 = 0; nodo_1 < g.n() - 1; nodo_1++) {
        for (int nodo_2 = nodo_1 + 1; nodo_2 < g.n(); nodo_2++) {
            
            // Conta vicini comuni
            int count_adiacenti = 0;
            for (int i = 0; i < g.n(); i++)
                if (i != nodo_1 && i != nodo_2 && 
                    g(nodo_1, i) && g(nodo_2, i))
                    count_adiacenti++;
            
            if (count_adiacenti > max_num_adiacenti) {
                max_num_adiacenti = count_adiacenti;
                coppiaPiuAdiacenti = {nodo_1, nodo_2};
            }
        }
    }
    
    return coppiaPiuAdiacenti;
}
```

**Complessità:** O(n³) - tre cicli annidati.

---

### 4.6 connesso (BFS)

**Problema:** Verificare se il grafo è connesso.

```cpp
bool connesso(const GrafoNonOrientato& g) {
    vector<bool> visitati(g.n(), false);
    queue<unsigned> q;
    
    // Parto dal nodo 0
    q.push(0);
    visitati[0] = true;
    int nodi_raggiunti = 1;
    
    while (!q.empty()) {
        unsigned u = q.front();
        q.pop();
        
        // Esplora tutti i vicini non visitati
        for (unsigned v = 0; v < g.n(); ++v) {
            if (g(u, v) && u != v && !visitati[v]) {
                q.push(v);
                visitati[v] = true;
                nodi_raggiunti++;
            }
        }
    }
    
    // Connesso se raggiungo tutti
    return nodi_raggiunti == g.n();
}
```

---

### 4.7 inUnCiclo (BFS Modificata)

**Problema:** Verificare se un nodo specifico appartiene a un ciclo.

```cpp
bool inUnCiclo(const Grafo& g, int nodo) {
    vector<bool> visitati(g.n(), false);
    queue<unsigned> q;
    
    q.push(nodo);
    // NON marchiamo nodo come visitato!
    
    while (!q.empty()) {
        unsigned u = q.front();
        q.pop();
        
        for (unsigned v = 0; v < g.n(); ++v) {
            if (g(u, v) && u != v && !visitati[v]) {
                // Se torniamo al nodo iniziale → ciclo!
                if (v == nodo) return true;
                
                q.push(v);
                visitati[v] = true;
            }
        }
    }
    
    return false;
}
```

**Logica:**
- Non marchiamo il nodo iniziale come visitato
- Se durante la BFS lo incontriamo come vicino → c'è un ciclo che passa per lui

---

### 4.8 proprieta_1 (Coppie con Vicini Comuni ≥ k)

```cpp
bool proprieta_1(const Grafo& g, int k) {
    int num_coppie_valide = 0;
    
    for (int i = 0; i < g.n() - 1; i++) {
        for (int j = i + 1; j < g.n(); j++) {
            bool coppia_valida = false;
            
            // Basta trovare UN vicino comune
            for (int k = 0; k < g.n() && !coppia_valida; k++)
                if (k != i && k != j && g(i, k) && g(j, k))
                    coppia_valida = true;
            
            if (coppia_valida)
                num_coppie_valide++;
        }
    }
    
    return num_coppie_valide >= k;
}
```

---

### 4.9 proprieta_2 (Pesi e Vicini)

**Problema:** Verificare che per ogni nodo v: `P[v] × grado(v) ≥ Σ P[vicini]`

```cpp
bool proprieta_2(const Grafo& g, vector<int> pesi) {
    for (int nodo = 0; nodo < g.n(); nodo++)
        if (!sotto_proprieta(nodo, g, pesi))
            return false;
    return true;
}

bool sotto_proprieta(int nodo, const Grafo& g, vector<int> pesi) {
    int num_adiacenti = 0;
    int somma_pesi = 0;
    
    for (int i = 0; i < g.n(); i++) {
        if (i != nodo && g(nodo, i)) {
            num_adiacenti++;
            somma_pesi += pesi[i];
        }
    }
    
    return pesi[nodo] * num_adiacenti >= somma_pesi;
}
```

**Esempio:**
```
Grafo:           Pesi:
  0 ── 1         P = [10, 3, 4]
  │
  2

Nodo 0: vicini = {1, 2}, grado = 2
        P[0] × 2 = 10 × 2 = 20
        P[1] + P[2] = 3 + 4 = 7
        20 ≥ 7 ✓

Nodo 1: vicini = {0}, grado = 1
        P[1] × 1 = 3 × 1 = 3
        P[0] = 10
        3 ≥ 10 ✗ → return false!
```

---

## 5. Trace di Esecuzione

### 5.1 BFS per Connessione

```
Grafo:
  0 ── 1
  │    │
  2 ── 3

Esecuzione connesso(g):

Inizializzazione:
  visitati = [false, false, false, false]
  q = [0]
  visitati[0] = true
  nodi_raggiunti = 1

Iterazione 1:
  u = 0 (pop da q)
  Vicini di 0: {1, 2}
    v=1: non visitato → q.push(1), visitati[1]=true, nodi_raggiunti=2
    v=2: non visitato → q.push(2), visitati[2]=true, nodi_raggiunti=3
  q = [1, 2]

Iterazione 2:
  u = 1 (pop da q)
  Vicini di 1: {0, 3}
    v=0: già visitato → skip
    v=3: non visitato → q.push(3), visitati[3]=true, nodi_raggiunti=4
  q = [2, 3]

Iterazione 3:
  u = 2 (pop da q)
  Vicini di 2: {0, 3}
    v=0: già visitato → skip
    v=3: già visitato → skip
  q = [3]

Iterazione 4:
  u = 3 (pop da q)
  Vicini di 3: {1, 2}
    tutti già visitati → skip
  q = []

Fine:
  nodi_raggiunti = 4 = g.n()
  return true (connesso)
```

---

## 6. Pattern Ricorrenti

### 6.1 Pattern: Itera su Tutti i Vicini

```cpp
for (int v = 0; v < g.n(); v++) {
    if (g(u, v) && u != v) {  // Esclude self-loop
        // v è un vicino di u
    }
}
```

### 6.2 Pattern: Itera su Tutte le Coppie (Senza Ripetizioni)

```cpp
for (int i = 0; i < g.n() - 1; i++) {
    for (int j = i + 1; j < g.n(); j++) {
        // (i, j) è una coppia unica
    }
}
```

### 6.3 Pattern: BFS

```cpp
vector<bool> visitati(g.n(), false);
queue<unsigned> q;

q.push(sorgente);
visitati[sorgente] = true;

while (!q.empty()) {
    unsigned u = q.front();
    q.pop();
    
    // Processa u
    
    for (unsigned v = 0; v < g.n(); ++v) {
        if (g(u, v) && !visitati[v]) {
            q.push(v);
            visitati[v] = true;
        }
    }
}
```

### 6.4 Pattern: Conta Grado

```cpp
int grado = 0;
for (int i = 0; i < g.n(); i++) {
    if (g(nodo, i) && i != nodo)
        grado++;
}
```

---

## Appendice: Tabella Riassuntiva Esercizi

| Esercizio | Complessità | Tecnica |
|-----------|-------------|---------|
| stampaGrafo | O(n²) | Scansione matrice |
| getNodoConGradoMassimo | O(n²) | Conteggio gradi |
| stessoNumeroNodiStessoGrado | O(n²) | Counting array |
| almenoUnNodoAdiacenteATutti | O(n²) | Doppio ciclo con break |
| getCoppiaConPiuAdiacenti | O(n³) | Triplo ciclo |
| connesso | O(n²) | BFS |
| inUnCiclo | O(n²) | BFS modificata |
| proprieta_1 | O(n³) | Triplo ciclo con break |
| proprieta_2 | O(n²) | Doppio ciclo |
