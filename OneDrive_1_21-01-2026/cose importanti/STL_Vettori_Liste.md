# Cheat Sheet: std::vector, std::list e Adattatori

Guida ai container sequenziali e alle strutture dati astratte.

## Indice
1. [std::vector](#1-stdvector)
2. [std::list](#2-stdlist)
3. [std::deque](#3-stddeque)
4. [Stack e Queue](#4-stack-e-queue)
5. [Priority Queue](#5-priority-queue)

---

## 1. std::vector

Il container più usato. Array dinamico con accesso casuale.

| Operazione | Sintassi | Complessità |
| :--- | :--- | :--- |
| Inserimento in fondo | `v.push_back(x)` | $O(1)$ ammortizzato |
| Accesso i-esimo | `v[i]` / `v.at(i)` | $O(1)$ |
| Dimensione | `v.size()` | $O(1)$ |
| Cancellazione fine | `v.pop_back()` | $O(1)$ |
| Inserimento generico | `v.insert(it, x)` | $O(N)$ |
| Rimozione generica | `v.erase(it)` | $O(N)$ |

### Snippet: Riserva memoria (Performance)
Se sai già quanti elementi avrai, usa `reserve` per evitare riallocazioni continue.
```cpp
vector<int> v;
v.reserve(1000); // Alloca spazio ma size resta 0
```

---

## 2. std::list

Lista doppiamene concatenata. Non supporta l'accesso casuale (`v[i]`).

| Operazione | Sintassi | Complessità |
| :--- | :--- | :--- |
| Testa | `l.push_front(x)` / `l.pop_front()` | $O(1)$ |
| Coda | `l.push_back(x)` / `l.pop_back()` | $O(1)$ |
| Inserimento/Rimozione | `l.insert(it, x)` / `l.erase(it)` | $O(1)$ |

---

## 3. std::deque (Double Ended Queue)

Via di mezzo tra vector e list. Supporta `push_front` e `push_back` in $O(1)$ e mantiene l'accesso casuale $O(1)$.

```cpp
#include <deque>
deque<int> d;
d.push_front(10);
d.push_back(20);
cout << d[0]; // 10
```

---

## 4. Stack e Queue

### 4.1 std::stack (LIFO - Last In First Out)
```cpp
#include <stack>
stack<int> s;
s.push(10);     // Inserisce
s.top();        // Legge l'ultimo inserito (senza toglierlo)
s.pop();        // Rimuove l'ultimo inserito
s.empty();      // true se vuoto
```

### 4.2 std::queue (FIFO - First In First Out)
```cpp
#include <queue>
queue<int> q;
q.push(10);     // Inserisce in fondo
q.front();      // Legge il primo inserito
q.pop();        // Rimuove il primo inserito
```

---

## 5. Priority Queue

Mantiene gli elementi ordinati, permettendo l'estrazione rapida del massimo (di default).

```cpp
#include <queue>
priority_queue<int> pq;

pq.push(10);
pq.push(30);
pq.push(20);

cout << pq.top(); // 30 (il più grande)
pq.pop();
cout << pq.top(); // 20
```

### Snippet: Priority Queue per il Minimo
```cpp
priority_queue<int, vector<int>, greater<int>> min_pq;
min_pq.push(30);
min_pq.push(10);
cout << min_pq.top(); // 10 (il più piccolo)
```
