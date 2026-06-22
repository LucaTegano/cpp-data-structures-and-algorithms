# Spiegazione di `Grafo.h` ed `ese.cpp`

Questo documento fornisce una spiegazione dettagliata delle classi e funzioni definite nei file `Grafo.h` ed `ese.cpp`.

## `Grafo.h`

Il file definisce la classe `Grafo`, che rappresenta un **grafo orientato** (dove l'arco $(i, j)$ è diverso dall'arco $(j, i)$).

### Struttura Dati
Il grafo viene rappresentato tramite una **Matrice di Adiacenza**:
-   `std::vector<boolVec> archi;` dove `boolVec` è un `std::vector<bool>`.
-   `archi[i][j] == true` indica che esiste un arco che va dal nodo `i` al nodo `j`.
-   `vn`: numero di nodi del grafo.
-   `vm`: numero di archi correnti nel grafo.

### Metodi Principali

1.  **Costruttore `Grafo(unsigned n)`**
    -   Inizializza un grafo con `n` nodi e 0 archi.
    -   La matrice di adiacenza viene dimensionata a $n \times n$ e inizializzata interamente a `false`.
    -   Complessità: $O(n^2)$ (per l'inizializzazione della matrice).

2.  **Modifica Archi `operator()(unsigned i, unsigned j, bool b)`**
    -   Inserisce o rimuove un arco tra `i` e `j`.
    -   Se `b` è `true`, cerca di inserire l'arco. Se `b` è `false`, cerca di rimuoverlo.
    -   Aggiorna il contatore degli archi `vm` solo se lo stato dell'arco cambia effettivamente.
    -   Complessità: $O(1)$.

3.  **Lettura Archi `operator()(unsigned i, unsigned j) const`**
    -   Restituisce `true` se esiste l'arco $(i, j)$, altrimenti `false`.
    -   Complessità: $O(1)$.

4.  **Svuota `svuota()`**
    -   Rimuove tutti gli archi settando la matrice a `false`.
    -   Complessità: $O(n^2)$.

5.  **Getters `n()` e `m()`**
    -   Restituiscono rispettivamente il numero di nodi e di archi.

## `ese.cpp`

Il file contiene la soluzione a un esercizio che richiede la verifica di tre condizioni su un oggetto `Grafo`.

### Funzione `bool f(const Grafo& g)`

La funzione prende in input un grafo costante `g` e restituisce `true` se e solo se tutte le seguenti condizioni sono soddisfatte:

#### 1. Verifica assenza di autoarchi (Condizione 3 nel codice)
-   Durante l'iterazione sulla matrice di adiacenza, controlla se `i == j` e `g(i, j)` è vero.
-   Se trova un autoarco (un arco che collega un nodo a se stesso), restituisce immediatamente `false`.

#### 2. Numero totale di archi pari (Condizione 2 nel codice)
-   Conta il numero totale di archi (`count_archi`) scorrendo l'intera matrice.
-   Alla fine del conteggio, verifica se `count_archi % 2 != 0`. Se dispari, restituisce `false`.
-   *Nota: Sebbene la classe Grafo mantenga internamente un contatore `vm`, l'esercizio ricalcola il conteggio manualmente scorrendo la matrice.*

#### 3. Condizione sui gradi (Condizione 1 nel codice)
Questa è la condizione più articolata. Richiede che:
> Il grado uscente di **ogni** nodo di $g$ sia minore o uguale (in base all'implementazione) del numero di nodi di $g$ che hanno *al più* un arco entrante.

**Logica implementativa:**
1.  **Calcolo dei gradi:** Mentre itera sulla matrice per contare gli archi, calcola anche:
    -   `grado_uscente`: Quanti archi escono da ogni nodo `i`.
    -   `grado_entrante`: Quanti archi entrano in ogni nodo `j`.
2.  **Conteggio soglia (`count_max_uno_entrante`):** Conta quanti nodi hanno `grado_entrante <= 1`.
3.  **Verifica finale:** Itera su tutti i nodi e controlla se il loro `grado_uscente` supera la soglia calcolata.
    -   Check nel codice: `if (grado_uscente[i] > count_max_uno_entrante) return false;`
    -   Questo implica che per restituire `true`, deve valere: `grado_uscente[i] <= count_max_uno_entrante`.

### Complessità Totale
-   L'algoritmo itera su tutta la matrice di adiacenza $n \times n$.
-   **Complessità Temporale:** $O(n^2)$.
-   **Complessità Spaziale:** $O(n)$ per memorizzare i vettori dei gradi uscenti ed entranti.
