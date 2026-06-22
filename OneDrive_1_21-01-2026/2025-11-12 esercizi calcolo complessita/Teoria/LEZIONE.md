# Teoria Completa: Calcolo della Complessita - Esercizi Guidati

In questo modulo non c'e codice sorgente da compilare, perche l'analisi della complessita e un'attivita analitica (statica) che si fa "a occhio" o con carta e penna.

---

## Indice
1. [Regole Fondamentali per l'Esame](#1-regole-fondamentali-per-lesame)
2. [Analisi dei Cicli](#2-analisi-dei-cicli)
3. [Complessita Ricorsiva](#3-complessita-ricorsiva)
4. [Strutture Dati STL](#4-strutture-dati-stl)
5. [Esercizi Risolti Tipo Esame](#5-esercizi-risolti-tipo-esame)

---

## 1. Regole Fondamentali per l'Esame

Quando ti viene chiesto di calcolare la complessita temporale $T(n)$:

### 1.1 Istruzioni Semplici - $O(1)$
Assegnamenti (`a = b`), operazioni aritmetiche (`+`, `-`, `*`, `/`), confronti (`if`, `==`), accesso ad array o vector (`v[i]`), I/O (`cout`, `cin`) hanno costo **costante $O(1)$**.

```cpp
int a = 5;           // O(1)
int b = a + 3;       // O(1)
if (a > b) { }       // O(1)
cout << a;           // O(1)
int x = arr[10];     // O(1)
```

### 1.2 Regola della Somma
Per blocchi di codice **sequenziali**, si prende il massimo.

$$O(f(n)) + O(g(n)) = O(\max(f(n), g(n)))$$

```cpp
// Blocco A: O(n)
for (int i = 0; i < n; i++) { ... }

// Blocco B: O(n^2)
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) { ... }
}

// Totale: O(n^2) (domina il termine maggiore)
```

### 1.3 Regola del Prodotto
Per codice **annidato**, si moltiplicano.

$$O(f(n)) \times O(g(n)) = O(f(n) \cdot g(n))$$

```cpp
for (int i = 0; i < n; i++) {        // O(n)
    for (int j = 0; j < m; j++) {    // O(m)
        cout << i + j;               // O(1)
    }
}
// Totale: O(n * m)
```

---

## 2. Analisi dei Cicli

### 2.1 Cicli `for` e `while` Semplici
La complessita e data da:
$$ \text{Numero Iterazioni} \times \text{Costo del Corpo del Ciclo} $$

```cpp
// i va da 0 a n-1 -> n iterazioni
// Corpo e O(1)
for (int i = 0; i < n; i++) {
    k++; 
}
// Totale: O(n)
```

### 2.2 Cicli Annidati Indipendenti
Se il ciclo interno non dipende dall'indice esterno.

```cpp
for (int i = 0; i < n; i++) {     // n volte
    for (int j = 0; j < n; j++) { // n volte
        k++;
    }
}
// Totale: n * n = O(n^2)
```

### 2.3 Cicli Annidati Dipendenti (Triangolari)
Il ciclo interno dipende da `i`.

```cpp
for (int i = 0; i < n; i++) {       // n volte
    for (int j = 0; j < i; j++) {   // 0, 1, 2, ..., n-1 volte
        k++;
    }
}
```

**Calcolo:**
$$\sum_{i=0}^{n-1} i = 0 + 1 + 2 + ... + (n-1) = \frac{n(n-1)}{2} = \frac{n^2 - n}{2}$$

In notazione asintotica domina il termine di grado massimo: **$O(n^2)$**.

### 2.4 Cicli Logaritmici
L'indice cresce esponenzialmente (moltiplicazione) o decresce esponenzialmente (divisione).

```cpp
for (int i = 1; i < n; i = i * 2) {
    cout << i;
}
```

Iterazioni: $1, 2, 4, 8, \dots, 2^k < n$.
Risolvendo per $k$: $k < \log_2 n$.
Complessita: **$O(\log n)$**.

### 2.5 Tabella Riassuntiva Cicli

| Struttura | Iterazioni | Complessita |
|-----------|------------|-------------|
| `for(i=0; i<n; i++)` | $n$ | $O(n)$ |
| `for(i=0; i<n; i+=2)` | $n/2$ | $O(n)$ |
| `for(i=n; i>0; i--)` | $n$ | $O(n)$ |
| `for(i=1; i<n; i*=2)` | $\log n$ | $O(\log n)$ |
| `for(i=n; i>1; i/=2)` | $\log n$ | $O(\log n)$ |
| `while(i*i < n)` | $\sqrt{n}$ | $O(\sqrt{n})$ |

---

## 3. Complessita Ricorsiva

### 3.1 Master Theorem (Semplificato)
Se hai una funzione ricorsiva:

$$T(n) = a \cdot T(n/b) + f(n)$$

| Algoritmo | Ricorrenza | Risultato |
|-----------|------------|-----------|
| Binary Search | $T(n) = T(n/2) + O(1)$ | $O(\log n)$ |
| Merge Sort | $T(n) = 2T(n/2) + O(n)$ | $O(n \log n)$ |
| Quick Sort (avg) | $T(n) = 2T(n/2) + O(n)$ | $O(n \log n)$ |
| Fibonacci (Naive) | $T(n) = T(n-1) + T(n-2)$ | $O(2^n)$ |

### 3.2 Fibonacci: Esempio di Complessita Esponenziale

```cpp
int fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);
}
```

**Albero delle chiamate per fib(5):**
```
                    fib(5)
                   /      \
               fib(4)     fib(3)
              /    \       /    \
          fib(3) fib(2) fib(2) fib(1)
          /   \    |      |
      fib(2) fib(1)...   ...
```

Molte chiamate ripetute! Complessita: $O(2^n)$

**Versione ottimizzata (Programmazione Dinamica):**
```cpp
int fibDP(int n) {
    if (n <= 1) return n;
    int prev2 = 0, prev1 = 1;
    for (int i = 2; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}
// Complessita: O(n)
```

---

## 4. Strutture Dati STL

### 4.1 Complessita delle Operazioni STL

| Struttura | Operazione | Complessita Media | Caso Peggiore |
|-----------|------------|-------------------|---------------|
| **vector** | `push_back` | $O(1)$ ammortizzato | $O(n)$ (resize) |
| **vector** | `operator[]` | $O(1)$ | $O(1)$ |
| **vector** | `insert` (in mezzo) | $O(n)$ | $O(n)$ |
| **vector** | `erase` (in mezzo) | $O(n)$ | $O(n)$ |
| **list** | `push_front/back` | $O(1)$ | $O(1)$ |
| **list** | `insert` (con iteratore) | $O(1)$ | $O(1)$ |
| **list** | accesso k-esimo | $O(k)$ | $O(n)$ |
| **set/map** | `insert`, `find`, `erase` | $O(\log n)$ | $O(\log n)$ |
| **unordered_set/map** | `insert`, `find` | $O(1)$ | $O(n)$ (collisioni) |

### 4.2 Perche `vector::insert` e $O(n)$?

```cpp
vector<int> v = {1, 2, 3, 4, 5};
v.insert(v.begin() + 2, 99);
// Prima: [1, 2, 3, 4, 5]
// Dopo:  [1, 2, 99, 3, 4, 5]
```

Tutti gli elementi dopo la posizione di inserimento devono essere **spostati** di una posizione.

### 4.3 Perche `unordered_map` puo essere $O(n)$?

Nel caso peggiore, tutte le chiavi finiscono nello stesso bucket (collisione totale), trasformando la hash table in una lista.

---

## 5. Esercizi Risolti Tipo Esame

### Esercizio 1: Ciclo con Limite Costante

```cpp
void func(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 100; j++) {
            k++;
        }
    }
}
```

**Analisi:**
- Ciclo esterno: $n$ iterazioni
- Ciclo interno: **100 iterazioni** (costante, non dipende da n!)
- Corpo: $O(1)$
- Totale: $n \times 100 \times O(1) = 100n$

**Risposta: $O(n)$** - Le costanti si ignorano!

---

### Esercizio 2: While con Condizione Quadratica

```cpp
int i = 0;
while (i * i < n) {
    i++;
}
```

**Analisi:**
- Il ciclo termina quando $i^2 \geq n$
- Quindi $i \geq \sqrt{n}$
- Numero di iterazioni: circa $\sqrt{n}$

**Risposta: $O(\sqrt{n})$**

---

### Esercizio 3: Modifica dell'Indice Esterno

```cpp
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        k++;
        i++;  // ATTENZIONE!
    }
}
```

**Analisi passo-passo:**
- Prima iterazione esterna (i=0):
  - j va da 0 a n-1 (n iterazioni)
  - Ad ogni iterazione, i aumenta di 1
  - Alla fine: i = n
- Dopo il ciclo interno: i++ nel for -> i = n+1
- Condizione: i < n? No! -> ciclo esterno termina

**Totale operazioni:** solo $n$ (una passata del ciclo interno)

**Risposta: $O(n)$** - Non e quadratico!

---

### Esercizio 4: Somme Prefisse

**Problema:** Per ogni posizione, calcola la somma degli elementi precedenti.

**Soluzione Naive ($O(n^2)$):**
```cpp
for (int target = 0; target < n; target++) {
    int sum = 0;
    for (int i = 0; i <= target; i++) {
        sum += arr[i];
    }
    cout << sum << " ";
}
```

**Analisi:** $0 + 1 + 2 + ... + (n-1) = \frac{n(n-1)}{2} = O(n^2)$

**Soluzione Ottima ($O(n)$):**
```cpp
int sum = 0;
for (int i = 0; i < n; i++) {
    sum += arr[i];
    cout << sum << " ";
}
```

**Trucco:** Riutilizza il risultato parziale invece di ricalcolare da zero!

---

### Esercizio 5: Ricerca del Massimo e Minimo

```cpp
int max = arr[0], min = arr[0];
for (int i = 1; i < n; i++) {
    if (arr[i] > max) max = arr[i];
    if (arr[i] < min) min = arr[i];
}
```

**Analisi:**
- Un solo ciclo da 1 a n-1: $n-1$ iterazioni
- Ogni iterazione: 2 confronti = $O(1)$

**Risposta: $O(n)$**

---

### Esercizio 6: Ciclo Logaritmico Annidato

```cpp
for (int i = 1; i < n; i *= 2) {      // O(log n)
    for (int j = 0; j < n; j++) {      // O(n)
        cout << i + j;
    }
}
```

**Analisi:**
- Ciclo esterno: $\log n$ iterazioni
- Ciclo interno: $n$ iterazioni
- Totale: $\log n \times n$

**Risposta: $O(n \log n)$**

---

### Esercizio 7: Somma Geometrica

```cpp
for (int i = 1; i <= n; i *= 2) {
    for (int j = 0; j < i; j++) {
        k++;
    }
}
```

**Analisi:**
| i | Iterazioni j |
|---|--------------|
| 1 | 1 |
| 2 | 2 |
| 4 | 4 |
| ... | ... |
| n | n |

Totale: $1 + 2 + 4 + ... + n = 2n - 1$ (serie geometrica)

**Risposta: $O(n)$** - Non e $O(n \log n)$!

---

### Esercizio 8: Algoritmo con Vector

```cpp
void elabora(vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        v.insert(v.begin(), v[i]);  // Inserimento in testa!
    }
}
```

**Analisi:**
- Ciclo: $n$ iterazioni
- `v.insert(v.begin(), ...)`: $O(n)$ per ogni inserimento!
- Totale: $n \times O(n)$

**Risposta: $O(n^2)$**

---

## Consigli per l'Esame

1. **Identifica il caso peggiore** - E quello che chiedono quasi sempre

2. **Attenzione ai limiti costanti** - `j < 100` e $O(1)$, non conta!

3. **Cerca modifiche nascoste agli indici** - Possono cambiare tutto

4. **Somme note:**
   - Aritmetica: $1 + 2 + ... + n = \frac{n(n+1)}{2} = O(n^2)$
   - Geometrica: $1 + 2 + 4 + ... + n = 2n - 1 = O(n)$
   - Logaritmica: $\sum_{i=1}^{n} \frac{1}{i} = O(\log n)$

5. **Per le STL:** Ricorda le complessita delle operazioni!

6. **Se in dubbio, conta manualmente** per $n = 4$ o $n = 8$

7. **Costanti si ignorano:** $O(5n) = O(n)$, $O(n^2 + n) = O(n^2)$
