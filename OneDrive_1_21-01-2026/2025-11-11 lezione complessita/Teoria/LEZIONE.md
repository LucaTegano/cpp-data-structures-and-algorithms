# Teoria Completa: Analisi della Complessita Computazionale

Questo documento fornisce una spiegazione approfondita dell'analisi della complessita temporale e spaziale degli algoritmi, con esempi pratici e regole per l'esame.

---

## Indice
1. [Cos'e la Complessita Computazionale](#1-cose-la-complessita-computazionale)
2. [Notazioni Asintotiche](#2-notazioni-asintotiche)
3. [Regole di Calcolo](#3-regole-di-calcolo)
4. [Complessita dei Cicli](#4-complessita-dei-cicli)
5. [Complessita Ricorsiva](#5-complessita-ricorsiva)
6. [Complessita delle Strutture Dati STL](#6-complessita-delle-strutture-dati-stl)
7. [Esempi Risolti](#7-esempi-risolti)

---

## 1. Cos'e la Complessita Computazionale

La complessita computazionale misura la quantita di risorse (tempo o spazio) necessarie per eseguire un algoritmo in funzione della dimensione dell'input `n`.

### Perche e importante?
- Permette di confrontare algoritmi indipendentemente dall'hardware
- Predice il comportamento per input molto grandi
- Identifica colli di bottiglia nel codice

### Due tipi di complessita:
| Tipo | Cosa misura | Unita |
|------|-------------|-------|
| **Temporale** | Numero di operazioni elementari | Passi/istruzioni |
| **Spaziale** | Memoria utilizzata | Byte/variabili |

---

## 2. Notazioni Asintotiche

### 2.1 Big-O (O) - Limite Superiore
Rappresenta il **caso peggiore**. E la notazione piu usata.

$$T(n) = O(f(n))$$

Significa: $T(n)$ cresce **al massimo** come $f(n)$ per $n$ grande.

```cpp
// Esempio: Ricerca lineare in array non ordinato
// Caso peggiore: elemento non presente -> O(n)
int ricercaLineare(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) return i;
    }
    return -1;
}
```

### 2.2 Big-Omega (Omega) - Limite Inferiore
Rappresenta il **caso migliore**.

$$T(n) = \Omega(f(n))$$

Significa: $T(n)$ cresce **almeno** come $f(n)$.

### 2.3 Big-Theta (Theta) - Limite Stretto
Quando caso migliore e peggiore coincidono.

$$T(n) = \Theta(f(n))$$

### Gerarchia delle Complessita (dalla piu veloce alla piu lenta)

| Notazione | Nome | Esempio |
|-----------|------|---------|
| $O(1)$ | Costante | Accesso array `arr[i]` |
| $O(\log n)$ | Logaritmica | Binary Search |
| $O(n)$ | Lineare | Scansione array |
| $O(n \log n)$ | Linearitmica | Merge Sort, Quick Sort |
| $O(n^2)$ | Quadratica | Bubble Sort, 2 cicli annidati |
| $O(n^3)$ | Cubica | Moltiplicazione matrici naive |
| $O(2^n)$ | Esponenziale | Fibonacci ricorsivo naive |
| $O(n!)$ | Fattoriale | Permutazioni, TSP brute-force |

---

## 3. Regole di Calcolo

### Regola 1: Costanti Moltiplicative si Ignorano
$$O(5n) = O(n)$$
$$O(100n^2) = O(n^2)$$

```cpp
// Questo e O(n), non O(3n)
for (int i = 0; i < n; i++) { op1(); }
for (int i = 0; i < n; i++) { op2(); }
for (int i = 0; i < n; i++) { op3(); }
```

### Regola 2: Termini di Ordine Inferiore si Ignorano
$$O(n^2 + n) = O(n^2)$$
$$O(n^3 + n^2 + n + 1) = O(n^3)$$

### Regola 3: Somma di Complessita
Per blocchi di codice **sequenziali**, si prende il massimo.
$$O(f(n)) + O(g(n)) = O(\max(f(n), g(n)))$$

```cpp
// Blocco A: O(n)
for (int i = 0; i < n; i++) { ... }

// Blocco B: O(n^2)
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) { ... }
}

// Totale: O(n^2)
```

### Regola 4: Prodotto di Complessita
Per codice **annidato**, si moltiplicano.
$$O(f(n)) \times O(g(n)) = O(f(n) \cdot g(n))$$

---

## 4. Complessita dei Cicli

### 4.1 Ciclo Semplice
```cpp
for (int i = 0; i < n; i++) {
    // Operazione O(1)
}
// Complessita: O(n)
```

### 4.2 Cicli Annidati Indipendenti
```cpp
for (int i = 0; i < n; i++) {         // n volte
    for (int j = 0; j < n; j++) {     // n volte
        // Operazione O(1)
    }
}
// Complessita: O(n * n) = O(n^2)
```

### 4.3 Cicli Annidati Dipendenti (Triangolari)
```cpp
for (int i = 0; i < n; i++) {         // n volte
    for (int j = 0; j < i; j++) {     // 0, 1, 2, ..., n-1 volte
        // Operazione O(1)
    }
}
```
**Calcolo:**
$$\sum_{i=0}^{n-1} i = 0 + 1 + 2 + ... + (n-1) = \frac{n(n-1)}{2} = \frac{n^2 - n}{2}$$

**Complessita: $O(n^2)$** (domina il termine $n^2$)

### 4.4 Cicli Logaritmici
```cpp
// Incremento moltiplicativo
for (int i = 1; i < n; i = i * 2) {
    // Operazione O(1)
}
// Iterazioni: 1, 2, 4, 8, ..., 2^k < n
// Risolvendo: k < log2(n)
// Complessita: O(log n)
```

```cpp
// Decremento divisivo
for (int i = n; i > 0; i = i / 2) {
    // Operazione O(1)
}
// Complessita: O(log n)
```

### 4.5 Ciclo While con Condizione Strana
```cpp
int i = 0;
while (i * i < n) {
    i++;
}
```
**Analisi:** Il ciclo termina quando $i^2 \geq n$, quindi $i \geq \sqrt{n}$

**Complessita: $O(\sqrt{n})$**

---

## 5. Complessita Ricorsiva

### 5.1 Metodo della Sostituzione
Indovina la soluzione e dimostrala per induzione.

### 5.2 Albero di Ricorsione
Disegna l'albero delle chiamate ricorsive.

### 5.3 Master Theorem (Semplificato)
Per ricorrenze della forma:
$$T(n) = a \cdot T\left(\frac{n}{b}\right) + f(n)$$

| Caso | Condizione | Risultato |
|------|------------|-----------|
| 1 | $f(n) = O(n^c)$ dove $c < \log_b a$ | $T(n) = O(n^{\log_b a})$ |
| 2 | $f(n) = O(n^c)$ dove $c = \log_b a$ | $T(n) = O(n^c \log n)$ |
| 3 | $f(n) = O(n^c)$ dove $c > \log_b a$ | $T(n) = O(f(n))$ |

### Esempi Comuni:

**Binary Search:**
$$T(n) = T(n/2) + O(1)$$
- $a=1, b=2, f(n)=O(1)$
- $\log_2 1 = 0$, $f(n) = O(n^0) = O(1)$
- Caso 2: **$T(n) = O(\log n)$**

**Merge Sort:**
$$T(n) = 2T(n/2) + O(n)$$
- $a=2, b=2, f(n)=O(n)$
- $\log_2 2 = 1$, $f(n) = O(n^1)$
- Caso 2: **$T(n) = O(n \log n)$**

**Fibonacci Ricorsivo (Naive):**
```cpp
int fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);
}
```
$$T(n) = T(n-1) + T(n-2) + O(1)$$
Soluzione: **$T(n) = O(2^n)$** (esponenziale!)

---

## 6. Complessita delle Strutture Dati STL

### 6.1 std::vector

| Operazione | Complessita Media | Caso Peggiore |
|------------|-------------------|---------------|
| `operator[]` | $O(1)$ | $O(1)$ |
| `push_back` | $O(1)$ ammortizzato | $O(n)$ (resize) |
| `pop_back` | $O(1)$ | $O(1)$ |
| `insert` (in mezzo) | $O(n)$ | $O(n)$ |
| `erase` (in mezzo) | $O(n)$ | $O(n)$ |
| `find` (non ordinato) | $O(n)$ | $O(n)$ |

### 6.2 std::list (Lista Doppiamente Concatenata)

| Operazione | Complessita |
|------------|-------------|
| `push_front` / `push_back` | $O(1)$ |
| `pop_front` / `pop_back` | $O(1)$ |
| `insert` (con iteratore) | $O(1)$ |
| Accesso elemento k-esimo | $O(k)$ |

### 6.3 std::set / std::map (Alberi Bilanciati)

| Operazione | Complessita |
|------------|-------------|
| `insert` | $O(\log n)$ |
| `find` | $O(\log n)$ |
| `erase` | $O(\log n)$ |
| Iterazione ordinata | $O(n)$ |

### 6.4 std::unordered_set / std::unordered_map (Hash Table)

| Operazione | Complessita Media | Caso Peggiore |
|------------|-------------------|---------------|
| `insert` | $O(1)$ | $O(n)$ |
| `find` | $O(1)$ | $O(n)$ |
| `erase` | $O(1)$ | $O(n)$ |

---

## 7. Esempi Risolti

### Esempio 1: Analisi Ciclo con Limite Costante
```cpp
void func(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 100; j++) {
            cout << i + j;
        }
    }
}
```
**Analisi:**
- Ciclo esterno: $n$ iterazioni
- Ciclo interno: sempre 100 iterazioni (COSTANTE!)
- Totale: $n \times 100 = 100n$

**Complessita: $O(n)$** (non $O(n^2)$!)

### Esempio 2: Ciclo con Modifica dell'Indice
```cpp
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        k++;
        i++;  // ATTENZIONE! Modifica i
    }
}
```
**Analisi:**
- Ogni esecuzione del ciclo interno incrementa `i` di `n`
- Il ciclo esterno terminera dopo poche iterazioni
- Totale operazioni: circa $n$

**Complessita: $O(n)$** (non $O(n^2)$!)

### Esempio 3: Somme Prefisse

**Versione Naive ($O(n^2)$):**
```cpp
for (int target = 0; target < n; target++) {
    int sum = 0;
    for (int i = 0; i <= target; i++) {
        sum += arr[i];
    }
    cout << sum << " ";
}
```

**Versione Ottimizzata ($O(n)$):**
```cpp
int sum = 0;
for (int i = 0; i < n; i++) {
    sum += arr[i];
    cout << sum << " ";
}
```
**Trucco:** Riutilizza il risultato parziale invece di ricalcolare.

### Esempio 4: Ricerca in Matrice

**Versione Naive ($O(n \times m)$):**
```cpp
bool cerca(int mat[][M], int n, int m, int x) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == x) return true;
        }
    }
    return false;
}
```

**Se la matrice e ordinata per righe e colonne ($O(n + m)$):**
```cpp
bool cercaOrdinata(int mat[][M], int n, int m, int x) {
    int i = 0, j = m - 1;  // Parti dall'angolo in alto a destra
    while (i < n && j >= 0) {
        if (mat[i][j] == x) return true;
        if (mat[i][j] > x) j--;  // Troppo grande, vai a sinistra
        else i++;                 // Troppo piccolo, vai in basso
    }
    return false;
}
```

---

## Consigli per l'Esame

1. **Identifica prima il caso peggiore** - E quello che ti chiedono quasi sempre
2. **Attenzione ai cicli con limite costante** - Non contribuiscono alla complessita
3. **Cerca pattern nascosti** - Indici che saltano, condizioni di uscita anticipata
4. **Somme aritmetiche** - $\sum_{i=1}^{n} i = \frac{n(n+1)}{2} = O(n^2)$
5. **Somme geometriche** - $\sum_{i=0}^{k} 2^i = 2^{k+1} - 1$
6. **Logaritmi** - Ogni volta che dividi per 2 (o moltiplichi per 2) -> $O(\log n)$
