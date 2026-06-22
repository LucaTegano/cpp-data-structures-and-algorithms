# Teoria Completa: Tweets e Two Sum - STL Avanzato

Questo documento analizza due esercizi classici che combinano stringhe, contenitori STL e algoritmi.

---

## Indice
1. [Esercizio Tweets](#1-esercizio-tweets)
2. [Esercizio Two Sum](#2-esercizio-two-sum)
3. [Strutture Dati Utilizzate](#3-strutture-dati-utilizzate)
4. [Pattern di Programmazione](#4-pattern-di-programmazione)

---

## 1. Esercizio Tweets

### Problema
Dato un insieme di tweet:
1. Estrai tutti gli hashtag
2. Conta la frequenza di ogni hashtag
3. Ordina per frequenza
4. Filtra tweet per hashtag specifico

### Struttura del Codice

```cpp
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
```

### Funzione `extract_hashtags()`

```cpp
vector<string> extract_hashtags(const string& tweet) {
    int pos_hash = 0; 
    int pos_space = 0;
    vector<string> hashtags; 
    
    while (pos_hash != -1) {
        pos_hash = tweet.find("#", pos_hash + 1);
        if (pos_hash != -1) {
            pos_space = tweet.find(" ", pos_hash + 1);
            hashtags.push_back(tweet.substr(pos_hash, pos_space - pos_hash));
        }
    }
    return hashtags;
}
```

#### Analisi

**`string::find()`:**
```cpp
size_t pos = str.find("pattern", start_pos);
// Ritorna posizione se trovato, string::npos se non trovato
// npos e tipicamente (size_t)-1, cioe un valore molto grande
```

**`string::substr()`:**
```cpp
string sub = str.substr(start, length);
// Estrae sottrostringa da start per length caratteri
```

**Esempio:**
```
Tweet: "Oggi sole #estate #mare bella giornata"

Iterazione 1: find("#") = 11, find(" ", 12) = 18
  substr(11, 18-11) = "#estate"

Iterazione 2: find("#", 12) = 19, find(" ", 20) = 24
  substr(19, 24-19) = "#mare"

Iterazione 3: find("#", 20) = -1 -> esci
```

### Classe `Tweet`

```cpp
class Tweet {
public:
    const string text;
    const vector<string> hashtags;

    Tweet(const string& text)
        : text(text), hashtags(extract_hashtags(text)) {}

    bool has_hashtag(const string& hashtag) const {
        return find(hashtags.begin(), hashtags.end(), hashtag) != hashtags.end(); 
    }

    static Tweet read(istream& in) {
        string text; 
        getline(in, text);
        return Tweet(text);
    }
};
```

#### Punti Chiave

**Initialization List con Funzione:**
```cpp
: text(text), hashtags(extract_hashtags(text))
```
Gli hashtag vengono estratti nel costruttore.

**Metodo Statico `read()`:**
```cpp
static Tweet read(istream& in)
```
Factory method che crea un Tweet leggendo da stream.

**`std::find()` su vector:**
```cpp
find(v.begin(), v.end(), value) != v.end()  // true se trovato
```

### Conteggio Frequenze con `std::map`

```cpp
map<string, int> hashtag_frequency;

for (int i = 0; i < n; ++i) {
    for (const string& h : tweets[i].hashtags) {
        hashtag_frequency[h]++;
    }
}
```

#### Magia dell'operator[]

```cpp
hashtag_frequency[h]++;
```

Se `h` non esiste nella mappa:
1. Viene creata una nuova entry con valore **default** (0 per int)
2. Poi viene incrementato
3. Risultato: `h` -> 1

Se `h` esiste:
1. Viene incrementato il valore esistente

### Ordinamento per Valore

Le mappe sono ordinate per **chiave**. Per ordinare per **valore** (frequenza):

```cpp
// 1. Copia in vector di pair
vector<pair<string,int>> vec;
for (auto& entry : hashtag_frequency) {
    vec.push_back(make_pair(entry.first, entry.second));
}

// 2. Definisci comparatore
bool sort_by_freq(const pair<string,int>& p1, const pair<string,int>& p2) {
    return p1.second < p2.second;  // Ordine crescente
}

// 3. Ordina
sort(vec.begin(), vec.end(), sort_by_freq);

// 4. Stampa in ordine decrescente (reverse iterator)
for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
    cout << it->first << ": " << it->second << endl; 
}
```

---

## 2. Esercizio Two Sum

### Problema
Dato un array di interi e un target, trova due numeri la cui somma e il target. Restituisci i loro indici.

**Esempio:**
```
Input: nums = [2, 7, 11, 15], target = 9
Output: [0, 1]  (nums[0] + nums[1] = 2 + 7 = 9)
```

### Soluzione Naive - O(n^2)

```cpp
vector<int> twoSumNaive(vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); i++) {
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[i] + nums[j] == target) {
                return {i, j};
            }
        }
    }
    return {};
}
```

### Soluzione Ottimale con Hash Map - O(n)

```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> mappa;  // valore -> indice
    
    for (int i = 0; i < nums.size(); i++) {
        int complemento = target - nums[i];
        
        // Cerca se il complemento esiste
        auto it = mappa.find(complemento);
        if (it != mappa.end()) {
            return {it->second, i};
        }
        
        // Inserisci numero corrente
        mappa[nums[i]] = i;
    }
    
    return {};
}
```

#### Spiegazione

**Idea:** Per ogni numero `x`, cerchiamo se `target - x` e gia stato visto.

**Esempio step-by-step:**
```
nums = [2, 7, 11, 15], target = 9

i=0: nums[0]=2, complemento=7
     mappa.find(7) -> non trovato
     mappa[2] = 0
     mappa: {2->0}

i=1: nums[1]=7, complemento=2
     mappa.find(2) -> TROVATO! indice 0
     return {0, 1}
```

#### Perche `unordered_map`?

| Operazione | map (albero) | unordered_map (hash) |
|------------|--------------|----------------------|
| find | O(log n) | O(1) medio |
| insert | O(log n) | O(1) medio |

Per questo problema, `unordered_map` e piu efficiente.

---

## 3. Strutture Dati Utilizzate

### 3.1 `std::map<K, V>`

Mappa ordinata basata su albero rosso-nero.

```cpp
map<string, int> m;

m["chiave"] = valore;     // Inserimento/modifica
int v = m["chiave"];      // Accesso (crea se non esiste!)
m.find("chiave");         // Cerca senza creare
m.count("chiave");        // 1 se esiste, 0 altrimenti
m.erase("chiave");        // Rimuovi

// Iterazione (ordinata per chiave)
for (auto& [k, v] : m) {
    cout << k << ": " << v << endl;
}
```

### 3.2 `std::unordered_map<K, V>`

Hash table - piu veloce ma non ordinata.

```cpp
unordered_map<int, int> m;

// Stesse operazioni di map
m[chiave] = valore;
auto it = m.find(chiave);
```

### 3.3 `std::pair<T1, T2>`

Coppia di valori.

```cpp
pair<string, int> p = {"hello", 42};
cout << p.first << " " << p.second;  // "hello 42"

// C++11: make_pair
auto p2 = make_pair("world", 100);
```

### 3.4 `std::vector<pair<>>`

Usato per ordinare mappe per valore.

```cpp
vector<pair<string, int>> vec;
vec.push_back({"a", 1});
vec.push_back({"b", 2});

sort(vec.begin(), vec.end(), [](auto& a, auto& b) {
    return a.second > b.second;  // Ordine decrescente per valore
});
```

---

## 4. Pattern di Programmazione

### 4.1 Input con `cin >> n` seguito da `getline`

**Problema:**
```cpp
int n;
cin >> n;  // Legge numero, lascia '\n' nel buffer

string line;
getline(cin, line);  // Legge '\n', line e vuota!
```

**Soluzione 1:** Ignora il resto della riga
```cpp
cin >> n;
cin.ignore();  // Salta un carattere (il '\n')
getline(cin, line);
```

**Soluzione 2:** Leggi una riga dummy
```cpp
cin >> n;
string dummy;
getline(cin, dummy);  // Consuma il '\n'
getline(cin, line);   // Ora funziona
```

### 4.2 Ricerca in Contenitori

```cpp
// In vector
auto it = find(v.begin(), v.end(), value);
bool found = (it != v.end());

// In map/unordered_map
auto it = m.find(key);
bool found = (it != m.end());

// Alternativa per map
bool found = m.count(key) > 0;
```

### 4.3 Ordinamento con Comparatore Custom

```cpp
// Funzione comparatore
bool myCompare(const T& a, const T& b) {
    return /* true se a < b */;
}
sort(v.begin(), v.end(), myCompare);

// Lambda (C++11)
sort(v.begin(), v.end(), [](const T& a, const T& b) {
    return a.field < b.field;
});
```

### 4.4 Iterazione Inversa

```cpp
// Con reverse iterator
for (auto it = v.rbegin(); it != v.rend(); ++it) {
    cout << *it << " ";
}
```

---

## Complessita Riassuntiva

| Operazione | Complessita |
|------------|-------------|
| extract_hashtags | O(L) dove L = lunghezza tweet |
| Conteggio frequenze | O(n * h) dove h = hashtag medi per tweet |
| Ordinamento vector | O(m log m) dove m = hashtag unici |
| Two Sum naive | O(n^2) |
| Two Sum ottimale | O(n) |

---

## Esercizi Proposti

### 1. Trovare Top-K Hashtag

```cpp
// Modifica il codice per mostrare solo i top 3 hashtag
partial_sort(vec.begin(), vec.begin() + 3, vec.end(), comparator);
for (int i = 0; i < 3; i++) {
    cout << vec[i].first << ": " << vec[i].second << endl;
}
```

### 2. Two Sum con Duplicati

```cpp
// Trova TUTTE le coppie (non solo la prima)
vector<pair<int,int>> twoSumAll(vector<int>& nums, int target) {
    vector<pair<int,int>> result;
    unordered_map<int, vector<int>> mappa;  // valore -> lista indici
    
    for (int i = 0; i < nums.size(); i++) {
        int comp = target - nums[i];
        if (mappa.count(comp)) {
            for (int j : mappa[comp]) {
                result.push_back({j, i});
            }
        }
        mappa[nums[i]].push_back(i);
    }
    return result;
}
```

### 3. Three Sum

```cpp
// Estendi a tre numeri: a + b + c = target
// Hint: per ogni elemento, risolvi Two Sum sul resto
```
