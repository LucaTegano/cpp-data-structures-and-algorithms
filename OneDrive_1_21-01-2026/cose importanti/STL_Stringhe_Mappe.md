# Cheat Sheet: std::string, std::map e std::set

Guida rapida ai container associativi e alla manipolazione del testo.

## Indice
1. [std::string](#1-stdstring)
2. [std::map e std::unordered_map](#2-stdmap-e-stdunordered_map)
3. [std::set e std::unordered_set](#3-stdset-e-stdunordered_set)
4. [Tipi Custom come Chiavi](#4-tipi-custom-come-chiavi)

---

## 1. std::string

| Metodo | Scopo |
| :--- | :--- |
| `s.length()` / `s.size()` | Lunghezza della stringa. |
| `s.empty()` | True se la stringa è "". |
| `s.clear()` | Rende la stringa vuota. |
| `s.push_back(c)` | Aggiunge un carattere alla fine. |
| `s.append(s2)` | Aggiunge una stringa alla fine (come `+=`). |
| `s.substr(pos, len)` | Sottostringa di `len` caratteri da `pos`. |
| `s.find(target)` | Cerca `target`. Ritorna `string::npos` se non trovato. |

### Snippet: Parsing di stringhe separate da virgola
```cpp
string s = "mela,pera,banana";
size_t start = 0;
size_t end = s.find(",");

while (end != string::npos) {
    cout << s.substr(start, end - start) << endl;
    start = end + 1;
    end = s.find(",", start);
}
cout << s.substr(start) << endl; // Ultimo pezzo
```

---

## 2. std::map e std::unordered_map

### 2.1 Differenze
| Caratteristica | `std::map` | `std::unordered_map` |
| :--- | :--- | :--- |
| **Struttura** | Albero Red-Black | Hash Table |
| **Ordine** | Chiavi ordinate | Nessun ordine |
| **Ricerca** | $O(\log N)$ | $O(1)$ medio |
| **Requisito** | `operator<` | `hash` + `operator==` |

### 2.2 Metodi Comuni
```cpp
m[key] = val;             // Inserisce o aggiorna
m.erase(key);             // Rimuove
m.count(key);             // 1 se presente, 0 altrimenti
m.find(key);              // Iteratore o m.end()
m.clear();                // Svuota
```

### 2.3 Chaining vs find
```cpp
// ⚠️ ATTENZIONE: m[key] crea l'elemento se non esiste!
if (m["chiave"] == 0) { ... } // Se non c'era, ora c'è un elemento con valore 0

// ✅ SICURO: usare find()
if (m.find("chiave") != m.end()) {
    // Esiste davvero
}
```

---

## 3. std::set e std::unordered_set

Usati per collezioni di elementi **unici**.

```cpp
set<int> s;
s.insert(10);
s.insert(10); // Non fa nulla, già presente

if (s.count(10)) cout << "Presente";

for (int x : s) cout << x << " "; // Stampati in ordine crescente
```

---

## 4. Tipi Custom come Chiavi

Se vuoi usare una tua classe (es. `Persona`) come chiave:

### 4.1 Per std::map (richiede `<`)
```cpp
struct Persona {
    string nome;
    bool operator<(const Persona& other) const {
        return nome < other.nome;
    }
};
map<Persona, int> m;
```

### 4.2 Per std::unordered_map (richiede hash + `==`)
```cpp
struct Persona {
    string nome;
    bool operator==(const Persona& other) const {
        return nome == other.nome;
    }
};

struct PersonaHash {
    size_t operator()(const Persona& p) const {
        return hash<string>{}(p.nome);
    }
};

unordered_map<Persona, int, PersonaHash> m;
```
