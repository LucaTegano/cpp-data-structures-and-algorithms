# Guida Pratica: Analisi Tweets e Two Sum

Questa guida analizza in dettaglio i file `tweets.cpp` e `two_sum/main.cpp`.

---

## Analisi: `tweets.cpp`

### Struttura del File

```cpp
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <list>
using namespace std;
```

### Funzione `extract_hashtags()` (Righe 10-22)

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

#### Trace di Esecuzione

```
Input: "Oggi #sole splendido #estate #mare"

Iterazione 1:
  pos_hash = find("#", 1) = 5
  pos_space = find(" ", 6) = 10
  substr(5, 10-5) = "#sole"
  hashtags = ["#sole"]

Iterazione 2:
  pos_hash = find("#", 6) = 21
  pos_space = find(" ", 22) = 28
  substr(21, 28-21) = "#estate"
  hashtags = ["#sole", "#estate"]

Iterazione 3:
  pos_hash = find("#", 22) = 29
  pos_space = find(" ", 30) = npos (fine stringa)
  substr(29, npos-29) = "#mare" (fino a fine stringa)
  hashtags = ["#sole", "#estate", "#mare"]

Iterazione 4:
  pos_hash = find("#", 30) = -1 (npos)
  Esce dal while
```

#### Potenziale Bug

Se un hashtag e alla fine senza spazio:
```cpp
pos_space = tweet.find(" ", pos_hash + 1);  // Ritorna npos
tweet.substr(pos_hash, npos - pos_hash);    // npos e ENORME!
```

Fortunatamente, `substr` con lunghezza > stringa restante tronca automaticamente.

### Classe `Tweet` (Righe 24-42)

```cpp
class Tweet {
public:
    const string text;           // Immutabile
    const vector<string> hashtags;  // Immutabile

    Tweet(const string& text)
        : text(text)
        , hashtags(extract_hashtags(text)) {}

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

#### Attributi `const`

```cpp
const string text;
const vector<string> hashtags;
```

Una volta creato, il Tweet non puo essere modificato. Questo garantisce:
- Thread safety
- Nessun side effect inatteso
- Gli hashtag corrispondono sempre al testo

#### Factory Method `read()`

```cpp
static Tweet read(istream& in) {
    string text; 
    getline(in, text);
    return Tweet(text);
}
```

- `static`: Non richiede un'istanza per essere chiamato
- Legge una riga intera (con spazi)
- Ritorna un nuovo Tweet

### Comparatore per Ordinamento (Riga 44-46)

```cpp
bool sort_frequence_pairs(const pair<string, int>& p1, const pair<string, int>& p2) {
    return p1.second < p2.second;  // Ordine crescente
}
```

Usato con `sort()` per ordinare pair per il secondo elemento (frequenza).

### Main - Lettura Tweet (Righe 49-60)

```cpp
int main() {
    vector<Tweet> tweets;
    int n; 
    cin >> n; 

    // ATTENZIONE: cin non pulisce il buffer dopo l'inserimento di n

    for (int i = 0; i < n; ++i) {
        tweets.push_back(Tweet::read(cin)); 
    }
```

#### Il Problema del Buffer

```cpp
cin >> n;  // Legge "5", lascia "\n" nel buffer
Tweet::read(cin);  // getline legge "\n" -> stringa vuota!
```

**Soluzione nel codice originale:** Il primo tweet letto sara vuoto, ma i successivi funzionano. Per fix completo:

```cpp
cin >> n;
cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Pulisci buffer
```

### Main - Conteggio Frequenze (Righe 63-69)

```cpp
map<string, int> hashtag_frequency;
for (int i = 0; i < n; ++i) {
    for (const string& h : tweets[i].hashtags) {
        hashtag_frequency[h]++;
    }
}
```

**Magia di `operator[]`:**
- Se `h` non esiste: crea entry con valore 0, poi incrementa
- Se `h` esiste: incrementa direttamente

### Main - Conversione e Ordinamento (Righe 71-81)

```cpp
vector<pair<string,int>> hashtags_with_frequence;

// Copia mappa in vettore
for (auto i = hashtag_frequency.begin(); i != hashtag_frequency.end(); ++i) {
    hashtags_with_frequence.push_back(make_pair(i->first, i->second));
}

// Ordina per frequenza
sort(hashtags_with_frequence.begin(), hashtags_with_frequence.end(), sort_frequence_pairs);

// Stampa in ordine decrescente (reverse)
for (auto it = hashtags_with_frequence.rbegin(); it != hashtags_with_frequence.rend(); ++it) {
    cout << it->first << ": " << it->second << endl; 
}
```

#### Perche Convertire in Vector?

- `std::map` e ordinata per **chiave** (stringa)
- Vogliamo ordinare per **valore** (frequenza)
- `std::sort` funziona solo su contenitori con random access

### Main - Filtro per Hashtag (Righe 83-89)

```cpp
string hashtag; 
cin >> hashtag; 

cout << "All tweets containing the hashtag: " << hashtag << endl; 
for (const Tweet& t : tweets) {
    if (t.has_hashtag(hashtag)) 
        cout << t.text << endl; 
}
```

---

## Analisi: `two_sum/main.cpp`

### Codice Completo

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target);

int main() {
    vector<int> nums{2, 3, 5, 4, 5, 4, 22, 21};
    int target = 43;
    
    vector<int> soluzione = twoSum(nums, target);
    for (int i = 0; i < soluzione.size(); i++) {
        cout << "Indice: " << soluzione[i] << " - Valore: " << nums[soluzione[i]] << endl;
    }

    return 0;
}

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> mappa;  // valore -> indice
    vector<int> solution;

    for (int i = 0; i < nums.size(); i++) {
        // Cerca complemento
        auto it = mappa.find(target - nums[i]);
        
        if (it != mappa.end()) {
            cout << "Soluzione trovata" << endl;
            solution.push_back(it->second);  // Indice del complemento
            solution.push_back(i);           // Indice corrente
            return solution;
        }
        
        // Inserisci nella mappa
        mappa.insert({nums[i], i});
    }

    return solution;  // Vuoto se non trovato
}
```

### Trace di Esecuzione

```
nums = [2, 3, 5, 4, 5, 4, 22, 21], target = 43

i=0: nums[0]=2, cerco 43-2=41
     mappa.find(41) -> non trovato
     mappa.insert({2, 0})
     mappa: {2->0}

i=1: nums[1]=3, cerco 40
     non trovato
     mappa: {2->0, 3->1}

i=2: nums[2]=5, cerco 38
     non trovato
     mappa: {2->0, 3->1, 5->2}

i=3: nums[3]=4, cerco 39
     non trovato
     mappa: {2->0, 3->1, 5->2, 4->3}

i=4: nums[4]=5, cerco 38
     non trovato
     mappa: {2->0, 3->1, 5->4, 4->3}  // 5 sovrascrive!

i=5: nums[5]=4, cerco 39
     non trovato
     mappa: {2->0, 3->1, 5->4, 4->5}  // 4 sovrascrive!

i=6: nums[6]=22, cerco 21
     non trovato
     mappa: {..., 22->6}

i=7: nums[7]=21, cerco 22
     mappa.find(22) -> TROVATO! indice 6
     return {6, 7}

Output:
Indice: 6 - Valore: 22
Indice: 7 - Valore: 21
```

### Punti Chiave

#### `unordered_map::find()` vs `operator[]`

```cpp
// find() - non modifica la mappa
auto it = mappa.find(key);
if (it != mappa.end()) {
    int value = it->second;
}

// operator[] - CREA entry se non esiste!
int value = mappa[key];  // Se key non esiste, crea key->0
```

Per la ricerca, usa sempre `find()` per evitare inserimenti accidentali.

#### `mappa.insert()` vs `mappa[]`

```cpp
mappa.insert({nums[i], i});  // Non sovrascrive se esiste
mappa[nums[i]] = i;          // Sovrascrive sempre
```

Nel codice, `insert` e usato, quindi il primo indice viene mantenuto. Ma nota che il codice continua il loop anche dopo `insert`, quindi elementi successivi potrebbero sovrascrivere... 

**In realta il codice usa insert correttamente:** `insert` non sovrascrive, quindi il primo indice di ogni valore viene mantenuto.

#### Struttura della Soluzione

```cpp
vector<int> solution;
solution.push_back(it->second);  // Primo: indice del complemento (trovato prima)
solution.push_back(i);           // Secondo: indice corrente
```

Ritorna sempre l'indice minore per primo (quello inserito nella mappa era precedente).

---

## Esercizi Proposti

### 1. Gestire il Buffer di Input nei Tweets

```cpp
cin >> n;
string dummy;
getline(cin, dummy);  // Consuma il '\n'

for (int i = 0; i < n; ++i) {
    tweets.push_back(Tweet::read(cin)); 
}
```

### 2. Two Sum che Trova Tutte le Coppie

```cpp
vector<pair<int,int>> twoSumAll(vector<int>& nums, int target) {
    vector<pair<int,int>> result;
    unordered_map<int, vector<int>> mappa;  // valore -> LISTA indici
    
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

### 3. Hashtag Trending (Finestra Temporale)

```cpp
// Assumi che i tweet abbiano un timestamp
// Trova hashtag piu frequenti nelle ultime N ore
```

---

## Errori Comuni

### 1. Non Gestire il Buffer dopo `cin >>`

```cpp
// SBAGLIATO
cin >> n;
getline(cin, line);  // Legge stringa vuota!

// CORRETTO
cin >> n;
cin.ignore();
getline(cin, line);
```

### 2. Usare `[]` per Cercare

```cpp
// SBAGLIATO - crea entry se non esiste!
if (mappa[key] != 0) { ... }

// CORRETTO
if (mappa.find(key) != mappa.end()) { ... }
// oppure
if (mappa.count(key) > 0) { ... }
```

### 3. Dimenticare `const&` nel Loop

```cpp
// Copia ogni stringa - inefficiente
for (string h : tweets[i].hashtags) { ... }

// Riferimento costante - efficiente
for (const string& h : tweets[i].hashtags) { ... }
```

### 4. Comparatore con Ordine Sbagliato

```cpp
// Per ordine CRESCENTE
return a.second < b.second;

// Per ordine DECRESCENTE
return a.second > b.second;
```
