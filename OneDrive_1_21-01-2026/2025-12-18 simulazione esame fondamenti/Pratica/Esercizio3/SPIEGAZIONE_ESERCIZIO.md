# Spiegazione Soluzione Esercizio 3 (Dicembre)

Questo documento analizza nel dettaglio la funzione `bool f(const Grafo& g)` implementata in `esercizio3.cpp`. L'esercizio richiede di verificare tre specifiche condizioni strutturali su un grafo orientato.

## Obiettivo della Funzione

La funzione deve restituire `true` se e solo se il grafo `g` soddisfa contemporaneamente:
1.  **Condizione Autoarchi**: Il grafo non deve contenere cappi (autoarchi), ovvero archi del tipo $(i, i)$.
2.  **Condizione Parità**: Il numero totale di archi deve essere pari.
3.  **Condizione Gradi**: Il grado uscente di *ogni* nodo deve essere minore o uguale al numero di nodi che hanno al più un arco entrante.

---

## Analisi del Codice

### 1. Strutture Dati di Supporto
Per evitare di scorrere la matrice più volte del necessario, l'algoritmo utilizza vettori di supporto per calcolare i gradi dei nodi in un unico passaggio.

```cpp
vector<int> grado_uscente(g.n()); // Memorizza il grado uscente per ogni nodo i
vector<int> grado_entrante(g.n()); // Memorizza il grado entrante per ogni nodo j
int count_archi = 0;               // Contatore manuale degli archi totali
```

### 2. Scansione della Matrice (Core Loop)
L'algoritmo itera su tutta la matrice di adiacenza $N \times N$.

```cpp
for (int i = 0; i < g.n(); ++i) {
    for (int j = 0; j < g.n(); ++j) {
        if (g(i, j)) {  // Se esiste l'arco (i -> j)
            
            // VERIFICA CONDIZIONE 1 (Autoarchi)
            if (i == j) return false; 
            
            // Aggiornamento statistiche per la Condizione 3
            grado_entrante[j]++;    
            grado_uscente[i]++;     
            
            // Conteggio per la Condizione 2
            count_archi++;          
        }
    }
}
```
**Complessità di questa fase**: $O(n^2)$, dove $n$ è il numero di nodi.

### 3. Verifica Condizione Parità Archi
Dopo aver contato tutti gli archi, si verifica se il numero è pari.

```cpp
if (count_archi % 2 != 0)
    return false;
```
*Nota*: Anche se la classe `Grafo` possiede un metodo `.m()`, ricalcolare il numero di archi durante il loop è una scelta sicura che non aumenta la complessità asintotica dell'algoritmo.

### 4. Verifica Condizione sui Gradi
Questa è la parte più complessa logica dell'esercizio:
> *"il grado uscente di ogni nodo di g è minore del numero di nodi di g che hanno al più un arco entrante"*

L'algoritmo procede in due sotto-step:

#### Step A: Calcolo della Soglia
Si conta quanti nodi hanno un `grado_entrante` $\le 1$.

```cpp
int count_max_uno_entrante = 0;
for (int i = 0; i < g.n(); ++i)
    if (grado_entrante[i] <= 1)
        count_max_uno_entrante++;
```

#### Step B: Verifica per Ogni Nodo
Si controlla che il `grado_uscente` di ogni nodo non superi la soglia calcolata (`count_max_uno_entrante`).
L'esercizio richiede "minore" nel testo, ma il codice implementa un check inverso: se trova un nodo con grado *maggiore* della soglia (`>`), ritorna `false`. Questo implica che la condizione valida è $\le$.
*(Nota: Verificare sempre se il testo d'esame richiede strettamente minore `<` o minore uguale `\le`. In questo codice è implementato come `\le`)*.

```cpp
for (int i = 0; i < g.n(); ++i)
    if (grado_uscente[i] > count_max_uno_entrante)
        return false;
```

---

## Complessità Totale

- **Temporale**: L'operazione dominante è la doppia scansione dei cicli `for` annidati per leggere la matrice di adiacenza.
    - Scansione matrice: $O(n^2)$
    - Verifiche finali lineari: $O(n)$
    - **Totale**: $O(n^2)$
- **Spaziale**: $O(n)$ per i vettori `grado_uscente` e `grado_entrante`.

## Esempio di Utilizzo

```cpp
Grafo g(3);
g(0, 1, true);
g(1, 2, true);

// Esecuzione funzione
bool risultato = f(g);

if (risultato) {
    cout << "Il grafo soddisfa tutte le condizioni." << endl;
} else {
    cout << "Il grafo NON soddisfa le condizioni." << endl;
}
```
