# Guida Pratica: Esercizi Liste (Esercizio1-6.cpp)

Questa guida analizza in dettaglio ogni esercizio della cartella.

---

## Esercizio 1: Creazione e Rimozione Pari

### Traccia
Crea una lista di numeri interi 1-10, stampa, rimuovi i pari, ristampa.

### Codice Completo

```cpp
#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> numbers;
    
    // Inserimento 1-10
    for (int i = 1; i <= 10; ++i) {
        numbers.push_back(i);
    }

    // Stampa iniziale
    cout << "Contenuto della lista: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // Rimuovi numeri pari
    for (auto it = numbers.begin(); it != numbers.end(); ) {
        if (*it % 2 == 0) {
            it = numbers.erase(it);  // IMPORTANTE: aggiorna it
        } else {
            ++it;
        }
    }

    // Stampa finale
    cout << "Lista senza numeri pari: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
```

### Punti Chiave

#### Pattern di Rimozione con Iteratore
```cpp
for (auto it = numbers.begin(); it != numbers.end(); ) {  // NO ++it qui!
    if (condizione) {
        it = numbers.erase(it);  // erase ritorna il prossimo
    } else {
        ++it;  // Avanza solo se non rimuovi
    }
}
```

**ERRORE COMUNE:**
```cpp
for (auto it = numbers.begin(); it != numbers.end(); ++it) {
    if (*it % 2 == 0) {
        numbers.erase(it);  // it invalido! Crash al prossimo ++it
    }
}
```

---

## Esercizio 2: Manipolazione Nomi

### Traccia
Lista di nomi, aggiungi in testa e coda, rimuovi uno specifico, ordina.

### Codice Completo

```cpp
#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() {
    list<string> names = {"Anna", "Luca", "Giovanni", "Paola"};
    
    names.push_front("Marco");  // Aggiungi in testa
    names.push_back("Elisa");   // Aggiungi in coda

    names.remove("Luca");       // Rimuovi tutte le occorrenze di "Luca"

    cout << "Lista dei nomi: ";
    for (const string& name : names) {
        cout << name << " ";
    }
    cout << endl;

    names.sort();  // Metodo membro, non std::sort!

    cout << "Lista ordinata: ";
    for (const string& name : names) {
        cout << name << " ";
    }
    cout << endl;

    return 0;
}
```

### Punti Chiave

#### `remove()` vs `erase()`
```cpp
names.remove("Luca");  // Rimuove TUTTE le occorrenze
// vs
it = names.erase(it);  // Rimuove UN elemento all'iteratore
```

#### `sort()` Membro vs `std::sort()`
```cpp
names.sort();  // OK per list
// std::sort(names.begin(), names.end());  // ERRORE! Richiede RandomAccessIterator
```

#### `const string&` nel Loop
```cpp
for (const string& name : names)  // Evita copie inutili
```

---

## Esercizio 3: Numeri Casuali e Media

### Traccia
Lista di 15 numeri casuali 1-100, rimuovi < 50, calcola media rimanenti.

### Codice Completo

```cpp
#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    list<int> numbers;
    srand(time(0));

    for (int i = 0; i < 15; ++i) {
        numbers.push_back(rand() % 100 + 1);
    }

    cout << "Lista originale: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // Rimuovi < 50
    for (auto it = numbers.begin(); it != numbers.end(); ) {
        if (*it < 50) {
            it = numbers.erase(it);
        } else {
            ++it;
        }
    }

    cout << "Lista con valori >= 50: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // Calcolo media
    int somma = 0;
    for (int num : numbers) {
        somma += num;
    }
    double media = numbers.empty() ? 0 : static_cast<double>(somma) / numbers.size();

    cout << "Media dei valori rimanenti: " << media << endl;

    return 0;
}
```

### Punti Chiave

#### Generazione Numeri Casuali
```cpp
srand(time(0));           // Inizializza seed con tempo corrente
rand() % 100 + 1;         // Numero tra 1 e 100
```

#### Controllo Lista Vuota
```cpp
double media = numbers.empty() ? 0 : (double)somma / numbers.size();
```

Evita divisione per zero!

---

## Esercizio 4: Rimozione Duplicati

### Traccia
Data una lista con duplicati, rimuovili mantenendo l'ordine.

### Codice Completo

```cpp
#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> numbers = {1, 2, 3, 2, 4, 1, 5, 3, 6};

    // Per ogni elemento, rimuovi i duplicati successivi
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        auto it_inner = it;
        ++it_inner;  // Parti dall'elemento successivo

        while (it_inner != numbers.end()) {
            if (*it == *it_inner) {
                it_inner = numbers.erase(it_inner);
            } else {
                ++it_inner;
            }
        }
    }

    cout << "Lista senza duplicati: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
```

### Complessita: O(n^2)

### Alternativa con unique() - O(n) ma richiede ordinamento

```cpp
numbers.sort();    // Prima ordina
numbers.unique();  // Poi rimuovi duplicati adiacenti
// Problema: cambia l'ordine originale
```

---

## Esercizio 5: Merge con Bubble Sort

### Traccia
Unisci due liste ordinate in una sola ordinata (senza std::sort).

### Codice Completo

```cpp
#include <iostream>
#include <list>
using namespace std;

void bubbleSortList(list<int>& lst) {
    bool swapped;
    do {
        swapped = false;
        for (auto it1 = lst.begin(); it1 != lst.end(); ++it1) {
            auto it2 = it1;
            ++it2;
            
            if (it2 != lst.end() && *it1 > *it2) {
                int temp = *it1;
                *it1 = *it2;
                *it2 = temp;
                swapped = true;
            }
        }
    } while (swapped);
}

int main() {
    list<int> list1 = {1, 3, 5, 7};
    list<int> list2 = {8, 2, 4, 6};

    list1.merge(list2);     // Unisce (l2 diventa vuota)
    bubbleSortList(list1);  // Ordina

    cout << "Lista unita e ordinata: ";
    for (int num : list1) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
```

### Punti Chiave

#### merge() Richiede Liste Ordinate!
```cpp
list1.sort();
list2.sort();
list1.merge(list2);  // Ora funziona correttamente
```

Se le liste non sono ordinate, merge() non garantisce risultato ordinato.

#### Bubble Sort su Lista
Non possiamo usare `[]`, quindi usiamo iteratori e swap dei valori.

---

## Esercizio 6: Inversione Lista

### Traccia
Inverti l'ordine degli elementi.

### Codice Completo

```cpp
#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() {
    list<string> names = {"Anna", "Luca", "Giovanni", "Paola"};

    names.reverse();

    cout << "Lista invertita: ";
    for (const string& name : names) {
        cout << name << " ";
    }
    cout << endl;

    return 0;
}
```

### Complessita: O(n)

La lista scambia i puntatori prev/next di ogni nodo.

---

## Tabella Riassuntiva Esercizi

| Esercizio | Operazioni Chiave | Complessita |
|-----------|-------------------|-------------|
| 1 | push_back, erase con iteratore | O(n) |
| 2 | push_front/back, remove, sort | O(n log n) |
| 3 | rand, erase, media | O(n) |
| 4 | doppio loop, erase | O(n^2) |
| 5 | merge, bubble sort | O(n^2) |
| 6 | reverse | O(n) |

---

## Errori Comuni e Soluzioni

### 1. Iteratore Invalidato

```cpp
// SBAGLIATO
for (auto it = l.begin(); it != l.end(); ++it) {
    l.erase(it);  // it invalido!
}

// CORRETTO
for (auto it = l.begin(); it != l.end(); ) {
    it = l.erase(it);
}
```

### 2. Usare std::sort su list

```cpp
// SBAGLIATO
std::sort(l.begin(), l.end());  // Errore di compilazione!

// CORRETTO
l.sort();  // Metodo membro
```

### 3. Accesso con []

```cpp
// SBAGLIATO
int x = l[5];  // list non ha operator[]!

// CORRETTO
auto it = l.begin();
advance(it, 5);
int x = *it;
```

### 4. unique() su Lista Non Ordinata

```cpp
list<int> l = {1, 2, 1, 2, 1};
l.unique();  // Risultato: {1, 2, 1, 2, 1} - nessun cambiamento!
// unique rimuove solo duplicati ADIACENTI

l.sort();    // {1, 1, 1, 2, 2}
l.unique();  // {1, 2} - ora funziona
```

### 5. Dimenticare di Avanzare Iteratore Interno

```cpp
// SBAGLIATO - loop infinito
while (it_inner != l.end()) {
    if (*it == *it_inner) {
        l.erase(it_inner);  // it_inner non aggiornato!
    }
}

// CORRETTO
while (it_inner != l.end()) {
    if (*it == *it_inner) {
        it_inner = l.erase(it_inner);
    } else {
        ++it_inner;
    }
}
```
