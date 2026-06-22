# Lezione: Gestione Rubrica Telefonica con unordered_map

## Indice
1. [Introduzione](#1-introduzione)
2. [Hash Table: Concetti Fondamentali](#2-hash-table-concetti-fondamentali)
3. [std::unordered_map in C++](#3-stdunordered_map-in-c)
4. [Funzioni Hash Personalizzate](#4-funzioni-hash-personalizzate)
5. [Overloading degli Operatori](#5-overloading-degli-operatori)
6. [Complessità Computazionale](#6-complessità-computazionale)
7. [Confronto map vs unordered_map](#7-confronto-map-vs-unordered_map)
8. [Errori Comuni](#8-errori-comuni)
9. [Esercizi Proposti](#9-esercizi-proposti)

---

## 1. Introduzione

In questa lezione implementiamo una **rubrica telefonica** che associa persone a numeri di telefono. Utilizziamo `std::unordered_map` che offre operazioni in tempo **O(1)** medio grazie all'uso di **hash table**.

### Obiettivi Didattici
- Comprendere il funzionamento delle hash table
- Creare funzioni hash personalizzate per tipi custom
- Implementare operator overloading per I/O e confronto
- Gestire collisioni e bucket

### Struttura del Progetto
```
Pratica/
├── Persona.h       # Classe Persona con operator==, operator<<, operator>>
├── main.cpp        # Hash functor + logica rubrica con unordered_map
```

---

## 2. Hash Table: Concetti Fondamentali

### 2.1 Cos'è una Hash Table?

Una **hash table** è una struttura dati che implementa un **array associativo** (dizionario). Mappa chiavi a valori usando una **funzione hash**.

```
┌─────────────────────────────────────────────────────────────┐
│                    HASH TABLE                                │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│   Chiave ──────► h(chiave) ──────► indice ──────► Valore    │
│                                                              │
│   "Mario Rossi" ─► hash() ─► 42 ─► bucket[42] ─► "3331234"  │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

### 2.2 Funzione Hash

Una funzione hash `h: K → {0, 1, ..., m-1}` converte una chiave in un indice dell'array (bucket).

**Proprietà di una buona funzione hash:**
1. **Deterministica**: stessa chiave → stesso hash
2. **Uniforme**: distribuisce le chiavi uniformemente
3. **Efficiente**: calcolo in O(1)

### 2.3 Gestione delle Collisioni

Quando due chiavi diverse producono lo stesso hash (collisione), servono strategie:

```
┌─────────────────────────────────────────────────────────────┐
│ SEPARATE CHAINING (usato da unordered_map)                  │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│  Bucket[0] → NULL                                           │
│  Bucket[1] → [K1,V1] → [K5,V5] → NULL   ← Collisione!       │
│  Bucket[2] → [K2,V2] → NULL                                 │
│  Bucket[3] → NULL                                           │
│  Bucket[4] → [K3,V3] → [K7,V7] → [K9,V9] → NULL             │
│  ...                                                         │
│                                                              │
│  Ogni bucket è una lista di coppie (chiave, valore)         │
│  In caso di collisione, si aggiunge alla lista              │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

### 2.4 Load Factor

Il **load factor** `α = n/m` indica il rapporto tra elementi (n) e bucket (m).

- `α < 1`: poche collisioni, buone prestazioni
- `α > 1`: molte collisioni, prestazioni degradano
- `unordered_map` fa **rehashing** automatico quando α supera una soglia (~1.0)

---

## 3. std::unordered_map in C++

### 3.1 Dichiarazione

```cpp
#include <unordered_map>

// Sintassi generale
unordered_map<KeyType, ValueType, HashFunctor, EqualFunctor> mappa;

// Per tipi primitivi (hash già definito)
unordered_map<string, int> eta;
unordered_map<int, string> nomi;

// Per tipi custom (serve hash personalizzato)
unordered_map<Persona, string, Hash_Persona> rubrica;
```

### 3.2 Operazioni Principali

| Operazione | Sintassi | Complessità Media | Descrizione |
|------------|----------|-------------------|-------------|
| Inserimento | `m.insert({k, v})` | O(1) | Inserisce coppia |
| Inserimento | `m[k] = v` | O(1) | Inserisce o aggiorna |
| Ricerca | `m.find(k)` | O(1) | Ritorna iteratore |
| Accesso | `m[k]` | O(1) | Ritorna riferimento a valore |
| Accesso | `m.at(k)` | O(1) | Come [] ma con bounds check |
| Rimozione | `m.erase(k)` | O(1) | Rimuove elemento |
| Dimensione | `m.size()` | O(1) | Numero elementi |
| Vuota? | `m.empty()` | O(1) | true se vuota |
| Svuota | `m.clear()` | O(n) | Rimuove tutti |
| Contiene? | `m.count(k)` | O(1) | 0 o 1 (esiste?) |

### 3.3 Esempi di Utilizzo

```cpp
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main() {
    unordered_map<string, int> voti;
    
    // Inserimento
    voti["Mario"] = 28;           // operator[]
    voti.insert({"Luigi", 30});   // insert con initializer_list
    voti.emplace("Anna", 27);     // emplace (costruisce in-place)
    
    // Ricerca
    auto it = voti.find("Mario");
    if (it != voti.end()) {
        cout << it->first << ": " << it->second << endl;
        // Output: Mario: 28
    }
    
    // Accesso diretto
    cout << voti["Luigi"] << endl;  // 30
    
    // ATTENZIONE: operator[] crea elemento se non esiste!
    cout << voti["NonEsiste"] << endl;  // Crea "NonEsiste" con valore 0!
    
    // Sicuro: usare find() o count()
    if (voti.count("Pippo") > 0) {
        cout << voti["Pippo"] << endl;
    }
    
    // Iterazione
    for (const auto& [nome, voto] : voti) {  // C++17 structured binding
        cout << nome << " -> " << voto << endl;
    }
    
    // Rimozione
    voti.erase("Mario");  // Ritorna 1 se rimosso, 0 altrimenti
    
    return 0;
}
```

### 3.4 Differenza tra operator[] e at()

```cpp
unordered_map<string, int> m;
m["A"] = 10;

// operator[] - NON SICURO per lettura
int x = m["B"];  // Crea "B" con valore 0, poi ritorna 0!

// at() - SICURO, lancia eccezione se chiave non esiste
try {
    int y = m.at("C");  // throws std::out_of_range
} catch (const out_of_range& e) {
    cerr << "Chiave non trovata!" << endl;
}
```

---

## 4. Funzioni Hash Personalizzate

### 4.1 Perché Servono?

`std::unordered_map` usa `std::hash<Key>` di default, ma questo è definito solo per tipi primitivi e `std::string`. Per classi custom, dobbiamo fornire una funzione hash.

### 4.2 Implementazione come Functor (Struct con operator())

```cpp
class Persona {
private:
    string nome;
    string cognome;
public:
    string getNome() const { return nome; }
    string getCognome() const { return cognome; }
};

// Functor hash personalizzato
struct Hash_Persona {
    size_t operator()(const Persona& p) const {
        // Usa hash<string> della STL
        hash<string> hasher;
        
        size_t h1 = hasher(p.getNome());
        size_t h2 = hasher(p.getCognome());
        
        // Combina i due hash con XOR e shift
        return h1 ^ (h2 << 1);
    }
};

// Utilizzo
unordered_map<Persona, string, Hash_Persona> rubrica;
```

### 4.3 Combinazione di Hash

Il pattern `h1 ^ (h2 << 1)` combina due hash:

```
h1 = hash("Mario")  = 0b10110101...
h2 = hash("Rossi")  = 0b01101001...

h2 << 1             = 0b11010010...  (shift sinistro di 1 bit)

h1 ^ (h2 << 1)      = 0b01100111...  (XOR bit a bit)
```

**Perché lo shift?**
- Evita che `hash(A,B) == hash(B,A)` (commutatività indesiderata)
- Migliora la distribuzione

### 4.4 Tecniche Alternative di Combinazione

```cpp
// Metodo boost::hash_combine (più robusto)
template <typename T>
void hash_combine(size_t& seed, const T& value) {
    hash<T> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

// Uso
struct Hash_Persona_Boost {
    size_t operator()(const Persona& p) const {
        size_t seed = 0;
        hash_combine(seed, p.getNome());
        hash_combine(seed, p.getCognome());
        return seed;
    }
};
```

### 4.5 Requisiti per la Chiave

Per usare un tipo come chiave di `unordered_map` servono:

| Requisito | Perché | Come Implementare |
|-----------|--------|-------------------|
| Hash function | Per calcolare l'indice del bucket | `struct HashFunctor` o specializzare `std::hash<T>` |
| Equality operator | Per confrontare chiavi nello stesso bucket | `bool operator==(const T&) const` |

---

## 5. Overloading degli Operatori

### 5.1 Operatore di Uguaglianza (operator==)

**Fondamentale** per `unordered_map`: quando due chiavi hanno lo stesso hash (collisione), serve `operator==` per trovare quella corretta nel bucket.

```cpp
class Persona {
private:
    string nome;
    string cognome;
    
public:
    // operator== come metodo membro
    bool operator==(const Persona& other) const {
        return nome == other.nome && cognome == other.cognome;
    }
};
```

**Bug Comune (presente nel codice originale):**
```cpp
// SBAGLIATO - confronta other con se stesso!
bool operator==(const Persona& v) const {
    return v.nome == nome && v.cognome == v.cognome;  // BUG: v.cognome == v.cognome
}

// CORRETTO
bool operator==(const Persona& v) const {
    return nome == v.nome && cognome == v.cognome;
}
```

### 5.2 Operatori di I/O (operator<< e operator>>)

Gli operatori di streaming devono essere funzioni **friend** perché:
1. Il primo parametro è lo stream, non l'oggetto
2. Devono accedere ai membri privati

```cpp
class Persona {
    // Dichiarazione friend all'interno della classe
    friend istream& operator>>(istream& in, Persona& p);
    friend ostream& operator<<(ostream& out, const Persona& p);
    
private:
    string nome;
    string cognome;
};

// Definizione (può essere inline nella classe o esterna)
istream& operator>>(istream& in, Persona& p) {
    cout << "Inserisci nome: ";
    in >> p.nome;
    cout << "Inserisci cognome: ";
    in >> p.cognome;
    return in;  // Permette chaining: cin >> p1 >> p2
}

ostream& operator<<(ostream& out, const Persona& p) {
    out << "Nome: " << p.nome << endl;
    out << "Cognome: " << p.cognome << endl;
    return out;  // Permette chaining: cout << p1 << p2
}
```

### 5.3 Diagramma Friend Functions

```
┌─────────────────────────────────────────────────────────────┐
│ FRIEND FUNCTION vs MEMBER FUNCTION                          │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│ Member function:                                             │
│   p.print(cout)         ← l'oggetto è a sinistra            │
│   Firma: void Persona::print(ostream& out)                  │
│                                                              │
│ Friend function (operatore):                                 │
│   cout << p             ← lo stream è a sinistra!           │
│   Firma: ostream& operator<<(ostream&, const Persona&)      │
│                                                              │
│ Non possiamo fare cout.operator<<(p) perché non possiamo    │
│ modificare la classe ostream!                                │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

---

## 6. Complessità Computazionale

### 6.1 Tabella Complessità unordered_map

| Operazione | Caso Medio | Caso Peggiore | Note |
|------------|------------|---------------|------|
| `insert()` | O(1) | O(n) | Peggiore durante rehashing |
| `find()` | O(1) | O(n) | Peggiore con molte collisioni |
| `erase()` | O(1) | O(n) | Peggiore con molte collisioni |
| `operator[]` | O(1) | O(n) | Come find/insert |
| `size()` | O(1) | O(1) | Sempre costante |
| `clear()` | O(n) | O(n) | Deve deallocare tutto |

### 6.2 Quando il Caso Peggiore?

Il caso peggiore O(n) si verifica quando:
1. **Funzione hash pessima**: tutte le chiavi nello stesso bucket
2. **Molte collisioni**: load factor troppo alto
3. **Rehashing**: quando la tabella deve crescere

```
┌─────────────────────────────────────────────────────────────┐
│ CASO PESSIMO: Tutte le chiavi nello stesso bucket           │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│  Bucket[0] → NULL                                           │
│  Bucket[1] → NULL                                           │
│  Bucket[2] → [K1] → [K2] → [K3] → ... → [Kn] → NULL        │
│  Bucket[3] → NULL                                           │
│  ...                                                         │
│                                                              │
│  Ricerca: devo scorrere tutta la lista → O(n)               │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

### 6.3 Confronto con Altre Strutture

| Struttura | Ricerca | Inserimento | Ordinata? |
|-----------|---------|-------------|-----------|
| `vector` + linear search | O(n) | O(1) amm. | No |
| `vector` + binary search | O(log n) | O(n) | Sì |
| `list` | O(n) | O(1) | No |
| `set` (BST) | O(log n) | O(log n) | Sì |
| `map` (BST) | O(log n) | O(log n) | Sì |
| `unordered_set` | O(1) avg | O(1) avg | No |
| `unordered_map` | O(1) avg | O(1) avg | No |

---

## 7. Confronto map vs unordered_map

### 7.1 Differenze Strutturali

```
┌─────────────────────────────────────────────────────────────┐
│ std::map (Red-Black Tree)                                    │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│              [M]                                             │
│             /   \                                            │
│          [D]     [T]        Albero bilanciato               │
│         /  \    /   \       Elementi ordinati per chiave    │
│       [A]  [G][P]   [Z]     Richiede operator<              │
│                                                              │
└─────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────┐
│ std::unordered_map (Hash Table)                             │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│   [0] → [G,val] → NULL                                      │
│   [1] → NULL                 Tabella hash                   │
│   [2] → [A,val] → [M,val]    Elementi NON ordinati          │
│   [3] → [T,val] → NULL       Richiede hash + operator==     │
│   [4] → [D,val] → [P,val] → [Z,val]                         │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

### 7.2 Quando Usare Quale?

| Usa `map` quando... | Usa `unordered_map` quando... |
|---------------------|-------------------------------|
| Serve ordine delle chiavi | L'ordine non importa |
| Devi iterare in ordine | Performance è critica |
| Chiavi hanno solo `<` definito | Puoi definire hash + `==` |
| Dataset piccoli | Dataset grandi |
| Worst case O(log n) accettabile | O(1) medio necessario |

---

## 8. Errori Comuni

### 8.1 Bug nel Codice Originale

```cpp
// ❌ SBAGLIATO (Persona.h linea 38)
bool operator==(const Persona& v) const {
    return v.nome == nome && v.cognome == v.cognome;  // v.cognome == v.cognome sempre true!
}

// ✅ CORRETTO
bool operator==(const Persona& v) const {
    return nome == v.nome && cognome == v.cognome;
}
```

### 8.2 Missing break nel switch

```cpp
// ❌ SBAGLIATO (main.cpp linea 62-63)
case '3':
{
    // ... codice per eliminare ...
}  // MANCA break; → fall-through nel case '4'!
case '4':
{
    // ... questo viene eseguito anche dopo case '3'!
}
```

### 8.3 Uso di operator[] per Lettura

```cpp
// ❌ PERICOLOSO
if (rubrica[p] != "") {  // CREA l'elemento se non esiste!
    cout << rubrica[p];
}

// ✅ CORRETTO
if (rubrica.find(p) != rubrica.end()) {
    cout << rubrica[p];
}

// ✅ ANCHE CORRETTO
if (rubrica.count(p) > 0) {
    cout << rubrica.at(p);
}
```

### 8.4 Hash Non Definito per Tipo Custom

```cpp
// ❌ NON COMPILA
unordered_map<Persona, string> rubrica;  // Errore: no hash for Persona

// ✅ CORRETTO
unordered_map<Persona, string, Hash_Persona> rubrica;
```

### 8.5 operator== Non Definito

```cpp
// ❌ COMPILA MA CRASH A RUNTIME
struct Persona { string nome; };
struct Hash { size_t operator()(const Persona& p) const { return 0; } };
unordered_map<Persona, int, Hash> m;  // Manca operator==!
```

### 8.6 Statement Inutile

```cpp
// ❌ SBAGLIATO (main.cpp linea 10)
struct Hash_Persona {
    size_t operator()(const Persona& v) const {
        hash<string>{};  // ← Statement inutile! Non fa nulla
        size_t h1 = hash<string>{}(v.getNome());  // Questa è corretta
        ...
    }
};
```

---

## 9. Esercizi Proposti

### Esercizio 1: Rubrica con Email (Facile)
Estendi la classe `Persona` per includere un campo email. Aggiorna:
- La funzione hash per considerare anche l'email
- Gli operatori di I/O
- L'operator==

### Esercizio 2: Conteggio Occorrenze (Medio)
Scrivi un programma che legge parole da input e conta quante volte appare ciascuna parola usando `unordered_map<string, int>`.

```cpp
// Input: "ciao mondo ciao hello ciao"
// Output:
// ciao: 3
// mondo: 1
// hello: 1
```

### Esercizio 3: Cache LRU (Difficile)
Implementa una cache LRU (Least Recently Used) usando `unordered_map` + `list`:
- `get(key)`: ritorna il valore e marca come "usato di recente"
- `put(key, value)`: inserisce, rimuovendo il meno usato se la cache è piena

### Esercizio 4: Specializzazione std::hash (Avanzato)
Invece di usare un functor, specializza `std::hash<Persona>`:

```cpp
namespace std {
    template<>
    struct hash<Persona> {
        size_t operator()(const Persona& p) const {
            // ...
        }
    };
}

// Ora puoi usare senza terzo parametro
unordered_map<Persona, string> rubrica;  // Funziona!
```

---

## Appendice A: API Reference unordered_map

### Costruttori
```cpp
unordered_map<K,V> m;                    // Default
unordered_map<K,V> m(n);                 // n bucket iniziali
unordered_map<K,V> m(first, last);       // Da range di pair
unordered_map<K,V> m{{k1,v1}, {k2,v2}};  // Initializer list
unordered_map<K,V> m(other);             // Copy
unordered_map<K,V> m(std::move(other));  // Move
```

### Metodi sui Bucket
```cpp
m.bucket_count();           // Numero di bucket
m.max_bucket_count();       // Massimo numero di bucket
m.bucket_size(n);           // Elementi nel bucket n
m.bucket(key);              // In quale bucket finirebbe key
m.load_factor();            // n_elementi / n_bucket
m.max_load_factor();        // Soglia per rehashing
m.rehash(n);                // Forza almeno n bucket
m.reserve(n);               // Prepara spazio per n elementi
```

---

## Appendice B: Visualizzazione Hash Table

```
┌─────────────────────────────────────────────────────────────┐
│ ESEMPIO: Rubrica con 3 persone                              │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│ Inserimenti:                                                 │
│   rubrica[Persona("Mario","Rossi")] = "333-1234567"         │
│   rubrica[Persona("Anna","Verdi")] = "333-7654321"          │
│   rubrica[Persona("Luca","Bianchi")] = "333-9999999"        │
│                                                              │
│ Hash calculation (esempio):                                  │
│   hash("Mario") ^ (hash("Rossi") << 1) = 5                  │
│   hash("Anna") ^ (hash("Verdi") << 1) = 2                   │
│   hash("Luca") ^ (hash("Bianchi") << 1) = 5  ← Collisione!  │
│                                                              │
│ Stato interno (8 bucket):                                    │
│                                                              │
│   [0] → NULL                                                │
│   [1] → NULL                                                │
│   [2] → [Anna Verdi, 333-7654321] → NULL                    │
│   [3] → NULL                                                │
│   [4] → NULL                                                │
│   [5] → [Mario Rossi, 333-1234567] → [Luca Bianchi, ...]    │
│   [6] → NULL                                                │
│   [7] → NULL                                                │
│                                                              │
│ Ricerca "Luca Bianchi":                                      │
│   1. Calcola hash = 5                                        │
│   2. Vai a bucket[5]                                         │
│   3. Confronta con operator==:                               │
│      - "Mario Rossi" == "Luca Bianchi"? NO                  │
│      - "Luca Bianchi" == "Luca Bianchi"? SÌ → Trovato!      │
│   4. Ritorna "333-9999999"                                   │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```
