# Lezione: Simulazione Esame - Gestione Debiti, Alberi e Cicli Hamiltoniani

## Indice
1. [Introduzione](#1-introduzione)
2. [Esercizio 2: Sistema Gestione Debiti (ADT)](#2-esercizio-2-sistema-gestione-debiti-adt)
3. [Esercizio 3: Algoritmo "Spremi" su Alberi Binari](#3-esercizio-3-algoritmo-spremi-su-alberi-binari)
4. [Esercizio 4: Ciclo Hamiltoniano (Backtracking)](#4-esercizio-4-ciclo-hamiltoniano-backtracking)
5. [Considerazioni Finali e Complessità](#5-considerazioni-finali-e-complessità)

---

## 1. Introduzione
Questa cartella contiene una simulazione d'esame completa. Gli esercizi affrontano problematiche reali tradotte in strutture dati classiche:
- **Esercizio 2**: Gestione di transazioni finanziarie (Grafi pesati / Matrici).
- **Esercizio 3**: Trasformazione strutturale di alberi binari.
- **Esercizio 4**: Problema di ottimizzazione combinatoria su grafi.

---

## 2. Esercizio 2: Sistema Gestione Debiti (ADT)

### 2.1 Analisi del Problema
Si vuole implementare una classe `GestioneDebiti` per tracciare i debiti tra un gruppo di amici.
- `anticipa(x, y, k)`: l'amico $x$ paga $k$ per l'amico $y$. Se $y$ è "*", la spesa è divisa tra tutti.
- `saldo(x, y)`: restituisce quanto $x$ deve effettivamente a $y$ (netto).
- `paga(x, y, k)`: l'amico $x$ restituisce $k$ a $y$.

### 2.2 Rappresentazione Interna
Per gestire efficientemente i dati, usiamo una combinazione di due strutture:
1. **Mappa Nomi → ID**: `unordered_map<string, unsigned>`. Associa ogni nome a un numero intero univoco da $0$ a $N-1$.
2. **Matrice di Adiacenza Pesata**: `vector<vector<float>>`. La cella `contiCompagnia[i][j]` memorizza il debito totale accumulato dal debitore $i$ verso il creditore $j$.

### 2.3 Logica del Saldo Netto
Se $X$ deve $10$ a $Y$, e $Y$ deve $4$ a $X$, il saldo netto di $X$ verso $Y$ è $6$.
```cpp
float saldo = debito[X][Y] - debito[Y][X];
return saldo > 0 ? saldo : 0;
```

---

## 3. Esercizio 3: Algoritmo "Spremi" su Alberi Binari

### 3.1 Definizione dell'Operazione
L'operazione `spremi` trasforma un albero binario "spingendo" i valori dei nodi interni verso le foglie:
- Un nodo interno $V$ somma il suo valore a quello ricevuto dal padre.
- Il totale viene diviso equamente tra i due figli.
- Il nodo $V$ diventa $0$.
- Le foglie accumulano tutto e mantengono il risultato.
- Se un figlio non esiste, la sua quota viene "persa" e raccolta in un accumulatore globale.

### 3.2 Implementazione Ricorsiva
La funzione `recursive_spremi` utilizza un pattern di **discesa con accumulatore**:
- `c_value`: valore che scende dal padre.
- `quota`: variabile passata per riferimento per raccogliere i valori che "escono" dai rami nulli.

```cpp
float cc_value = (alberoB.radice() + c_value) / 2; // Quota per i figli
```

---

## 4. Esercizio 4: Ciclo Hamiltoniano (Backtracking)

### 4.1 Definizione
Trovare un cammino che visiti ogni nodo del grafo esattamente una volta e torni al punto di partenza. È un problema **NP-completo**, risolvibile con backtracking.

### 4.2 Pattern Backtracking
L'algoritmo prova a costruire il ciclo aggiungendo un nodo alla volta:
1. **Scelta**: Un nodo adiacente all'ultimo inserito.
2. **Vincolo**: Il nodo non deve essere già presente nel cammino corrente (`visitati`).
3. **Condizione di Chiusura**:
   - Lunghezza cammino == Numero totale nodi.
   - Esiste un arco dall'ultimo nodo al primo.

```cpp
bool isComplete(Soluzione &sol) {
    return sol.ciclo.size() == sol.g.n() && 
           sol.g(sol.ciclo.back(), sol.ciclo.front());
}
```

---

## 5. Considerazioni Finali e Complessità

### 5.1 Tabella Complessità
| Operazione | Complessità Temporale | Note |
|------------|-----------------------|------|
| `GestioneDebiti::anticipa` | $O(1)$ o $O(N)$ | $O(N)$ se per tutto il gruppo |
| `GestioneDebiti::saldo` | $O(1)$ | Accesso diretto alla matrice |
| `spremi` (Albero) | $O(N)$ | Visita completa di ogni nodo |
| `Ciclo Hamiltoniano` | $O(N!)$ | Esplosione combinatoria |

### 5.2 Best Practices evidenziate
- **Utilizzo di `at()`**: Nelle mappe `const`, usare `.at()` invece di `[]` per evitare inserimenti accidentali.
- **Riferimenti**: Passare strutture grandi (`vector`, `AlberoB`) per riferimento (`&`) o riferimento costante (`const &`) per evitare copie inutili.
- **Inizializzazione Matrici**: `vector<vector<float>>(N, vector<float>(N, 0))` è il modo standard per allocare matrici dinamiche.
