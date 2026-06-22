/*
ESEMPIO DI ESAME: Polimorfismo (Polymorphism) in C++

CONCETTI CHIAVE ILLUSTRATI:
1. Puntatori alla classe base che puntano ad oggetti della classe derivata.
2. Funzioni virtuali (virtual) e Dynamic Binding (collegamento dinamico a runtime).
3. Classi Astratte e Funzioni Virtuali Pure (interfacce).
4. Operatore dynamic_cast per l'identificazione del tipo a runtime (RTTI - Run-Time Type Information).
5. Distruttore Virtuale per evitare Memory Leak.
*/

#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>

using namespace std;

// 1. CLASSE BASE ASTRATTA (Interfaccia)
// Una classe è astratta se ha almeno una funzione virtuale pura (virtual ... = 0).
// Non è possibile istanziare direttamente un oggetto di questa classe.
class Prodotto {
protected:
    string descrizione;
    double prezzoBase;

public:
    Prodotto(string desc, double prezzo) : descrizione(desc), prezzoBase(prezzo) {}

    // Distruttore Virtuale:
    // Se non fosse virtuale, facendo "delete" su un puntatore Prodotto* che punta a un ProdottoAlimentare,
    // verrebbe chiamato solo il distruttore di Prodotto, lasciando attiva e non deallocata la memoria specifica
    // del ProdottoAlimentare (causando memory leak).
    virtual ~Prodotto() {
        cout << "[Distruttore Base] Deallocazione Prodotto: " << descrizione << endl;
    }

    string getDescrizione() const { return descrizione; }
    double getPrezzoBase() const { return prezzoBase; }

    // Funzione Virtuale Pura:
    // Forza le sottoclassi a implementare questo metodo. 
    // Rende la classe Prodotto una classe astratta.
    virtual double calcolaPrezzoFinale() const = 0; 
};


// 2. CLASSE DERIVATA 1: ProdottoAlimentare
class ProdottoAlimentare : public Prodotto {
private:
    int giorniAllaScadenza;

public:
    ProdottoAlimentare(string desc, double prezzo, int giorniScadenza)
        : Prodotto(desc, prezzo), giorniAllaScadenza(giorniScadenza) {}

    ~ProdottoAlimentare() override {
        cout << "[Distruttore Derivato] Deallocazione specifica ProdottoAlimentare." << endl;
    }

    int getGiorniAllaScadenza() const { return giorniAllaScadenza; }

    // Implementazione del metodo virtuale puro
    double calcolaPrezzoFinale() const override {
        if (giorniAllaScadenza <= 3) {
            return prezzoBase * 0.5; // Sconto 50% vicino alla scadenza
        }
        return prezzoBase * 0.9;     // Sconto standard 10%
    }
};


// 3. CLASSE DERIVATA 2: ProdottoElettronico
class ProdottoElettronico : public Prodotto {
private:
    int anniGaranzia;

public:
    ProdottoElettronico(string desc, double prezzo, int garanzia)
        : Prodotto(desc, prezzo), anniGaranzia(garanzia) {}

    ~ProdottoElettronico() override {
        cout << "[Distruttore Derivato] Deallocazione specifica ProdottoElettronico." << endl;
    }

    int getAnniGaranzia() const { return anniGaranzia; }

    // Implementazione del metodo virtuale puro
    double calcolaPrezzoFinale() const override {
        if (anniGaranzia > 2) {
            return prezzoBase * 1.05; // 5% in più per garanzia estesa
        }
        return prezzoBase;
    }
};


// 4. CLASSE CONTENITORE: Carrello (gestisce il polimorfismo)
class Carrello {
private:
    // Collezione di puntatori alla classe base.
    // Questo permette di inserire nella stessa struttura dati sia ProdottoAlimentare che ProdottoElettronico!
    vector<Prodotto*> elementi;

public:
    // Distruttore di Carrello: si occupa di liberare la memoria dinamica
    ~Carrello() {
        cout << "--- Svuotamento Carrello (Deallocazione polimorfica) ---" << endl;
        for (Prodotto* p : elementi) {
            // Grazie al distruttore virtuale nella classe base Prodotto, C++ sa quale distruttore specifico chiamare
            // a seconda del tipo reale dell'oggetto a runtime!
            delete p; 
        }
        elementi.clear();
    }

    void aggiungiProdotto(Prodotto* p) {
        elementi.push_back(p);
    }

    // Calcola il totale polimorfico del carrello
    double calcolaTotaleCarrello() const {
        double totale = 0.0;
        for (const Prodotto* p : elementi) {
            // POLIMORFISMO IN AZIONE:
            // C++ risolve a runtime quale implementazione di 'calcolaPrezzoFinale()' chiamare
            // basandosi sulla vtable (tabella dei metodi virtuali) dell'oggetto reale.
            totale += p->calcolaPrezzoFinale();
        }
        return totale;
    }

    // Esempio d'uso di dynamic_cast (RTTI)
    // Conta quanti prodotti alimentari sono prossimi alla scadenza (scadenza <= 3 giorni)
    int contaAlimentariInScadenza() const {
        int contatore = 0;
        for (Prodotto* p : elementi) {
            // dynamic_cast tenta di convertire il puntatore Prodotto* in ProdottoAlimentare*.
            // - Se l'oggetto puntato è EFFETTIVAMENTE un ProdottoAlimentare (o sua sottoclasse), il cast riesce e restituisce il puntatore convertito.
            // - Se l'oggetto è di un altro tipo (es. ProdottoElettronico), il cast fallisce e restituisce nullptr.
            // NOTA: dynamic_cast funziona solo su classi polimorfiche (cioè con almeno un metodo virtuale).
            ProdottoAlimentare* alim = dynamic_cast<ProdottoAlimentare*>(p);
            
            if (alim != nullptr) {
                // Ora possiamo accedere ai metodi specifici di ProdottoAlimentare che non sono presenti in Prodotto!
                if (alim->getGiorniAllaScadenza() <= 3) {
                    contatore++;
                }
            }
        }
        return contatore;
    }

    void stampaDettagliCarrello() const {
        cout << "--- Elementi nel Carrello ---" << endl;
        for (const Prodotto* p : elementi) {
            cout << "- " << p->getDescrizione() << " | Prezzo Base: " << p->getPrezzoBase() 
                 << " EUR | Prezzo Finale: " << p->calcolaPrezzoFinale() << " EUR";
            
            // Usiamo dynamic_cast anche per stampare attributi specifici
            const ProdottoAlimentare* alim = dynamic_cast<const ProdottoAlimentare*>(p);
            if (alim != nullptr) {
                cout << " [Scadenza: " << alim->getGiorniAllaScadenza() << " giorni]";
            }
            
            const ProdottoElettronico* elet = dynamic_cast<const ProdottoElettronico*>(p);
            if (elet != nullptr) {
                cout << " [Garanzia: " << elet->getAnniGaranzia() << " anni]";
            }
            cout << endl;
        }
        cout << "-----------------------------" << endl;
    }
};


int main() {
    cout << "=== Test Polimorfismo ===" << endl << endl;

    Carrello spesa;

    // Aggiungiamo elementi al carrello (allocati dinamicamente)
    spesa.aggiungiProdotto(new ProdottoAlimentare("Yogurt Greco", 1.80, 2));   // In scadenza (sconto 50%)
    spesa.aggiungiProdotto(new ProdottoAlimentare("Pasta Barilla", 1.20, 150)); // Non in scadenza (sconto 10%)
    spesa.aggiungiProdotto(new ProdottoElettronico("Televisore Smart", 500.0, 3)); // Garanzia > 2 anni (+5%)
    spesa.aggiungiProdotto(new ProdottoElettronico("Cuffie Bluetooth", 50.0, 2));  // Garanzia standard (nessun sovrapprezzo)

    // Stampa dettagli
    spesa.stampaDettagliCarrello();

    // Calcolo totale polimorfico
    cout << "Valore totale del carrello: " << spesa.calcolaTotaleCarrello() << " EUR" << endl;

    // Conteggio specifico con dynamic_cast
    cout << "Numero di prodotti alimentari in scadenza (<= 3gg): " << spesa.contaAlimentariInScadenza() << endl << endl;

    // All'uscita del main, l'oggetto 'spesa' (sullo stack) viene distrutto.
    // Il suo distruttore distruggerà correttamente tutti i prodotti polimorfici.
    return 0;
}
