# Guida Pratica: Esercizi su Alberi Binari

## Indice
1. [Panoramica del Progetto](#1-panoramica-del-progetto)
2. [Analisi di AlberoB.h](#2-analisi-di-alberobh)
3. [Esercizi Risolti: main.cpp](#3-esercizi-risolti-maincpp)
4. [File Bonus: sort_find.cpp e example_static.cpp](#4-file-bonus-sort_findcpp-e-example_staticcpp)
5. [Trace di Esecuzione](#5-trace-di-esecuzione)
6. [Pattern Ricorrenti](#6-pattern-ricorrenti)

---

## 1. Panoramica del Progetto

### 1.1 Struttura File

```
Pratica/
├── alberi/
│   ├── AlberoB.h          # Template classe AlberoB
│   └── main.cpp           # 8 esercizi risolti sugli alberi
├── sort_find.cpp          # Esempio di sort e find con comparatori custom
└── example_static.cpp     # Esempio di variabili statiche in classi
```

### 1.2 Albero di Esempio nel main()

```cpp
AlberoB<int> a(7);      // Radice

AlberoB<int> a1(1), a2(4);
a.insFiglio(SIN, a1);   // 7 -> 1 (sinistra)
a.insFiglio(DES, a2);   // 7 -> 4 (destra)

// Continua costruzione...
```

**Albero risultante:**
```
                    7
                   / \
                  1   4
                 /   / \
                7   3   21
               / \ / \ / \
              2  5 12 2 6  4
```

---

## 2. Analisi di AlberoB.h

### 2.1 Struttura SNodo

```cpp
template <class T>
struct SNodo {
    T vinfo;                     // Dato del nodo
    SNodo *ppadre, *pfiglio[2];  // Puntatori: padre e figli
    
    // Costruttore
    SNodo(const T& inf) : vinfo(inf) {
        ppadre = pfiglio[SIN] = pfiglio[DES] = 0;
    }
    
    // Distruttore RICORSIVO!
    ~SNodo() {
        delete pfiglio[SIN];     // Elimina sottoalbero sinistro
        delete pfiglio[DES];     // Elimina sottoalbero destro
    }
};
```

**Diagramma memoria:**
```
┌─────────────────────────────────────────────────────────────┐
│ SNodo<int> per valore 7                                      │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│  ┌──────────────────────────────────────────────────────┐   │
│  │  vinfo: 7                                             │   │
│  ├──────────────────────────────────────────────────────┤   │
│  │  ppadre: nullptr (è la radice)                        │   │
│  ├──────────────────────────────────────────────────────┤   │
│  │  pfiglio[SIN]: ──────────► SNodo(1)                   │   │
│  │  pfiglio[DES]: ──────────► SNodo(4)                   │   │
│  └──────────────────────────────────────────────────────┘   │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

### 2.2 Metodi Chiave di AlberoB

```cpp
// Verifica se vuoto
bool nullo() const { return pradice == 0; }

// Verifica se foglia (no figli)
bool foglia() const {
    return !nullo() && figlio(SIN).nullo() && figlio(DES).nullo();
}

// Accesso al valore della radice
const T& radice() const {
    assert(!nullo());
    return pradice->vinfo;
}

// Navigazione ai figli
AlberoB<T> figlio(Direzione d) const {
    assert(!nullo());
    AlberoB<T> AC;
    AC.pradice = pradice->pfiglio[d];
    return AC;  // Ritorna una "vista"
}
```

### 2.3 Inserimento Figlio

```cpp
void insFiglio(Direzione d, AlberoB& AC) {
    assert(!nullo());             // Devo avere una radice
    assert(figlio(d).nullo());   // Posizione deve essere libera
    
    if (!AC.nullo()) {
        pradice->pfiglio[d] = AC.pradice;  // Collega figlio
        AC.pradice->ppadre = pradice;       // Collega padre
    }
}
```

**Trace di costruzione:**
```cpp
AlberoB<int> a(7);        // a.pradice -> SNodo(7)
AlberoB<int> a1(1);       // a1.pradice -> SNodo(1)

a.insFiglio(SIN, a1);
// Dopo:
// a.pradice->pfiglio[SIN] = a1.pradice
// a1.pradice->ppadre = a.pradice

//     7
//    /
//   1
```

---

## 3. Esercizi Risolti: main.cpp

### 3.1 isHeap - Verifica Proprietà Max-Heap

**Problema:** Verificare se l'albero è un max-heap (ogni nodo >= figli)

```cpp
bool isHeap(const AlberoB<int>& a) {
    // Caso base: albero vuoto o foglia → sempre heap
    if (a.nullo() || a.foglia())
        return true;
    
    // Controllo figlio destro
    if (!a.figlio(DES).nullo() && a.radice() < a.figlio(DES).radice())
        return false;
    
    // Controllo figlio sinistro
    if (!a.figlio(SIN).nullo() && a.radice() < a.figlio(SIN).radice())
        return false;
    
    // Ricorsione sui sottoalberi
    return isHeap(a.figlio(SIN)) && isHeap(a.figlio(DES));
}
```

**Trace su esempio:**
```
        50
       /  \
      30   20
     / \
    15  10

isHeap(50):
  50 >= 30? Sì
  50 >= 20? Sì
  isHeap(30):
    30 >= 15? Sì
    30 >= 10? Sì
    isHeap(15): foglia → true
    isHeap(10): foglia → true
    return true && true = true
  isHeap(20): foglia → true
  return true && true = true

Risultato: true (è un max-heap)
```

---

### 3.2 ogniPercorsoRadiceFoglia - Somma Path ≤ Max

**Problema:** Verificare che ogni percorso radice-foglia abbia somma ≤ max

```cpp
bool ogniPercorsoRadiceFoglia(const AlberoB<int>& a, int max) {
    return ogniPercorsoRadiceFoglia(a, max, 0);  // Wrapper
}

bool ogniPercorsoRadiceFoglia(const AlberoB<int>& a, int max, int current) {
    // Albero nullo: nessun percorso da controllare
    if (a.nullo())
        return true;
    
    // Foglia: controllo finale
    if (a.foglia())
        return current + a.radice() <= max;
    
    // Ricorsione: accumula il valore corrente
    return ogniPercorsoRadiceFoglia(a.figlio(SIN), max, current + a.radice()) 
        && ogniPercorsoRadiceFoglia(a.figlio(DES), max, current + a.radice());
}
```

**Pattern: Accumulatore**
```
L'accumulatore `current` tiene traccia della somma parziale
man mano che scendiamo nell'albero.

        5 (current=0, sommo 5)
       / \
      3   2 (current=5, sommo 3 o 2)
     /
    1 (current=8, sommo 1 → totale 9)

Al nodo foglia 1: current + radice = 8 + 1 = 9
Se max=10, 9 <= 10 → true
```

---

### 3.3 pariEDispari - Parità per Livello

**Problema:** Livello dispari → valore dispari, livello pari → valore pari

```cpp
bool pariEDispari(const AlberoB<int>& a) {
    return pariEDispari(a, 1);  // Radice al livello 1
}

bool pariEDispari(const AlberoB<int>& a, int livello) {
    if (a.nullo())
        return true;
    
    // Livello pari con valore dispari → false
    // Livello dispari con valore pari → false
    if ((livello % 2 == 0 && a.radice() % 2 != 0) || 
        (livello % 2 == 1 && a.radice() % 2 == 0))
        return false;
    
    return pariEDispari(a.figlio(SIN), livello + 1) 
        && pariEDispari(a.figlio(DES), livello + 1);
}
```

**Esempio valido:**
```
Livello 1 (dispari): valore dispari
        1
       / \
Livello 2 (pari): valori pari
      4   2
     /
Livello 3 (dispari): valore dispari
    3

pariEDispari(1, liv=1): 1%2==1 && 1%2==1 ✓
pariEDispari(4, liv=2): 2%2==0 && 4%2==0 ✓
pariEDispari(2, liv=2): 2%2==0 && 2%2==0 ✓
pariEDispari(3, liv=3): 3%2==1 && 3%2==1 ✓
```

---

### 3.4 vocaliEConsonanti - Differenza Vocali/Consonanti

**Problema:** Ogni path radice-foglia forma una parola. Verificare che |vocali - consonanti| ≤ 1

```cpp
bool vocaliEConsonanti(const AlberoB<char>& a) {
    return vocaliEConsonanti(a, 0);
}

bool vocaliEConsonanti(const AlberoB<char>& a, int diff) {
    if (a.nullo())
        return true;
    
    // Alla foglia controlliamo la differenza accumulata
    if (a.foglia())
        return abs(diff) <= 1;
    
    // Aggiorna la differenza: vocale +1, consonante -1
    if (a.radice() == 'a' || a.radice() == 'e' || 
        a.radice() == 'i' || a.radice() == 'o' || a.radice() == 'u')
        diff++;
    else
        diff--;
    
    return vocaliEConsonanti(a.figlio(SIN), diff) 
        && vocaliEConsonanti(a.figlio(DES), diff);
}
```

**Esempio:**
```
        c      diff=0
       / \
      a   i    diff=-1 (c è consonante)
     /
    r          diff=0 (a è vocale)

Path "car": c(-1), a(0), r(-1) → |−1| <= 1 ✓
Path "ci": c(-1), i(0) → |0| <= 1 ✓
```

---

### 3.5 fogliePosEqfoglieNeg - Bilanciamento Foglie Positive/Negative

**Problema:** Verificare che #foglie positive == #foglie negative

```cpp
bool fogliePosEqfoglieNeg(const AlberoB<int>& a) {
    return diffFoglie(a) == 0;
}

int diffFoglie(const AlberoB<int>& a) {
    if (a.nullo())
        return 0;
    
    if (a.foglia())
        return a.radice() < 0 ? -1 : 1;  // Negativa: -1, Positiva: +1
    
    return diffFoglie(a.figlio(SIN)) + diffFoglie(a.figlio(DES));
}
```

**Trace:**
```
        5
       / \
      -3   2
     / \
    -1  4

diffFoglie(-1) = -1 (negativa)
diffFoglie(4) = +1 (positiva)
diffFoglie(-3) = -1 + 1 = 0
diffFoglie(2) = +1 (foglia positiva)
diffFoglie(5) = 0 + 1 = 1

Risultato: 1 ≠ 0 → false (non bilanciato)
```

---

### 3.6 sommaPath - Numeri Formati dai Path

**Problema:** Ogni path radice-foglia forma un numero. Calcolare la somma di tutti.

```cpp
/*
       2
      / \
     3   4
        /
       5
   
   Risultato: 23 + 245 = 268
*/

int sommaPath(const AlberoB<int>& a) {
    return sommaPath(a, 0);
}

int sommaPath(const AlberoB<int>& a, int somma_corrente) {
    if (a.nullo())
        return 0;
    
    if (a.foglia())
        return somma_corrente * 10 + a.radice();  // Completa il numero
    
    return sommaPath(a.figlio(DES), somma_corrente * 10 + a.radice()) 
         + sommaPath(a.figlio(SIN), somma_corrente * 10 + a.radice());
}
```

**Trace dettagliata:**
```
        2
       / \
      3   4
         /
        5

sommaPath(2, 0):
  nuova_somma = 0*10 + 2 = 2
  
  sommaPath(3, 2):     // Ramo sinistro
    nuova_somma = 2*10 + 3 = 23
    è foglia → return 23
    
  sommaPath(4, 2):     // Ramo destro
    nuova_somma = 2*10 + 4 = 24
    
    sommaPath(5, 24):
      nuova_somma = 24*10 + 5 = 245
      è foglia → return 245
      
    return 0 + 245 = 245 (solo figlio SIN presente)
    
  return 23 + 245 = 268
```

---

### 3.7 vecToAlbero - Costruzione da Array

**Problema:** Convertire un array (rappresentazione implicita) in albero esplicito

```cpp
/*
 vettore = {3, 5, 7, 2, 4, 1, 5}
 
 albero:       3
              / \
             5   7
            / \ / \
           2  4 1  5
*/

AlberoB<int> vecToAlbero(vector<int> vettore) {
    AlberoB<int> albero(vettore[0]);  // Radice
    
    vector<AlberoB<int>> alberi;
    alberi.push_back(albero);
    
    for (int i = 1; i < vettore.size(); i++) {
        AlberoB<int> nuovo(vettore[i]);
        alberi.push_back(nuovo);
        
        // Formula: padre di i è (i-1)/2
        // i dispari → figlio sinistro
        // i pari → figlio destro
        if (i % 2 == 1)
            alberi[(i-1)/2].insFiglio(SIN, nuovo);
        else
            alberi[(i-1)/2].insFiglio(DES, nuovo);
    }
    
    return albero;
}
```

**Corrispondenza indice-posizione:**
```
Indice:  0   1   2   3   4   5   6
Valore:  3   5   7   2   4   1   5

i=0: radice
i=1: padre=(1-1)/2=0, dispari→SIN  →  alberi[0].insFiglio(SIN, 5)
i=2: padre=(2-1)/2=0, pari→DES     →  alberi[0].insFiglio(DES, 7)
i=3: padre=(3-1)/2=1, dispari→SIN  →  alberi[1].insFiglio(SIN, 2)
i=4: padre=(4-1)/2=1, pari→DES     →  alberi[1].insFiglio(DES, 4)
i=5: padre=(5-1)/2=2, dispari→SIN  →  alberi[2].insFiglio(SIN, 1)
i=6: padre=(6-1)/2=2, pari→DES     →  alberi[2].insFiglio(DES, 5)
```

---

### 3.8 sommaLivelliAdiacenti - BFS con Somma Livelli

**Problema:** Verificare che la somma di ogni coppia di livelli adiacenti ≤ pesoMax

```cpp
bool sommaLivelliAdiacenti(const AlberoB<int>& a, int pesoMax) {
    if (a.nullo()) return true;
    
    queue<AlberoB<int>> qAlberi;   // Coda per BFS
    queue<int> qLivelli;            // Livello di ogni nodo
    
    qAlberi.push(a);
    qLivelli.push(1);
    
    int sommaLivPrecedente = a.radice();
    int sommaLivSuccessivo = 0;
    int livelloPrecedente = 1;
    int livelloSuccessivo = 2;
    
    while (!qAlberi.empty()) {
        AlberoB<int> temp = qAlberi.front();
        qAlberi.pop();
        int livelloTemp = qLivelli.front();
        qLivelli.pop();
        
        if (livelloTemp == livelloSuccessivo) {
            // Stesso livello: accumula
            sommaLivSuccessivo += temp.radice();
        } else if (livelloTemp == livelloSuccessivo + 1) {
            // Nuovo livello: controlla e aggiorna
            if (sommaLivPrecedente + sommaLivSuccessivo > pesoMax)
                return false;
            
            livelloPrecedente = livelloSuccessivo;
            livelloSuccessivo++;
            sommaLivPrecedente = sommaLivSuccessivo;
            sommaLivSuccessivo = temp.radice();
        }
        
        // Aggiungi figli alla coda
        if (!temp.figlio(SIN).nullo()) {
            qAlberi.push(temp.figlio(SIN));
            qLivelli.push(livelloTemp + 1);
        }
        if (!temp.figlio(DES).nullo()) {
            qAlberi.push(temp.figlio(DES));
            qLivelli.push(livelloTemp + 1);
        }
    }
    
    // Controlla ultima coppia di livelli
    if (sommaLivPrecedente + sommaLivSuccessivo > pesoMax)
        return false;
    
    return true;
}
```

**Trace con l'albero del main:**
```
                    7           Livello 1: somma = 7
                   / \
                  1   4         Livello 2: somma = 1+4 = 5
                 /   / \
                7   3   21      Livello 3: somma = 7+3+21 = 31
               / \ / \ / \
              2  5 12 2 6  4    Livello 4: somma = 2+5+12+2+6+4 = 31

Coppie adiacenti:
  Liv 1 + Liv 2 = 7 + 5 = 12
  Liv 2 + Liv 3 = 5 + 31 = 36
  Liv 3 + Liv 4 = 31 + 31 = 62

Se pesoMax = 61: 62 > 61 → false
Se pesoMax = 62: tutte <= 62 → true
```

---

## 4. File Bonus: sort_find.cpp e example_static.cpp

### 4.1 sort_find.cpp - Comparatori Custom

```cpp
class Prodotto {
private:
    int id;
    string nome;
public:
    Prodotto(int id, string nome) : id(id), nome(nome) {}
    
    string getNome() const { return nome; }
    
    friend ostream& operator<<(ostream& o, const Prodotto& p) {
        o << p.id << p.nome;
        return o;
    }
};

// Comparatore custom per sort (ordine decrescente per nome)
bool mycmp(const Prodotto& p1, const Prodotto& p2) {
    return p1.getNome() > p2.getNome();  // '>' per decrescente
}

int main() {
    vector<Prodotto> v = {Prodotto(10,"Sale"), Prodotto(1,"Pepe")};
    
    // Ordina con comparatore custom
    sort(v.begin(), v.end(), mycmp);
    // Risultato: Sale, Pepe (decrescente alfabetico)
    
    // Ricerca con find (richiede operator==)
    Prodotto p3(1, "Sale");
    auto it = find(v.begin(), v.end(), p3);
    // ⚠️ operator== è commentato! Questo non compila!
}
```

**Nota sul codice:** 
- `operator==` è commentato, quindi `find()` non compila
- Per farlo funzionare, decommentare `operator==`

### 4.2 example_static.cpp - Variabili Statiche

```cpp
class Prodotto {
private:
    unsigned int id;
    string nome;
    static unsigned int progressivo;  // Dichiarazione
    
public:
    Prodotto(string nome) : id(progressivo++), nome(nome) {
        cout << "progressivo dopo creazione: " << progressivo << endl;
    }
};

// Inizializzazione FUORI dalla classe (obbligatoria!)
unsigned int Prodotto::progressivo = 0;

int main() {
    Prodotto p1("Sale");   // id=0, progressivo diventa 1
    Prodotto p2("Pepe");   // id=1, progressivo diventa 2
    Prodotto p3("Sale");   // id=2, progressivo diventa 3
}
```

**Output:**
```
0xABCD123  progressivo dopo creazione: 1
0Sale      progressivo: 3
0xDEF456   progressivo dopo creazione: 2
0Sale      progressivo: 3
1Pepe      progressivo: 3
0xGHI789   progressivo dopo creazione: 3
0Sale      progressivo: 3
1Pepe      progressivo: 3
2Sale      progressivo: 3
```

**Concetto chiave:** `progressivo` è condiviso tra TUTTE le istanze. Quando stampi qualsiasi oggetto, vedi il valore corrente globale (3).

---

## 5. Trace di Esecuzione

### 5.1 Costruzione Albero del main()

```cpp
AlberoB<int> a(7);        // Radice
AlberoB<int> a1(1), a2(4);
a.insFiglio(SIN, a1);     // 7→1
a.insFiglio(DES, a2);     // 7→4
```

```
Passo 1: AlberoB<int> a(7)
    
    pradice → [7]
              padre: null
              SIN: null
              DES: null

Passo 2: AlberoB<int> a1(1), a2(4)

    a.pradice → [7]
    a1.pradice → [1]
    a2.pradice → [4]

Passo 3: a.insFiglio(SIN, a1)

    a.pradice → [7]
                padre: null
                SIN: ────→ [1]
                            padre: ↑
                DES: null

Passo 4: a.insFiglio(DES, a2)

    a.pradice → [7]
                padre: null
                SIN: ────→ [1]
                DES: ────→ [4]
```

### 5.2 Chiamata isHeap

```
isHeap(7):
├── 7.nullo()? No
├── 7.foglia()? No
├── 7 < figlio(DES).radice() = 4? No (7 >= 4 ✓)
├── 7 < figlio(SIN).radice() = 1? No (7 >= 1 ✓)
├── isHeap(1):
│   ├── 1.nullo()? No
│   ├── 1.foglia()? No (ha figlio)
│   ├── 1 < 7? Sì! ← FALSO!
│   └── return false
└── return false (short-circuit, non valuta DES)

Risultato: false (l'albero NON è un max-heap)
```

---

## 6. Pattern Ricorrenti

### 6.1 Pattern: Funzione Wrapper

```cpp
// Versione pubblica (senza parametri extra)
bool funzione(const AlberoB<int>& a) {
    return funzione(a, valoreIniziale);
}

// Versione privata (con accumulatore)
bool funzione(const AlberoB<int>& a, int accumulatore) {
    // Implementazione con accumulatore
}
```

**Usato in:** `pariEDispari`, `ogniPercorsoRadiceFoglia`, `vocaliEConsonanti`, `sommaPath`

### 6.2 Pattern: Controllo AND

```cpp
// Proprietà deve valere per TUTTI i nodi
return proprieta(nodoCorrente) 
    && ricorsione(figlio(SIN)) 
    && ricorsione(figlio(DES));
```

**Usato in:** `isHeap`, `pariEDispari`, `ogniPercorsoRadiceFoglia`

### 6.3 Pattern: Somma Ricorsiva

```cpp
// Somma valori di tutti i nodi/foglie
return valore(nodoCorrente) 
     + ricorsione(figlio(SIN)) 
     + ricorsione(figlio(DES));
```

**Usato in:** `sommaPath`, `diffFoglie`

### 6.4 Pattern: BFS con Livelli

```cpp
queue<pair<AlberoB<T>, int>> q;  // (nodo, livello)
q.push({radice, 1});

while (!q.empty()) {
    auto [nodo, livello] = q.front();
    q.pop();
    
    // Processa nodo
    
    if (!nodo.figlio(SIN).nullo())
        q.push({nodo.figlio(SIN), livello + 1});
    if (!nodo.figlio(DES).nullo())
        q.push({nodo.figlio(DES), livello + 1});
}
```

**Usato in:** `sommaLivelliAdiacenti`

---

## Appendice: Tabella Riassuntiva Esercizi

| Esercizio | Tipo Visita | Accumulatore | Complessità |
|-----------|-------------|--------------|-------------|
| isHeap | DFS preorder | No | O(n) |
| ogniPercorsoRadiceFoglia | DFS preorder | Sì (somma) | O(n) |
| pariEDispari | DFS preorder | Sì (livello) | O(n) |
| vocaliEConsonanti | DFS preorder | Sì (diff) | O(n) |
| fogliePosEqfoglieNeg | DFS postorder | No | O(n) |
| sommaPath | DFS preorder | Sì (numero) | O(n) |
| vecToAlbero | Iterativo | No | O(n) |
| sommaLivelliAdiacenti | BFS | Sì (somme) | O(n) |
