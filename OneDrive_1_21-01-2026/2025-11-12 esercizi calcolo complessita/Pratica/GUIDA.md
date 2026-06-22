# Guida Pratica: Risolvere i PDF di Complessita

Analizziamo i pattern ricorrenti che troverai nei file `.pdf` di questa cartella (`EserciziPerCasa.pdf`, `esercitazione_complessita.pdf`).

---

## Metodologia di Risoluzione

### Step 1: Leggi il Codice Attentamente
- Identifica tutti i cicli e il loro annidamento
- Nota i limiti dei cicli (costanti vs variabili)
- Cerca modifiche agli indici all'interno dei cicli

### Step 2: Conta le Iterazioni
Per ogni ciclo, determina:
- Valore iniziale
- Condizione di terminazione
- Come cambia l'indice ad ogni iterazione

### Step 3: Combina le Complessita
- Cicli sequenziali: prendi il massimo
- Cicli annidati: moltiplica
- Applica le regole asintotiche (ignora costanti, prendi termine dominante)

---

## Pattern 1: Il "Finto" Quadratico

```cpp
void func(int n) {
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 100; j++) { // Costante!
            k++;
        }
    }
}
```

**Errore comune:** Pensare che sia $O(n^2)$

**Analisi corretta:**
- Ciclo esterno: $n$ iterazioni
- Ciclo interno: **100** iterazioni (costante, indipendente da `n`!)
- Totale: $100 \times n = 100n$

**Risposta: $O(n)$**

**Regola:** Le costanti moltiplicative si ignorano in Big O, ma se il limite fosse `j < m` allora sarebbe $O(n \cdot m)$.

---

## Pattern 2: While che dipende da condizione "strana"

```cpp
int i = 0;
while (i * i < n) {
    i++;
}
```

**Analisi:**
- Il ciclo termina quando $i^2 \ge n$
- Quindi quando $i \ge \sqrt{n}$
- Numero di iterazioni: $\sqrt{n}$

**Risposta: $O(\sqrt{n})$**

**Varianti:**
```cpp
while (i * i * i < n) { i++; }  // O(n^(1/3)) - radice cubica
while (2 << i < n) { i++; }     // O(log n) - esponente
while (i! < n) { i++; }         // O(log n / log log n) - fattoriale inverso
```

---

## Pattern 3: Modifica dell'Iteratore Interno

```cpp
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        k++;
        i++; // Attenzione! Modifica l'indice esterno
    }
}
```

**Analisi passo-passo:**

Apparentemente $O(n^2)$. Ma guarda bene!

**Prima iterazione esterna (i=0):**
- j va da 0 a n-1: n iterazioni
- Ad ogni iterazione: k++, i++
- Dopo il ciclo interno: i = n
- Poi il for fa i++: i = n+1

**Seconda iterazione esterna:**
- Condizione: i < n? No (i = n+1)
- Il ciclo esterno termina!

**Totale operazioni:** $n$ (solo una passata del ciclo interno)

**Risposta: $O(n)$**

---

## Pattern 4: Ciclo Logaritmico

```cpp
for (int i = 1; i < n; i *= 2) {
    cout << i;
}
```

**Analisi:**
- Valori di i: $1, 2, 4, 8, ..., 2^k$
- Condizione: $2^k < n$
- Risolvendo: $k < \log_2 n$

**Risposta: $O(\log n)$**

**Varianti:**
```cpp
for (int i = n; i > 0; i /= 2) { ... }     // O(log n)
for (int i = 1; i < n; i *= 3) { ... }     // O(log n) (base 3)
for (int i = 2; i < n; i = i * i) { ... }  // O(log log n)
```

---

## Pattern 5: Ciclo Triangolare

```cpp
for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
        cout << "*";
    }
}
```

**Analisi:**
| i | Iterazioni j |
|---|--------------|
| 0 | 0 |
| 1 | 1 |
| 2 | 2 |
| ... | ... |
| n-1 | n-1 |

**Totale:** $0 + 1 + 2 + ... + (n-1) = \frac{n(n-1)}{2}$

**Risposta: $O(n^2)$**

---

## Pattern 6: Serie Geometrica

```cpp
for (int i = 1; i <= n; i *= 2) {
    for (int j = 0; j < i; j++) {
        k++;
    }
}
```

**Analisi:**
| i | Iterazioni j |
|---|--------------|
| 1 | 1 |
| 2 | 2 |
| 4 | 4 |
| ... | ... |
| n | n |

**Totale:** $1 + 2 + 4 + ... + n = 2n - 1$ (serie geometrica)

**Risposta: $O(n)$** - Non e $O(n \log n)$!

---

## Pattern 7: Logaritmo Annidato con Lineare

```cpp
for (int i = 1; i < n; i *= 2) {   // log n
    for (int j = 0; j < n; j++) {   // n
        cout << i + j;
    }
}
```

**Analisi:**
- Ciclo esterno: $\log n$ iterazioni
- Ciclo interno: $n$ iterazioni (indipendente!)
- Totale: $\log n \times n$

**Risposta: $O(n \log n)$**

---

## Pattern 8: Ricorsione Lineare

```cpp
void func(int n) {
    if (n <= 0) return;
    cout << n;
    func(n - 1);
}
```

**Analisi:**
- Chiamate: func(n), func(n-1), ..., func(1), func(0)
- Totale chiamate: $n + 1$
- Ogni chiamata: $O(1)$

**Risposta: $O(n)$**

---

## Pattern 9: Ricorsione Binaria

```cpp
void func(int n) {
    if (n <= 1) return;
    func(n / 2);
    func(n / 2);
    cout << n;
}
```

**Analisi con Master Theorem:**
$$T(n) = 2T(n/2) + O(1)$$

- $a = 2$, $b = 2$, $f(n) = O(1)$
- $\log_b a = \log_2 2 = 1$
- $f(n) = O(n^0)$, quindi $c = 0 < 1$
- Caso 1: $T(n) = O(n^{\log_b a}) = O(n)$

**Risposta: $O(n)$**

---

## Esercizio Tipo: Somme Prefisse

Calcolare la somma degli elementi fino a `i` per ogni posizione.

**Soluzione Naive ($O(n^2)$):**
```cpp
for (int target = 0; target < n; target++) {
    int sum = 0;
    for (int i = 0; i <= target; i++) {
        sum += arr[i];
    }
    cout << sum << endl;
}
```

**Perche e $O(n^2)$?**
- Per target=0: 1 somma
- Per target=1: 2 somme
- ...
- Per target=n-1: n somme
- Totale: $1 + 2 + ... + n = \frac{n(n+1)}{2} = O(n^2)$

**Soluzione Ottima ($O(n)$):**
```cpp
int sum = 0;
for (int i = 0; i < n; i++) {
    sum += arr[i];
    cout << sum << endl;
}
```

**Trucco:** Riutilizza il risultato parziale invece di ricalcolare!

---

## Tabella Riassuntiva

| Pattern | Esempio | Complessita |
|---------|---------|-------------|
| Ciclo semplice | `for(i=0; i<n; i++)` | $O(n)$ |
| Ciclo costante | `for(i=0; i<100; i++)` | $O(1)$ |
| Due cicli sequenziali | `for... for...` (non annidati) | $O(n)$ |
| Due cicli annidati indipendenti | `for i { for j }` | $O(n^2)$ |
| Ciclo triangolare | `for i { for j<i }` | $O(n^2)$ |
| Ciclo logaritmico | `for(i=1; i<n; i*=2)` | $O(\log n)$ |
| Log + lineare annidati | `for i*=2 { for j<n }` | $O(n \log n)$ |
| Serie geometrica | `for i*=2 { for j<i }` | $O(n)$ |
| Radice quadrata | `while(i*i < n)` | $O(\sqrt{n})$ |

---

## Errori Comuni da Evitare

### 1. Confondere costante con variabile
```cpp
for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) { ... }  // O(n*m), non O(n^2)!
}
```

### 2. Non notare modifiche agli indici
```cpp
for (int i = 0; i < n; i++) {
    i += 10;  // Ora e O(n/10) = O(n), ma il fattore cambia!
}
```

### 3. Confondere caso medio e peggiore
```cpp
// unordered_map
map.find(key);  // O(1) medio, O(n) peggiore
```

### 4. Dimenticare operazioni costose nelle STL
```cpp
vector<int> v;
for (int i = 0; i < n; i++) {
    v.insert(v.begin(), i);  // O(n) per ogni insert! Totale: O(n^2)
}
```

---

## Consigli Finali per l'Esame

1. **Leggi TUTTO il codice** prima di iniziare l'analisi

2. **Identifica le parti dominanti** - spesso il 90% del tempo e in un solo ciclo

3. **Attenzione alle chiamate a funzione** - potrebbero non essere $O(1)$

4. **Se non sei sicuro, CONTA** - esegui mentalmente per n=4 o n=8

5. **Scrivi i passaggi** - mostra il ragionamento, non solo la risposta

6. **Ricorda le formule delle somme:**
   - $\sum_{i=1}^{n} 1 = n$
   - $\sum_{i=1}^{n} i = \frac{n(n+1)}{2}$
   - $\sum_{i=0}^{k} 2^i = 2^{k+1} - 1$
   - $\sum_{i=1}^{n} \frac{1}{i} \approx \ln n$
