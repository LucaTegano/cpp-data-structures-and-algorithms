# STL Deep Dive: Ricerca, Iterazione e Manipolazione Avanzata

In questa guida approfondiamo l'uso della Standard Template Library (STL) e confrontiamo l'approccio manuale (cicli) con quello professionale (algoritmi) per superare i test d'esame.

## Indice
1. [Trovare Elementi in un Vector: 3 Modi](#1-trovare-elementi-in-un-vector-3-modi)
2. [Ricerca Avanzata con Condizioni (Predicati)](#2-ricerca-avanzata-con-condizioni-predicati)
3. [Ricerca in Map e Set (La trappola della performance)](#3-ricerca-in-map-e-set-la-trappola-della-performance)
4. [Ricerca Binaria (Veloce: O(log N))](#4-ricerca-binaria-veloce-olog-n)
5. [Algoritmi di Verifica (Any, All, None)](#5-algoritmi-di-verifica-any-all-none)
6. [Trasformazione e Riduzione (Map/Reduce)](#6-trasformazione-e-riduzione-mapreduce)
7. [Utility Indispensabili](#7-utility-indispensabili)

---

## 1. Trovare Elementi in un Vector: 3 Modi

Immaginiamo di avere `vector<int> v = {10, 20, 30, 40, 50};` e cerchiamo il valore `30`.

### Metodo A: Il Ciclo Manuale (Approccio "Base")
Utile se devi fare operazioni molto complesse durante la ricerca.
```cpp
int target = 30;
int trovato_a = -1;

for (int i = 0; i < v.size(); i++) {
    if (v[i] == target) {
        trovato_a = i;
        break; // Esci appena trovi
    }
}
// trovato_a vale 2
```

### Metodo B: std::find (Approccio Professionale)
Più pulito, meno soggetto a errori (come gli indici sballati).
```cpp
auto it = find(v.begin(), v.end(), 30);

if (it != v.end()) {
    // Trovato! Calcoliamo l'indice se serve:
    int index = distance(v.begin(), it);
    cout << "Trovato a: " << index;
} else {
    cout << "Non trovato";
}
```

### Metodo C: Ricerca con Puntatori (Solo per esperti)
```cpp
int* p = find(&v[0], &v[0] + v.size(), 30);
if (p != &v[0] + v.size()) { /* Trovato */ }
```

---

## 2. Ricerca Avanzata con Condizioni (Predicati)

Spesso non cerchi un valore esatto, ma "il primo numero pari" o "lo studente con media > 28".

### std::find_if
```cpp
vector<int> v = {1, 3, 5, 8, 11};

// Trova il primo numero pari
auto it = find_if(v.begin(), v.end(), [](int n) {
    return n % 2 == 0;
});

if (it != v.end()) cout << "Trovato: " << *it; // Stampa 8
```

---

## 3. Ricerca in Map e Set (La trappola della performance)

**⚠️ ERRORE DA BOCCIATURA**: Usare `std::find(m.begin(), m.end(), val)` su una mappa.
- `std::find`: Scorre tutta la mappa linearmente ($O(N)$). **LENTO**.
- `m.find()`: Usa la struttura dell'albero ($O(\log N)$). **VELOCE**.

### Esempio Corretto
```cpp
map<string, int> voti = {{"Luca", 28}, {"Anna", 30}};

// ✅ SEMPRE USARE IL METODO MEMBRO
auto it = voti.find("Anna"); 

if (it != voti.end()) {
    cout << "Voto di Anna: " << it->second;
}
```

---

## 4. Ricerca Binaria (Veloce: $O(\log N)$)

Se il vector è **ordinato**, `find` è uno spreco. Usiamo la ricerca binaria.

| Funzione | Cosa Ritorna | Uso |
| :--- | :--- | :--- |
| `binary_search` | `bool` | Esiste o no? |
| `lower_bound` | `iterator` | Primo elemento $\ge$ target. |
| `upper_bound` | `iterator` | Primo elemento $>$ target. |

```cpp
vector<int> v = {10, 20, 30, 30, 40}; // Deve essere ordinato!

// Cerchiamo dove inserire un "30" mantenendo l'ordine
auto lb = lower_bound(v.begin(), v.end(), 30); // Punta al primo 30 (indice 2)
auto ub = upper_bound(v.begin(), v.end(), 30); // Punta al 40 (indice 4)

// Quanti 30 ci sono?
int count = distance(lb, ub); // 2
```

---

## 5. Algoritmi di Verifica (Any, All, None)

Per rispondere velocemente a domande su intere collezioni.

```cpp
vector<int> v = {2, 4, 6, 8};

bool tutti_pari = all_of(v.begin(), v.end(), [](int x){ return x%2==0; }); // true
bool almeno_un_dispari = any_of(v.begin(), v.end(), [](int x){ return x%2!=0; }); // false
bool nessuno_negativo = none_of(v.begin(), v.end(), [](int x){ return x < 0; }); // true
```

---

## 6. Trasformazione e Riduzione (Map/Reduce)

### std::transform (Applica funzione a tutti)
```cpp
vector<int> v = {1, 2, 3};
// Raddoppia tutti i numeri
transform(v.begin(), v.end(), v.begin(), [](int x){ return x * 2; });
// v ora è {2, 4, 6}
```

### std::accumulate (Combina tutti)
```cpp
#include <numeric>
vector<string> parole = {"C++", "è", "bello"};

// Concatena tutte le stringhe partendo da ""
string frase = accumulate(parole.begin(), parole.end(), string(""), 
    [](string a, string b) { return a + " " + b; });
// frase = " C++ è bello"
```

---

## 7. Utility Indispensabili

### Minimo e Massimo con logica custom
```cpp
struct Studente { string nome; int voto; };
vector<Studente> classe = {{"Z", 18}, {"A", 30}, {"B", 25}};

// Trova lo studente con il voto più alto
auto best = max_element(classe.begin(), classe.end(), [](const Studente& a, const Studente& b) {
    return a.voto < b.voto;
});
cout << "Top: " << best->nome; // Stampa A
```

### std::iota (Generatore di sequenze)
```cpp
vector<int> indici(10);
iota(indici.begin(), indici.end(), 0); // Riempie con 0, 1, 2, ..., 9
```

---

## 8. Tabella Riassuntiva: Quale Algoritmo usare?

| Situazione | Algoritmo Consigliato | Note |
| :--- | :--- | :--- |
| Valore esatto in Vector | `std::find` | $O(N)$ |
| Condizione in Vector | `std::find_if` | Usa una lambda |
| Valore in Map/Set | `m.find()` / `s.find()` | **MAI** usare `std::find` |
| Valore in Vector ORDINATO | `std::lower_bound` | $O(\log N)$ |
| Contare occorrenze | `std::count` | $O(N)$ |
| Verificare se TUTTI OK | `std::all_of` | $O(N)$ |
| Sommare o Combinare | `std::accumulate` | Header `<numeric>` |
| Modificare ogni elemento | `std::transform` | - |
