# Spiegazione di `AlberoB.h` ed `ese3alberoB.cpp`

Questo documento fornisce una spiegazione dettagliata della classe template `AlberoB` e dell'esercizio svolto in `ese3alberoB.cpp`.

## `AlberoB.h`

Il file definisce la classe template `AlberoB`, che rappresenta un **Albero Binario** implementato tramite puntatori (struttura collegata).

### Struttura Dati
L'albero è costruito utilizzando nodi di tipo `SNodo<T>`:
-   `T vinfo`: il valore informativo contenuto nel nodo.
-   `SNodo *ppadre`: puntatore al nodo padre (utile per risalire la struttura).
-   `SNodo *pfiglio[2]`: array di due puntatori ai figli, indicizzati tramite l'enum `Direzione`:
    -   `SIN` (0): Figlio Sinistro.
    -   `DES` (1): Figlio Destro.
-   La classe `AlberoB` mantiene un puntatore `SNodo<T>* pradice` alla radice dell'albero.

### Metodi Principali

1.  **Costruttori**
    -   `AlberoB()`: Crea un albero vuoto (radice `0` o `NULL`).
    -   `AlberoB(const T& a)`: Crea un albero con un solo nodo radice contenente il valore `a`.

2.  **Gestione Figli**
    -   `insFiglio(Direzione d, AlberoB AC)`: Inserisce l'albero `AC` come figlio `d` (SIN o DES) della radice corrente. Richiede che l'albero corrente non sia nullo e che la posizione `d` sia libera. Collega correttamente i puntatori padre/figlio.
    -   `estraiFiglio(Direzione d)`: Stacca il sottraalbero figlio nella direzione `d` e lo restituisce come un nuovo oggetto `AlberoB`. Rimuove il collegamento con il padre.

3.  **Accesso e Modifica**
    -   `radice() const`: Restituisce il valore informativo della radice. Richiede che l'albero non sia nullo.
    -   `modRadice(const T& a)`: Modifica il valore informativo della radice.
    -   `figlio(Direzione d) const`: Restituisce un oggetto `AlberoB` che rappresenta il sottoalbero sinistro o destro. *Nota: non crea una copia profonda, ma condivide la struttura dei nodi (attenzione alla gestione della memoria se non si usa `copia()`).*
    -   `padre() const`: Restituisce un oggetto `AlberoB` che ha come radice il padre del nodo corrente.

4.  **Utility**
    -   `bool nullo() const`: Restituisce `true` se l'albero è vuoto.
    -   `bool foglia() const`: Restituisce `true` se il nodo è una foglia (non ha figli sinistro né destro).
    -   `copia() const`: Crea e restituisce una **copia profonda** (deep copy) ricorsiva dell'intero albero.
    -   `svuota()`: Cancella tutti i nodi dell'albero liberando la memoria e setta la radice a 0.
    -   `annulla()`: Setta la radice a 0 senza liberare memoria (utile se il sottoalbero è stato spostato o copiato altrove per evitare *double free* involontari, ma da usare con cautela).

## `ese3alberoB.cpp`

Il file contiene un esercizio che manipola un albero binario di `float`. L'obiettivo sembra essere una trasformazione dell'albero ("spremitura") che calcola nuovi valori e accumula una "quota" dai nodi mancanti o nulli.

### Funzione `float spremi(AlberoB<float>& alberoB)`
Funzione wrapper che:
1.  Inizializza una variabile `quota` a 0.
2.  Chiama la funzione ricorsiva `recursive_spremi` passando l'albero, un valore iniziale `0` (interpretabile come un valore "ereditato" o accumulatore di contesto) e la referenza a `quota`.
3.  Stampa il nuovo albero generato.
4.  Restituisce il valore finale di `quota`.

### Funzione `AlberoB<float> recursive_spremi(...)`
La firma è: `AlberoB<float> recursive_spremi(const AlberoB<float>& alberoB, float c_value, float& quota)`

**Logica:**
1.  **Caso Base (Albero Nullo):**
    -   Se l'albero corrente è nullo, aggiunge `c_value` alla variabile `quota`.
    -   Restituisce un albero vuoto.
    -   *Interpretazione:* Se un ramo termina, il valore "pendente" `c_value` viene scaricato nella `quota` globale.

2.  **Caso Base (Foglia):**
    -   Se il nodo corrente è una foglia, restituisce un nuovo albero (nodo singolo) contenente la somma del valore attuale del nodo (`alberoB.radice()`) e di `c_value`.
    -   *Interpretazione:* Le foglie assorbono il valore accumulato.

3.  **Passo Ricorsivo (Nodo Interno):**
    -   Calcola un nuovo valore da propagare ai figli: `cc_value = (alberoB.radice() + c_value) / 2`.
    -   Crea un nuovo nodo radice (inizializzato a 0 nel codice, ma poi usato come contenitore strutturale). *Nota: Nel codice originale `AlberoB<float> toReturn=AlberoB<float>(0);` crea una radice con valore 0. I figli vengono attaccati a questa radice.*
    -   Chiama ricorsivamente la funzione sui figli sinistro e destro passando `cc_value`.
    -   I sottoalberi risultanti vengono attaccati al nuovo nodo `toReturn`.
    -   Restituisce il nuovo sottoalbero costruito.

**In sintesi:** La funzione trasforma l'albero originale in uno nuovo dove:
-   Le foglie hanno valore = valore_originale + valore_ereditato.
-   I rami nulli contribuiscono ad accrescere la `quota` con il valore ereditato.
-   I nodi interni propagano ai figli la media tra il loro valore e quello ereditato.

### Funzione `void stampa(...)`
Stampa l'albero in forma testuale ruotata (la radice è a sinistra, i figli verso destra).
-   Utilizza una visita **Simmetrica Inversa** (Des -> Radice -> Sin) per visualizzare l'albero correttamente ruotato di 90 gradi in senso antiorario (il figlio destro è in alto, il sinistro in basso).
