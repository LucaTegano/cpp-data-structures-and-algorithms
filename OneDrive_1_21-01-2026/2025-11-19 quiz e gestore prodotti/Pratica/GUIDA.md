# Guida Pratica: Gestione Prodotti Alimentari e Quiz

Questa guida analizza il codice nella cartella `Soluzione/` e fornisce risposte ai quiz teorici.

---

## Struttura del Progetto

```
Soluzione/
├── Prodotto.h                  // Classe base astratta
├── ProdottoFresco.h            // Derivata per prodotti freschi
├── ProdottoConservato.h        // Derivata per prodotti conservati
├── GestoreProdottiAlimentari.h // Container polimorfico
└── main.cpp                    // Test e esempi d'uso
```

---

## Analisi Dettagliata: `Prodotto.h`

### Codice
```cpp
#ifndef P_H
#define P_H

#include <iostream>
#include <string>
using namespace std;

class Prodotto {
protected:
    string nome;
    double prezzo;

public:
    Prodotto(string n, double p) : nome(n), prezzo(p) {}
    virtual ~Prodotto() {}

    virtual void stampa() const = 0;  // Metodo virtuale puro
    
    double getPrezzo() const { return prezzo; }
    string getNome() const { return nome; }
};

#endif
```

### Punti Chiave

#### Include Guard
```cpp
#ifndef P_H
#define P_H
// ...
#endif
```
Previene inclusioni multiple che causerebbero errori di "redefinition".

#### `= 0` - Metodo Virtuale Puro
```cpp
virtual void stampa() const = 0;
```

Questo significa:
1. Non c'e implementazione nella classe base
2. Le classi derivate DEVONO implementarlo
3. `Prodotto` e una classe astratta (non istanziabile)

```cpp
Prodotto p("test", 1.0);  // ERRORE! Classe astratta
```

#### Perche `virtual ~Prodotto() {}`?

Senza distruttore virtuale:
```cpp
Prodotto* p = new ProdottoFresco("Latte", 1.50);
delete p;  // Chiama SOLO ~Prodotto()!
```

Con distruttore virtuale:
```cpp
delete p;  // Chiama ~ProdottoFresco() e POI ~Prodotto()
```

---

## Analisi Dettagliata: Classi Derivate

### `ProdottoFresco.h`
```cpp
class ProdottoFresco : public Prodotto {
public:
    ProdottoFresco(string n, double p) : Prodotto(n, p) {}

    void stampa() const override {
        cout << "Prodotto Fresco: " << nome << " | " << prezzo << "€\n";
    }
};
```

### `ProdottoConservato.h`
```cpp
class ProdottoConservato : public Prodotto {
public:
    ProdottoConservato(string n, double p) : Prodotto(n, p) {}

    void stampa() const override {
        cout << "Prodotto Conservato: " << nome << " | " << prezzo << "€\n";
    }
};
```

### Cosa fa `override`?

```cpp
void stampa() const override { ... }
```

Il compilatore verifica che:
1. Esiste un metodo `stampa()` nella classe base
2. E dichiarato `virtual`
3. La firma corrisponde esattamente

**Errore catturato da `override`:**
```cpp
void stampa() override { ... }  // ERRORE! Manca const
// error: 'void ProdottoFresco::stampa()' marked 'override' but does not override
```

---

## Analisi Dettagliata: `GestoreProdottiAlimentari.h`

### Codice Completo
```cpp
class GestoreProdottiAlimentari {
    vector<Prodotto*> prodotti;

public:
    ~GestoreProdottiAlimentari() {
        for (auto p : prodotti)
            delete p;
    }

    void aggiungi(Prodotto* p) {
        prodotti.push_back(p);
    }

    void stampa() const {
        for (auto p : prodotti)
            p->stampa();
    }

    Prodotto* cerca(const string& nome) {
        for (auto p : prodotti)
            if (p->getNome() == nome)
                return p;
        return nullptr;
    }

    double totale() const {
        double sum = 0;
        for (auto p : prodotti)
            sum += p->getPrezzo();
        return sum;
    }
};
```

### Metodo `aggiungi()`

```cpp
void aggiungi(Prodotto* p) {
    prodotti.push_back(p);
}
```

**Uso corretto:**
```cpp
g.aggiungi(new ProdottoFresco("Latte", 1.50));
```

**Attenzione:** Dopo `aggiungi()`, il gestore "possiede" l'oggetto. Non fare:
```cpp
ProdottoFresco* pf = new ProdottoFresco("Latte", 1.50);
g.aggiungi(pf);
delete pf;  // ERRORE! Double free quando g viene distrutto
```

### Metodo `stampa()` - Polimorfismo

```cpp
void stampa() const {
    for (auto p : prodotti)
        p->stampa();  // Binding dinamico!
}
```

Ogni puntatore `p`:
1. Ha tipo statico `Prodotto*`
2. Ha tipo dinamico `ProdottoFresco*` o `ProdottoConservato*`
3. Grazie a `virtual`, viene chiamato il metodo del tipo dinamico

### Metodo `cerca()` - Gestione nullptr

```cpp
Prodotto* cerca(const string& nome) {
    // ...
    return nullptr;  // Se non trovato
}
```

**Uso corretto:**
```cpp
Prodotto* p = g.cerca("Latte");
if (p != nullptr) {
    cout << "Trovato: " << p->getNome() << endl;
} else {
    cout << "Non trovato!" << endl;
}
```

**ERRORE COMUNE:**
```cpp
Prodotto* p = g.cerca("Birra");
p->stampa();  // CRASH se p e nullptr!
```

### Metodo `totale()` - Somma Prezzi

```cpp
double totale() const {
    double sum = 0;
    for (auto p : prodotti)
        sum += p->getPrezzo();
    return sum;
}
```

Se `getPrezzo()` fosse `virtual` e override in `ProdottoFresco` per applicare sconti, funzionerebbe automaticamente!

---

## Analisi del `main.cpp`

### Uso Corretto

```cpp
GestoreProdottiAlimentari g;

g.aggiungi(new ProdottoFresco("Latte", 1.50));
g.aggiungi(new ProdottoConservato("Pasta", 0.90));

g.stampa();
// Output:
// Prodotto Fresco: Latte | 1.5€
// Prodotto Conservato: Pasta | 0.9€

cout << "Totale: " << g.totale() << " €\n";
// Output: Totale: 2.4 €

Prodotto* trovato = g.cerca("Latte");
if (trovato)
    cout << "Trovato: " << trovato->getNome() << "\n";
```

### Errori Dimostrati

#### Object Slicing
```cpp
ProdottoFresco pf("Carne", 5.0);
// Prodotto p = pf;   // SLICING!
```

Se assegni un oggetto derivato a una variabile della base (per valore), perdi la parte derivata.

#### Downcast Pericoloso
```cpp
Prodotto* base = new ProdottoConservato("Tonno", 3.5);
ProdottoFresco* wrong = static_cast<ProdottoFresco*>(base);
// wrong punta a un ProdottoConservato, ma pensiamo sia ProdottoFresco!
// Comportamento indefinito se usiamo wrong
```

#### Memory Leak
```cpp
Prodotto* base = new ProdottoConservato("Tonno", 3.5);
// ... non viene mai fatto delete base ...
// LEAK: 3.5 bytes (circa) persi per sempre
```

---

## Risposte al Quiz (QuizERisposte.pdf)

### Domanda: Cos'e una classe astratta?
**Risposta:** Una classe che contiene almeno un metodo virtuale puro (`= 0`). Non puo essere istanziata direttamente, ma serve come interfaccia per le classi derivate.

### Domanda: Perche usare `vector<Prodotto*>` invece di `vector<Prodotto>`?
**Risposta:**
1. `Prodotto` e astratta, quindi non istanziabile
2. Anche se non fosse astratta, si avrebbe object slicing
3. I puntatori permettono il polimorfismo a runtime

### Domanda: Quando chiamare `delete`?
**Risposta:** Quando l'oggetto non serve piu e nessun altro codice lo usa. Nel caso del gestore, il distruttore si occupa di liberare tutti i prodotti.

### Domanda: Cosa succede senza distruttore virtuale?
**Risposta:** Se fai `delete` su un puntatore alla base che punta a un oggetto derivato, viene chiamato solo il distruttore della base. Le risorse allocate dalla derivata non vengono liberate (memory leak).

### Domanda: Cos'e il binding dinamico?
**Risposta:** Il meccanismo per cui la decisione su quale metodo chiamare viene presa a **runtime** (non a compile-time) in base al tipo effettivo dell'oggetto. Richiede `virtual` e puntatori/riferimenti.

---

## Esercizi Pratici

### Esercizio 1: Aggiungere un Metodo `rimuovi()`

```cpp
bool rimuovi(const string& nome) {
    for (auto it = prodotti.begin(); it != prodotti.end(); ++it) {
        if ((*it)->getNome() == nome) {
            delete *it;        // Libera memoria
            prodotti.erase(it); // Rimuovi dal vettore
            return true;
        }
    }
    return false;
}
```

### Esercizio 2: Contare Prodotti per Tipo

```cpp
int contaFreschi() const {
    int count = 0;
    for (auto p : prodotti) {
        if (dynamic_cast<ProdottoFresco*>(p) != nullptr) {
            count++;
        }
    }
    return count;
}
```

### Esercizio 3: Prodotto con Scadenza

```cpp
class ProdottoFrescoConScadenza : public Prodotto {
    int giorniAllaScadenza;
    
public:
    ProdottoFrescoConScadenza(string n, double p, int giorni)
        : Prodotto(n, p), giorniAllaScadenza(giorni) {}
    
    double getPrezzoEffettivo() const {
        if (giorniAllaScadenza <= 1) return prezzo * 0.5;
        if (giorniAllaScadenza <= 3) return prezzo * 0.7;
        return prezzo;
    }
    
    void stampa() const override {
        cout << "Fresco: " << nome << " | " << getPrezzoEffettivo() 
             << "€ (scade in " << giorniAllaScadenza << "gg)\n";
    }
};
```

### Esercizio 4: Ordinare per Prezzo

```cpp
#include <algorithm>

void ordinaPerPrezzo() {
    sort(prodotti.begin(), prodotti.end(), 
        [](Prodotto* a, Prodotto* b) {
            return a->getPrezzo() < b->getPrezzo();
        });
}
```

---

## Tabella Riassuntiva Concetti

| Concetto | Keyword | Dove | Scopo |
|----------|---------|------|-------|
| Metodo virtuale | `virtual` | Classe base | Abilita binding dinamico |
| Metodo puro | `= 0` | Classe base | Rende la classe astratta |
| Override | `override` | Classe derivata | Verifica compilazione |
| Distruttore virtuale | `virtual ~Class()` | Classe base | Distruzione corretta |
| Ereditarieta pubblica | `: public Base` | Classe derivata | Relazione IS-A |

---

## Errori da Evitare all'Esame

1. **Dimenticare `virtual` nel distruttore**
2. **Dimenticare `override` nei metodi derivati** (non e errore, ma bad practice)
3. **Non controllare `nullptr` dopo `cerca()`**
4. **Fare `delete` su oggetti gia gestiti dal container**
5. **Confondere `virtual` con `override`**
6. **Usare `static_cast` invece di `dynamic_cast` per downcast**
