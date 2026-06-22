# Teoria Completa: Ereditarieta in C++ - Libreria Digitale

Questo documento analizza la gerarchia di classi per la gestione di una libreria digitale, dimostrando i concetti di **ereditarieta pubblica, protetta e privata**.

---

## Indice
1. [Cos'e l'Ereditarieta](#1-cose-lereditarieta)
2. [Tipi di Ereditarieta](#2-tipi-di-ereditarieta)
3. [Gerarchia delle Classi](#3-gerarchia-delle-classi)
4. [Classe Base: Pubblicazione](#4-classe-base-pubblicazione)
5. [Classe Derivata: Libro](#5-classe-derivata-libro)
6. [Classe Derivata: Rivista](#6-classe-derivata-rivista)
7. [Classe Derivata: DocumentoRiservato](#7-classe-derivata-documentoriservato)
8. [Polimorfismo e Virtual](#8-polimorfismo-e-virtual)
9. [Best Practices](#9-best-practices)

---

## 1. Cos'e l'Ereditarieta

L'**ereditarieta** e un meccanismo OOP che permette di creare nuove classi basate su classi esistenti.

### Terminologia
- **Classe Base (Parent/Super)**: La classe da cui si eredita
- **Classe Derivata (Child/Sub)**: La classe che eredita
- **Ereditare**: Acquisire attributi e metodi dalla classe base

### Vantaggi
- **Riutilizzo del codice**: Non riscrivere codice gia esistente
- **Estendibilita**: Aggiungere funzionalita senza modificare il codice originale
- **Polimorfismo**: Trattare oggetti diversi in modo uniforme

### Sintassi Base
```cpp
class ClasseDerivata : [modificatore] ClasseBase {
    // ...
};
```

---

## 2. Tipi di Ereditarieta

### 2.1 Ereditarieta Pubblica (`public`)
```cpp
class Libro : public Pubblicazione { ... }
```

| Nella Base | Nella Derivata |
|------------|----------------|
| `public` | `public` |
| `protected` | `protected` |
| `private` | **Non accessibile** |

**Uso:** Relazione "IS-A" (Un Libro E' una Pubblicazione)

### 2.2 Ereditarieta Protetta (`protected`)
```cpp
class Rivista : protected Pubblicazione { ... }
```

| Nella Base | Nella Derivata |
|------------|----------------|
| `public` | `protected` |
| `protected` | `protected` |
| `private` | **Non accessibile** |

**Uso:** La derivata puo usare i metodi della base, ma l'esterno no.

### 2.3 Ereditarieta Privata (`private`)
```cpp
class DocumentoRiservato : private Pubblicazione { ... }
```

| Nella Base | Nella Derivata |
|------------|----------------|
| `public` | `private` |
| `protected` | `private` |
| `private` | **Non accessibile** |

**Uso:** "Implementato in termini di" - nasconde completamente la base.

### Tabella Riassuntiva

```
                    | public   | protected | private
---------------------------------------------------
public member       | public   | protected | private
protected member    | protected| protected | private
private member      | -        | -         | -
```

---

## 3. Gerarchia delle Classi

```
                  +----------------+
                  | Pubblicazione  |
                  +----------------+
                  | - id           |
                  | - titolo       |
                  | - autore       |
                  +----------------+
                  | + setId()      |
                  | + setTitolo()  |
                  | + setAutore()  |
                  | + mostraDettagli() |
                  +----------------+
                         ^
          _______________|________________
         |               |                |
    [public]        [protected]      [private]
         |               |                |
   +----------+    +-----------+    +-------------------+
   |  Libro   |    |  Rivista  |    | DocumentoRiservato|
   +----------+    +-----------+    +-------------------+
   | - numPag |    | - numEdiz |    | - pin             |
   +----------+    +-----------+    +-------------------+
```

---

## 4. Classe Base: Pubblicazione

### Header (`Pubblicazione.h`)
```cpp
#ifndef LIBRERIADIGITALE_PUBBLICAZIONE_H
#define LIBRERIADIGITALE_PUBBLICAZIONE_H

#include <iostream>
#include <string>
using namespace std;

class Pubblicazione {
protected:  // Accessibile dalle classi derivate
    int id;
    string titolo;
    string autore;

public:
    // Costruttore
    Pubblicazione(int id, const string& titolo, const string& autore)
        : id(id), titolo(titolo), autore(autore) {}

    // Setter
    void setId(int id);
    void setTitolo(const string& titolo);
    void setAutore(const string& autore);

    // Visualizzazione
    void mostraDettagli() const;
};

#endif
```

### Implementazione (`Pubblicazione.cpp`)
```cpp
#include "Pubblicazione.h"

void Pubblicazione::setId(int id) {
    this->id = id;
}

void Pubblicazione::setTitolo(const string& titolo) {
    this->titolo = titolo;
}

void Pubblicazione::setAutore(const string& autore) {
    this->autore = autore;
}

void Pubblicazione::mostraDettagli() const {
    cout << "ID: " << id << endl;
    cout << "Titolo: " << titolo << endl;
    cout << "Autore: " << autore << endl;
}
```

### Punti Chiave

#### `protected` per gli Attributi
```cpp
protected:
    int id;
    string titolo;
    string autore;
```
- Le classi derivate possono accedere direttamente a `id`, `titolo`, `autore`
- Il codice esterno NON puo accedervi

#### `this->` per Disambiguazione
```cpp
void Pubblicazione::setId(int id) {
    this->id = id;  // this->id e l'attributo, id e il parametro
}
```

---

## 5. Classe Derivata: Libro (Ereditarieta Pubblica)

### Codice (`Libro.h`)
```cpp
#ifndef LIBRERIADIGITALE_LIBRO_H
#define LIBRERIADIGITALE_LIBRO_H

#include "Pubblicazione.h"

class Libro : public Pubblicazione {  // Ereditarieta PUBBLICA
private:
    int numeroPagine;

public:
    // Costruttore: DEVE chiamare il costruttore della base
    Libro(int id, const string& titolo, const string& autore, int numeroPagine)
        : Pubblicazione(id, titolo, autore), numeroPagine(numeroPagine) {}

    // Setter specifico
    void setNumeroPagine(int numeroPagine) { 
        this->numeroPagine = numeroPagine; 
    }

    // Override di mostraDettagli
    void mostraDettagli() const {
        Pubblicazione::mostraDettagli();  // Richiama il metodo della base
        cout << "Numero di pagine: " << numeroPagine << endl;
    }
};

#endif
```

### Analisi

#### Initialization List
```cpp
Libro(...) : Pubblicazione(id, titolo, autore), numeroPagine(numeroPagine) {}
```

L'ordine di inizializzazione:
1. **Prima** il costruttore della classe base `Pubblicazione`
2. **Poi** gli attributi della classe derivata `numeroPagine`

**IMPORTANTE:** Se non chiami esplicitamente il costruttore della base, il compilatore cerca il costruttore di default `Pubblicazione()`. Se non esiste, errore di compilazione!

#### Override di `mostraDettagli()`
```cpp
void mostraDettagli() const {
    Pubblicazione::mostraDettagli();  // Riuso codice!
    cout << "Numero di pagine: " << numeroPagine << endl;
}
```

- Richiama il metodo della classe base con `Pubblicazione::`
- Aggiunge la stampa del campo specifico

#### Cosa Eredita Libro?
Con ereditarieta `public`:
- I setter `setId()`, `setTitolo()`, `setAutore()` sono pubblici anche per `Libro`
- Gli attributi `id`, `titolo`, `autore` restano `protected`

```cpp
Libro libro(1, "1984", "Orwell", 328);
libro.setTitolo("Nineteen Eighty-Four");  // OK - pubblico
// libro.titolo = "test";  // ERRORE - protected, non accessibile dall'esterno
```

---

## 6. Classe Derivata: Rivista (Ereditarieta Protetta)

### Codice (`Rivista.h`)
```cpp
class Rivista : protected Pubblicazione {  // Ereditarieta PROTETTA
private:
    int numeroEdizione;

public:
    Rivista(int id, const string& titolo, const string& autore, int numeroEdizione)
        : Pubblicazione(id, titolo, autore), numeroEdizione(numeroEdizione) {}

    // DEVE ridefinire i setter perche quelli della base sono ora protected!
    void setTitolo(const string& nuovoTitolo) { 
        Pubblicazione::setTitolo(nuovoTitolo); 
    }
    void setAutore(const string& nuovoAutore) { 
        Pubblicazione::setAutore(nuovoAutore); 
    }
    void setId(int nuovoId) { 
        Pubblicazione::setId(nuovoId); 
    }
    void setNumeroEdizione(int nuovoNumeroEdizione) { 
        numeroEdizione = nuovoNumeroEdizione; 
    }

    void mostraDettagli() const {
        cout << "ID: " << id << endl;
        cout << "Titolo: " << titolo << endl;
        cout << "Autore: " << autore << endl;
        cout << "Numero di edizione: " << numeroEdizione << endl;
    }
};
```

### Differenze con Libro

#### I Metodi della Base Diventano `protected`
```cpp
Rivista rivista(2, "Nature", "AA.VV.", 42);
// rivista.Pubblicazione::setTitolo("Science");  // ERRORE! setTitolo e protected
rivista.setTitolo("Science");  // OK - usa il wrapper definito in Rivista
```

#### Wrapper Necessari
Siccome `Pubblicazione::setTitolo()` e ora `protected`, Rivista deve esporre i propri metodi pubblici che chiamano internamente quelli della base.

#### Accesso Diretto agli Attributi
```cpp
void mostraDettagli() const {
    cout << "ID: " << id << endl;  // OK - id e protected, accessibile dalla derivata
}
```

---

## 7. Classe Derivata: DocumentoRiservato (Ereditarieta Privata)

### Codice (`DocumentoRiservato.h`)
```cpp
class DocumentoRiservato : private Pubblicazione {  // Ereditarieta PRIVATA
private:
    string pin;

    // Metodo privato per validare il PIN
    bool checkPin(const string& inseritoPin) const {
        if (inseritoPin != pin) {
            cout << "PIN errato. Operazione negata." << endl;
            return false;
        }
        return true;
    }

public:
    DocumentoRiservato(int id, const string& titolo, const string& autore, const string& pin)
        : Pubblicazione(id, titolo, autore), pin(pin) {}

    // Tutti i metodi richiedono il PIN!
    void mostraDettagli(const string& inseritoPin) const {
        if (checkPin(inseritoPin)) {
            cout << "ID: " << id << endl;
            cout << "Titolo: " << titolo << endl;
            cout << "Autore: " << autore << endl;
        }
    }

    void setTitolo(const string& inseritoPin, const string& nuovoTitolo) {
        if (checkPin(inseritoPin)) 
            Pubblicazione::setTitolo(nuovoTitolo);
    }

    void setAutore(const string& inseritoPin, const string& nuovoAutore) {
        if (checkPin(inseritoPin)) 
            Pubblicazione::setAutore(nuovoAutore);
    }

    void setId(const string& inseritoPin, int nuovoId) {
        if (checkPin(inseritoPin)) 
            Pubblicazione::setId(nuovoId);
    }

    void setPin(const string& nuovoPin) { 
        pin = nuovoPin; 
    }
};
```

### Analisi

#### Ereditarieta Privata
Con `private`:
- **Tutti** i membri di `Pubblicazione` diventano `private` in `DocumentoRiservato`
- Dall'esterno, NON si puo sapere che `DocumentoRiservato` deriva da `Pubblicazione`

#### Firma dei Metodi Diversa
```cpp
// Pubblicazione
void mostraDettagli() const;

// DocumentoRiservato
void mostraDettagli(const string& inseritoPin) const;  // Firma diversa!
```

Questo NON e un override! Sono metodi diversi (overload su classi diverse).

#### Controllo Accesso con PIN
```cpp
void setTitolo(const string& inseritoPin, const string& nuovoTitolo) {
    if (checkPin(inseritoPin)) 
        Pubblicazione::setTitolo(nuovoTitolo);
}
```

Il metodo:
1. Verifica il PIN
2. Solo se corretto, chiama il setter della classe base

---

## 8. Polimorfismo e Virtual

### Problema Attuale
Nel codice attuale, `mostraDettagli()` NON e `virtual`. Questo significa:

```cpp
Pubblicazione* p = new Libro(1, "1984", "Orwell", 328);
p->mostraDettagli();  // Chiama Pubblicazione::mostraDettagli(), NON Libro!
```

### Soluzione: Metodi Virtuali
```cpp
class Pubblicazione {
public:
    virtual void mostraDettagli() const {  // VIRTUAL!
        cout << "ID: " << id << endl;
        // ...
    }
    
    virtual ~Pubblicazione() {}  // Distruttore virtuale ESSENZIALE!
};

class Libro : public Pubblicazione {
public:
    void mostraDettagli() const override {  // OVERRIDE esplicito
        Pubblicazione::mostraDettagli();
        cout << "Numero di pagine: " << numeroPagine << endl;
    }
};
```

Ora:
```cpp
Pubblicazione* p = new Libro(1, "1984", "Orwell", 328);
p->mostraDettagli();  // Chiama Libro::mostraDettagli()!
delete p;             // Chiama il distruttore corretto grazie a virtual ~
```

### Distruttore Virtuale
**REGOLA:** Se una classe ha almeno un metodo virtuale, il distruttore DEVE essere virtuale!

```cpp
virtual ~Pubblicazione() {}
```

Altrimenti, `delete p` (dove `p` e un `Pubblicazione*` che punta a un `Libro`) non chiamera `~Libro()`, causando memory leak.

---

## 9. Best Practices

### 1. Usa `override` nelle Classi Derivate
```cpp
void mostraDettagli() const override {  // Il compilatore verifica!
    // ...
}
```

Se scrivi `override` ma il metodo della base non e `virtual` o la firma e sbagliata, il compilatore da errore.

### 2. Preferisci Composizione a Ereditarieta
L'ereditarieta crea un accoppiamento forte. Usa la composizione quando possibile:

```cpp
// Invece di:
class Rivista : public Pubblicazione { ... }

// Considera:
class Rivista {
    Pubblicazione pub;  // Composizione
    int numeroEdizione;
};
```

### 3. Ereditarieta Pubblica = IS-A
Usa ereditarieta pubblica solo se la relazione e "IS-A":
- Un Libro E' una Pubblicazione
- Un Cerchio E' una Forma

### 4. Ereditarieta Privata = Implemented-in-terms-of
Usa ereditarieta privata per riutilizzare l'implementazione senza esporre l'interfaccia.

### 5. Distruttore Virtuale per Classi Polimorfiche
Se prevedi che la classe verra derivata e usata polimorficamente, aggiungi subito `virtual ~NomeClasse() {}`.

---

## Esempio Completo: main.cpp

```cpp
#include "DocumentoRiservato.h"
#include "Libro.h"
#include "Rivista.h"

int main() {
    // Ereditarieta pubblica - tutti i metodi accessibili
    Libro libro1(1, "Il Signore degli Anelli", "J.R.R. Tolkien", 1200);
    libro1.mostraDettagli();
    libro1.setTitolo("LOTR");  // OK - metodo pubblico ereditato
    
    // Ereditarieta protetta - serve wrapper
    Rivista rivista1(2, "Nature", "AA.VV.", 42);
    rivista1.mostraDettagli();
    rivista1.setTitolo("Science");  // OK - wrapper definito in Rivista
    
    // Ereditarieta privata - serve PIN
    DocumentoRiservato doc1(3, "Progetto Segreto", "John Doe", "1234");
    doc1.mostraDettagli("1234");  // OK - PIN corretto
    doc1.mostraDettagli("0000");  // Errore: PIN errato
    
    doc1.setTitolo("1234", "Nuovo Titolo");  // OK
    doc1.setTitolo("0000", "Hacked");        // Fallisce silenziosamente
    
    return 0;
}
```

### Output Atteso
```
--- Libro ---
ID: 1
Titolo: Il Signore degli Anelli
Autore: J.R.R. Tolkien
Numero di pagine: 1200

--- Rivista ---
ID: 2
Titolo: Nature
Autore: AA.VV.
Numero di edizione: 42

--- Documento Riservato con PIN corretto ---
ID: 3
Titolo: Progetto Segreto
Autore: John Doe

--- Documento Riservato con PIN errato ---
PIN errato. Operazione negata.
```
