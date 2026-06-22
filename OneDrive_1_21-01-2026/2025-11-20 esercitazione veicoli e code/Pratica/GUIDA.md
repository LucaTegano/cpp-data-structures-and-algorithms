# Analisi Esercizi: Veicoli, Code Ereditarie, Computers

## Esercizio 1: Concessionaria (Polimorfismo & Clone)
La parte cruciale di questo esercizio è il metodo `clone()`.
In `Veicolo.h`:
```cpp
virtual Veicolo* clone() const = 0; // Virtuale Puro
```
In `Automobile.h`:
```cpp
virtual Veicolo* clone() const override {
    return new Automobile(*this); // Chiama il costruttore di copia
}
```
Senza questo meccanismo, il `GestoreVeicoli` non potrebbe fare copie profonde corrette (avrebbe il problema dello Slicing o non saprebbe che tipo concreto istanziare).

## Esercizio 2: Coda Ereditaria (Incapsulamento)
L'esercizio chiede di implementare una Coda usando l'ereditarietà privata da `vector`.
**Perché privata?**
Se fosse pubblica (`public vector<Studente>`), un utente potrebbe fare:
`coda.insert(coda.begin() + 5, s);`
Rompendo la logica FIFO della coda! Con `private`, nascondiamo l'interfaccia del vettore e mostriamo solo `aggiungi` (enqueue) e `rimuovi` (dequeue).

## Esercizio 3: Gestore Computers
Simile al gestore veicoli, ma attenzione alla gestione della memoria.
Verifica se `GestoreComputers` ha:
1.  Distruttore che fa `delete` sui puntatori.
2.  Metodi di ricerca che ritornano puntatori o riferimenti (non copie, per non perdere il polimorfismo).
