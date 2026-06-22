# Guida Completa all'Iterazione dei Contenitori in C++

In questa guida sono raccolti i modi più semplici, puliti e sicuri per scorrere (iterare) ogni tipo di struttura dati comune in C++.

---

## 1. std::vector
Il vettore supporta sia l'accesso tramite indice che tramite iteratori.

### Metodo A: Il ciclo più semplice (Range-based `for`) - **Consigliato**
Ideale se devi solo leggere o modificare gli elementi senza bisogno dell'indice numerico.
```cpp
vector<int> v = {10, 20, 30};

// Solo lettura (const & per efficienza)
for (const auto &elem : v) {
    cout << elem << " ";
}

// Lettura e Scrittura (per riferimento)
for (auto &elem : v) {
    elem += 5; // Modifica direttamente l'elemento nel vettore
}
```

### Metodo B: Ciclo classico con indice (size_t)
Utile se hai bisogno dell'indice numerico `i` (ad esempio per stampare la posizione o confrontare elementi a distanze diverse).
```cpp
for (size_t i = 0; i < v.size(); ++i) {
    cout << "Indice: " << i << ", Valore: " << v[i] << endl;
}
```

---

## 2. std::list
La lista **non** supporta l'accesso diretto tramite indice (no `l[i]`). Si può scorrere solo sequenzialmente.

### Metodo A: Range-based `for` - **Consigliato**
```cpp
list<string> parole = {"ciao", "mondo"};

for (const string &s : parole) {
    cout << s << endl;
}
```

### Metodo B: Ciclo con iteratori (Tradizionale)
Necessario se devi usare metodi specifici come `.insert()` o `.erase()`.
```cpp
for (auto it = parole.begin(); it != parole.end(); ++it) {
    cout << *it << endl; // Usiamo l'asterisco * per accedere al valore puntato
}
```

### Metodo C: Iterare e Rimuovere elementi in sicurezza (Importantissimo per l'Esame!)
Se fai `l.erase(it)` mentre cicli normalmente con `++it`, rompi l'iteratore e il programma crasha. Devi aggiornare l'iteratore con il valore di ritorno di `erase()`:
```cpp
auto it = parole.begin();
while (it != parole.end()) {
    if (*it == "elimina_me") {
        it = parole.erase(it); // erase rimuove l'elemento e restituisce l'iteratore successivo
    } else {
        ++it; // Avanziamo solo se non abbiamo cancellato
    }
}
```

---

## 3. std::unordered_map e std::map (Dizionari Chiave-Valore)
Le mappe contengono coppie di elementi (`std::pair`). Ogni elemento ha `.first` (la chiave) e `.second` (il valore).

### Metodo A: Structured Binding (C++17) - **Semplicissimo**
```cpp
unordered_map<string, int> eta = {{"Alice", 20}, {"Bob", 25}};

// Legge direttamente chiave e valore come variabili separate
for (const auto &[nome, anni] : eta) {
    cout << nome << " ha " << anni << " anni" << endl;
}
```

### Metodo B: Iterazione classica su `std::pair`
```cpp
for (const auto &coppia : eta) {
    cout << coppia.first << " -> " << coppia.second << endl;
}
```

---

## 4. std::set e std::unordered_set
I set contengono solo chiavi uniche e non sono indicizzabili. Gli elementi all'interno di un `std::set` sono **sempre di sola lettura** (const) per evitare di rompere l'ordinamento interno.

```cpp
set<int> numeri = {5, 1, 3};

for (const auto &num : numeri) {
    cout << num << " "; // Stamperà: 1 3 5 (ordinati automaticamente!)
}
```

---

## 5. Array classici (C-Style)
Funzionano esattamente come i vettori.

```cpp
int arr[] = {1, 2, 3, 4, 5};
int n = sizeof(arr) / sizeof(arr[0]); // Calcola la dimensione dell'array

// Ciclo con indice
for (int i = 0; i < n; ++i) {
    cout << arr[i] << " ";
}

// Range-based for (funziona anche qui!)
for (int x : arr) {
    cout << x << " ";
}
```

---

## 6. Code e Pile (std::queue e std::stack)
**Attenzione:** Le code e le pile **non si possono scorrere** con un ciclo `for` perché sono progettate per dare accesso solo al primo/ultimo elemento.
L'unico modo per vederli tutti è **svuotarli** uno alla volta (distruggendo la struttura originale, a meno di non farne prima una copia).

### Svuotare e scorrere una `std::queue` (FIFO)
```cpp
queue<int> q;
q.push(1);
q.push(2);

while (!q.empty()) {
    int valore = q.front(); // Prende l'elemento in testa
    q.pop();                // Lo rimuove dalla coda
    cout << valore << " ";
}
```

### Svuotare e scorrere uno `std::stack` (LIFO)
```cpp
stack<int> s;
s.push(1);
s.push(2);

while (!s.empty()) {
    int valore = s.top(); // Prende l'elemento in cima
    s.pop();              // Lo rimuove dalla pila
    cout << valore << " ";
}
```
