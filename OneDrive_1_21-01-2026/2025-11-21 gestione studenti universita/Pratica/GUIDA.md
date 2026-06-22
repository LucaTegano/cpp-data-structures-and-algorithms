# Guida Pratica: Analisi del Codice StudenteDinamico

Questa guida analizza in dettaglio i file nella cartella `StudenteDinamico/` e `Universita/`.

---

## Struttura del Progetto

```
Pratica/
├── StudenteDinamico/
│   ├── StudenteDinamico.h    // Header classe
│   ├── StudenteDinamico.cpp  // Implementazione
│   ├── Data.h / Data.cpp     // Classe ausiliaria
│   └── main.cpp              // Test
└── Universita/
    └── (versione estesa con gestione universita)
```

---

## Analisi: `StudenteDinamico.h`

### Attributi

```cpp
private:
    int matricola;
    Data dataDiNascita;
    int esamiSostenuti;
    int* elencoEsami;  // PUNTATORE = memoria dinamica
```

**Punto chiave:** `int*` indica che l'array sara allocato dinamicamente con `new`.

### Dichiarazioni Metodi

```cpp
// Regola dei Tre
StudenteDinamico();                                    // Costruttore
StudenteDinamico(const StudenteDinamico& oStudente);   // Copy constructor
~StudenteDinamico();                                    // Distruttore
StudenteDinamico& operator=(const StudenteDinamico& oStudente);  // Assegnazione

// Friend per I/O
friend ostream& operator<<(ostream& out, const StudenteDinamico& s);
friend istream& operator>>(istream& in, StudenteDinamico& s);
```

---

## Analisi: `StudenteDinamico.cpp`

### Costruttore di Default (Riga 11-16)

```cpp
StudenteDinamico::StudenteDinamico()
    : matricola(0), dataDiNascita(), esamiSostenuti(0) 
{
    elencoEsami = new int[25];
    for (int i = 0; i < 25; ++i) {
        elencoEsami[i] = 0;
    }
}
```

**Flusso:**
1. Inizializza `matricola` a 0
2. Chiama costruttore default di `Data`
3. Inizializza `esamiSostenuti` a 0
4. Alloca 25 int nello heap
5. Inizializza tutto a 0

### Costruttore di Copia (Riga 18-22)

```cpp
StudenteDinamico::StudenteDinamico(const StudenteDinamico& oStudente)
    : matricola(oStudente.matricola),
      dataDiNascita(oStudente.dataDiNascita),
      esamiSostenuti(oStudente.esamiSostenuti) 
{
    setElencoEsami(oStudente.getElencoEsami());
}
```

**Delega a `setElencoEsami`:** Il metodo si occupa di allocare e copiare.

### setElencoEsami (Riga 70-82)

```cpp
void StudenteDinamico::setElencoEsami(const int* oElencoEsami) {
    if (elencoEsami != nullptr) {
        delete[] elencoEsami;       // 1. Libera vecchia memoria
        elencoEsami = new int[25];  // 2. Alloca nuova
    }
    esamiSostenuti = 0;
    for (int i = 0; i < 25; ++i) {
        setEsame(i, oElencoEsami[i]);  // 3. Copia con validazione
        if (oElencoEsami[i] != 0)
            esamiSostenuti++;
    }
}
```

**Attenzione al bug potenziale:** Se `elencoEsami` e nullptr, non alloca! Dovrebbe essere:
```cpp
if (elencoEsami != nullptr) {
    delete[] elencoEsami;
}
elencoEsami = new int[25];  // Sempre alloca
```

### Operatore di Assegnazione (Riga 126-134)

```cpp
StudenteDinamico& StudenteDinamico::operator=(const StudenteDinamico& oStudente) {
    // 1. Controllo auto-assegnamento
    if (this == &oStudente)
        return *this;
    
    // 2. Copia dati semplici
    this->matricola = oStudente.matricola;
    this->dataDiNascita = oStudente.dataDiNascita;
    this->esamiSostenuti = oStudente.esamiSostenuti;
    
    // 3. Deep copy dell'array (tramite setElencoEsami)
    setElencoEsami(oStudente.getElencoEsami());
    
    return *this;
}
```

### Distruttore (Riga 151-153)

```cpp
StudenteDinamico::~StudenteDinamico() {
    delete[] elencoEsami;
}
```

**Semplice ma essenziale:** Libera i 25 int allocati.

### aggiungiEsame (Riga 136-149)

```cpp
bool StudenteDinamico::aggiungiEsame(int voto) {
    bool added = false;
    if (voto > 0 && voto <= 30) {
        for (int i = 0; i < 25; ++i) {
            if (elencoEsami[i] == 0) {  // Trova primo slot libero
                elencoEsami[i] = voto;
                added = true;
                esamiSostenuti++;
                break;  // Esci dopo l'inserimento
            }
        }
    }
    return added;
}
```

### getMedia (Riga 88-100)

```cpp
float StudenteDinamico::getMedia() const {
    float sommaVoti = 0;
    int n_esami = 0;
    
    for (int i = 0; i < 25; ++i) {
        if (elencoEsami[i] != 0) {
            sommaVoti += elencoEsami[i];
            n_esami++;
        }
    }
    
    if (n_esami != 0)
        return sommaVoti / n_esami;
    return 0;
}
```

**Nota il `const`:** Il metodo non modifica l'oggetto.

### Operatore << (Riga 158-172)

```cpp
ostream& operator<<(ostream& out, const StudenteDinamico& s) {
    out << "Matricola: " << s.matricola << endl;
    out << "Data di nascita: " << s.dataDiNascita << endl;
    out << "Numero esami sostenuti: " << s.esamiSostenuti << endl;
    out << "Con votazione:" << endl;
    
    int esami = 0;
    for (int i = 0; i < 25; ++i) {
        if (s.elencoEsami[i] > 0) {
            esami++;
            out << esami << ") " << s.elencoEsami[i] << endl;
        }
    }
    out << "Media: " << s.getMedia();
    
    return out;
}
```

**Uso:**
```cpp
StudenteDinamico s;
cout << s << endl;
```

### Operatore >> (Riga 174-189)

```cpp
istream& operator>>(istream& in, StudenteDinamico& s) {
    cout << "Inserisci la matricola: ";
    in >> s.matricola;
    
    cout << "Inserisci la data di nascita: ";
    in >> s.dataDiNascita;
    
    cout << "Inserisci il numero di esami sostenuti: ";
    in >> s.esamiSostenuti;
    
    for (int i = 0; i < s.esamiSostenuti; ++i) {
        cout << "Inserisci il voto dell'esame " << (i + 1) << ": ";
        in >> s.elencoEsami[i];
    }
    
    cout << "Ho letto il seguente studente:" << endl;
    cout << s;
    
    return in;
}
```

**Nota:** Il parametro e `StudenteDinamico&` (non const) perche viene modificato.

---

## Test della Correttezza

### Test 1: Verifica Memory Leak

```cpp
int main() {
    for (int i = 0; i < 1000000; i++) {
        StudenteDinamico* s = new StudenteDinamico();
        s->aggiungiEsame(30);
        delete s;  // Se manca il distruttore -> memory leak
    }
    return 0;
}
```

Usa Valgrind per verificare:
```bash
valgrind --leak-check=full ./programma
```

### Test 2: Verifica Deep Copy

```cpp
int main() {
    StudenteDinamico s1;
    s1.aggiungiEsame(30);
    s1.aggiungiEsame(28);
    
    // Test copy constructor
    StudenteDinamico s2 = s1;
    s2.aggiungiEsame(25);
    
    cout << "s1 media: " << s1.getMedia() << endl;  // Dovrebbe essere 29
    cout << "s2 media: " << s2.getMedia() << endl;  // Dovrebbe essere 27.67
    
    // Se shallow copy: entrambi 27.67 (condividono memoria)
    
    return 0;
}
```

### Test 3: Verifica operator=

```cpp
int main() {
    StudenteDinamico s1, s2;
    s1.aggiungiEsame(30);
    
    s2 = s1;  // operator=
    s2.aggiungiEsame(20);
    
    // s1 e s2 devono essere indipendenti
    assert(s1.getEsamiSostenuti() == 1);
    assert(s2.getEsamiSostenuti() == 2);
    
    cout << "Test passato!" << endl;
    return 0;
}
```

### Test 4: Passaggio per Valore

```cpp
void testFunzione(StudenteDinamico s) {
    s.aggiungiEsame(18);
    cout << "In funzione: " << s.getMedia() << endl;
}  // s distrutto qui

int main() {
    StudenteDinamico s1;
    s1.aggiungiEsame(30);
    
    testFunzione(s1);  // Crea copia
    
    // s1 deve essere intatto
    assert(s1.getEsamiSostenuti() == 1);
    cout << "s1 dopo funzione: " << s1.getMedia() << endl;  // 30
    
    return 0;
}
```

---

## Esercizi Proposti

### Esercizio 1: Aggiungere `rimuoviEsame(int index)`

```cpp
bool StudenteDinamico::rimuoviEsame(int index) {
    if (index < 0 || index >= 25 || elencoEsami[index] == 0)
        return false;
    
    elencoEsami[index] = 0;
    esamiSostenuti--;
    return true;
}
```

### Esercizio 2: Aggiungere Copy Constructor con Parametro Extra

```cpp
// Costruttore che copia solo i primi n esami
StudenteDinamico::StudenteDinamico(const StudenteDinamico& o, int n)
    : matricola(o.matricola), dataDiNascita(o.dataDiNascita), esamiSostenuti(0)
{
    elencoEsami = new int[25];
    for (int i = 0; i < 25; ++i) {
        elencoEsami[i] = 0;
    }
    
    for (int i = 0; i < min(n, o.esamiSostenuti); ++i) {
        aggiungiEsame(o.elencoEsami[i]);
    }
}
```

### Esercizio 3: Implementare Move Semantics (C++11)

```cpp
// Move constructor
StudenteDinamico::StudenteDinamico(StudenteDinamico&& o) noexcept
    : matricola(o.matricola), dataDiNascita(o.dataDiNascita),
      esamiSostenuti(o.esamiSostenuti), elencoEsami(o.elencoEsami)
{
    o.elencoEsami = nullptr;  // "Ruba" la memoria
    o.esamiSostenuti = 0;
}

// Move assignment
StudenteDinamico& operator=(StudenteDinamico&& o) noexcept {
    if (this != &o) {
        delete[] elencoEsami;
        
        matricola = o.matricola;
        dataDiNascita = o.dataDiNascita;
        esamiSostenuti = o.esamiSostenuti;
        elencoEsami = o.elencoEsami;
        
        o.elencoEsami = nullptr;
        o.esamiSostenuti = 0;
    }
    return *this;
}
```

---

## Errori Comuni nel Codice

### 1. Bug in setElencoEsami

Il codice attuale ha un potenziale problema:
```cpp
if (elencoEsami != nullptr) {
    delete[] elencoEsami;
    elencoEsami = new int[25];
}
```

Se `elencoEsami` e nullptr, non viene allocato! Correzione:
```cpp
delete[] elencoEsami;  // delete su nullptr e safe
elencoEsami = new int[25];
```

### 2. Range check in setEsame

```cpp
void StudenteDinamico::setEsame(int i, int voto) {
    if (i > 0 && i < 25) {  // BUG: dovrebbe essere i >= 0
        // ...
    }
}
```

Con `i > 0`, l'esame in posizione 0 non puo essere modificato!

### 3. Validazione voto incompleta

```cpp
if (voto > 0 && voto < 30)  // Esclude 30!
```

Dovrebbe essere `voto <= 30` per includere 30 e lode.

---

## Riepilogo Concetti Chiave

| Concetto | File | Riga |
|----------|------|------|
| Allocazione dinamica | .cpp | 12 |
| Deep copy | .cpp | 18-22, 70-82 |
| Auto-assegnamento | .cpp | 127-128 |
| delete[] vs delete | .cpp | 72, 152 |
| Friend function | .h | 57-58 |
| const correctness | .h/.cpp | passim |
