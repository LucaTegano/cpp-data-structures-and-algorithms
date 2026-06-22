# Teoria Completa: Pila, Coda e Coda con Priorita

Questo documento fornisce una spiegazione approfondita delle strutture dati **Pila (Stack)**, **Coda (Queue)** e **Coda con Priorita (Priority Queue)**, con implementazioni basate su `std::list`.

---

## Indice
1. [Strutture Dati Astratte (ADT)](#1-strutture-dati-astratte-adt)
2. [Pila (Stack)](#2-pila-stack)
3. [Coda (Queue)](#3-coda-queue)
4. [Coda con Priorita (Priority Queue)](#4-coda-con-priorita-priority-queue)
5. [Implementazioni con Ereditarieta](#5-implementazioni-con-ereditarieta)
6. [Confronto e Complessita](#6-confronto-e-complessita)
7. [Applicazioni Pratiche](#7-applicazioni-pratiche)

---

## 1. Strutture Dati Astratte (ADT)

Un **ADT (Abstract Data Type)** definisce:
- Un insieme di **dati**
- Un insieme di **operazioni** su quei dati
- NON specifica l'implementazione interna

### Vantaggi degli ADT
- **Incapsulamento**: l'utente non conosce i dettagli interni
- **Modularita**: facile sostituire l'implementazione
- **Riutilizzabilita**: interfaccia standard per diversi usi

---

## 2. Pila (Stack)

### Concetto
La pila segue il principio **LIFO** (Last In, First Out): l'ultimo elemento inserito e il primo a essere rimosso.

### Analogia
Pensa a una pila di piatti: puoi aggiungere/rimuovere solo dal sopra.

```
    TOP
    |
    v
  +---+
  | 4 |  <- Ultimo inserito, primo rimosso
  +---+
  | 3 |
  +---+
  | 2 |
  +---+
  | 1 |  <- Primo inserito, ultimo rimosso
  +---+
```

### Operazioni Fondamentali

| Operazione | Descrizione | Complessita |
|------------|-------------|-------------|
| `push(x)` | Inserisce `x` in cima | $O(1)$ |
| `pop()` | Rimuove l'elemento in cima | $O(1)$ |
| `top()` | Restituisce l'elemento in cima (senza rimuovere) | $O(1)$ |
| `empty()` | Verifica se la pila e vuota | $O(1)$ |
| `size()` | Restituisce il numero di elementi | $O(1)$ |

### Implementazione con Composizione

```cpp
#include <list>
#include <cassert>
using namespace std;

template<typename T>
class Stack {
private:
    list<T> S;  // La lista e il contenitore interno (composizione)

public:
    // Inserisce un elemento in cima alla pila
    void push(T el) {
        S.push_back(el);
    }
    
    // Rimuove l'elemento in cima alla pila
    void pop() {
        assert(!S.empty());  // Precondizione: pila non vuota
        S.pop_back();
    }
    
    // Restituisce l'elemento in cima senza rimuoverlo
    T top() {
        assert(!S.empty());
        return S.back();
    }
    
    // Verifica se la pila e vuota
    bool empty() {
        return S.empty();
    }
    
    // Restituisce il numero di elementi
    size_t size() {
        return S.size();
    }
};
```

### Esempio d'Uso

```cpp
int main() {
    Stack<int> pila;
    
    // Push di elementi
    pila.push(10);
    pila.push(20);
    pila.push(30);
    
    cout << "Top: " << pila.top() << endl;  // 30
    cout << "Size: " << pila.size() << endl; // 3
    
    // Pop e visualizzazione
    while (!pila.empty()) {
        cout << pila.top() << " ";  // 30 20 10
        pila.pop();
    }
    
    return 0;
}
```

### Perche `push_back` e `pop_back`?
Usiamo la **coda** della lista perche:
- Sia `push_back` che `pop_back` sono $O(1)$ in `std::list`
- Manteniamo la semantica LIFO: l'ultimo elemento inserito (back) e il primo rimosso

---

## 3. Coda (Queue)

### Concetto
La coda segue il principio **FIFO** (First In, First Out): il primo elemento inserito e il primo a essere rimosso.

### Analogia
Pensa alla coda al supermercato: chi arriva prima viene servito prima.

```
  FRONT                          BACK
    |                              |
    v                              v
  +---+   +---+   +---+   +---+
  | 1 |-->| 2 |-->| 3 |-->| 4 |
  +---+   +---+   +---+   +---+
    ^                        ^
    |                        |
  Primo                   Ultimo
  a uscire               inserito
```

### Operazioni Fondamentali

| Operazione | Descrizione | Complessita |
|------------|-------------|-------------|
| `enqueue(x)` | Inserisce `x` in fondo | $O(1)$ |
| `dequeue()` | Rimuove l'elemento in testa | $O(1)$ |
| `front()` | Restituisce l'elemento in testa | $O(1)$ |
| `empty()` | Verifica se la coda e vuota | $O(1)$ |
| `size()` | Restituisce il numero di elementi | $O(1)$ |

### Implementazione con Composizione

```cpp
template<typename T>
class Queue {
private:
    list<T> S;

public:
    // Inserisce un elemento in fondo alla coda
    void enqueue(T el) {
        S.push_back(el);
    }
    
    // Rimuove l'elemento in testa alla coda
    void dequeue() {
        assert(!S.empty());
        S.pop_front();
    }
    
    // Restituisce l'elemento in testa senza rimuoverlo
    T front() {
        assert(!S.empty());
        return S.front();
    }
    
    // Verifica se la coda e vuota
    bool empty() {
        return S.empty();
    }
    
    // Restituisce il numero di elementi
    size_t size() {
        return S.size();
    }
};
```

### Esempio d'Uso

```cpp
int main() {
    Queue<string> coda;
    
    // Enqueue di clienti
    coda.enqueue("Mario");
    coda.enqueue("Luigi");
    coda.enqueue("Peach");
    
    cout << "Prossimo cliente: " << coda.front() << endl;  // Mario
    
    // Servi i clienti
    while (!coda.empty()) {
        cout << "Servo: " << coda.front() << endl;
        coda.dequeue();
    }
    // Output:
    // Servo: Mario
    // Servo: Luigi
    // Servo: Peach
    
    return 0;
}
```

### Perche `push_back` e `pop_front`?
- `push_back`: inserisci alla fine (ultimo arrivato)
- `pop_front`: rimuovi dalla testa (primo arrivato)
- Entrambe operazioni $O(1)$ in `std::list`

---

## 4. Coda con Priorita (Priority Queue)

### Concetto
Una coda con priorita serve gli elementi in base alla loro **priorita**, non all'ordine di arrivo.

### Tipi
- **Max-Priority Queue**: l'elemento con priorita massima esce per primo
- **Min-Priority Queue**: l'elemento con priorita minima esce per primo

### Operazioni Fondamentali

| Operazione | Descrizione | Complessita |
|------------|-------------|-------------|
| `enqueue(x)` | Inserisce `x` nella posizione corretta | $O(n)$ |
| `dequeue()` | Rimuove l'elemento con priorita massima | $O(1)$ |
| `front()` | Restituisce l'elemento con priorita massima | $O(1)$ |
| `empty()` | Verifica se la coda e vuota | $O(1)$ |

### Implementazione con Inserimento Ordinato

```cpp
template<typename T>
class PriorityQueue {
private:
    list<T> S;

public:
    // Inserisce mantenendo l'ordine decrescente
    // Elementi maggiori all'inizio (max-priority)
    void enqueue(T el) {
        typename list<T>::iterator it = S.begin();
        
        // Trova la posizione corretta
        while (it != S.end() && el <= (*it)) {
            it++;
        }
        
        // Inserisce prima di it
        S.insert(it, el);
    }
    
    // Rimuove l'elemento con priorita massima (in testa)
    void dequeue() {
        assert(!S.empty());
        S.pop_front();
    }
    
    // Restituisce l'elemento con priorita massima
    T front() {
        assert(!S.empty());
        return S.front();
    }
    
    bool empty() {
        return S.empty();
    }
    
    size_t size() {
        return S.size();
    }
};
```

### Come Funziona l'Inserimento?

```cpp
// Inserimento di 3, 2, 4 in ordine

// Dopo enqueue(3):
// Lista: [3]

// Dopo enqueue(2):
// - Confronto: 2 <= 3? Si, avanzo
// - Fine lista, inserisco qui
// Lista: [3, 2]

// Dopo enqueue(4):
// - Confronto: 4 <= 3? No, inserisco qui
// Lista: [4, 3, 2]
```

### Esempio d'Uso

```cpp
int main() {
    PriorityQueue<int> pq;
    
    pq.enqueue(3);
    pq.enqueue(1);
    pq.enqueue(4);
    pq.enqueue(1);
    pq.enqueue(5);
    pq.enqueue(9);
    
    // Estrazione in ordine di priorita
    while (!pq.empty()) {
        cout << pq.front() << " ";
        pq.dequeue();
    }
    // Output: 9 5 4 3 1 1
    
    return 0;
}
```

---

## 5. Implementazioni con Ereditarieta

### Coda con Ereditarieta Protetta

```cpp
template<typename T>
class QueueINH : protected list<T> {
public:
    void enqueue(T el) {
        this->push_back(el);
    }
    
    void dequeue() {
        assert(!empty());
        list<T>::pop_front();
    }
    
    // Importa empty() dalla classe base
    using list<T>::empty;
    
    size_t size() {
        return list<T>::size();
    }
    
    T front() {
        return list<T>::front();
    }
};
```

### Perche `protected`?
- L'ereditarieta `protected` nasconde i metodi di `list<T>` all'esterno
- L'utente non puo chiamare direttamente `push_front`, `pop_back`, ecc.
- Solo i metodi definiti in `QueueINH` sono accessibili

### Coda con Priorita che Eredita dalla Coda

```cpp
template<typename T>
class QueueINHwithPriority : public QueueINH<T> {
public:
    // Override di enqueue per inserimento ordinato
    void enqueue(T el) {
        typename list<T>::iterator it = this->begin();
        
        while (it != this->end() && el <= (*it)) {
            it++;
        }
        
        this->insert(it, el);
    }
    // dequeue, front, empty, size sono ereditati da QueueINH
};
```

### Diagramma delle Classi

```
      +-------------+
      |  std::list  |
      +-------------+
            ^
            | protected
            |
      +-----------+
      | QueueINH  |
      +-----------+
      | +enqueue()|
      | +dequeue()|
      | +front()  |
      +-----------+
            ^
            | public
            |
+------------------------+
| QueueINHwithPriority   |
+------------------------+
| +enqueue() [override]  |
+------------------------+
```

---

## 6. Confronto e Complessita

### Tabella Comparativa

| Struttura | Inserimento | Rimozione | Accesso | Criterio |
|-----------|-------------|-----------|---------|----------|
| Stack | $O(1)$ top | $O(1)$ top | $O(1)$ top | LIFO |
| Queue | $O(1)$ back | $O(1)$ front | $O(1)$ front | FIFO |
| PriorityQueue (lista) | $O(n)$ | $O(1)$ | $O(1)$ max | Priorita |
| PriorityQueue (heap) | $O(\log n)$ | $O(\log n)$ | $O(1)$ max | Priorita |

### Quando Usare Cosa?

**Stack:**
- Undo/Redo in editor
- Valutazione espressioni
- Backtracking
- Chiamate a funzione (call stack)

**Queue:**
- BFS (Breadth-First Search)
- Buffer di stampa
- Gestione richieste server

**Priority Queue:**
- Algoritmo di Dijkstra
- Scheduling CPU
- Compressione Huffman
- Gestione emergenze ospedale

---

## 7. Applicazioni Pratiche

### 7.1 Verifica Parentesi Bilanciate (Stack)

```cpp
bool parentesiBilanciate(const string& expr) {
    Stack<char> stack;
    
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (stack.empty()) return false;
            
            char top = stack.top();
            stack.pop();
            
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                return false;
            }
        }
    }
    
    return stack.empty();
}

// Esempi
// parentesiBilanciate("((a+b)*c)") -> true
// parentesiBilanciate("[(a+b])") -> false
// parentesiBilanciate("((())") -> false
```

### 7.2 Inversione di una Stringa (Stack)

```cpp
string inverti(const string& s) {
    Stack<char> stack;
    
    for (char c : s) {
        stack.push(c);
    }
    
    string result = "";
    while (!stack.empty()) {
        result += stack.top();
        stack.pop();
    }
    
    return result;
}

// inverti("ciao") -> "oaic"
```

### 7.3 Simulazione Coda Supermercato

```cpp
void simulaCoda() {
    Queue<string> coda;
    
    // Arrivano clienti
    coda.enqueue("Cliente 1");
    coda.enqueue("Cliente 2");
    coda.enqueue("Cliente 3");
    
    // Servi 2 clienti
    for (int i = 0; i < 2 && !coda.empty(); i++) {
        cout << "Servo: " << coda.front() << endl;
        coda.dequeue();
    }
    
    // Arrivano altri clienti
    coda.enqueue("Cliente 4");
    coda.enqueue("Cliente 5");
    
    // Servi tutti
    while (!coda.empty()) {
        cout << "Servo: " << coda.front() << endl;
        coda.dequeue();
    }
}
```

### 7.4 Gestione Emergenze (Priority Queue)

```cpp
struct Paziente {
    string nome;
    int priorita;  // 1=critico, 5=non urgente
    
    // Operatore per confronto (priorita minore = piu urgente)
    bool operator<=(const Paziente& other) const {
        return this->priorita >= other.priorita;
    }
};

int main() {
    PriorityQueue<Paziente> pronto_soccorso;
    
    pronto_soccorso.enqueue({"Mario", 3});
    pronto_soccorso.enqueue({"Luigi", 1});  // Critico!
    pronto_soccorso.enqueue({"Peach", 5});
    pronto_soccorso.enqueue({"Toad", 2});
    
    while (!pronto_soccorso.empty()) {
        Paziente p = pronto_soccorso.front();
        cout << "Visita: " << p.nome << " (priorita " << p.priorita << ")" << endl;
        pronto_soccorso.dequeue();
    }
    // Output:
    // Visita: Luigi (priorita 1)
    // Visita: Toad (priorita 2)
    // Visita: Mario (priorita 3)
    // Visita: Peach (priorita 5)
    
    return 0;
}
```

---

## Riepilogo

| Struttura | Principio | Operazione Chiave | Implementazione |
|-----------|-----------|-------------------|-----------------|
| **Stack** | LIFO | `push`, `pop`, `top` | `list::push_back/pop_back` |
| **Queue** | FIFO | `enqueue`, `dequeue`, `front` | `list::push_back/pop_front` |
| **Priority Queue** | Priorita | `enqueue` ordinato | `list::insert` nella posizione |

### Punti Chiave per l'Esame

1. **Stack = LIFO**: L'ultimo inserito e il primo a uscire
2. **Queue = FIFO**: Il primo inserito e il primo a uscire
3. **PriorityQueue**: L'elemento con priorita massima esce per primo
4. **Ereditarieta protected**: Nasconde l'interfaccia della classe base
5. **`using`**: Importa un metodo dalla classe base senza ridefinirlo
