# Teoria Completa: Polimorfismo e Gestione Prodotti Alimentari

Questo documento analizza un sistema di gestione prodotti che dimostra **polimorfismo**, **classi astratte**, **gestione memoria dinamica** e pattern di design OOP.

---

## Indice
1. [Concetti Fondamentali](#1-concetti-fondamentali)
2. [Classe Astratta Prodotto](#2-classe-astratta-prodotto)
3. [Classi Derivate](#3-classi-derivate)
4. [Classe Gestore (Container)](#4-classe-gestore-container)
5. [Polimorfismo in Azione](#5-polimorfismo-in-azione)
6. [Errori Comuni](#6-errori-comuni)
7. [Quiz e Domande Teoriche](#7-quiz-e-domande-teoriche)

---

## 1. Concetti Fondamentali

### 1.1 Polimorfismo
Il **polimorfismo** permette di trattare oggetti di classi diverse in modo uniforme attraverso un'interfaccia comune.

```cpp
Prodotto* p1 = new ProdottoFresco("Latte", 1.50);
Prodotto* p2 = new ProdottoConservato("Pasta", 0.90);

p1->stampa();  // Chiama ProdottoFresco::stampa()
p2->stampa();  // Chiama ProdottoConservato::stampa()
```

### 1.2 Classi Astratte
Una classe e **astratta** se contiene almeno un metodo **virtuale puro**.

```cpp
virtual void stampa() const = 0;  // Metodo virtuale puro
```

- Non puoi istanziare una classe astratta
- Le classi derivate DEVONO implementare i metodi virtuali puri
- Serve come "contratto" per le sottoclassi

### 1.3 Distruttore Virtuale
**REGOLA FONDAMENTALE:** Se una classe ha metodi virtuali, il distruttore DEVE essere virtuale.

```cpp
virtual ~Prodotto() {}
```

Senza distruttore virtuale:
```cpp
Prodotto* p = new ProdottoFresco("Latte", 1.50);
delete p;  // PROBLEMA! Chiama solo ~Prodotto(), non ~ProdottoFresco()
```

---

## 2. Classe Astratta Prodotto

### Codice Completo
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
    // Costruttore
    Prodotto(string n, double p) : nome(n), prezzo(p) {}
    
    // Distruttore virtuale - ESSENZIALE!
    virtual ~Prodotto() {}

    // Metodo virtuale puro - rende la classe ASTRATTA
    virtual void stampa() const = 0;
    
    // Getter (non virtuali, comportamento uniforme)
    double getPrezzo() const { return prezzo; }
    string getNome() const { return nome; }
};

#endif
```

### Analisi

#### Attributi `protected`
```cpp
protected:
    string nome;
    double prezzo;
```
Le classi derivate possono accedere direttamente a `nome` e `prezzo`.

#### Metodo Virtuale Puro
```cpp
virtual void stampa() const = 0;
```

- `virtual`: Abilita il binding dinamico (polimorfismo)
- `= 0`: Rende il metodo "puro" (nessuna implementazione di default)
- La classe diventa **astratta**: non puoi fare `new Prodotto(...)`

#### Distruttore Virtuale
```cpp
virtual ~Prodotto() {}
```

- Il corpo e vuoto perche `Prodotto` non alloca risorse
- Ma DEVE essere virtuale per garantire la corretta distruzione delle derivate

---

## 3. Classi Derivate

### 3.1 ProdottoFresco

```cpp
#ifndef PF_H
#define PF_H

#include "Prodotto.h"

class ProdottoFresco : public Prodotto {
public:
    ProdottoFresco(string n, double p) : Prodotto(n, p) {}

    void stampa() const override {
        cout << "Prodotto Fresco: " << nome << " | " << prezzo << "€\n";
    }
};

#endif
```

### 3.2 ProdottoConservato

```cpp
#ifndef PC_H
#define PC_H

#include "Prodotto.h"

class ProdottoConservato : public Prodotto {
public:
    ProdottoConservato(string n, double p) : Prodotto(n, p) {}

    void stampa() const override {
        cout << "Prodotto Conservato: " << nome << " | " << prezzo << "€\n";
    }
};

#endif
```

### Punti Chiave

#### `override`
```cpp
void stampa() const override { ... }
```

La keyword `override`:
- Verifica che esista un metodo virtuale con la stessa firma nella base
- Se la firma e sbagliata, il compilatore da errore
- E una **best practice** sempre consigliata

#### Accesso agli Attributi Ereditati
```cpp
cout << nome << " | " << prezzo;  // Accesso diretto (protected)
```

---

## 4. Classe Gestore (Container)

### Codice Completo
```cpp
#ifndef GA_H
#define GA_H

#include "Prodotto.h"
#include <vector>

class GestoreProdottiAlimentari {
    vector<Prodotto*> prodotti;  // Vettore di PUNTATORI

public:
    // Distruttore: libera la memoria
    ~GestoreProdottiAlimentari() {
        for (auto p : prodotti)
            delete p;
    }

    // Aggiunge un prodotto (trasferisce ownership)
    void aggiungi(Prodotto* p) {
        prodotti.push_back(p);
    }

    // Stampa tutti i prodotti (polimorfismo!)
    void stampa() const {
        for (auto p : prodotti)
            p->stampa();  // Chiama il metodo giusto per ogni tipo
    }

    // Cerca un prodotto per nome
    Prodotto* cerca(const string& nome) {
        for (auto p : prodotti)
            if (p->getNome() == nome)
                return p;
        return nullptr;
    }

    // Calcola il totale dei prezzi
    double totale() const {
        double sum = 0;
        for (auto p : prodotti)
            sum += p->getPrezzo();
        return sum;
    }
};

#endif
```

### Analisi Dettagliata

#### Perche `vector<Prodotto*>` e non `vector<Prodotto>`?

**Con `vector<Prodotto>`:**
```cpp
vector<Prodotto> prodotti;
ProdottoFresco pf("Latte", 1.50);
prodotti.push_back(pf);  // OBJECT SLICING!
```

L'oggetto viene "tagliato": solo la parte `Prodotto` viene copiata, perdendo i dati specifici di `ProdottoFresco`.

**Con `vector<Prodotto*>`:**
```cpp
vector<Prodotto*> prodotti;
prodotti.push_back(new ProdottoFresco("Latte", 1.50));
```

Il puntatore punta all'oggetto completo. Il polimorfismo funziona correttamente.

#### Distruttore e Ownership

```cpp
~GestoreProdottiAlimentari() {
    for (auto p : prodotti)
        delete p;
}
```

Il gestore "possiede" i prodotti (ownership). Quando viene distrutto:
1. Itera su tutti i puntatori
2. Chiama `delete` su ognuno
3. Grazie al distruttore virtuale, chiama il distruttore corretto

**IMPORTANTE:** Una volta passato un puntatore ad `aggiungi()`, il gestore e responsabile della sua deallocazione.

#### Ricerca con `nullptr`

```cpp
Prodotto* cerca(const string& nome) {
    for (auto p : prodotti)
        if (p->getNome() == nome)
            return p;
    return nullptr;  // Convenzione: non trovato
}
```

Il chiamante DEVE controllare il risultato:
```cpp
Prodotto* p = gestore.cerca("Latte");
if (p != nullptr) {
    p->stampa();
} else {
    cout << "Prodotto non trovato!" << endl;
}
```

---

## 5. Polimorfismo in Azione

### Esempio Completo

```cpp
int main() {
    GestoreProdottiAlimentari g;

    // Aggiungi prodotti di tipi diversi
    g.aggiungi(new ProdottoFresco("Latte", 1.50));
    g.aggiungi(new ProdottoConservato("Pasta", 0.90));
    g.aggiungi(new ProdottoFresco("Yogurt", 0.80));
    g.aggiungi(new ProdottoConservato("Tonno", 2.50));

    // Stampa: ogni prodotto usa il SUO metodo stampa()
    cout << "--- Elenco prodotti ---\n";
    g.stampa();
    
    // Output:
    // Prodotto Fresco: Latte | 1.5€
    // Prodotto Conservato: Pasta | 0.9€
    // Prodotto Fresco: Yogurt | 0.8€
    // Prodotto Conservato: Tonno | 2.5€

    cout << "\nTotale: " << g.totale() << " €\n";
    // Output: Totale: 5.7 €

    return 0;
}  // Distruttore di g libera tutta la memoria
```

### Come Funziona il Polimorfismo?

```cpp
for (auto p : prodotti)
    p->stampa();
```

Per ogni puntatore `p`:
1. Il compilatore vede che `p` e di tipo `Prodotto*`
2. `stampa()` e `virtual`, quindi usa il **binding dinamico**
3. A runtime, controlla il tipo effettivo dell'oggetto puntato
4. Chiama il metodo della classe corretta

Questo e possibile grazie alla **vtable** (virtual table) che ogni oggetto polimorfico contiene.

---

## 6. Errori Comuni

### 6.1 Object Slicing

```cpp
// SBAGLIATO!
ProdottoFresco pf("Carne", 5.0);
Prodotto p = pf;  // SLICING! Copia solo la parte Prodotto

p.stampa();  // Se fosse possibile, chiamerebbe Prodotto::stampa()
```

La copia per valore "taglia" via la parte derivata.

**Soluzione:** Usa puntatori o riferimenti.

### 6.2 Downcast Pericoloso

```cpp
// PERICOLOSO!
Prodotto* base = new ProdottoConservato("Tonno", 3.5);
ProdottoFresco* wrong = static_cast<ProdottoFresco*>(base);

wrong->stampa();  // COMPORTAMENTO INDEFINITO!
```

`static_cast` non verifica il tipo a runtime. Se sbagli, crash o corruzione.

**Soluzione:** Usa `dynamic_cast` (richiede RTTI):
```cpp
ProdottoFresco* pf = dynamic_cast<ProdottoFresco*>(base);
if (pf != nullptr) {
    pf->stampa();  // Safe
} else {
    cout << "Non e un ProdottoFresco!" << endl;
}
```

### 6.3 Memory Leak

```cpp
// SBAGLIATO!
Prodotto* p = new ProdottoFresco("Latte", 1.50);
// ... uso p ...
// Dimenticato delete p!  <- MEMORY LEAK
```

**Soluzioni:**
1. Usa un gestore che si occupa della memoria
2. Usa smart pointers (`unique_ptr`, `shared_ptr`)

### 6.4 Dimenticare il Distruttore Virtuale

```cpp
class Prodotto {
    // MANCA: virtual ~Prodotto() {}
};

Prodotto* p = new ProdottoFresco("Latte", 1.50);
delete p;  // Chiama solo ~Prodotto(), NON ~ProdottoFresco()!
```

Se `ProdottoFresco` allocasse risorse, verrebbero perse.

---

## 7. Quiz e Domande Teoriche

### Domanda 1
*Perche il distruttore di una classe base polimorfica deve essere virtuale?*

**Risposta:** Per garantire che, quando si fa `delete` su un puntatore alla classe base che punta a un oggetto derivato, venga chiamato il distruttore della classe derivata e poi quello della base, liberando correttamente tutte le risorse.

### Domanda 2
*Cosa succede se dimentico `= 0` in un metodo che dovrebbe essere virtuale puro?*

**Risposta:** Il metodo diventa virtuale normale (non puro). La classe non e piu astratta e puo essere istanziata, ma il metodo deve avere un'implementazione.

### Domanda 3
*Qual e la differenza tra `override` e `virtual`?*

**Risposta:**
- `virtual` (nella base): Abilita il binding dinamico
- `override` (nella derivata): Verifica che il metodo sovrascriva effettivamente un metodo virtuale della base

### Domanda 4
*Perche usare `vector<Prodotto*>` invece di `vector<Prodotto>`?*

**Risposta:**
1. `Prodotto` e astratta, non puo essere istanziata
2. Anche se non fosse astratta, si avrebbe object slicing
3. I puntatori permettono il polimorfismo runtime

### Domanda 5
*Come si evita il memory leak nel gestore?*

**Risposta:** Il distruttore del gestore itera su tutti i puntatori e chiama `delete` su ognuno. Il gestore ha l'ownership degli oggetti.

---

## Espansioni Possibili

### Aggiungere Data di Scadenza a ProdottoFresco

```cpp
class ProdottoFresco : public Prodotto {
    int giorniAllaScadenza;
    
public:
    ProdottoFresco(string n, double p, int giorni) 
        : Prodotto(n, p), giorniAllaScadenza(giorni) {}

    // Prezzo scontato se vicino a scadenza
    double getPrezzo() const {  // Potrebbe essere virtual in Prodotto
        if (giorniAllaScadenza < 2) 
            return prezzo * 0.5;  // Sconto 50%
        return prezzo;
    }

    void stampa() const override {
        cout << "Fresco: " << nome << " | " << getPrezzo() 
             << "€ (scade in " << giorniAllaScadenza << " giorni)\n";
    }
};
```

### Usare Smart Pointers

```cpp
#include <memory>

class GestoreProdottiAlimentari {
    vector<unique_ptr<Prodotto>> prodotti;

public:
    // Niente distruttore esplicito! unique_ptr si occupa di tutto

    void aggiungi(unique_ptr<Prodotto> p) {
        prodotti.push_back(move(p));
    }
};

// Uso:
g.aggiungi(make_unique<ProdottoFresco>("Latte", 1.50));
```
