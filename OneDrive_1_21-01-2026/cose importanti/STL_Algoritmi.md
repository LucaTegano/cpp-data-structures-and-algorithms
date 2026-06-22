# Cheat Sheet: Algoritmi STL (<algorithm>)

Questo documento riassume gli algoritmi più utili della libreria standard C++, organizzati per categoria.

## Indice
1. [Ricerca e Conteggio](#1-ricerca-e-conteggio)
2. [Ordinamento](#2-ordinamento)
3. [Modifica Sequenze](#3-modifica-sequenze)
4. [Minimo e Massimo](#4-minimo-e-massimo)
5. [Algoritmi Numerici](#5-algoritmi-numerici)
6. [Comparatori e Lambda](#6-comparatori-e-lambda)

---

## 1. Ricerca e Conteggio

| Funzione | Scopo | Complessità |
| :--- | :--- | :--- |
| `find(beg, end, val)` | Trova la prima occorrenza di `val`. | $O(N)$ |
| `count(beg, end, val)` | Conta quante volte appare `val`. | $O(N)$ |
| `binary_search(beg, end, val)` | Verifica se `val` esiste (richiede range ordinato). | $O(\log N)$ |
| `lower_bound(beg, end, val)` | Primo elemento $\ge$ `val`. | $O(\log N)$ |
| `upper_bound(beg, end, val)` | Primo elemento $>$ `val`. | $O(\log N)$ |

### Snippet: Uso di find
```cpp
auto it = find(v.begin(), v.end(), 42);
if (it != v.end()) {
    cout << "Trovato in posizione: " << distance(v.begin(), it);
}
```

---

## 2. Ordinamento

| Funzione | Scopo | Note |
| :--- | :--- | :--- |
| `sort(beg, end)` | Ordina in modo crescente. | $O(N \log N)$ |
| `stable_sort(beg, end)` | Mantiene l'ordine relativo dei duplicati. | $O(N \log^2 N)$ |
| `is_sorted(beg, end)` | Ritorna true se il range è ordinato. | $O(N)$ |
| `reverse(beg, end)` | Inverte l'ordine degli elementi. | $O(N)$ |

### Snippet: Sort Decrescente
```cpp
sort(v.begin(), v.end(), greater<int>());
```

---

## 3. Modifica Sequenze

| Funzione | Scopo | Note |
| :--- | :--- | :--- |
| `copy(src_beg, src_end, dest_beg)` | Copia elementi. | - |
| `fill(beg, end, val)` | Riempie tutto il range con `val`. | - |
| `unique(beg, end)` | Raggruppa i duplicati in fondo (richiede sort). | Ritorna iteratore alla fine del nuovo range. |
| `replace(beg, end, old_v, new_v)` | Sostituisce ogni `old_v` con `new_v`. | - |

### Snippet: Rimuovere duplicati
```cpp
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());
```

---

## 4. Minimo e Massimo

| Funzione | Scopo | Note |
| :--- | :--- | :--- |
| `min_element(beg, end)` | Iteratore all'elemento minimo. | Usa `*` per il valore. |
| `max_element(beg, end)` | Iteratore all'elemento massimo. | Usa `*` per il valore. |
| `minmax_element(beg, end)` | Ritorna un `pair` di iteratori {min, max}. | - |
| `clamp(val, lo, hi)` | Forza `val` nell'intervallo [lo, hi]. | C++17 |

---

## 5. Algoritmi Numerici (`<numeric>`)

| Funzione | Scopo | Note |
| :--- | :--- | :--- |
| `accumulate(beg, end, init)` | Somma di tutti gli elementi. | `init` è il valore di partenza (es. 0). |
| `iota(beg, end, start_val)` | Riempie con valori sequenziali (1, 2, 3...). | Utile per indici. |

### Snippet: Media di un vector
```cpp
double media = accumulate(v.begin(), v.end(), 0.0) / v.size();
```

---

## 6. Comparatori e Lambda

Moltissimi algoritmi accettano un terzo parametro per personalizzare il comportamento.

### 6.1 Usando Struct (Functor)
```cpp
struct Comp {
    bool operator()(const Studente& a, const Studente& b) {
        return a.media > b.media; // Ordina per media decrescente
    }
};
sort(studenti.begin(), studenti.end(), Comp());
```

### 6.2 Usando Lambda (C++11+)
```cpp
sort(v.begin(), v.end(), [](int a, int b) {
    return abs(a) < abs(b); // Ordina per valore assoluto
});
```

### 6.3 Algoritmi "_if"
Molti algoritmi hanno una versione che accetta un predicato (condizione).
```cpp
// Conta quanti numeri sono divisibili per 3
int c = count_if(v.begin(), v.end(), [](int x){ return x % 3 == 0; });
```
