# Guida Pratica: Gestione Rubrica Telefonica

## Indice
1. [Panoramica del Progetto](#1-panoramica-del-progetto)
2. [Analisi di Persona.h](#2-analisi-di-personah)
3. [Analisi di main.cpp](#3-analisi-di-maincpp)
4. [Trace di Esecuzione](#4-trace-di-esecuzione)
5. [Bug e Correzioni](#5-bug-e-correzioni)
6. [Estensioni Suggerite](#6-estensioni-suggerite)

---

## 1. Panoramica del Progetto

### 1.1 Obiettivo
Implementare una rubrica telefonica interattiva che:
- Associa persone (nome, cognome) a numeri di telefono
- Supporta operazioni CRUD (Create, Read, Update, Delete)
- Usa `unordered_map` per accesso O(1)

### 1.2 File del Progetto

```
Pratica/
├── Persona.h    # Classe Persona con operator overloading
├── main.cpp     # Hash functor + menu interattivo
```

### 1.3 Struttura Dati Principale

```cpp
unordered_map<Persona, string, Hash_Persona> rubrica;
//            ↑         ↑      ↑
//            Chiave    Valore Hash functor personalizzato
//            (Nome,    (Numero
//            Cognome)  telefono)
```

### 1.4 Diagramma delle Dipendenze

```
┌─────────────────────────────────────────────────────────────┐
│                       main.cpp                               │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│  #include "Persona.h"                                        │
│  #include <unordered_map>                                    │
│                                                              │
│  ┌─────────────────┐     ┌─────────────────────────────┐    │
│  │   Hash_Persona  │     │     unordered_map           │    │
│  │   (functor)     │────►│  <Persona, string,          │    │
│  │   operator()    │     │   Hash_Persona>             │    │
│  └─────────────────┘     └─────────────────────────────┘    │
│          ↓                          ↓                        │
│  ┌─────────────────┐     ┌─────────────────────────────┐    │
│  │    Persona.h    │     │   Operazioni Menu           │    │
│  │  - nome         │     │   1. Inserisci              │    │
│  │  - cognome      │     │   2. Cerca                  │    │
│  │  - operator==   │     │   3. Elimina                │    │
│  │  - operator>>   │     │   4. Modifica numero        │    │
│  │  - operator<<   │     │   5. Modifica nome/cognome  │    │
│  └─────────────────┘     │   6. Stampa tutto           │    │
│                          │   7. Svuota                  │    │
│                          └─────────────────────────────┘    │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

---

## 2. Analisi di Persona.h

### 2.1 Codice Completo Annotato

```cpp
#ifndef PERSONA_H    // Include guard - evita inclusioni multiple
#define PERSONA_H
#include <iostream>
using namespace std;

class Persona {

    // ═══════════════════════════════════════════════════════════
    // FRIEND FUNCTIONS - Operatori I/O
    // Dichiarate friend perché il primo parametro è lo stream,
    // non l'oggetto Persona
    // ═══════════════════════════════════════════════════════════

    friend istream& operator>> (istream& in, Persona& v) {
        // Legge una Persona da input stream
        // Nota: stampa prompt su cout anche se legge da file!
        cout << "Inserisci il nome -> ";
        in >> v.nome;

        cout << endl << "Inserisci il cognome -> ";
        in >> v.cognome;

        cout << endl;

        return in;  // Ritorna stream per permettere chaining
                    // Es: cin >> p1 >> p2 >> p3;
    }

    friend ostream& operator<< (ostream& out, const Persona& v) {
        // Scrive una Persona su output stream
        out << "Nome: " << v.nome << endl;
        out << "Cognome: " << v.cognome << endl;
       
        return out;  // Ritorna stream per chaining
    }

    
private:
    string nome;
    string cognome;

public:
    
    // Getter - necessari per Hash_Persona che è esterna alla classe
    string getNome() const { return nome; }
    string getCognome() const { return cognome; }

    // ⚠️ BUG: v.cognome == v.cognome è sempre true!
    // Dovrebbe essere: cognome == v.cognome
    bool operator==(const Persona& v) const {
        return v.nome == nome && v.cognome == v.cognome;
    }

};
#endif
```

### 2.2 Anatomia di operator>>

```
istream& operator>>(istream& in, Persona& v)
   │          │         │            │
   │          │         │            └─ Riferimento modificabile
   │          │         │               (deve scrivere i dati)
   │          │         │
   │          │         └─ Stream di input (cin, ifstream, etc.)
   │          │
   │          └─ Ritorna riferimento allo stream
   │             (permette chaining: cin >> p1 >> p2)
   │
   └─ Tipo di ritorno

Perché è friend?
- Non è un metodo di Persona
- È una funzione libera che accede ai membri privati
- La sintassi richiede: cin >> persona (stream a sinistra)
- Se fosse metodo: persona.leggi(cin) (poco naturale)
```

### 2.3 Flusso di operator==

```
persona1 == persona2

      persona1                    persona2
   ┌────────────┐              ┌────────────┐
   │ nome: "A"  │              │ nome: "A"  │
   │ cognome:"B"│              │ cognome:"B"│
   └────────────┘              └────────────┘
         │                           │
         └───────────┬───────────────┘
                     ▼
         this->nome == v.nome?  "A" == "A" → true
                AND
         this->cognome == v.cognome?  "B" == "B" → true
                     │
                     ▼
                  RESULT: true

⚠️ Nel codice originale c'è un bug!
   v.cognome == v.cognome confronta v con se stesso → sempre true
```

---

## 3. Analisi di main.cpp

### 3.1 Hash Functor

```cpp
struct Hash_Persona {
    size_t operator()(const Persona& v) const {
        // ⚠️ LINEA INUTILE - statement senza effetto
        hash<string>{};  // Crea oggetto temporaneo, lo scarta
        
        // Calcola hash del nome
        size_t h1 = hash<string>{}(v.getNome());
        //          └─────┬─────┘ └──────┬─────┘
        //    Crea hash<string>   Chiama operator() su di esso
        
        // Calcola hash del cognome
        size_t h2 = hash<string>{}(v.getCognome());
        
        // Combina i due hash
        return h1 ^ (h2 << 1);
    }
};
```

**Spiegazione della combinazione `h1 ^ (h2 << 1)`:**

```
Esempio con valori semplificati (8 bit invece di 64):

h1 = hash("Mario") = 10110101
h2 = hash("Rossi") = 01101001

h2 << 1 (shift left di 1 bit):
   01101001
   ────────
   11010010  (ultimo bit diventa 0, tutti gli altri shiftano)

h1 ^ (h2 << 1) (XOR bit a bit):
   10110101
 ^ 11010010
   ────────
   01100111  ← Risultato finale

Perché lo shift?
- Senza: hash("Mario","Rossi") potrebbe == hash("Rossi","Mario")
- Con shift: l'ordine conta, risultati diversi
```

### 3.2 Dichiarazione della Rubrica

```cpp
unordered_map<Persona, string, Hash_Persona> rubrica;
//            │        │       │
//            │        │       └─ Terzo parametro template:
//            │        │          functor per calcolare hash
//            │        │
//            │        └─ Tipo del valore: numero di telefono
//            │
//            └─ Tipo della chiave: persona (nome + cognome)

// Internamente:
// rubrica = {
//     bucket[0]: lista vuota
//     bucket[1]: [(Persona("Mario","Rossi"), "333-1234567")]
//     bucket[2]: lista vuota
//     ...
// }
```

### 3.3 Operazione 1: Inserimento

```cpp
case '1':
{
    Persona p; 
    cin >> p;  // Chiama operator>> → legge nome e cognome

    cout << "Inserisci n. di telefono -> ";
    string n_di_telefono; 
    cin >> n_di_telefono;

    rubrica.insert({p, n_di_telefono});
    // Equivalente a: rubrica.insert(make_pair(p, n_di_telefono));
    // Equivalente a: rubrica[p] = n_di_telefono;
    
    break;
}
```

**Trace inserimento:**
```
Input utente: Mario, Rossi, 333-1234567

1. cin >> p
   - operator>>(cin, p) chiamato
   - p.nome = "Mario"
   - p.cognome = "Rossi"

2. cin >> n_di_telefono
   - n_di_telefono = "333-1234567"

3. rubrica.insert({p, n_di_telefono})
   - Calcola hash: Hash_Persona{}(p)
     - h1 = hash("Mario") = 12345 (esempio)
     - h2 = hash("Rossi") = 67890
     - result = 12345 ^ (67890 << 1) = 148159
   - bucket_index = 148159 % bucket_count
   - Inserisce nel bucket corrispondente
```

### 3.4 Operazione 2: Ricerca

```cpp
case '2':
{
    Persona p; 
    cin >> p;  // Legge chi cercare

    if (rubrica.find(p) != rubrica.end())
        // Trovato! Stampa il numero
        cout << "Il numero di telefono di " 
             << p.getNome() << " " << p.getCognome() 
             << " e' " << rubrica[p] << endl;
    else
        cout << "Contatto non presente in rubrica" << endl;

    break;
}
```

**Processo di ricerca:**
```
Cerco: Persona("Mario", "Rossi")

1. Calcola hash della chiave cercata
   hash = Hash_Persona{}(p) = 148159

2. Trova il bucket
   bucket_index = 148159 % bucket_count = 3 (esempio)

3. Scorri la lista nel bucket[3]
   - Elemento 1: Persona("Anna", "Verdi")
     operator==: "Mario" == "Anna"? NO, continua
   - Elemento 2: Persona("Mario", "Rossi")  
     operator==: "Mario" == "Mario" && "Rossi" == "Rossi"? SÌ!
   
4. Trovato! Ritorna iteratore all'elemento
```

### 3.5 Operazione 3: Eliminazione

```cpp
case '3':
{
    Persona p; 
    cin >> p;

    if (rubrica.erase(p))  // erase ritorna numero elementi rimossi
        cout << "Contatto eliminato" << endl;
    else 
        cout << "Contatto non presente in rubrica" << endl;
}
// ⚠️ BUG: MANCA break; → Fall-through nel case '4'!
```

### 3.6 Operazione 4: Modifica Numero

```cpp
case '4':
{
    Persona p; 
    cin >> p;
    
    // Prima verifica che esista
    if (rubrica.find(p) == rubrica.end()) {
        cout << "Contatto non presente" << endl;
        break;
    }

    // Modifica il valore associato alla chiave
    cout << "Inserisci il nuovo numero -> ";
    string n_di_telefono; 
    cin >> n_di_telefono;
    
    rubrica[p] = n_di_telefono;  // Sovrascrive il valore
    // operator[] con chiave esistente: ritorna riferimento al valore

    break;
}
```

### 3.7 Operazione 5: Modifica Nome/Cognome

```cpp
case '5':
{
    Persona p; 
    cin >> p;
    
    if (rubrica.find(p) == rubrica.end()) {
        cout << "Contatto non presente" << endl;
        break;
    }
    
    // Salva il numero prima di eliminare
    string n_di_telefono = rubrica[p];
    
    // Elimina la vecchia voce
    // (La chiave cambia → hash cambia → deve essere reinserita)
    rubrica.erase(p);

    // Leggi i nuovi dati
    cout << "Inserisci i nuovi dati." << endl;
    cin >> p;

    // Reinserisci con lo stesso numero
    rubrica.insert({p, n_di_telefono});
    
    break;
}
```

**Perché non possiamo modificare la chiave in-place?**
```
La chiave determina il bucket!
Se cambia nome/cognome → cambia hash → cambierebbe bucket

SBAGLIATO:
  it->first.setNome("Nuovo");  // Non si può! first è const

CORRETTO:
  1. Salva il valore
  2. Elimina la vecchia entry
  3. Crea nuova chiave
  4. Inserisci con nuova chiave e vecchio valore
```

### 3.8 Operazione 6: Stampa Tutto

```cpp
case '6':
{
    // Iteratore su pair<const Persona, string>
    for (auto it = rubrica.begin(); it != rubrica.end(); ++it) {
        cout << endl << it->first;   // Chiave (Persona)
        // Chiama operator<<(cout, it->first)
        
        cout << "Numero di telefono: " << it->second << endl;  // Valore
    }

    break;
}
```

**Versione moderna con range-based for:**
```cpp
for (const auto& [persona, telefono] : rubrica) {
    cout << persona;  // C++17 structured bindings
    cout << "Telefono: " << telefono << endl;
}
```

### 3.9 Operazione 7: Svuota

```cpp
case '7':
{
    cout << "Rubrica svuotata" << endl;
    // ⚠️ BUG: Non chiama mai rubrica.clear()!
    break;
}
```

---

## 4. Trace di Esecuzione

### 4.1 Scenario Completo

```
Stato iniziale: rubrica = {}

═══════════════════════════════════════════════════════════════
OPERAZIONE: Inserisci Mario Rossi, 333-111
═══════════════════════════════════════════════════════════════

Input: 1, Mario, Rossi, 333-111

Esecuzione:
  1. cin >> p → p = Persona("Mario", "Rossi")
  2. cin >> tel → tel = "333-111"
  3. rubrica.insert({p, tel})
     - hash(p) = hash("Mario") ^ (hash("Rossi") << 1) = 42 (esempio)
     - bucket = 42 % 8 = 2
     - bucket[2].push_back({p, tel})

Stato: rubrica = {
    bucket[2]: [("Mario Rossi", "333-111")]
}

═══════════════════════════════════════════════════════════════
OPERAZIONE: Inserisci Anna Verdi, 333-222
═══════════════════════════════════════════════════════════════

Input: 1, Anna, Verdi, 333-222

Esecuzione:
  1. hash(Anna Verdi) = 42 (collisione!)
  2. bucket[2].push_back({Anna Verdi, "333-222"})

Stato: rubrica = {
    bucket[2]: [("Mario Rossi", "333-111"), ("Anna Verdi", "333-222")]
}

═══════════════════════════════════════════════════════════════
OPERAZIONE: Cerca Anna Verdi
═══════════════════════════════════════════════════════════════

Input: 2, Anna, Verdi

Esecuzione:
  1. hash(Anna Verdi) = 42
  2. bucket = 42 % 8 = 2
  3. Scorri bucket[2]:
     - [0] = "Mario Rossi" == "Anna Verdi"? NO
     - [1] = "Anna Verdi" == "Anna Verdi"? SÌ!
  4. Ritorna iteratore → stampa "333-222"

Output: "Il numero di telefono di Anna Verdi e' 333-222"

═══════════════════════════════════════════════════════════════
OPERAZIONE: Modifica nome Anna Verdi → Anna Bianchi
═══════════════════════════════════════════════════════════════

Input: 5, Anna, Verdi, Anna, Bianchi

Esecuzione:
  1. Trova Anna Verdi → salva tel = "333-222"
  2. erase(Anna Verdi) → bucket[2] = [("Mario Rossi", "333-111")]
  3. cin >> p → p = Persona("Anna", "Bianchi")
  4. hash(Anna Bianchi) = 17 (bucket diverso!)
  5. insert({Anna Bianchi, "333-222"})

Stato: rubrica = {
    bucket[1]: [("Anna Bianchi", "333-222")]
    bucket[2]: [("Mario Rossi", "333-111")]
}
```

---

## 5. Bug e Correzioni

### 5.1 Bug 1: operator== Errato

**Problema (Persona.h:38):**
```cpp
bool operator==(const Persona& v) const {
    return v.nome == nome && v.cognome == v.cognome;
    //                       ↑_______↑
    //                       Confronta v con se stesso!
}
```

**Conseguenza:** Due persone con stesso nome ma cognome diverso risultano uguali!

**Correzione:**
```cpp
bool operator==(const Persona& v) const {
    return nome == v.nome && cognome == v.cognome;
}
```

### 5.2 Bug 2: Missing break nel case '3'

**Problema (main.cpp:62):**
```cpp
case '3':
{
    // ... elimina ...
}  // ← MANCA break;
case '4':
{
    // Questo viene eseguito anche dopo case '3'!
}
```

**Conseguenza:** Dopo eliminazione, chiede anche di modificare!

**Correzione:**
```cpp
case '3':
{
    // ... elimina ...
    break;  // ← AGGIUNGERE
}
```

### 5.3 Bug 3: Case '7' Non Svuota

**Problema (main.cpp:108-112):**
```cpp
case '7':
{
    cout << "Rubrica svuotata" << endl;
    // Manca rubrica.clear()!
    break;
}
```

**Correzione:**
```cpp
case '7':
{
    rubrica.clear();
    cout << "Rubrica svuotata" << endl;
    break;
}
```

### 5.4 Bug 4: Statement Inutile

**Problema (main.cpp:10):**
```cpp
size_t operator()(const Persona& v) const {
    hash<string>{};  // ← Non fa nulla!
    size_t h1 = hash<string>{}(v.getNome());
    // ...
}
```

**Correzione:** Rimuovere la linea inutile.

### 5.5 Codice Corretto Completo

**Persona.h corretto:**
```cpp
#ifndef PERSONA_H
#define PERSONA_H
#include <iostream>
using namespace std;

class Persona {
    friend istream& operator>>(istream& in, Persona& v) {
        cout << "Inserisci il nome -> ";
        in >> v.nome;
        cout << "Inserisci il cognome -> ";
        in >> v.cognome;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Persona& v) {
        out << "Nome: " << v.nome << ", Cognome: " << v.cognome;
        return out;
    }

private:
    string nome;
    string cognome;

public:
    string getNome() const { return nome; }
    string getCognome() const { return cognome; }

    // ✅ CORRETTO
    bool operator==(const Persona& v) const {
        return nome == v.nome && cognome == v.cognome;
    }
};
#endif
```

---

## 6. Estensioni Suggerite

### 6.1 Persistenza su File

```cpp
void salvaRubrica(const unordered_map<Persona, string, Hash_Persona>& rubrica,
                  const string& filename) {
    ofstream file(filename);
    for (const auto& [persona, telefono] : rubrica) {
        // Formato CSV: nome,cognome,telefono
        file << persona.getNome() << ","
             << persona.getCognome() << ","
             << telefono << endl;
    }
}

void caricaRubrica(unordered_map<Persona, string, Hash_Persona>& rubrica,
                   const string& filename) {
    ifstream file(filename);
    string linea;
    while (getline(file, linea)) {
        // Parse CSV
        size_t pos1 = linea.find(',');
        size_t pos2 = linea.find(',', pos1 + 1);
        
        Persona p;
        // Serve un costruttore o setter...
        string telefono = linea.substr(pos2 + 1);
        
        rubrica[p] = telefono;
    }
}
```

### 6.2 Ricerca Parziale

```cpp
vector<pair<Persona, string>> cercaPerNome(
    const unordered_map<Persona, string, Hash_Persona>& rubrica,
    const string& nome) {
    
    vector<pair<Persona, string>> risultati;
    
    // unordered_map non supporta ricerca parziale efficiente!
    // Dobbiamo scorrere tutto → O(n)
    for (const auto& [persona, telefono] : rubrica) {
        if (persona.getNome() == nome) {
            risultati.push_back({persona, telefono});
        }
    }
    
    return risultati;
}

// Per ricerca parziale efficiente, considera:
// - multimap<string, pair<string, string>> indicePernome
// - Trie per ricerca prefisso
```

### 6.3 Rubrica con Multipli Numeri

```cpp
// Una persona può avere più numeri
unordered_map<Persona, vector<string>, Hash_Persona> rubrica;

// Oppure usa un tipo strutturato per il valore
struct InfoContatto {
    string telefonoCasa;
    string telefonoCellulare;
    string email;
};

unordered_map<Persona, InfoContatto, Hash_Persona> rubrica;
```

### 6.4 Specializzazione std::hash (Alternativa al Functor)

```cpp
// Invece di Hash_Persona functor, specializza std::hash
namespace std {
    template<>
    struct hash<Persona> {
        size_t operator()(const Persona& p) const {
            size_t h1 = hash<string>{}(p.getNome());
            size_t h2 = hash<string>{}(p.getCognome());
            return h1 ^ (h2 << 1);
        }
    };
}

// Ora puoi usare senza terzo parametro!
unordered_map<Persona, string> rubrica;  // Funziona!
```

---

## Appendice: Complessità delle Operazioni

| Operazione | Funzione | Complessità Media | Complessità Peggiore |
|------------|----------|-------------------|----------------------|
| Inserimento | `insert()` | O(1) | O(n) rehashing |
| Ricerca | `find()` | O(1) | O(n) tutte collisioni |
| Eliminazione | `erase()` | O(1) | O(n) |
| Modifica valore | `m[k] = v` | O(1) | O(n) |
| Modifica chiave | erase + insert | O(1) | O(n) |
| Stampa tutto | loop | O(n) | O(n) |
| Svuota | `clear()` | O(n) | O(n) |
