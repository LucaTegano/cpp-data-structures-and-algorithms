# Teoria Completa: Liste Concatenate in C++ (std::list)

Questo documento analizza la struttura dati `std::list` della STL con esempi pratici dagli esercizi.

---

## Indice
1. [Cos'e std::list](#1-cose-stdlist)
2. [Operazioni Fondamentali](#2-operazioni-fondamentali)
3. [Iteratori](#3-iteratori)
4. [Metodi Avanzati](#4-metodi-avanzati)
5. [Confronto list vs vector](#5-confronto-list-vs-vector)
6. [Esercizi Risolti](#6-esercizi-risolti)

---

## 1. Cos'e std::list

`std::list` e una **lista doppiamente concatenata**: ogni nodo contiene un valore e due puntatori (al nodo precedente e successivo).

```
  HEAD                                    TAIL
   |                                       |
   v                                       v
+-----+    +-----+    +-----+    +-----+
|  1  |<-->|  2  |<-->|  3  |<-->|  4  |
+-----+    +-----+    +-----+    +-----+
```

### Caratteristiche
- Inserimento/rimozione O(1) **con iteratore**
- Accesso O(n) - devi scorrere dal primo
- Non supporta `operator[]`
- Iteratori bidirezionali (non random access)

### Inclusione
```cpp
#include <list>
using namespace std;

list<int> numeri;
list<string> nomi;
```

---

## 2. Operazioni Fondamentali

### 2.1 Creazione e Inizializzazione

```cpp
// Lista vuota
list<int> l1;

// Lista con valori iniziali (C++11)
list<int> l2 = {1, 2, 3, 4, 5};

// Lista con n copie di un valore
list<int> l3(5, 0);  // {0, 0, 0, 0, 0}

// Copia di un'altra lista
list<int> l4(l2);
```

### 2.2 Inserimento

```cpp
list<int> l;

// In coda - O(1)
l.push_back(10);   // {10}
l.push_back(20);   // {10, 20}

// In testa - O(1)
l.push_front(5);   // {5, 10, 20}

// In posizione specifica - O(1) con iteratore
auto it = l.begin();
advance(it, 1);     // Vai al secondo elemento
l.insert(it, 7);    // {5, 7, 10, 20}
```

### 2.3 Rimozione

```cpp
list<int> l = {5, 7, 10, 20};

// Dalla coda - O(1)
l.pop_back();      // {5, 7, 10}

// Dalla testa - O(1)
l.pop_front();     // {7, 10}

// Elemento specifico - O(n) cerca + O(1) rimuove
l.remove(10);      // {7} - rimuove TUTTE le occorrenze di 10

// Con iteratore - O(1)
auto it = l.begin();
l.erase(it);       // {} - rimuove elemento puntato da it
```

### 2.4 Accesso

```cpp
list<int> l = {1, 2, 3, 4, 5};

// Primo elemento
int primo = l.front();   // 1

// Ultimo elemento
int ultimo = l.back();   // 5

// K-esimo elemento (NO operator[]!)
auto it = l.begin();
advance(it, 2);          // Vai al terzo elemento
int terzo = *it;         // 3
```

### 2.5 Informazioni

```cpp
list<int> l = {1, 2, 3};

bool vuota = l.empty();   // false
size_t dim = l.size();    // 3
```

---

## 3. Iteratori

### 3.1 Tipi di Iteratori

```cpp
list<int>::iterator it;        // Lettura/scrittura
list<int>::const_iterator cit; // Solo lettura
list<int>::reverse_iterator rit; // Scorre al contrario
```

### 3.2 Navigazione

```cpp
list<int> l = {10, 20, 30, 40, 50};

auto it = l.begin();  // Punta al primo (10)
++it;                 // Punta al secondo (20)
--it;                 // Torna al primo (10)

auto rit = l.rbegin(); // Punta all'ultimo (50) in reverse
++rit;                 // Punta al penultimo (40)
```

### 3.3 Pattern di Iterazione

```cpp
// Range-based for (C++11) - CONSIGLIATO
for (int x : l) {
    cout << x << " ";
}

// Con const reference (evita copie)
for (const int& x : l) {
    cout << x << " ";
}

// Con iteratori espliciti
for (auto it = l.begin(); it != l.end(); ++it) {
    cout << *it << " ";
}

// Reverse
for (auto rit = l.rbegin(); rit != l.rend(); ++rit) {
    cout << *rit << " ";
}
```

### 3.4 Invalidazione Iteratori

**ATTENZIONE:** Dopo `erase()`, l'iteratore diventa invalido!

```cpp
// SBAGLIATO - crash!
for (auto it = l.begin(); it != l.end(); ++it) {
    if (*it % 2 == 0) {
        l.erase(it);  // it ora e invalido!
    }
}

// CORRETTO
for (auto it = l.begin(); it != l.end(); ) {
    if (*it % 2 == 0) {
        it = l.erase(it);  // erase restituisce il prossimo valido
    } else {
        ++it;
    }
}
```

---

## 4. Metodi Avanzati

### 4.1 Ordinamento

```cpp
list<int> l = {3, 1, 4, 1, 5, 9};

// Ordine crescente
l.sort();  // {1, 1, 3, 4, 5, 9}

// Ordine decrescente
l.sort(greater<int>());  // {9, 5, 4, 3, 1, 1}

// Con comparatore custom
l.sort([](int a, int b) { return a > b; });
```

**NOTA:** Non puoi usare `std::sort()` con list perche richiede random access iterators!

### 4.2 Inversione

```cpp
list<int> l = {1, 2, 3, 4};
l.reverse();  // {4, 3, 2, 1}
```

### 4.3 Rimozione Duplicati

```cpp
list<int> l = {1, 1, 2, 2, 3, 3};

// ATTENZIONE: funziona solo su liste ORDINATE!
l.unique();  // {1, 2, 3}
```

### 4.4 Merge (Fusione Ordinata)

```cpp
list<int> l1 = {1, 3, 5};
list<int> l2 = {2, 4, 6};

// Entrambe devono essere ordinate!
l1.merge(l2);  
// l1 = {1, 2, 3, 4, 5, 6}
// l2 = {} (vuota)
```

### 4.5 Splice (Trasferimento Nodi)

```cpp
list<int> l1 = {1, 2, 3};
list<int> l2 = {10, 20};

// Sposta tutto l2 alla fine di l1
l1.splice(l1.end(), l2);
// l1 = {1, 2, 3, 10, 20}
// l2 = {}

// Sposta un singolo elemento
auto it = l1.begin();
advance(it, 2);  // Punta a 3
l2.splice(l2.begin(), l1, it);
// l1 = {1, 2, 10, 20}
// l2 = {3}
```

**Vantaggio:** Splice e O(1) - sposta puntatori, non copia dati!

---

## 5. Confronto list vs vector

| Operazione | list | vector |
|------------|------|--------|
| Accesso [i] | O(n) | **O(1)** |
| push_back | O(1) | O(1) amm. |
| push_front | **O(1)** | O(n) |
| insert (in mezzo) | **O(1)** con it | O(n) |
| erase (in mezzo) | **O(1)** con it | O(n) |
| Memoria | Piu overhead | Contigua |
| Cache locality | Scarsa | **Eccellente** |
| Iteratori dopo insert | **Validi** | Invalidati |

### Quando usare list?
- Frequenti inserimenti/rimozioni nel mezzo
- Necessita di stabilita degli iteratori
- Operazioni splice/merge frequenti

### Quando usare vector? (Nel 95% dei casi!)
- Accesso casuale frequente
- Iterazione semplice
- Cache efficiency importante

---

## 6. Esercizi Risolti

### Esercizio 1: Inserimento e Rimozione Pari

```cpp
// Crea lista 1-10, rimuovi i pari
list<int> numbers;
for (int i = 1; i <= 10; ++i) {
    numbers.push_back(i);
}

// Rimuovi pari (pattern corretto!)
for (auto it = numbers.begin(); it != numbers.end(); ) {
    if (*it % 2 == 0) {
        it = numbers.erase(it);
    } else {
        ++it;
    }
}
// Risultato: {1, 3, 5, 7, 9}
```

### Esercizio 2: Manipolazione Nomi

```cpp
list<string> names = {"Anna", "Luca", "Giovanni", "Paola"};

names.push_front("Marco");  // Aggiungi in testa
names.push_back("Elisa");   // Aggiungi in coda
names.remove("Luca");       // Rimuovi Luca

names.sort();  // Ordina alfabeticamente
// Risultato: {"Anna", "Elisa", "Giovanni", "Marco", "Paola"}
```

### Esercizio 3: Media Valori >= 50

```cpp
list<int> numbers;
srand(time(0));
for (int i = 0; i < 15; ++i) {
    numbers.push_back(rand() % 100 + 1);
}

// Rimuovi < 50
for (auto it = numbers.begin(); it != numbers.end(); ) {
    if (*it < 50) {
        it = numbers.erase(it);
    } else {
        ++it;
    }
}

// Calcola media
int somma = 0;
for (int n : numbers) somma += n;
double media = numbers.empty() ? 0 : (double)somma / numbers.size();
```

### Esercizio 4: Rimozione Duplicati

```cpp
list<int> numbers = {1, 2, 3, 2, 4, 1, 5, 3, 6};

// Metodo O(n^2) senza ordinare
for (auto it = numbers.begin(); it != numbers.end(); ++it) {
    auto it_inner = it;
    ++it_inner;
    
    while (it_inner != numbers.end()) {
        if (*it == *it_inner) {
            it_inner = numbers.erase(it_inner);
        } else {
            ++it_inner;
        }
    }
}
// Risultato: {1, 2, 3, 4, 5, 6}
```

### Esercizio 5: Bubble Sort su Lista

```cpp
void bubbleSortList(list<int>& lst) {
    bool swapped;
    do {
        swapped = false;
        for (auto it1 = lst.begin(); it1 != lst.end(); ++it1) {
            auto it2 = it1;
            ++it2;
            
            if (it2 != lst.end() && *it1 > *it2) {
                swap(*it1, *it2);  // Scambia valori, non nodi
                swapped = true;
            }
        }
    } while (swapped);
}
```

### Esercizio 6: Inversione Lista

```cpp
list<string> names = {"Anna", "Luca", "Giovanni", "Paola"};

names.reverse();
// Risultato: {"Paola", "Giovanni", "Luca", "Anna"}

// Stampa
for (const string& name : names) {
    cout << name << " ";
}
```

---

## Riepilogo Complessita

| Metodo | Complessita |
|--------|-------------|
| `push_front` / `push_back` | O(1) |
| `pop_front` / `pop_back` | O(1) |
| `insert` (con iteratore) | O(1) |
| `erase` (con iteratore) | O(1) |
| `remove` (per valore) | O(n) |
| `size` | O(1) (C++11+) |
| `sort` | O(n log n) |
| `reverse` | O(n) |
| `merge` | O(n) |
| `splice` | O(1) o O(n) |
| `unique` | O(n) |
| Accesso k-esimo | O(k) |
