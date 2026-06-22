# Guida Pratica: Analisi del Codice `stackEtAl.cpp`

Questa guida analizza il file `stackEtAl.cpp` che implementa Stack, Queue e Priority Queue usando `std::list`.

---

## Struttura del File

Il file contiene 4 classi template:
1. `Stack<T>` - Pila (composizione)
2. `Queue<T>` - Coda (composizione)
3. `QueueINH<T>` - Coda (ereditarieta)
4. `QueueINHwithPriority<T>` - Coda con priorita (ereditarieta)

---

## Classe `Stack<T>` (Righe 7-17)

### Struttura
```cpp
template<typename T>
class Stack {
private:
    list<T> S;  // Contenitore interno
public:
    void push(T el) { S.push_back(el); }
    void pop() { assert(!S.empty()); S.pop_back(); }
    bool empty() { return S.empty(); }
    size_t size() { return S.size(); }
    T top() { return S.back(); }
};
```

### Analisi delle Operazioni

#### `push(T el)`
```cpp
void push(T el) { S.push_back(el); }
```
- **Cosa fa**: Inserisce un elemento in cima alla pila
- **Implementazione**: Usa `push_back` della lista
- **Complessita**: $O(1)$

**Esempio passo-passo:**
```cpp
Stack<int> s;
s.push(10);  // Lista: [10]        <- top
s.push(20);  // Lista: [10, 20]    <- top
s.push(30);  // Lista: [10, 20, 30] <- top
```

#### `pop()`
```cpp
void pop() { assert(!S.empty()); S.pop_back(); }
```
- **Cosa fa**: Rimuove l'elemento in cima
- **Precondizione**: La pila NON deve essere vuota (`assert`)
- **Complessita**: $O(1)$

**ATTENZIONE**: Se chiami `pop()` su pila vuota, il programma termina con errore!

```cpp
// SBAGLIATO - causa crash
Stack<int> s;
s.pop();  // assert fallisce!

// CORRETTO - controlla prima
if (!s.empty()) {
    s.pop();
}
```

#### `top()`
```cpp
T top() { return S.back(); }
```
- **Cosa fa**: Restituisce l'elemento in cima SENZA rimuoverlo
- **Complessita**: $O(1)$

---

## Classe `Queue<T>` (Righe 19-29)

### Struttura
```cpp
template<typename T>
class Queue {
private:
    list<T> S;
public:
    void enqueue(T el) { S.push_back(el); }
    void dequeue() { assert(!S.empty()); S.pop_front(); }
    bool empty() { return S.empty(); }
    size_t size() { return S.size(); }
    T front() { return S.front(); }
};
```

### Differenza con Stack

| Operazione | Stack | Queue |
|------------|-------|-------|
| Inserimento | `push_back` (in coda) | `push_back` (in coda) |
| Rimozione | `pop_back` (dalla coda) | `pop_front` (dalla testa) |
| Accesso | `back()` (coda) | `front()` (testa) |

**Visualizzazione:**
```
Stack (LIFO):
  push ->  [1, 2, 3]  <- pop/top
           
Queue (FIFO):
  front/dequeue <- [1, 2, 3] <- enqueue
```

### Esempio d'Uso
```cpp
Queue<string> q;
q.enqueue("A");  // [A]
q.enqueue("B");  // [A, B]
q.enqueue("C");  // [A, B, C]

cout << q.front();  // "A" (primo inserito)
q.dequeue();        // [B, C]
cout << q.front();  // "B"
```

---

## Classe `QueueINH<T>` (Righe 31-42)

### Struttura con Ereditarieta Protetta
```cpp
template<typename T>
class QueueINH : protected list<T> {
public:
    void enqueue(T el) { this->push_back(el); }
    void dequeue() { assert(!empty()); list<T>::pop_front(); }
    
    using list<T>::empty;  // Importa il metodo
    
    size_t size() { return list<T>::size(); }
    T front() { return list<T>::front(); }
};
```

### Differenze con la Versione a Composizione

#### 1. Accesso ai Metodi della Lista
**Composizione:**
```cpp
S.push_back(el);  // Accesso tramite oggetto S
```

**Ereditarieta:**
```cpp
this->push_back(el);        // Accesso tramite this (puntatore implicito)
// oppure
list<T>::push_back(el);     // Accesso esplicito con scope resolution
```

#### 2. `using` per Importare Metodi
```cpp
using list<T>::empty;
```
- Rende `empty()` pubblico senza ridefinirlo
- Evita di scrivere `bool empty() { return list<T>::empty(); }`

#### 3. Ereditarieta `protected`
```cpp
class QueueINH : protected list<T>
```
- I metodi pubblici di `list<T>` diventano `protected` in `QueueINH`
- L'utente esterno NON puo chiamare `push_front`, `pop_back`, ecc.
- Solo i metodi esplicitamente definiti sono accessibili

```cpp
QueueINH<int> q;
q.enqueue(5);    // OK - metodo pubblico di QueueINH
q.push_front(3); // ERRORE! push_front e protected
```

---

## Classe `QueueINHwithPriority<T>` (Righe 44-57)

### Struttura
```cpp
template<typename T>
class QueueINHwithPriority : public QueueINH<T> {
public:
    void enqueue(T el) {
        typename list<T>::iterator it = this->begin();
        while (it != this->end() && el <= (*it)) {
            it++;
        }
        this->insert(it, el);
    }
};
```

### Analisi dell'Inserimento Ordinato

#### Il Ciclo di Ricerca
```cpp
typename list<T>::iterator it = this->begin();
while (it != this->end() && el <= (*it)) {
    it++;
}
```

**Logica:**
1. Parti dall'inizio della lista
2. Finche l'elemento da inserire e <= all'elemento corrente, avanza
3. Fermati quando trovi un elemento minore o raggiungi la fine

**Risultato:** La lista rimane ordinata in ordine **decrescente**.

#### Esempio Passo-Passo

```cpp
QueueINHwithPriority<int> Q;

// Inserimento 3
Q.enqueue(3);
// Lista: [3]

// Inserimento 2
Q.enqueue(2);
// it = begin() -> *it = 3
// 2 <= 3? Si -> avanza
// it = end()
// Inserisci 2 prima di end()
// Lista: [3, 2]

// Inserimento 4
Q.enqueue(4);
// it = begin() -> *it = 3
// 4 <= 3? No -> stop!
// Inserisci 4 prima di 3
// Lista: [4, 3, 2]
```

#### `typename` - Perche e Necessario?
```cpp
typename list<T>::iterator it = ...
```

Serve perche `list<T>::iterator` e un **tipo dipendente** (dipende dal parametro template `T`). Il compilatore non sa se e un tipo o una variabile, quindi `typename` lo chiarisce.

**Regola:** Quando accedi a un tipo annidato di una classe template, usa `typename`.

---

## Analisi del `main()` (Righe 61-78)

```cpp
int main() {
    Stack<int> H;
    if (!H.empty())
        H.pop();  // Non eseguito (H e vuota)
    
    QueueINHwithPriority<int> Q;
    Q.enqueue(3);
    Q.enqueue(2);
    Q.enqueue(4);
    
    cout << Q.front() << " " << endl;  // 4
    Q.dequeue();
    cout << Q.front() << " " << endl;  // 3
    Q.dequeue();
    cout << Q.front() << " " << endl;  // 2
    
    if (Q.empty())
        cout << "coda vuota" << endl;  // Non stampato (c'e ancora 2)
}
```

### Trace dell'Esecuzione

| Operazione | Stato Lista | Output |
|------------|-------------|--------|
| `enqueue(3)` | [3] | - |
| `enqueue(2)` | [3, 2] | - |
| `enqueue(4)` | [4, 3, 2] | - |
| `Q.front()` | [4, 3, 2] | `4 ` |
| `dequeue()` | [3, 2] | - |
| `Q.front()` | [3, 2] | `3 ` |
| `dequeue()` | [2] | - |
| `Q.front()` | [2] | `2 ` |
| `Q.empty()` | [2] | `false` (nessun output) |

---

## Esercizi Pratici

### Esercizio 1: Inverti una Coda usando uno Stack

```cpp
void invertiCoda(Queue<int>& q) {
    Stack<int> s;
    
    // Svuota la coda nello stack
    while (!q.empty()) {
        s.push(q.front());
        q.dequeue();
    }
    
    // Ricarica la coda dallo stack (invertita)
    while (!s.empty()) {
        q.enqueue(s.top());
        s.pop();
    }
}

// Esempio:
// Coda iniziale: [1, 2, 3, 4]
// Coda finale:   [4, 3, 2, 1]
```

### Esercizio 2: Min-Priority Queue

Modifica `QueueINHwithPriority` per avere l'elemento minimo in testa:

```cpp
template<typename T>
class MinPriorityQueue : public QueueINH<T> {
public:
    void enqueue(T el) {
        typename list<T>::iterator it = this->begin();
        while (it != this->end() && el >= (*it)) {  // Cambiato <= in >=
            it++;
        }
        this->insert(it, el);
    }
};

// Esempio:
// Inserimenti: 3, 1, 4, 1, 5
// Lista: [1, 1, 3, 4, 5]
// front() restituisce 1 (minimo)
```

### Esercizio 3: Stack con Operazione getMin() in O(1)

```cpp
template<typename T>
class MinStack {
private:
    Stack<T> mainStack;
    Stack<T> minStack;  // Tiene traccia dei minimi

public:
    void push(T el) {
        mainStack.push(el);
        if (minStack.empty() || el <= minStack.top()) {
            minStack.push(el);
        }
    }
    
    void pop() {
        if (mainStack.top() == minStack.top()) {
            minStack.pop();
        }
        mainStack.pop();
    }
    
    T top() { return mainStack.top(); }
    T getMin() { return minStack.top(); }
    bool empty() { return mainStack.empty(); }
};
```

---

## Errori Comuni e Soluzioni

### 1. Chiamare `pop()`/`dequeue()` su struttura vuota
```cpp
// SBAGLIATO
while (true) {
    cout << stack.top();
    stack.pop();  // Crash quando vuoto!
}

// CORRETTO
while (!stack.empty()) {
    cout << stack.top();
    stack.pop();
}
```

### 2. Dimenticare `typename` con tipi dipendenti
```cpp
// SBAGLIATO - errore di compilazione
list<T>::iterator it = this->begin();

// CORRETTO
typename list<T>::iterator it = this->begin();
```

### 3. Confondere `this->` con `list<T>::` 
```cpp
// Questi sono equivalenti in questo contesto:
this->push_back(el);
list<T>::push_back(el);

// Ma per empty() usiamo using:
using list<T>::empty;
// Ora possiamo chiamare empty() direttamente
```

### 4. Dimenticare che Priority Queue e ordinata al contrario
```cpp
// front() restituisce il MASSIMO, non il minimo!
QueueINHwithPriority<int> pq;
pq.enqueue(1);
pq.enqueue(5);
pq.enqueue(3);
cout << pq.front();  // 5, non 1!
```

---

## Riepilogo Complessita

| Classe | `enqueue`/`push` | `dequeue`/`pop` | `front`/`top` |
|--------|------------------|-----------------|---------------|
| `Stack` | $O(1)$ | $O(1)$ | $O(1)$ |
| `Queue` | $O(1)$ | $O(1)$ | $O(1)$ |
| `QueueINH` | $O(1)$ | $O(1)$ | $O(1)$ |
| `QueueINHwithPriority` | $O(n)$ | $O(1)$ | $O(1)$ |

**Nota:** Per Priority Queue con heap (come `std::priority_queue`), l'inserimento e $O(\log n)$.
