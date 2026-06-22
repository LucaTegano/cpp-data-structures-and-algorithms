# Cheat Sheet: Snippet e Pattern Comuni C++

Questo documento raccoglie i pattern di programmazione più frequenti incontrati nel corso, utili per risolvere velocemente problemi d'esame e compiti di laboratorio.

## Indice
1. [Input/Output e File](#1-inputoutput-e-file)
2. [Gestione Matrici](#2-gestione-matrici)
3. [Manipolazione Vector](#3-manipolazione-vector)
4. [Stringhe e Parsing](#4-stringhe-e-parsing)
5. [Pattern di Ricorsione](#5-pattern-di-ricorsione)
6. [Pattern di Backtracking](#6-pattern-di-backtracking)
7. [Gestione Memoria Dinamica](#7-gestione-memoria-dinamica)
8. [Classi e Best Practices](#8-classi-e-best-practices)

---

## 1. Input/Output e File

### 1.1 Lettura fino a fine file (EOF)
Ideale quando non conosci il numero di elementi.
```cpp
#include <iostream>
#include <fstream>

// Da console
int x;
while(cin >> x) {
    // processa x
}

// Da file
ifstream in("dati.txt");
if (!in) return -1; // Errore apertura
while(in >> x) {
    // processa x
}
```

### 1.2 Lettura riga per riga
Per leggere stringhe che contengono spazi.
```cpp
string linea;
while(getline(cin, linea)) {
    if (linea.empty()) continue;
    // processa la riga intera
}
```

### 1.3 Formattazione Output
```cpp
#include <iomanip>
cout << fixed << setprecision(2) << 3.1415; // Stampa "3.14"
cout << setw(10) << left << "Testo";       // Allinea a sinistra in 10 spazi
```

---

## 2. Gestione Matrici

### 2.1 Dichiarazione dinamica (Vector di Vector)
```cpp
// Matrice R x C inizializzata a zero
int R = 10, C = 5;
vector<vector<int>> matrice(R, vector<int>(C, 0));

// Accesso: matrice[riga][colonna]
matrice[2][3] = 42;
```

### 2.2 Scorrimento per righe vs per colonne
```cpp
// Per righe (cache-friendly)
for(int i = 0; i < R; ++i)
    for(int j = 0; j < C; ++j)
        // usa matrice[i][j]

// Per colonne
for(int j = 0; j < C; ++j)
    for(int i = 0; i < R; ++i)
        // usa matrice[i][j]
```

### 2.3 Vicini di una cella (8 direzioni)
Pattern per muoversi in una griglia evitando mille `if`.
```cpp
int dr[] = {-1, -1, -1,  0, 0,  1, 1, 1};
int dc[] = {-1,  0,  1, -1, 1, -1, 0, 1};

for(int i = 0; i < 8; i++) {
    int rr = riga_corr + dr[i];
    int cc = col_corr + dc[i];
    
    // Controllo bordi
    if (rr >= 0 && rr < R && cc >= 0 && cc < C) {
        // processa vicino matrice[rr][cc]
    }
}
```

---

## 3. Manipolazione Vector

### 3.1 Rimuovere duplicati (Sort + Unique)
```cpp
sort(v.begin(), v.end());
auto last = unique(v.begin(), v.end());
v.erase(last, v.end());
```

### 3.2 Rimuovere elementi che soddisfano una condizione
```cpp
// Rimuovi tutti i numeri pari
v.erase(remove_if(v.begin(), v.end(), [](int x){ 
    return x % 2 == 0; 
}), v.end());
```

### 3.3 Verificare se un elemento esiste
```cpp
if (find(v.begin(), v.end(), target) != v.end()) {
    // Trovato
}
```

---

## 4. Stringhe e Parsing

### 4.1 Split di una stringa (Tokenizzazione)
```cpp
#include <sstream>

string s = "mario rossi 25";
stringstream ss(s);
string nome, cognome;
int eta;

ss >> nome >> cognome >> eta;
```

### 4.2 Conversione Numerica
```cpp
int i = stoi("42");
double d = stod("3.14");
string s = to_string(100);
```

### 4.3 Trasformare Case (Maiuscolo/Minuscolo)
```cpp
string data = "AbCd";
transform(data.begin(), data.end(), data.begin(), ::tolower); // "abcd"
transform(data.begin(), data.end(), data.begin(), ::toupper); // "ABCD"
```

---

## 5. Pattern di Ricorsione

### 5.1 Pattern: Wrapper e Funzione Ausiliaria
Utile quando servono parametri extra (es. indici o accumulatori).
```cpp
// Funzione pubblica pulita
int somma(const vector<int>& v) {
    return somma_ric(v, 0);
}

// Funzione privata reale
int somma_ric(const vector<int>& v, int index) {
    if (index == v.size()) return 0; // Caso base
    return v[index] + somma_ric(v, index + 1); // Passo ricorsivo
}
```

### 5.2 Pattern: Ricorsione su Alberi
```cpp
int contaNodi(Nodo* root) {
    if (root == nullptr) return 0;
    return 1 + contaNodi(root->left) + contaNodi(root->right);
}
```

---

## 6. Pattern di Backtracking

### 6.1 Struttura Standard
```cpp
void solve(Soluzione& corrente) {
    if (isComplete(corrente)) {
        salva(corrente);
        return;
    }
    
    for (auto scelta : opzioni_valide) {
        if (canAdd(scelta, corrente)) {
            add(scelta, corrente);  // TRY
            solve(corrente);        // RECURSE
            remove(scelta, corrente); // UNDO (Backtrack)
        }
    }
}
```

---

## 7. Gestione Memoria Dinamica

### 7.1 La "Regola dei Tre" (Rule of Three)
Se definisci uno di questi, probabilmente ti servono tutti e tre:
1. **Distruttore**: `~Classe() { delete ptr; }`
2. **Costruttore di Copia**: `Classe(const Classe& other)` (Deep Copy)
3. **Operatore di Assegnazione**: `Classe& operator=(const Classe& other)`

### 7.2 Deep Copy di un array
```cpp
// Nel costruttore di copia
this->size = other.size;
this->data = new int[size];
for(int i=0; i<size; i++) 
    this->data[i] = other.data[i];
```

---

## 8. Classi e Best Practices

### 8.1 Operator Overloading (I/O)
Sempre fuori dalla classe come `friend`.
```cpp
friend ostream& operator<<(ostream& os, const Persona& p) {
    os << p.nome << " " << p.cognome;
    return os;
}

friend istream& operator>>(istream& is, Persona& p) {
    is >> p.nome >> p.cognome;
    return is;
}
```

### 8.2 Uso di `const`
- Parametri: `void func(const string& s)` (evita copie e garantisce immutabilità)
- Metodi: `int getValue() const` (promette di non modificare l'oggetto)

### 8.3 Inizializzazione Member List
Più efficiente dell'assegnazione nel corpo del costruttore.
```cpp
// Preferisci questo:
Persona(string n, int e) : nome(n), eta(e) {}

// A questo:
Persona(string n, int e) {
    nome = n;
    eta = e;
}
```
