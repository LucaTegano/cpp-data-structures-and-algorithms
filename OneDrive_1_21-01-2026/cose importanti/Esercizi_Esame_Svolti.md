# Esercizi d'Esame Svolti: Logica e Snippet Completi

Questo documento contiene simulazioni di esercizi d'esame "lunghi". Per ogni esercizio trovi: la **Traccia**, la **Strategia** (cosa fare) e lo **Snippet Completo**.

---

## Esercizio 1: Gestore Magazzino (Polimorfismo e Puntatori)

### 📝 Traccia
Si progetti un sistema per gestire un magazzino. 
1. Definire una classe base astratta `Prodotto` con attributi `codice` e `prezzoBase`.
2. Derivare `ProdottoAlimentare` (con `scadenza`) e `ProdottoElettronico` (con `anniGaranzia`).
3. Implementare un metodo virtuale `calcolaPrezzoFinale()`: gli alimentari hanno uno sconto del 20% se scadono entro 3 giorni, gli elettronici hanno un sovrapprezzo del 10% se la garanzia è > 2 anni.
4. Creare una classe `Magazzino` che gestisca un `vector<Prodotto*>` e implementi il calcolo del valore totale del magazzino e la deallocazione corretta.

### 💡 Strategia (Cosa fare)
- **Puntatori**: Usiamo `Prodotto*` per sfruttare il polimorfismo.
- **Virtual**: Il distruttore della base **deve** essere virtuale.
- **Rule of Three**: In `Magazzino` serve gestire bene la memoria (distruttore che cicla sul vector).

### 💻 Codice Completo
```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 1. CLASSE BASE ASTRATTA
class Prodotto {
protected:
    string codice;
    double prezzoBase;
public:
    Prodotto(string c, double p) : codice(c), prezzoBase(p) {}
    
    // Distruttore VIRTUAL fondamentale per deallocare i figli!
    virtual ~Prodotto() { cout << "Elimino Prodotto base\n"; }
    
    // Metodo pure virtual
    virtual double calcolaPrezzoFinale() const = 0;
    
    string getCodice() const { return codice; }
};

// 2. CLASSI DERIVATE
class ProdottoAlimentare : public Prodotto {
    int giorniAllaScadenza;
public:
    ProdottoAlimentare(string c, double p, int g) : Prodotto(c, p), giorniAllaScadenza(g) {}
    
    double calcolaPrezzoFinale() const override {
        if (giorniAllaScadenza <= 3) return prezzoBase * 0.8; // Sconto 20%
        return prezzoBase;
    }
    ~ProdottoAlimentare() { cout << "Elimino Alimentare\n"; }
};

class ProdottoElettronico : public Prodotto {
    int garanzia;
public:
    ProdottoElettronico(string c, double p, int gar) : Prodotto(c, p), garanzia(gar) {}
    
    double calcolaPrezzoFinale() const override {
        if (garanzia > 2) return prezzoBase * 1.1; // Sovrapprezzo 10%
        return prezzoBase;
    }
};

// 3. CLASSE GESTORE (MAGAZZINO)
class Magazzino {
private:
    vector<Prodotto*> inventario;
public:
    // Aggiunta polimorfica
    void aggiungi(Prodotto* p) { inventario.push_back(p); }

    double valoreTotale() const {
        double totale = 0;
        for (Prodotto* p : inventario) {
            totale += p->calcolaPrezzoFinale(); // Chiamata polimorfica
        }
        return totale;
    }

    // GESTIONE MEMORIA: Dealloca ogni singolo oggetto
    ~Magazzino() {
        for (Prodotto* p : inventario) {
            delete p; 
        }
        inventario.clear();
    }
};

int main() {
    Magazzino m;
    m.aggiungi(new ProdottoAlimentare("Mela1", 1.0, 2));   // Scontato
    m.aggiungi(new ProdottoElettronico("PC-X", 1000, 3)); // Maggiorato
    
    cout << "Valore magazzino: " << m.valoreTotale() << endl;
    return 0;
}
```

---

## Esercizio 2: Rotte Aeree (Mappa di Mappe)

### 📝 Traccia
Si vuole gestire un sistema di rotte aeree tra città.
1. La classe `SistemaVoli` deve memorizzare i prezzi dei voli tra coppie di città.
2. Usare una struttura che permetta di rispondere velocemente alla domanda: "Quanto costa andare da Roma a Milano?".
3. Implementare un metodo `aggiungiRotta(partenza, destinazione, prezzo)`.
4. Implementare `prezzoMinimo(città)` che restituisce il volo più economico in partenza da quella città e la sua destinazione.

### 💡 Strategia (Cosa fare)
- **Struttura**: `map<string, map<string, double>>`. 
  - Chiave 1: Città Partenza.
  - Chiave 2: Città Arrivo.
  - Valore: Prezzo.
- **Vantaggio**: Accesso istantaneo $O(\log N)$ a qualsiasi rotta specifica.

### 💻 Codice Completo
```cpp
#include <iostream>
#include <map>
#include <string>
#include <limits>

using namespace std;

class SistemaVoli {
private:
    // Partenza -> { Destinazione -> Prezzo }
    map<string, map<string, double>> rotte;

public:
    void aggiungiRotta(string da, string a, double prezzo) {
        // Se la rotta esiste già, aggiorna col prezzo minore
        if (rotte[da].count(a)) {
            rotte[da][a] = min(rotte[da][a], prezzo);
        } else {
            rotte[da][a] = prezzo;
        }
    }

    double getPrezzo(string da, string a) const {
        // Uso .at() e .count() per sicurezza (const-safety)
        if (rotte.count(da) && rotte.at(da).count(a)) {
            return rotte.at(da).at(a);
        }
        return -1; // Rotta inesistente
    }

    // Ritorna pair <Destinazione, Prezzo>
    pair<string, double> rottaPiuEconomica(string da) const {
        if (rotte.find(da) == rotte.end()) return {"", -1};

        string bestDest = "";
        double minPrezzo = numeric_limits<double>::max();

        // Itero sulla mappa interna (le destinazioni da 'da')
        for (const auto& [dest, prezzo] : rotte.at(da)) {
            if (prezzo < minPrezzo) {
                minPrezzo = prezzo;
                bestDest = dest;
            }
        }
        return {bestDest, minPrezzo};
    }
};

int main() {
    SistemaVoli sv;
    sv.aggiungiRotta("Roma", "Milano", 150.0);
    sv.aggiungiRotta("Roma", "Parigi", 80.0);
    sv.aggiungiRotta("Roma", "Londra", 120.0);

    auto [citta, prezzo] = sv.rottaPiuEconomica("Roma");
    cout << "Da Roma il volo piu' economico e' per " << citta << " a " << prezzo << " euro." << endl;

    return 0;
}
```

---

## Esercizio 3: Registro Sessioni (Pair + Set)

### 📝 Traccia
Si gestisca un server che logga gli accessi degli utenti.
1. Ogni accesso è identificato da `(ID_Utente, Timestamp)`.
2. Non possono esserci due log identici (stesso utente allo stesso secondo).
3. Implementare un metodo `logga(id, time)` e `puntiTotali(id)` sapendo che ogni accesso vale 10 punti.

### 💻 Codice Completo
```cpp
#include <iostream>
#include <set>
#include <map>

using namespace std;

class RegistroServer {
private:
    // pair<id, timestamp> garantisce l'unicità della coppia
    set<pair<int, long>> accessi;
    
    // Per velocizzare il calcolo dei punti uso una mappa d'appoggio
    map<int, int> puntiUtente;

public:
    void logga(int id, long timestamp) {
        // insert nel set ritorna un pair <iterator, bool>
        // il bool è true se l'elemento è stato inserito (non era duplicato)
        auto result = accessi.insert({id, timestamp});
        
        if (result.second) {
            puntiUtente[id] += 10;
            cout << "Log registrato per " << id << endl;
        } else {
            cout << "Errore: Log duplicato!" << endl;
        }
    }

    int getPunti(int id) const {
        if (puntiUtente.count(id)) return puntiUtente.at(id);
        return 0;
    }
};
```
