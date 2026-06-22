# Lezione: Grafi Orientati e Non Orientati

## Indice
1. [Introduzione ai Grafi](#1-introduzione-ai-grafi)
2. [Definizioni Formali](#2-definizioni-formali)
3. [Rappresentazione in Memoria](#3-rappresentazione-in-memoria)
4. [La Classe Grafo (Orientato)](#4-la-classe-grafo-orientato)
5. [La Classe GrafoNonOrientato](#5-la-classe-grafononorientato)
6. [Algoritmi di Visita](#6-algoritmi-di-visita)
7. [Proprietà dei Grafi](#7-proprietà-dei-grafi)
8. [Complessità Computazionale](#8-complessità-computazionale)
9. [Errori Comuni](#9-errori-comuni)
10. [Esercizi Proposti](#10-esercizi-proposti)

---

## 1. Introduzione ai Grafi

### 1.1 Cos'è un Grafo?

Un **grafo** G = (V, E) è una struttura matematica composta da:
- **V**: insieme di **vertici** (o nodi)
- **E**: insieme di **archi** (o spigoli) che connettono coppie di vertici

```
┌─────────────────────────────────────────────────────────────┐
│ GRAFO NON ORIENTATO                                          │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│       0 ──────── 1           V = {0, 1, 2, 3, 4}            │
│       │ \        │           E = {{0,1}, {0,2}, {0,3},      │
│       │   \      │                {1,2}, {3,4}}             │
│       │     \    │                                           │
│       2 ──────── 3 ──── 4    |V| = 5, |E| = 5               │
│                                                              │
│   Arco {u,v} = {v,u}  (ordine non conta)                    │
│                                                              │
└─────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────┐
│ GRAFO ORIENTATO (Digrafo)                                    │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│       0 ───────► 1           V = {0, 1, 2, 3, 4}            │
│       │ \        │           E = {(0,1), (0,2), (0,3),      │
│       │   \      │                (1,2), (2,1), (3,4)}      │
│       ▼     ▼    ▼                                           │
│       2 ◄──────► 3 ───► 4    |V| = 5, |E| = 6               │
│                                                              │
│   Arco (u,v) ≠ (v,u)  (ordine conta!)                       │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

### 1.2 Applicazioni dei Grafi

| Dominio | Nodi | Archi |
|---------|------|-------|
| Social Network | Persone | Amicizie/Follow |
| Web | Pagine | Link ipertestuali |
| Strade | Incroci | Strade |
| Reti | Computer | Connessioni |
| Biologia | Proteine | Interazioni |
| Compilatori | Istruzioni | Dipendenze |

---

## 2. Definizioni Formali

### 2.1 Terminologia Base

| Termine | Definizione |
|---------|-------------|
| **Adiacenza** | Due nodi u e v sono adiacenti se esiste l'arco (u,v) |
| **Incidenza** | Un arco (u,v) è incidente ai nodi u e v |
| **Grado** | Numero di archi incidenti a un nodo |
| **Grado entrante** | (Digrafi) Numero di archi che entrano nel nodo |
| **Grado uscente** | (Digrafi) Numero di archi che escono dal nodo |
| **Cammino** | Sequenza di nodi v₀, v₁, ..., vₖ con archi consecutivi |
| **Ciclo** | Cammino con v₀ = vₖ |
| **Connesso** | Esiste un cammino tra ogni coppia di nodi |
| **Componente connessa** | Sottografo massimale connesso |

### 2.2 Proprietà Numeriche

Per un grafo G = (V, E) con n = |V| nodi e m = |E| archi:

| Proprietà | Non Orientato | Orientato |
|-----------|---------------|-----------|
| Archi massimi | n(n-1)/2 | n(n-1) |
| Somma gradi | 2m | m (entranti) + m (uscenti) |
| Grafo completo | Kₙ | Dₙ |
| Archi in albero | n-1 | n-1 |

### 2.3 Tipi di Grafi

```
┌─────────────────────────────────────────────────────────────┐
│ GRAFO COMPLETO K₄                                            │
├─────────────────────────────────────────────────────────────┤
│       0 ──────── 1                                           │
│       │ \      / │       Ogni nodo connesso a tutti         │
│       │   \  /   │       Archi: n(n-1)/2 = 6                │
│       │    \/    │                                           │
│       │    /\    │                                           │
│       │  /    \  │                                           │
│       2 ──────── 3                                           │
└─────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────┐
│ GRAFO BIPARTITO                                              │
├─────────────────────────────────────────────────────────────┤
│    A₁ ──┐    ┌── B₁                                          │
│         │    │                                               │
│    A₂ ──┼────┼── B₂      Nodi divisi in due insiemi         │
│         │    │           Archi solo tra insiemi diversi     │
│    A₃ ──┴────┴── B₃                                          │
└─────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────┐
│ DAG (Directed Acyclic Graph)                                 │
├─────────────────────────────────────────────────────────────┤
│       0 ───► 1 ───► 3                                        │
│       │      │                                               │
│       ▼      ▼        Orientato                              │
│       2 ───► 4        Senza cicli                            │
│                       Usato per: dipendenze, scheduling      │
└─────────────────────────────────────────────────────────────┘
```

---

## 3. Rappresentazione in Memoria

### 3.1 Matrice di Adiacenza

Matrice booleana n×n dove `M[i][j] = true` se esiste l'arco (i,j).

```cpp
class Grafo {
protected:
    unsigned vn;                    // Numero nodi
    unsigned vm;                    // Numero archi
    vector<vector<bool>> archi;     // Matrice n×n
};
```

**Esempio:**
```
Grafo:              Matrice:
  0 → 1               0  1  2  3
  ↓ ↘               ┌─────────────
  2 → 3           0 │ 0  1  1  1
                  1 │ 0  0  1  0
                  2 │ 0  0  0  1
                  3 │ 0  0  0  0
```

**Vantaggi:**
- Accesso O(1) per verificare esistenza arco
- Semplice implementazione

**Svantaggi:**
- Spazio O(n²) anche per grafi sparsi
- Iterare sui vicini richiede O(n)

### 3.2 Liste di Adiacenza (Alternativa)

```cpp
class GrafoListe {
    unsigned n;
    vector<list<unsigned>> adj;  // adj[i] = lista dei vicini di i
};
```

**Esempio:**
```
Grafo:              Liste:
  0 → 1             0: [1, 2, 3]
  ↓ ↘               1: [2]
  2 → 3             2: [3]
                    3: []
```

**Vantaggi:**
- Spazio O(n + m)
- Iterare sui vicini è O(grado)

**Svantaggi:**
- Verificare esistenza arco è O(grado)

### 3.3 Confronto

| Operazione | Matrice | Liste |
|------------|---------|-------|
| Spazio | O(n²) | O(n + m) |
| Arco esiste? | O(1) | O(grado) |
| Aggiungi arco | O(1) | O(1) |
| Rimuovi arco | O(1) | O(grado) |
| Itera vicini | O(n) | O(grado) |

**Quando usare cosa?**
- **Matrice**: Grafi densi (m ≈ n²), query frequenti su archi
- **Liste**: Grafi sparsi (m << n²), iterazione frequente sui vicini

---

## 4. La Classe Grafo (Orientato)

### 4.1 Struttura

```cpp
using boolVec = std::vector<bool>;

class Grafo {
protected:
    unsigned vn = 0, vm = 0;        // Nodi, archi
    std::vector<boolVec> archi;     // Matrice di adiacenza
    
    void init(unsigned n) {
        this->vn = n;
        this->vm = 0;
        this->archi = std::vector<boolVec>(n);
        for (unsigned i = 0; i < n; i++)
            this->archi[i] = boolVec(n, false);
    }
    
public:
    Grafo(unsigned n) {
        assert(n >= 1);
        this->init(n);
    }
    
    unsigned n() const { return vn; }  // Numero nodi
    unsigned m() const { return vm; }  // Numero archi
    
    // ... altri metodi
};
```

### 4.2 Operator() - Accesso e Modifica

```cpp
// Lettura: verifica se esiste arco (i,j)
bool operator()(unsigned i, unsigned j) const {
    assert(i >= 0 && i < this->n() && j >= 0 && j < this->n());
    return this->archi[i][j];
}

// Scrittura: inserisce o rimuove arco (i,j)
void operator()(unsigned i, unsigned j, bool b) {
    assert(i >= 0 && i < this->n() && j >= 0 && j < this->n());
    
    bool esisteArco = this->archi[i][j];
    
    // Aggiorna solo se lo stato cambia
    if ((!esisteArco && b) || (esisteArco && !b)) {
        this->archi[i][j] = b;
        if (b) vm++;     // Inserimento
        else vm--;       // Rimozione
    }
}
```

**Uso:**
```cpp
Grafo g(5);

// Inserimento arco
g(0, 1, true);   // 0 → 1

// Verifica esistenza
if (g(0, 1)) {
    cout << "Arco 0→1 esiste" << endl;
}

// Rimozione arco
g(0, 1, false);
```

### 4.3 Perché Due Versioni di operator()?

```cpp
// Versione const (lettura) - 2 parametri
bool operator()(unsigned i, unsigned j) const;

// Versione non-const (scrittura) - 3 parametri  
void operator()(unsigned i, unsigned j, bool b);
```

Il C++ sceglie la versione corretta in base a:
1. Numero di parametri (2 vs 3)
2. Contesto const (su oggetto const usa solo la versione const)

---

## 5. La Classe GrafoNonOrientato

### 5.1 Ereditarietà Protetta

```cpp
class GrafoNonOrientato : protected Grafo {
public:
    GrafoNonOrientato(unsigned n) : Grafo(n) {}
    
    // Ridefinisce operator() per garantire simmetria
    void operator()(unsigned i, unsigned j, bool b) {
        assert(i >= 0 && i < this->n() && j >= 0 && j < this->n());
        
        bool esisteArco = this->archi[i][j];
        if ((!esisteArco && b) || (esisteArco && !b)) {
            this->archi[i][j] = b;  // Arco i→j
            this->archi[j][i] = b;  // Arco j→i (SIMMETRIA!)
            if (b) vm++;
            else vm--;
        }
    }
    
    // Espone metodi pubblici della classe base
    unsigned n() const { return Grafo::n(); }
    unsigned m() const { return Grafo::m(); }
    bool operator()(unsigned i, unsigned j) const {
        return Grafo::operator()(i, j);
    }
};
```

### 5.2 Differenza Chiave

```
GRAFO ORIENTATO:                 GRAFO NON ORIENTATO:
g(0, 1, true);                   gno(0, 1, true);
                                 
  Matrice:                         Matrice (simmetrica):
    0 1 2                            0 1 2
  ┌───────                         ┌───────
0 │ 0 1 0                        0 │ 0 1 0
1 │ 0 0 0   ← Solo (0,1)         1 │ 1 0 0   ← Sia (0,1) che (1,0)
2 │ 0 0 0                        2 │ 0 0 0
```

### 5.3 Conteggio Archi

```cpp
// Grafo orientato: ogni arco conta 1
g(0, 1, true);   // vm = 1
g(1, 0, true);   // vm = 2

// Grafo non orientato: ogni arco "logico" conta 1
gno(0, 1, true); // vm = 1 (anche se modifica due celle)
```

---

## 6. Algoritmi di Visita

### 6.1 BFS (Breadth-First Search)

Visita in ampiezza: esplora tutti i nodi a distanza k prima di quelli a distanza k+1.

```cpp
bool connesso(const GrafoNonOrientato& g) {
    vector<bool> visitati(g.n(), false);
    queue<unsigned> q;
    
    // Parti dal nodo 0
    q.push(0);
    visitati[0] = true;
    int nodi_raggiunti = 1;
    
    while (!q.empty()) {
        unsigned u = q.front();
        q.pop();
        
        // Esplora tutti i vicini
        for (unsigned v = 0; v < g.n(); ++v) {
            if (g(u, v) && u != v && !visitati[v]) {
                q.push(v);
                visitati[v] = true;
                nodi_raggiunti++;
            }
        }
    }
    
    return nodi_raggiunti == g.n();
}
```

**Trace BFS:**
```
Grafo:          Esecuzione:
  0 ── 1        Coda: [0]      Visitati: {0}
  │    │        
  2 ── 3        Pop 0, aggiungi vicini 1,2
                Coda: [1, 2]   Visitati: {0, 1, 2}
                
                Pop 1, aggiungi vicino 3
                Coda: [2, 3]   Visitati: {0, 1, 2, 3}
                
                Pop 2, nessun nuovo vicino
                Pop 3, nessun nuovo vicino
                
                Coda vuota, raggiunti 4 su 4 → connesso!
```

### 6.2 Rilevamento Cicli (BFS Modificata)

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
                // Se torniamo al nodo di partenza → ciclo!
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
- Se durante la BFS lo incontriamo di nuovo → abbiamo trovato un ciclo

### 6.3 DFS (Depth-First Search)

```cpp
void dfs(const Grafo& g, int nodo, vector<bool>& visitati) {
    visitati[nodo] = true;
    cout << nodo << " ";
    
    for (int v = 0; v < g.n(); v++) {
        if (g(nodo, v) && !visitati[v]) {
            dfs(g, v, visitati);
        }
    }
}

// Wrapper
void dfs(const Grafo& g) {
    vector<bool> visitati(g.n(), false);
    dfs(g, 0, visitati);
}
```

---

## 7. Proprietà dei Grafi

### 7.1 Grado di un Nodo

```cpp
int getNodoConGradoMassimo(const GrafoNonOrientato& g) {
    int grado_max = -1;
    int nodo_con_grado_max = -1;
    
    for (int nodo = 0; nodo < g.n(); nodo++) {
        int grado = 0;
        for (int i = 0; i < g.n(); i++)
            if (g(nodo, i) && i != nodo)
                grado++;
        
        if (grado > grado_max) {
            grado_max = grado;
            nodo_con_grado_max = nodo;
        }
    }
    
    return nodo_con_grado_max;
}
```

### 7.2 Nodo Universale

Un nodo è **universale** se è adiacente a tutti gli altri.

```cpp
bool almenoUnNodoAdiacenteATutti(const GrafoNonOrientato& g) {
    for (int nodo = 0; nodo < g.n(); nodo++) {
        bool adiacenteATutti = true;
        
        for (int i = 0; i < g.n() && adiacenteATutti; i++)
            if (!g(nodo, i) && i != nodo)
                adiacenteATutti = false;
        
        if (adiacenteATutti)
            return true;
    }
    return false;
}
```

### 7.3 Distribuzione dei Gradi

```cpp
bool stessoNumeroNodiStessoGrado(const GrafoNonOrientato& g1, 
                                  const GrafoNonOrientato& g2) {
    if (g1.n() != g2.n()) return false;
    
    // Array di conteggio: counting sort style
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
    
    // Verifica: tutto zero?
    for (int i = 0; i < g1.n(); i++)
        if (num_nodi_per_grado[i] != 0)
            return false;
    
    return true;
}
```

### 7.4 Vicini Comuni

```cpp
CoppiaNodi getCoppiaConPiuAdiacenti(const GrafoNonOrientato& g) {
    CoppiaNodi coppiaPiuAdiacenti;
    int max_num_adiacenti = -1;
    
    // Per ogni coppia (i, j) con i < j
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

---

## 8. Complessità Computazionale

### 8.1 Operazioni Base (Matrice di Adiacenza)

| Operazione | Complessità |
|------------|-------------|
| Costruttore | O(n²) |
| Aggiungi/Rimuovi arco | O(1) |
| Verifica arco | O(1) |
| Itera tutti i vicini | O(n) |
| Conta archi | O(1) |
| Svuota | O(n²) |

### 8.2 Algoritmi

| Algoritmo | Complessità | Note |
|-----------|-------------|------|
| BFS/DFS | O(n²) | Con matrice |
| BFS/DFS | O(n + m) | Con liste |
| Grado massimo | O(n²) | Scorre tutta matrice |
| Nodo universale | O(n²) | Worst case |
| Coppie con vicini comuni | O(n³) | Tre cicli annidati |
| Connesso | O(n²) | BFS + scansione vicini |

### 8.3 Confronto Matrice vs Liste

| Operazione | Matrice | Liste |
|------------|---------|-------|
| BFS/DFS | O(n²) | O(n + m) |
| Itera vicini di u | O(n) | O(grado(u)) |
| Arco esiste? | O(1) | O(grado(u)) |
| Spazio | O(n²) | O(n + m) |

---

## 9. Errori Comuni

### 9.1 Self-Loop Non Gestiti

```cpp
// ❌ Potrebbe contare self-loop
for (int i = 0; i < g.n(); i++)
    if (g(nodo, i))
        grado++;

// ✅ Esclude self-loop
for (int i = 0; i < g.n(); i++)
    if (g(nodo, i) && i != nodo)
        grado++;
```

### 9.2 Conteggio Doppio in Grafi Non Orientati

```cpp
// ❌ Conta ogni arco due volte
for (int i = 0; i < g.n(); i++)
    for (int j = 0; j < g.n(); j++)
        if (g(i, j)) archi++;

// ✅ Conta ogni arco una volta sola
for (int i = 0; i < g.n(); i++)
    for (int j = i + 1; j < g.n(); j++)  // j > i
        if (g(i, j)) archi++;
```

### 9.3 BFS senza Marcatura Pre-Inserimento

```cpp
// ❌ Può inserire lo stesso nodo multiple volte
if (g(u, v) && !visitati[v]) {
    q.push(v);
    // visitati[v] = true; // MANCANTE!
}

// ✅ Marca subito quando inserisci
if (g(u, v) && !visitati[v]) {
    q.push(v);
    visitati[v] = true;  // Marca PRIMA
}
```

### 9.4 Accesso con Indici Non Validi

```cpp
// ❌ Nessun controllo
bool esiste = g(100, 200);  // Crash se n < 200

// ✅ La classe ha assert, ma meglio controllare prima
if (i < g.n() && j < g.n()) {
    bool esiste = g(i, j);
}
```

---

## 10. Esercizi Proposti

### Esercizio 1: Componenti Connesse
```cpp
int contaComponentiConnesse(const GrafoNonOrientato& g);
// Conta quante componenti connesse ha il grafo
// Hint: BFS multipla su nodi non ancora visitati
```

### Esercizio 2: Grafo Bipartito
```cpp
bool isBipartito(const GrafoNonOrientato& g);
// Verifica se il grafo è bipartito (2-colorabile)
// Hint: BFS con colorazione alternata
```

### Esercizio 3: Cammino Minimo
```cpp
int distanza(const GrafoNonOrientato& g, int sorgente, int dest);
// Ritorna la lunghezza del cammino minimo (numero di archi)
// Hint: BFS dalla sorgente, tieni traccia delle distanze
```

### Esercizio 4: Ciclo in Grafo Non Orientato
```cpp
bool haCiclo(const GrafoNonOrientato& g);
// Verifica se il grafo contiene almeno un ciclo
// Hint: DFS con controllo "back edge"
```

### Esercizio 5: Ordinamento Topologico
```cpp
vector<int> ordinamentoTopologico(const Grafo& g);
// Ritorna un ordinamento dei nodi tale che (u,v) ∈ E → u prima di v
// Hint: DFS con stack, o BFS con conteggio gradi entranti (Kahn)
```

### Esercizio 6: Grafo Trasposto
```cpp
Grafo trasposto(const Grafo& g);
// Ritorna il grafo con tutti gli archi invertiti
// Cioè: (u,v) ∈ E ⟺ (v,u) ∈ E'
```
