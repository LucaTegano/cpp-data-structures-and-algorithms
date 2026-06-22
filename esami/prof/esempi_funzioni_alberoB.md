# Esempi Code Snippet per `AlberoB`

Questo documento contiene esempi di utilizzo per le funzioni pubbliche definite nella classe template `AlberoB` (in `AlberoB.h`).
Si assume l'uso di `AlberoB<int>` per semplicità, ma la classe funziona con qualsiasi tipo `T`.

## Classe `AlberoB` (Albero Binario)

### 1. Costruttori
Creazione di un albero vuoto o con una radice.
```cpp
// 1. Costruttore di default: Albero vuoto
AlberoB<int> alberoVuoto;

// 2. Costruttore con valore: Albero con sola radice (valore 10)
AlberoB<int> albero(10);
```

### 2. Inserimento Figlio: `insFiglio(Direzione d, AlberoB AC)`
Inserisce un sottoalbero come figlio sinistro (`SIN`) o destro (`DES`).
```cpp
AlberoB<int> radice(10);
AlberoB<int> figlioSx(5);
AlberoB<int> figlioDx(20);

// Inserisce il nodo 5 come figlio SINISTRO di 10
radice.insFiglio(SIN, figlioSx); 

// Inserisce il nodo 20 come figlio DESTRO di 10
radice.insFiglio(DES, figlioDx);
```

### 3. Accesso ai Valori: `radice()`
Restituisce il valore contenuto nel nodo radice dell'albero (o sottoalbero) corrente.
```cpp
cout << "Valore radice: " << radice.radice() << endl; // Stampa: 10
```

### 4. Navigazione: `figlio(Direzione d)` e `padre()`
Permette di spostarsi nell'albero. Restituisce un oggetto `AlberoB` che rappresenta il sottoalbero.
```cpp
// Accesso al figlio sinistro
AlberoB<int> sx = radice.figlio(SIN);
cout << "Valore figlio sx: " << sx.radice() << endl; // Stampa: 5

// Accesso al figlio destro
if (!radice.figlio(DES).nullo()) {
    cout << "Valore figlio dx: " << radice.figlio(DES).radice() << endl; // Stampa: 20
}

// Risalita al padre (da un sottoalbero)
// Nota: 'sx' è l'oggetto estratto prima. Il padre di 'sx' puntava alla struttura originale.
// Attenzione: padre() restituisce un AlberoB puntando al nodo padre.
```

### 5. Verifica Stato: `nullo()` e `foglia()`
Controlla se l'albero è vuoto o se il nodo corrente è una foglia.
```cpp
if (alberoVuoto.nullo()) {
    cout << "L'albero è vuoto" << endl;
}

if (sx.foglia()) {
    cout << "Il nodo 5 è una foglia (non ha figli)" << endl;
}
```

### 6. Modifica Radice: `modRadice(const T& a)`
Cambia il valore informativo della radice corrente.
```cpp
radice.modRadice(99); 
// Ora la radice vale 99 invece di 10
```

### 7. Estrazione Figlio: `estraiFiglio(Direzione d)`
Rimuove un sottoalbero dall'albero padre e lo restituisce come albero indipendente.
```cpp
// Stacca il figlio destro (che era 20)
AlberoB<int> sottoAlberoStaccato = radice.estraiFiglio(DES);

// Ora 'radice' non ha più il figlio destro
if (radice.figlio(DES).nullo()) {
    cout << "Figlio destro rimosso" << endl;
}

// 'sottoAlberoStaccato' è un albero valido con radice 20
cout << "Radice albero staccato: " << sottoAlberoStaccato.radice() << endl;
```

### 8. Utility: `copia()` e `svuota()`
Copia profonda e cancellazione.
```cpp
// Crea una copia completa dell'albero 'radice'
AlberoB<int> copiaAlbero = radice.copia();

// Cancella tutto l'albero 'radice' liberando memoria
radice.svuota();
// Ora radice.nullo() è true
```
