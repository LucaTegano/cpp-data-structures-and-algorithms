# Cheat Sheet Completo: Programmazione a Oggetti (OOP)

Guida definitiva alla progettazione di classi, ereditarietà e polimorfismo in C++.

## 1. Architettura di una Classe
Una classe è un progetto per creare oggetti. Incapsula dati (attributi) e funzioni (metodi).

```cpp
class Classe {
private:   // Solo metodi della classe
    int segreto;
protected: // Classe + Classi derivate
    int protetto;
public:    // Tutti
    Classe(int s) : segreto(s), protetto(0) {} // Member Initializer List (Best Practice)
    
    // Metodo CONST: garantisce di non modificare l'oggetto
    int getSegreto() const { return segreto; } 
};
```

---

## 2. Il Ciclo di Vita (Costruttori e Distruttori)

### 2.1 Tipi di Costruttori
- **Default**: `Classe() { ... }` (chiamato senza argomenti)
- **Parametrizzato**: `Classe(int x) : dato(x) { ... }`
- **Di Copia**: `Classe(const Classe& other)` (fondamentale per puntatori!)

### 2.2 Inizializzazione Member List vs Assegnazione
```cpp
// ✅ OTTIMO (Esegue 1 sola operazione: inizializzazione)
Persona(string n) : nome(n) {} 

// ❌ PESSIMO (Inizializza a vuoto, poi assegna -> 2 operazioni)
Persona(string n) { nome = n; }
```

### 2.3 Distruttore
Richiamato quando l'oggetto esce dallo scope o viene cancellato con `delete`.
```cpp
~Classe() { 
    // Libera memoria, chiudi file, ecc.
}
```

---

## 3. La "Regola dei Tre" (Fondamentale per l'esame)
Se una classe usa memoria dinamica (`new`), **DEVI** implementare:
1. **Distruttore**: Per evitare memory leak.
2. **Costruttore di Copia**: Per evitare che due oggetti puntino alla stessa memoria (shallow copy).
3. **Operatore di Assegnazione**: Per gestire `A = B`.

```cpp
class StudenteDinamico {
    int* voti;
    int n;
public:
    // 1. Distruttore
    ~StudenteDinamico() { delete[] voti; }

    // 2. Costruttore di Copia (Deep Copy)
    StudenteDinamico(const StudenteDinamico& s) {
        n = s.n;
        voti = new int[n];
        for(int i=0; i<n; i++) voti[i] = s.voti[i];
    }

    // 3. Operatore Assegnazione
    StudenteDinamico& operator=(const StudenteDinamico& s) {
        if (this == &s) return *this; // Protezione auto-assegnamento
        delete[] voti;               // Pulisci vecchia memoria
        n = s.n;
        voti = new int[n];           // Alloca nuova
        for(int i=0; i<n; i++) voti[i] = s.voti[i];
        return *this;
    }
};
```

---

## 4. Ereditarietà (Inheritance)

### 4.1 Tipi di Accesso
- `class B : public A`: B "è un" A. Public resta public.
- `class B : protected A`: Public di A diventa protected in B.
- `class B : private A`: Tutto di A diventa privato in B.

### 4.2 Ordine di Chiamata
- **Creazione**: Padre -> Figlio.
- **Distruzione**: Figlio -> Padre.

### 4.3 Chiamata Costruttore Padre
```cpp
Figlio(int x, int y) : Padre(x), datoFiglio(y) {}
```

---

## 5. Polimorfismo e Classi Astratte

### 5.1 Funzioni Virtuali e Dynamic Binding
Permettono di richiamare il metodo della classe reale anche tramite un puntatore alla classe base.
```cpp
Base* p = new Derivata();
p->metodo(); // Chiama Derivata::metodo() solo se metodo è VIRTUAL in Base
```

### 5.2 Distruttore Virtual (TRARELLO D'ESAME!)
Se hai ereditarietà, il distruttore della classe base **DEVE** essere `virtual`.
```cpp
virtual ~Base() {}
```
Se non lo è, `delete p` (dove p è `Base*` che punta a `Derivata`) chiamerà **solo** il distruttore del Padre, causando memory leak nel Figlio.

### 5.3 Classi Astratte e Pure Virtual
Una classe è astratta se ha almeno un metodo `= 0`. Non si possono creare oggetti di questa classe.
```cpp
class Forma {
    virtual void disegna() = 0; // Pure Virtual
};
```

---

## 6. Overloading degli Operatori

### 6.1 Operatori di I/O (Friend)
```cpp
friend ostream& operator<<(ostream& out, const Classe& c) {
    out << c.dato;
    return out;
}
```

### 6.2 Operatori di Confronto
- `operator==`: Per `unordered_map` e `find`.
- `operator<`: Per `map`, `set` e `sort`.

### 6.3 Operatore Parentesi (Functor)
Usato per definire criteri di hash o comparatori custom.
```cpp
struct MioHash {
    size_t operator()(const Persona& p) const { ... }
};
```

---

## 7. Membri Statici e Puntatore This

### 7.1 Static
- **Attributi statici**: Condivisi tra tutti gli oggetti. Vanno inizializzati fuori dalla classe: `int Classe::count = 0;`.
- **Metodi statici**: Possono accedere solo a membri statici. Si chiamano con `Classe::metodo()`.

### 7.2 This
Puntatore all'oggetto corrente.
- `this->x = x;` (risolve ambiguità con parametri).
- `return *this;` (permette concatenazione come `a = b = c`).

---

## 8. Template di Classe
Permettono di scrivere codice generico per qualsiasi tipo.
```cpp
template <class T>
class Contenitore {
    T dato;
};

Contenitore<int> c1;
Contenitore<string> c2;
```
