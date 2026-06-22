# Esempi Code Snippet per Gestore Veicoli e Coda Ereditaria

## 1. Gestore Veicoli (`GestoreVeicoli.h`)

Il `GestoreVeicoli` utilizza `std::vector` per memorizzare puntatori polimorfici alla classe base `Veicolo`.

### Gestione Memoria (Deep Copy)
Poiché la classe possiede risorse dinamiche (puntatori a veicoli), implementa la **Regola dei Tre** (in realtà qui Costruttore di Copia e Operatore di Assegnazione fanno Deep Copy).

```cpp
// Distruttore: svuota e dealloca
~GestoreVeicoli() {
    clear(); // Chiama delete su ogni puntatore
}

// Costruttore di Copia
GestoreVeicoli(const GestoreVeicoli& other) {
    for (Veicolo* v : other.veicoli)
        this->veicoli.push_back(v->clone()); 
        // clone() è un metodo virtuale (Pattern Prototype) essenziale qui!
        // Se facessimo new Veicolo(*v) avremmo slicing o errori di compilazione se Veicolo è astratto.
}
```

### Metodo `aggiungiVeicolo`
Controlla univocità della targa prima di inserire.
```cpp
void aggiungiVeicolo(Veicolo* v) {
    for (Veicolo* ptr : veicoli)
        if (ptr->getTarga() == v->getTarga()) {
            cout << "Errore: Targa duplicata";
            return;
        }
    veicoli.push_back(v);
}
```

---

## 2. Coda Ereditaria (`CodaEreditaria.h`)

Questa classe implementa una Coda ereditando privatamente da `std::vector`. 
**Nota Metodologica**: Ereditare da `std::vector` è generalmente sconsigliato (non ha distruttore virtuale), ma a fini didattici mostra come l'ereditarietà privata (`private`) serva per "implementare in termini di".

```cpp
class CodaEreditaria: private vector<Studente> { ... }
```
Ereditando privatamente, i metodi pubblici di vector (`push_back`, `at`, ecc.) diventano privati in `CodaEreditaria`. Esporremo solo ciò che vogliamo (`aggiungi`, `rimuovi`).

### Operazioni FIFO
```cpp
void aggiungi(const Studente& s) {
    this->push_back(s); // Usa metodo del padre (vector)
}

void rimuovi() {
    // Rimuovere dalla testa in un vector è inefficiente O(n)
    // erase(begin()) sposta tutti gli elementi. 
    if (!this->empty()) {
        this->erase(this->begin());
    }
}

Studente prossimo() const {
    if (!this->empty()) return this->front();
    throw runtime_error("Coda vuota");
}
```
L'override di `operator<<` permette di stampare la coda iterando come un vettore, dato che all'interno della classe (o nelle friend) abbiamo accesso alla parte privata (il vector padre).
