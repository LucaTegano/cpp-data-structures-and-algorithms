# Teoria Completa: Gestione Memoria Dinamica - StudenteDinamico

Questo documento analizza la classe `StudenteDinamico`, un esempio classico di gestione manuale della memoria in C++ con la **Regola dei Tre**.

---

## Indice
1. [Il Problema della Memoria Dinamica](#1-il-problema-della-memoria-dinamica)
2. [La Regola dei Tre](#2-la-regola-dei-tre)
3. [Classe StudenteDinamico](#3-classe-studentedinamico)
4. [Deep Copy vs Shallow Copy](#4-deep-copy-vs-shallow-copy)
5. [Operatori di I/O](#5-operatori-di-io)
6. [Errori Comuni e Debugging](#6-errori-comuni-e-debugging)

---

## 1. Il Problema della Memoria Dinamica

### Quando serve la memoria dinamica?
- Array di dimensione variabile (non nota a compile-time)
- Oggetti che devono sopravvivere allo scope corrente
- Strutture dati complesse (liste, alberi, grafi)

### I Pericoli

| Problema | Causa | Conseguenza |
|----------|-------|-------------|
| **Memory Leak** | `new` senza `delete` | Memoria esaurita |
| **Dangling Pointer** | Uso dopo `delete` | Crash o dati corrotti |
| **Double Free** | `delete` due volte | Crash |
| **Shallow Copy** | Copia puntatore invece che dati | Double free, dati condivisi |

---

## 2. La Regola dei Tre

> Se una classe necessita di uno tra **Distruttore**, **Costruttore di Copia** o **Operatore di Assegnazione** personalizzati, probabilmente li necessita **tutti e tre**.

### Perche?
Se la classe gestisce risorse (memoria, file, socket...), il comportamento di default del C++ non e sufficiente:

| Operazione | Default | Con risorse dinamiche |
|------------|---------|----------------------|
| Distruttore | Nulla | Deve fare `delete` |
| Copy Constructor | Shallow copy | Deve fare deep copy |
| operator= | Shallow copy | Deve fare deep copy |

### Schema

```cpp
class ClasseConRisorse {
    int* data;  // Risorsa dinamica
    
public:
    // 1. DISTRUTTORE
    ~ClasseConRisorse() {
        delete[] data;
    }
    
    // 2. COSTRUTTORE DI COPIA
    ClasseConRisorse(const ClasseConRisorse& other) {
        // Alloca nuova memoria e copia i dati
    }
    
    // 3. OPERATORE DI ASSEGNAZIONE
    ClasseConRisorse& operator=(const ClasseConRisorse& other) {
        // Rilascia vecchia memoria, alloca nuova, copia dati
        return *this;
    }
};
```

---

## 3. Classe StudenteDinamico

### Header (`StudenteDinamico.h`)

```cpp
class StudenteDinamico {
private:
    int matricola;
    Data dataDiNascita;
    int esamiSostenuti;
    int* elencoEsami;  // Array DINAMICO!

public:
    // Costruttore di default
    StudenteDinamico();
    
    // Costruttore di copia (DEEP COPY)
    StudenteDinamico(const StudenteDinamico& oStudente);
    
    // Distruttore
    ~StudenteDinamico();
    
    // Operatore di assegnazione
    StudenteDinamico& operator=(const StudenteDinamico& oStudente);
    
    // Metodi
    bool aggiungiEsame(int voto);
    float getMedia() const;
    int getVotoMax() const;
    
    // I/O
    friend ostream& operator<<(ostream& out, const StudenteDinamico& s);
    friend istream& operator>>(istream& in, StudenteDinamico& s);
};
```

### Costruttore di Default

```cpp
StudenteDinamico::StudenteDinamico()
    : matricola(0), dataDiNascita(), esamiSostenuti(0) 
{
    elencoEsami = new int[25];  // Alloca array per 25 esami
    for (int i = 0; i < 25; ++i) {
        elencoEsami[i] = 0;  // Inizializza a 0
    }
}
```

**Punti chiave:**
- `new int[25]` alloca memoria nello **heap**
- L'array sopravvive alla fine del costruttore
- DEVE essere liberato nel distruttore

### Distruttore

```cpp
StudenteDinamico::~StudenteDinamico() {
    delete[] elencoEsami;  // IMPORTANTE: delete[] per array!
}
```

**Attenzione:** `delete[]` e diverso da `delete`!
- `delete` per singoli oggetti (`new Tipo`)
- `delete[]` per array (`new Tipo[n]`)

### Costruttore di Copia (Deep Copy)

```cpp
StudenteDinamico::StudenteDinamico(const StudenteDinamico& oStudente)
    : matricola(oStudente.matricola),
      dataDiNascita(oStudente.dataDiNascita),
      esamiSostenuti(oStudente.esamiSostenuti) 
{
    // Alloca NUOVA memoria
    elencoEsami = new int[25];
    
    // Copia i VALORI, non il puntatore
    for (int i = 0; i < 25; ++i) {
        elencoEsami[i] = oStudente.elencoEsami[i];
    }
}
```

**Cosa succederebbe senza?**
```cpp
// Copia di default (SHALLOW COPY)
StudenteDinamico s1;
StudenteDinamico s2 = s1;  // s2.elencoEsami == s1.elencoEsami (stesso indirizzo!)

// Alla distruzione:
// ~s2() chiama delete[] elencoEsami
// ~s1() chiama delete[] elencoEsami SULLO STESSO INDIRIZZO -> CRASH!
```

### Operatore di Assegnazione

```cpp
StudenteDinamico& StudenteDinamico::operator=(const StudenteDinamico& oStudente) {
    // 1. Controllo auto-assegnamento
    if (this == &oStudente)
        return *this;
    
    // 2. Rilascia risorsa corrente
    delete[] elencoEsami;
    
    // 3. Copia dati semplici
    matricola = oStudente.matricola;
    dataDiNascita = oStudente.dataDiNascita;
    esamiSostenuti = oStudente.esamiSostenuti;
    
    // 4. Alloca nuova memoria e copia
    elencoEsami = new int[25];
    for (int i = 0; i < 25; ++i) {
        elencoEsami[i] = oStudente.elencoEsami[i];
    }
    
    // 5. Ritorna riferimento a se stesso
    return *this;
}
```

**Perche il controllo auto-assegnamento?**
```cpp
s1 = s1;  // Senza controllo:
// delete[] elencoEsami -> libera memoria
// elencoEsami = new int[25]
// copia da oStudente.elencoEsami -> che e stato appena liberato! CRASH!
```

**Perche `return *this`?**
Permette l'assegnazione a catena:
```cpp
s1 = s2 = s3;  // s2 = s3 ritorna s2, poi s1 = s2
```

---

## 4. Deep Copy vs Shallow Copy

### Visualizzazione

**Shallow Copy (DEFAULT - PERICOLOSO):**
```
s1.elencoEsami ----+
                   |
                   v
              [30, 28, 25, 0, ...]  (memoria heap)
                   ^
                   |
s2.elencoEsami ----+

Entrambi puntano alla STESSA memoria!
```

**Deep Copy (CORRETTO):**
```
s1.elencoEsami ---> [30, 28, 25, 0, ...]  (memoria heap 1)

s2.elencoEsami ---> [30, 28, 25, 0, ...]  (memoria heap 2)

Copie INDIPENDENTI!
```

### Quando Viene Chiamato il Copy Constructor?

```cpp
// 1. Inizializzazione con =
StudenteDinamico s2 = s1;

// 2. Passaggio per valore a funzione
void funzione(StudenteDinamico s);
funzione(s1);

// 3. Ritorno per valore
StudenteDinamico creaStudente() {
    StudenteDinamico s;
    return s;  // Copia al ritorno
}
```

### Quando Viene Chiamato operator=?

```cpp
StudenteDinamico s1, s2;
s2 = s1;  // Assegnazione su oggetto GIA' ESISTENTE
```

---

## 5. Operatori di I/O

### Operatore di Output (`<<`)

```cpp
ostream& operator<<(ostream& out, const StudenteDinamico& s) {
    out << "Matricola: " << s.matricola << endl;
    out << "Data di nascita: " << s.dataDiNascita << endl;
    out << "Esami sostenuti: " << s.esamiSostenuti << endl;
    out << "Voti:" << endl;
    
    for (int i = 0; i < 25; ++i) {
        if (s.elencoEsami[i] > 0) {
            out << "  Esame " << (i+1) << ": " << s.elencoEsami[i] << endl;
        }
    }
    out << "Media: " << s.getMedia() << endl;
    
    return out;
}
```

**Perche `friend`?**
L'operatore non e un metodo della classe (il primo parametro e `ostream`), ma deve accedere ai membri privati.

**Perche ritorna `ostream&`?**
Per permettere il concatenamento:
```cpp
cout << s1 << " --- " << s2;
```

### Operatore di Input (`>>`)

```cpp
istream& operator>>(istream& in, StudenteDinamico& s) {
    cout << "Inserisci la matricola: ";
    in >> s.matricola;
    
    cout << "Inserisci la data di nascita: ";
    in >> s.dataDiNascita;
    
    cout << "Inserisci il numero di esami sostenuti: ";
    in >> s.esamiSostenuti;
    
    for (int i = 0; i < s.esamiSostenuti; ++i) {
        cout << "Inserisci il voto dell'esame " << (i+1) << ": ";
        in >> s.elencoEsami[i];
    }
    
    return in;
}
```

**Nota:** Il parametro `s` non e `const` perche viene modificato.

---

## 6. Errori Comuni e Debugging

### Errore 1: Dimenticare `delete[]`

```cpp
~StudenteDinamico() {
    // Vuoto o mancante
}
// Memory leak: 25 * sizeof(int) byte persi per ogni oggetto
```

**Come rilevare:** Valgrind, AddressSanitizer

### Errore 2: Usare `delete` invece di `delete[]`

```cpp
~StudenteDinamico() {
    delete elencoEsami;  // SBAGLIATO per array!
}
```

**Conseguenza:** Comportamento indefinito, possibile corruzione memoria.

### Errore 3: Non controllare auto-assegnamento

```cpp
StudenteDinamico& operator=(const StudenteDinamico& o) {
    // Manca: if (this == &o) return *this;
    delete[] elencoEsami;
    // ...copia da o.elencoEsami che e stato appena liberato!
}
```

### Errore 4: Non allocare nel copy constructor

```cpp
StudenteDinamico(const StudenteDinamico& o) {
    elencoEsami = o.elencoEsami;  // Shallow copy!
}
```

### Errore 5: Usare oggetto dopo delete

```cpp
StudenteDinamico* s = new StudenteDinamico();
delete s;
s->getMedia();  // DANGLING POINTER!
```

### Test per Verificare la Correttezza

```cpp
void testFunzione(StudenteDinamico s) {
    // s e una copia - testa il copy constructor
    cout << "In funzione: " << s.getMedia() << endl;
}  // s viene distrutto qui

int main() {
    StudenteDinamico s1;
    s1.aggiungiEsame(30);
    s1.aggiungiEsame(28);
    
    testFunzione(s1);  // Copia s1, la distrugge
    
    // Se copy constructor e sbagliato, s1 e ora corrotto
    cout << "Dopo funzione: " << s1.getMedia() << endl;  // Crash o dati sbagliati
    
    StudenteDinamico s2;
    s2 = s1;  // Testa operator=
    
    s2.aggiungiEsame(25);
    
    // Se operator= e sbagliato, s1 e s2 condividono memoria
    cout << s1 << endl;  // Dovrebbe mostrare 30, 28
    cout << s2 << endl;  // Dovrebbe mostrare 30, 28, 25
    
    return 0;
}
```

---

## Metodi Aggiuntivi

### `aggiungiEsame()`

```cpp
bool StudenteDinamico::aggiungiEsame(int voto) {
    if (voto < 1 || voto > 30) return false;
    
    for (int i = 0; i < 25; ++i) {
        if (elencoEsami[i] == 0) {
            elencoEsami[i] = voto;
            esamiSostenuti++;
            return true;
        }
    }
    return false;  // Array pieno
}
```

### `getMedia()`

```cpp
float StudenteDinamico::getMedia() const {
    float somma = 0;
    int count = 0;
    
    for (int i = 0; i < 25; ++i) {
        if (elencoEsami[i] > 0) {
            somma += elencoEsami[i];
            count++;
        }
    }
    
    return (count > 0) ? somma / count : 0;
}
```

### `getVotoMax()`

```cpp
int StudenteDinamico::getVotoMax() const {
    int max = 0;
    for (int i = 0; i < 25; ++i) {
        if (elencoEsami[i] > max) {
            max = elencoEsami[i];
        }
    }
    return max;
}
```

---

## Riepilogo

| Metodo | Quando viene chiamato | Cosa deve fare |
|--------|----------------------|----------------|
| Distruttore | Fine vita oggetto | `delete[]` risorse |
| Copy Constructor | Inizializzazione, passaggio per valore | Alloca nuova memoria, copia dati |
| operator= | Assegnazione | Libera vecchia, alloca nuova, copia dati |

### Checklist per Classi con Memoria Dinamica

- [ ] `new` nel costruttore
- [ ] `delete`/`delete[]` nel distruttore
- [ ] Copy constructor che fa deep copy
- [ ] operator= con controllo auto-assegnamento
- [ ] operator= che libera prima di riallocare
- [ ] Tutti i metodi `const` che non modificano sono marcati `const`
