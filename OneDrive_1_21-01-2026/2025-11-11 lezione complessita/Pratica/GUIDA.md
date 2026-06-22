# Guida Pratica: Risolvere Esercizi di Complessita

Questa guida ti aiuta a risolvere gli esercizi nei file `comp1.pdf` e `comp2.pdf` con un approccio sistematico.

---

## Metodologia di Risoluzione

### Step 1: Identifica la Struttura del Codice
Leggi il codice e classifica i costrutti:
- Cicli `for`, `while`
- Chiamate ricorsive
- Operazioni su strutture dati

### Step 2: Conta le Iterazioni
Per ogni ciclo, determina:
- Valore iniziale dell'indice
- Condizione di terminazione
- Incremento/decremento

### Step 3: Applica le Regole
Usa le regole di somma e prodotto per combinare le complessita.

---

## Pattern Comuni e Soluzioni

### Pattern 1: Il "Finto" Quadratico

```cpp
void func(int n) {
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 100; j++) {  // <- COSTANTE!
            k++;
        }
    }
}
```

**Errore comune:** Pensare che sia $O(n^2)$

**Analisi corretta:**
- Ciclo esterno: $n$ iterazioni
- Ciclo interno: 100 iterazioni (sempre, indipendente da $n$)
- Totale: $n \times 100 = 100n$

**Risposta: $O(n)$**

**Regola:** Le costanti moltiplicative si ignorano!

---

### Pattern 2: While con Condizione Quadratica

```cpp
int i = 0;
while (i * i < n) {
    i++;
}
```

**Analisi:**
- Il ciclo termina quando $i^2 \geq n$
- Quindi $i \geq \sqrt{n}$
- Numero iterazioni: $\sqrt{n}$

**Risposta: $O(\sqrt{n})$**

**Varianti:**
```cpp
// Variante 1: i * i * i < n
while (i * i * i < n) { i++; }  // O(n^(1/3))

// Variante 2: 2^i < n
while ((1 << i) < n) { i++; }   // O(log n)
```

---

### Pattern 3: Cicli Triangolari

```cpp
for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
        cout << "*";
    }
}
```

**Analisi:**
| i | Iterazioni ciclo interno |
|---|--------------------------|
| 0 | 0 |
| 1 | 1 |
| 2 | 2 |
| ... | ... |
| n-1 | n-1 |

**Totale:**
$$0 + 1 + 2 + ... + (n-1) = \sum_{i=0}^{n-1} i = \frac{n(n-1)}{2}$$

**Risposta: $O(n^2)$**

---

### Pattern 4: Modifica dell'Indice Esterno

```cpp
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        k++;
        i++;  // ATTENZIONE!
    }
}
```

**Analisi passo-passo:**

**Prima iterazione (i=0):**
- `j` va da 0 a n-1 (n iterazioni)
- Ogni iterazione incrementa `i` di 1
- Alla fine del ciclo interno: `i = n`
- Ma poi il ciclo esterno fa `i++`, quindi `i = n+1`

**Seconda iterazione:**
- `i = n+1 >= n`, quindi il ciclo esterno termina!

**Totale operazioni:** $n$ (solo una passata del ciclo interno)

**Risposta: $O(n)$**

---

### Pattern 5: Cicli Logaritmici

```cpp
// Tipo 1: Moltiplicazione
for (int i = 1; i < n; i *= 2) {
    cout << i;
}
```

**Valori di i:** $1, 2, 4, 8, 16, ..., 2^k$ dove $2^k < n$

**Iterazioni:** $k = \lfloor \log_2 n \rfloor$

**Risposta: $O(\log n)$**

```cpp
// Tipo 2: Divisione
for (int i = n; i > 0; i /= 2) {
    cout << i;
}
```

**Risposta: $O(\log n)$**

```cpp
// Tipo 3: Annidato (IMPORTANTE!)
for (int i = 1; i < n; i *= 2) {      // log(n)
    for (int j = 0; j < n; j++) {      // n
        cout << i + j;
    }
}
```

**Risposta: $O(n \log n)$**

---

### Pattern 6: Somme Interne Variabili

```cpp
int s = 0;
for (int i = 1; i <= n; i *= 2) {
    for (int j = 0; j < i; j++) {
        s++;
    }
}
```

**Analisi:**
| i | Iterazioni j |
|---|--------------|
| 1 | 1 |
| 2 | 2 |
| 4 | 4 |
| 8 | 8 |
| ... | ... |
| n | n |

**Totale:**
$$1 + 2 + 4 + 8 + ... + n = 2n - 1$$

(Serie geometrica con ragione 2)

**Risposta: $O(n)$**

---

## Esercizi Tipo Esame con Soluzioni

### Esercizio 1
```cpp
void mystery(int n) {
    for (int i = n; i > 0; i--) {
        for (int j = 1; j < n; j *= 2) {
            cout << i + j;
        }
    }
}
```

**Soluzione:**
- Ciclo esterno: $n$ iterazioni (da n a 1)
- Ciclo interno: $\log n$ iterazioni (j raddoppia)
- Totale: $n \times \log n$

**Risposta: $O(n \log n)$**

---

### Esercizio 2
```cpp
void algo(int n) {
    int i = 1, s = 1;
    while (s <= n) {
        i++;
        s = s + i;
    }
}
```

**Analisi:**
- `s` assume i valori: $1, 1+2, 1+2+3, ..., \frac{k(k+1)}{2}$
- Il ciclo termina quando $\frac{k(k+1)}{2} > n$
- Approssimativamente: $k^2 \approx 2n$, quindi $k \approx \sqrt{2n}$

**Risposta: $O(\sqrt{n})$**

---

### Esercizio 3
```cpp
void ricorsiva(int n) {
    if (n <= 1) return;
    cout << n;
    ricorsiva(n / 2);
    ricorsiva(n / 2);
}
```

**Analisi con Master Theorem:**
$$T(n) = 2T(n/2) + O(1)$$

- $a = 2$, $b = 2$, $f(n) = O(1) = O(n^0)$
- $\log_b a = \log_2 2 = 1$
- $c = 0 < 1 = \log_b a$
- Caso 1: $T(n) = O(n^{\log_b a}) = O(n^1)$

**Risposta: $O(n)$**

---

### Esercizio 4
```cpp
void func(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            for (int k = j; k < n; k++) {
                cout << "*";
            }
        }
    }
}
```

**Analisi:**
Questo e un triplo ciclo dipendente. Conta il numero di asterischi stampati.

Formula esatta: $\binom{n+2}{3} = \frac{n(n+1)(n+2)}{6}$

**Risposta: $O(n^3)$**

---

## Tabella Riassuntiva

| Pattern | Esempio | Complessita |
|---------|---------|-------------|
| Ciclo semplice | `for(i=0; i<n; i++)` | $O(n)$ |
| Ciclo con costante | `for(i=0; i<100; i++)` | $O(1)$ |
| Due cicli annidati indipendenti | `for i: for j` | $O(n^2)$ |
| Ciclo triangolare | `for i: for j<i` | $O(n^2)$ |
| Ciclo logaritmico | `for(i=1; i<n; i*=2)` | $O(\log n)$ |
| Lineare + logaritmico | `for i: for j*=2` | $O(n \log n)$ |
| Radice quadrata | `while(i*i < n)` | $O(\sqrt{n})$ |

---

## Trucchi per l'Esame

1. **Leggi attentamente i limiti dei cicli** - Il diavolo sta nei dettagli!

2. **Attenzione alle variabili modificate dentro i cicli** - Possono cambiare drasticamente la complessita

3. **Identifica se il limite e costante o variabile** - `j < 100` e O(1), `j < m` e O(m)

4. **Per le somme:**
   - Aritmetica: $1 + 2 + ... + n = \frac{n(n+1)}{2} = O(n^2)$
   - Geometrica: $1 + 2 + 4 + ... + n = 2n - 1 = O(n)$

5. **Per la ricorsione:** Disegna l'albero delle chiamate se il Master Theorem non si applica

6. **Se in dubbio, conta!** - Simula mentalmente l'esecuzione per valori piccoli
