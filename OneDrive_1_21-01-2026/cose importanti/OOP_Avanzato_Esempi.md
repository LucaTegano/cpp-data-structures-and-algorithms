# C++ Avanzato: Oggetti Complessi e Strutture Dati Composte

Questo documento esplora la progettazione di classi "strane" che utilizzano combinazioni avanzate di container STL, spesso richieste negli esercizi d'esame più difficili.

## Indice
1. [Costruttori Delegati](#1-costruttori-delegati)
2. [Case Study 1: CalendarioProf (Mappa con Pair)](#2-case-study-1-calendarioprof-mappa-con-pair)
3. [Case Study 2: CalendarioStudenti (Matrice vector<vector>)](#3-case-study-2-calendariostudenti-matrice-vectorvector)
4. [Case Study 3: RegistroEsami (Mappa di Mappe)](#4-case-study-3-registroesami-mappa-di-mappe)
5. [Case Study 4: SocialNetwork (Mappa di Vector)](#5-case-study-4-socialnetwork-mappa-di-vector)
6. [Case Study 5: RegistroPresenze (Vector di Struct)](#6-case-study-5-registropresenze-vector-di-struct)
7. [Operator Overloading Avanzato](#7-operator-overloading-avanzato)

---

## 1. Costruttori Delegati
Evitano la duplicazione del codice di inizializzazione chiamando un costruttore dall'altro.
```cpp
class Aula {
    string codice;
    int capienza;
public:
    Aula(string c, int cap) : codice(c), capienza(cap) {}
    Aula(string c) : Aula(c, 50) {} // Delega al primo, capienza default 50
};
```

---

## 2. Case Study 1: CalendarioProf (Mappa con Pair)
Utile quando la chiave è composta da due attributi (es. Giorno e Ora).
```cpp
#include <map>
#include <string>
using namespace std;

class CalendarioProf {
    // Chiave: pair<string, int> -> (Giorno "DD/MM", Ora 8-19)
    // Valore: string -> Nome Studente
    map<pair<string, int>, string> appuntamenti;

public:
    bool isLibero(string g, int o) const {
        return appuntamenti.find({g, o}) == appuntamenti.end();
    }

    void prenota(string studente, string g, int o) {
        if (isLibero(g, o)) appuntamenti[{g, o}] = studente;
    }
};
```

---

## 3. Case Study 2: CalendarioStudenti (Matrice vector<vector>)
Modelliamo un calendario settimanale come una matrice fissa dove le righe sono le ORE e le colonne i GIORNI.

```cpp
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class CalendarioStudenti {
private:
    // matrice[ORA][GIORNO]
    // ORE: 0-23, GIORNI: 0-6 (Lun-Dom)
    vector<vector<string>> tabella;

public:
    // Costruttore: inizializza matrice 24x7 con stringhe vuote
    CalendarioStudenti() : tabella(24, vector<string>(7, "")) {}

    // giorno: 0=Lun, 1=Mar, ..., 6=Dom
    bool isLibero(int giorno, int ora) const {
        if (ora < 0 || ora > 23 || giorno < 0 || giorno > 6) return false;
        return tabella[ora][giorno] == "";
    }

    void prenota(string materia, int giorno, int ora) {
        if (isLibero(giorno, ora)) {
            tabella[ora][giorno] = materia;
        }
    }

    void stampaSettimana() const {
        for (int h = 8; h < 18; ++h) { // Solo ore ufficio
            cout << h << ":00 | ";
            for (int g = 0; g < 7; ++g) {
                cout << (tabella[h][g] == "" ? "---" : tabella[h][g]) << " | ";
            }
            cout << endl;
        }
    }
};
```

---

## 4. Case Study 3: RegistroEsami (Mappa di Mappe)
Per modellare relazioni complesse: `Studente -> (Materia -> Voto)`.

```cpp
#include <map>
#include <string>

class RegistroEsami {
    // Chiave esterna: Nome Studente
    // Chiave interna: Nome Materia
    // Valore: Voto (int)
    map<string, map<string, int>> dati;

public:
    void aggiungiVoto(string studente, string materia, int voto) {
        dati[studente][materia] = voto;
    }

    int getVoto(string studente, string materia) const {
        if (dati.count(studente) && dati.at(studente).count(materia)) {
            return dati.at(studente).at(materia);
        }
        return -1; // Non trovato
    }
};
```

---

## 5. Case Study 4: SocialNetwork (Mappa di Vector)
Rappresentazione di un grafo tramite liste di adiacenza.

```cpp
#include <unordered_map>
#include <vector>
#include <string>

class SocialNetwork {
    // Ogni utente ha una lista di amici
    unordered_map<string, vector<string>> amici;

public:
    void aggiungiAmico(string u1, string u2) {
        amici[u1].push_back(u2);
        amici[u2].push_back(u1);
    }

    bool sonoAmici(string u1, string u2) {
        if (amici.count(u1)) {
            for (const string& a : amici[u1]) {
                if (a == u2) return true;
            }
        }
        return false;
    }
};
```

---

## 6. Case Study 5: RegistroPresenze (Vector di Struct)
L'approccio "lineare". Utile quando serve mantenere l'ordine di inserimento (cronologico) o quando i dati sono molti e la ricerca per chiave non è l'unica operazione necessaria.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Registro {
    std::string data;
    int ora;
    std::string studente;
};

class GestorePresenze {
private:
    std::vector<Registro> listaPresenze;

public:
    // Inserimento: O(1)
    void aggiungiPresenza(std::string d, int o, std::string s) {
        listaPresenze.push_back({d, o, s});
    }

    // Ricerca: O(N) perché non è una mappa!
    bool haPartecipato(std::string nome) const {
        for (const auto& record : listaPresenze) {
            if (record.studente == nome) return true;
        }
        return false;
    }

    void stampaTutto() const {
        for (const auto& r : listaPresenze) {
            std::cout << r.data << " ore " << r.ora << ": " << r.studente << std::endl;
        }
    }
};
```

---

## 7. Operator Overloading Avanzato

### 7.1 L'Operatore di Indice `[]`
Permette di accedere all'oggetto come se fosse un array.
```cpp
class Magazzino {
    string prodotti[100];
public:
    // Versione per scrittura: ritorna riferimento
    string& operator[](int i) { return prodotti[i]; }
    
    // Versione per lettura: ritorna valore o rif const
    string operator[](int i) const { return prodotti[i]; }
};

// Uso: Magazzino m; m[0] = "Pasta";
```

### 7.2 L'Operatore Parentesi `()` (Functor)
Trasforma l'oggetto in una "funzione". Molto usato nei motori di ricerca interni.
```cpp
class FiltroPrezzo {
    double soglia;
public:
    FiltroPrezzo(double s) : soglia(s) {}
    
    // Ritorna true se il prezzo è sopra la soglia
    bool operator()(double prezzo) const {
        return prezzo > soglia;
    }
};

// Uso: 
FiltroPrezzo superCaro(100.0);
if (superCaro(120.5)) { /* ... */ }
```

---

## 8. Checklist: Come scegliere la struttura giusta?

| Se devi... | Usa... | Note |
| :--- | :--- | :--- |
| Mappare coppia univoca (X,Y) -> Valore | `map<pair<X,Y>, Valore>` | Ricerca O(log N) |
| Gestire griglia rettangolare fissa | `vector<vector<T>>` | Accesso O(1), Spazio fisso |
| Associare una chiave a molti valori | `map<K, vector<V>>` | Es. Amici, Voti |
| Gerarchia Studente -> Materia -> Dato | `map<string, map<string, T>>` | Accesso annidato |
| Lista cronologica di eventi | `vector<Struct>` | Rapido inserimento, ricerca lenta |
| Frequenza di oggetti custom | `unordered_map<T, int, HashT>` | Ricerca O(1) media |
