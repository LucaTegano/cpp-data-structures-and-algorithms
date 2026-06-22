# Guida Pratica: Analisi del Codice Libreria Digitale

Questa guida analizza in dettaglio il codice nella cartella `soluzione/` per implementare un sistema di gestione libreria con ereditarieta.

---

## Struttura del Progetto

```
soluzione/
├── Pubblicazione.h      // Classe base
├── Pubblicazione.cpp    // Implementazione
├── Libro.h              // Ereditarieta pubblica
├── Rivista.h            // Ereditarieta protetta
├── DocumentoRiservato.h // Ereditarieta privata
└── main.cpp             // Test
```

---

## Analisi Dettagliata: `Pubblicazione.h`

### Struttura
```cpp
class Pubblicazione {
protected:
    int id;
    string titolo;
    string autore;

public:
    Pubblicazione(int id, const string& titolo, const string& autore)
        : id(id), titolo(titolo), autore(autore) {}

    void setId(int id);
    void setTitolo(const string& titolo);
    void setAutore(const string& autore);
    void mostraDettagli() const;
};
```

### Perche `protected` e non `private`?

```cpp
protected:
    int id;
    string titolo;
    string autore;
```

**Confronto:**

| Modificatore | Classe Base | Classe Derivata | Esterno |
|--------------|-------------|-----------------|---------|
| `private` | Accessibile | **NO** | NO |
| `protected` | Accessibile | **SI** | NO |
| `public` | Accessibile | SI | SI |

Con `protected`, le classi derivate possono accedere direttamente:
```cpp
// In Libro.h o Rivista.h:
cout << titolo;  // OK! titolo e protected
```

Se fossero `private`, dovresti usare getter:
```cpp
cout << getTitolo();  // Necessario con private
```

### Costruttore con Initialization List

```cpp
Pubblicazione(int id, const string& titolo, const string& autore)
    : id(id), titolo(titolo), autore(autore) {}
```

**Perche usare l'Initialization List?**

1. **Efficienza**: Per oggetti complessi come `string`, evita costruzione di default + assegnamento
2. **Obbligatorio**: Per attributi `const` e riferimenti
3. **Chiarezza**: Mostra esplicitamente cosa viene inizializzato

**Equivalente meno efficiente:**
```cpp
Pubblicazione(int id, const string& titolo, const string& autore) {
    this->id = id;           // Costruzione default + assegnamento
    this->titolo = titolo;   // Meno efficiente per string!
    this->autore = autore;
}
```

---

## Analisi Dettagliata: `Libro.h`

### Codice Completo
```cpp
class Libro : public Pubblicazione {
private:
    int numeroPagine;

public:
    Libro(int id, const string& titolo, const string& autore, int numeroPagine)
        : Pubblicazione(id, titolo, autore), numeroPagine(numeroPagine) {}

    void setNumeroPagine(int numeroPagine) { 
        this->numeroPagine = numeroPagine; 
    }

    void mostraDettagli() const {
        Pubblicazione::mostraDettagli();
        cout << "Numero di pagine: " << numeroPagine << endl;
    }
};
```

### Chiamata al Costruttore della Base

```cpp
Libro(...) : Pubblicazione(id, titolo, autore), numeroPagine(numeroPagine) {}
```

**Ordine di esecuzione:**
1. `Pubblicazione(id, titolo, autore)` - costruisce la parte base
2. `numeroPagine(numeroPagine)` - inizializza l'attributo derivato
3. `{}` - corpo del costruttore (vuoto in questo caso)

**ERRORE COMUNE:**
```cpp
// SBAGLIATO - non chiama il costruttore della base!
Libro(...) : numeroPagine(numeroPagine) {
    this->id = id;  // ERRORE: Pubblicazione non ha costruttore default!
}
```

### Riutilizzo con `NomeClasse::`

```cpp
void mostraDettagli() const {
    Pubblicazione::mostraDettagli();  // Chiama il metodo della base
    cout << "Numero di pagine: " << numeroPagine << endl;
}
```

**Senza `Pubblicazione::`:**
```cpp
void mostraDettagli() const {
    mostraDettagli();  // ERRORE! Ricorsione infinita!
}
```

### Cosa Puo Fare un Oggetto Libro?

```cpp
Libro libro(1, "1984", "Orwell", 328);

// Metodi EREDITATI (pubblici perche ereditarieta pubblica)
libro.setId(2);           // OK
libro.setTitolo("Animal Farm");  // OK
libro.setAutore("G. Orwell");    // OK

// Metodi PROPRI
libro.setNumeroPagine(112);  // OK
libro.mostraDettagli();      // Chiama Libro::mostraDettagli

// Attributi (protected - non accessibili dall'esterno)
// libro.titolo = "test";  // ERRORE!
```

---

## Analisi Dettagliata: `Rivista.h`

### Codice Completo
```cpp
class Rivista : protected Pubblicazione {  // PROTETTA!
private:
    int numeroEdizione;

public:
    Rivista(int id, const string& titolo, const string& autore, int numeroEdizione)
        : Pubblicazione(id, titolo, autore), numeroEdizione(numeroEdizione) {}

    // Wrapper necessari!
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

### Perche Servono i Wrapper?

Con ereditarieta `protected`:
- `Pubblicazione::setTitolo()` diventa `protected` in `Rivista`
- NON e piu accessibile dall'esterno!

```cpp
Rivista r(1, "Nature", "AA.VV.", 42);

// SENZA wrapper:
// r.Pubblicazione::setTitolo("Science");  // ERRORE! protected

// CON wrapper:
r.setTitolo("Science");  // OK - chiama Rivista::setTitolo che chiama la base
```

### Accesso Diretto agli Attributi

```cpp
void mostraDettagli() const {
    cout << "ID: " << id << endl;      // OK - id e protected
    cout << "Titolo: " << titolo << endl;  // OK
}
```

Dentro la classe derivata, gli attributi `protected` della base sono accessibili direttamente.

---

## Analisi Dettagliata: `DocumentoRiservato.h`

### Codice Completo
```cpp
class DocumentoRiservato : private Pubblicazione {  // PRIVATA!
private:
    string pin;

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

    // ... altri setter con PIN
};
```

### Ereditarieta Privata: Conseguenze

```cpp
class DocumentoRiservato : private Pubblicazione
```

**Conseguenze:**
1. TUTTI i membri di `Pubblicazione` diventano `private`
2. Dall'esterno, e impossibile sapere che `DocumentoRiservato` deriva da `Pubblicazione`
3. Non puoi fare: `Pubblicazione* p = new DocumentoRiservato(...);`

### Pattern di Sicurezza

```cpp
void setTitolo(const string& inseritoPin, const string& nuovoTitolo) {
    if (checkPin(inseritoPin)) 
        Pubblicazione::setTitolo(nuovoTitolo);
}
```

**Flusso:**
1. L'utente chiama `setTitolo("1234", "Nuovo Titolo")`
2. `checkPin("1234")` verifica il PIN
3. Se corretto, chiama `Pubblicazione::setTitolo("Nuovo Titolo")`
4. Se errato, stampa errore e non fa nulla

### Firma Diversa = Non Override

```cpp
// Pubblicazione
void mostraDettagli() const;

// DocumentoRiservato
void mostraDettagli(const string& inseritoPin) const;
```

Queste sono **due funzioni diverse**! Non e un override, e un **overload** (su classi diverse).

---

## Analisi del `main.cpp`

### Creazione Oggetti

```cpp
Libro libro1(1, "Il Signore degli Anelli", "J.R.R. Tolkien", 1200);
Rivista rivista1(2, "Nature", "AA.VV.", 42);
DocumentoRiservato doc1(3, "Progetto Segreto", "John Doe", "1234");
```

Tutti gli oggetti sono **sullo stack** (memoria automatica). Verranno distrutti automaticamente alla fine del `main`.

### Test Ereditarieta Pubblica (Libro)

```cpp
libro1.mostraDettagli();  // Chiama Libro::mostraDettagli
libro1.setTitolo("LOTR");  // OK - ereditato e pubblico
```

### Test Ereditarieta Protetta (Rivista)

```cpp
rivista1.setTitolo("Science");  // Chiama Rivista::setTitolo (wrapper)
rivista1.setNumeroEdizione(43); // Chiama Rivista::setNumeroEdizione
```

### Test Ereditarieta Privata (DocumentoRiservato)

```cpp
// PIN corretto
doc1.mostraDettagli("1234");  // Mostra i dettagli
doc1.setTitolo("1234", "Progetto SuperSegreto");  // Modifica OK

// PIN errato
doc1.mostraDettagli("0000");  // Stampa "PIN errato. Operazione negata."
doc1.setTitolo("0000", "Fail Test");  // Non modifica nulla
```

---

## Esercizi Proposti

### Esercizio 1: Aggiungere un Getter

Aggiungi a `Libro` un metodo `getNumeroPagine()`:

```cpp
int getNumeroPagine() const { 
    return numeroPagine; 
}
```

### Esercizio 2: Validazione nel Setter

Modifica `setNumeroPagine` per accettare solo valori positivi:

```cpp
void setNumeroPagine(int numeroPagine) { 
    if (numeroPagine > 0) {
        this->numeroPagine = numeroPagine;
    } else {
        cout << "Errore: numero pagine deve essere positivo" << endl;
    }
}
```

### Esercizio 3: Aggiungere Polimorfismo

1. Aggiungi `virtual` a `mostraDettagli()` in `Pubblicazione`
2. Aggiungi `virtual ~Pubblicazione() {}`
3. Aggiungi `override` nelle classi derivate
4. Crea un `vector<Pubblicazione*>` e inserisci oggetti diversi

```cpp
vector<Pubblicazione*> biblioteca;
biblioteca.push_back(new Libro(1, "1984", "Orwell", 328));
biblioteca.push_back(new Rivista(2, "Nature", "AA.VV.", 42));  // ERRORE! protected

// Rivista non puo essere inserita perche l'ereditarieta e protected!
// Solo Libro (ereditarieta pubblica) puo essere trattato come Pubblicazione*
```

### Esercizio 4: Classe Ebook

Crea una classe `Ebook` che eredita da `Libro` e aggiunge:
- `string formato` (PDF, EPUB, MOBI)
- `double dimensioneMB`

```cpp
class Ebook : public Libro {
private:
    string formato;
    double dimensioneMB;

public:
    Ebook(int id, const string& titolo, const string& autore, 
          int numeroPagine, const string& formato, double dimensioneMB)
        : Libro(id, titolo, autore, numeroPagine), 
          formato(formato), dimensioneMB(dimensioneMB) {}

    void mostraDettagli() const {
        Libro::mostraDettagli();
        cout << "Formato: " << formato << endl;
        cout << "Dimensione: " << dimensioneMB << " MB" << endl;
    }
};
```

---

## Errori Comuni da Evitare

### 1. Dimenticare di chiamare il costruttore della base

```cpp
// SBAGLIATO
Libro(int id, ...) : numeroPagine(np) {
    // ERRORE: Pubblicazione non ha costruttore default!
}

// CORRETTO
Libro(int id, ...) : Pubblicazione(id, t, a), numeroPagine(np) {}
```

### 2. Ricorsione infinita nel metodo override

```cpp
// SBAGLIATO
void mostraDettagli() const {
    mostraDettagli();  // Chiama se stesso! Ricorsione infinita!
}

// CORRETTO
void mostraDettagli() const {
    Pubblicazione::mostraDettagli();  // Chiama la base
}
```

### 3. Dimenticare `const` nei metodi che non modificano

```cpp
// SBAGLIATO - non puo essere chiamato su oggetti const
void mostraDettagli() { ... }

// CORRETTO
void mostraDettagli() const { ... }
```

### 4. Confondere ereditarieta pubblica e protetta

```cpp
Rivista r(...);
Pubblicazione* p = &r;  // ERRORE! Rivista : protected Pubblicazione
```

Con ereditarieta protetta o privata, non puoi fare conversioni implicite alla classe base.
