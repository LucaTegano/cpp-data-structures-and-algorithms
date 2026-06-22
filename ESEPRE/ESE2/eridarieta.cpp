/*
ESEMPIO DI ESAME: Ereditarietà (Inheritance) in C++

CONCETTI CHIAVE ILLUSTRATI:
1. Classe Base (Prodotto) e Classi Derivate (ProdottoAlimentare, ProdottoElettronico).
2. Modificatori di accesso: private, protected, public.
3. Chiamata del costruttore della classe base da parte delle classi derivate (Costruttore in cascata).
4. Ereditarietà dei metodi e overriding di un metodo della classe base.
*/

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

// 1. CLASSE BASE
class Prodotto {
private:
    // Attributo private: accessibile SOLO all'interno di questa classe.
    // Nemmeno le classi derivate possono accedervi direttamente.
    string codice;

protected:
    // Attributo protected: accessibile all'interno di questa classe 
    // E da tutte le classi derivate (figlie), ma non dall'esterno.
    double prezzoBase;
    string descrizione;

public:
    // Costruttore con parametri della classe base
    Prodotto(string cod, double prezzo, string desc) 
        : codice(cod), prezzoBase(prezzo), descrizione(desc) {
        cout << "[Costruttore Prodotto] Inizializzato prodotto: " << descrizione << endl;
    }

    // Distruttore virtuale: FONDAMENTALE quando si usa l'ereditarietà.
    // Assicura che, se cancelliamo un oggetto derivato tramite un puntatore alla classe base,
    // venga chiamato anche il distruttore della classe derivata.
    virtual ~Prodotto() {
        cout << "[Distruttore Prodotto] Distrutto prodotto base: " << descrizione << endl;
    }

    // Getter per codice (essendo privato, serve un metodo pubblico per leggerlo all'esterno)
    string getCodice() const { return codice; }
    double getPrezzoBase() const { return prezzoBase; }
    string getDescrizione() const { return descrizione; }

    // Metodo che verrà sovrascritto (override) nelle classi derivate
    double calcolaPrezzoFinale() const {
        return prezzoBase; // Il prodotto generico non ha sconti applicati
    }
};


// 2. CLASSE DERIVATA 1: ProdottoAlimentare
// Eredita pubblicamente da Prodotto. Significa che i membri public della base rimangono public,
// e i membri protected rimangono protected nella classe derivata.
class ProdottoAlimentare : public Prodotto {
private:
    int giorniAllaScadenza;

public:
    // Costruttore di ProdottoAlimentare:
    // Deve chiamare esplicitamente il costruttore della classe base "Prodotto"
    // passandogli i parametri necessari tramite la lista di inizializzazione.
    ProdottoAlimentare(string cod, double prezzo, string desc, int giorniScadenza)
        : Prodotto(cod, prezzo, desc), giorniAllaScadenza(giorniScadenza) {
        cout << "[Costruttore ProdottoAlimentare] Inizializzato con giorni alla scadenza: " << giorniAllaScadenza << endl;
    }

    // Distruttore di ProdottoAlimentare
    ~ProdottoAlimentare() override {
        cout << "[Distruttore ProdottoAlimentare] Distrutto specifico alimentare." << endl;
    }

    int getGiorniAllaScadenza() const { return giorniAllaScadenza; }

    // OVERRIDING: Ridefiniamo il metodo calcolaPrezzoFinale().
    // La keyword 'override' (opzionale ma fortemente consigliata in C++11) 
    // assicura che il compilatore controlli che stiamo effettivamente sovrascrivendo un metodo virtuale della base.
    // Nota: per poter fare overriding a runtime, il metodo nella classe base deve essere dichiarato "virtual" 
    // (approfondito nel file del polimorfismo).
    double calcolaPrezzoFinale() const {
        // Se mancano meno di 3 giorni alla scadenza, applichiamo uno sconto del 50%
        if (giorniAllaScadenza <= 3) {
            // Possiamo accedere direttamente a prezzoBase perché è 'protected' nella classe base.
            // Non potremmo accedere direttamente a 'codice' perché è 'private' (dovremmo usare getCodice()).
            return prezzoBase * 0.5; 
        }
        // Altrimenti sconto standard del 10%
        return prezzoBase * 0.9;
    }
};


// 3. CLASSE DERIVATA 2: ProdottoElettronico
class ProdottoElettronico : public Prodotto {
private:
    int anniGaranzia;

public:
    ProdottoElettronico(string cod, double prezzo, string desc, int garanzia)
        : Prodotto(cod, prezzo, desc), anniGaranzia(garanzia) {
        cout << "[Costruttore ProdottoElettronico] Inizializzato con anni garanzia: " << anniGaranzia << endl;
    }

    ~ProdottoElettronico() override {
        cout << "[Distruttore ProdottoElettronico] Distrutto specifico elettronico." << endl;
    }

    int getAnniGaranzia() const { return anniGaranzia; }

    // Override del calcolo prezzo:
    // Se ha più di 2 anni di garanzia, c'è un sovrapprezzo del 5% per la copertura assicurativa.
    double calcolaPrezzoFinale() const {
        if (anniGaranzia > 2) {
            return prezzoBase * 1.05;
        }
        return prezzoBase;
    }
};


int main() {
    cout << "=== Test Ereditarieta' ===" << endl << endl;

    // Creiamo un Prodotto generico
    cout << "--- Creazione Prodotto Generico ---" << endl;
    Prodotto p("GEN123", 10.0, "Tazza di ceramica");
    cout << "Prezzo finale generico: " << p.calcolaPrezzoFinale() << " EUR" << endl << endl;

    // Creiamo un Prodotto Alimentare prossimo alla scadenza (sconto 50%)
    cout << "--- Creazione Prodotto Alimentare ---" << endl;
    ProdottoAlimentare pa("ALIM55", 4.0, "Latte Fresco", 2);
    cout << "Prezzo base: " << pa.getPrezzoBase() << " EUR" << endl;
    // Chiama il metodo sovrascritto in ProdottoAlimentare
    cout << "Prezzo scontato (scade tra " << pa.getGiorniAllaScadenza() << " gg): " 
         << pa.calcolaPrezzoFinale() << " EUR" << endl << endl;

    // Creiamo un Prodotto Elettronico con estensione garanzia (sovrapprezzo 5%)
    cout << "--- Creazione Prodotto Elettronico ---" << endl;
    ProdottoElettronico pe("ELET99", 1000.0, "Smartphone Ultra", 3);
    cout << "Prezzo finale con garanzia " << pe.getAnniGaranzia() << " anni: " 
         << pe.calcolaPrezzoFinale() << " EUR" << endl << endl;

    cout << "--- Distruzione Oggetti sullo Stack (in ordine inverso di creazione) ---" << endl;
    // Qui verranno chiamati automaticamente i distruttori.
    // Per gli oggetti derivati (pa, pe), viene prima chiamato il distruttore della classe figlia,
    // e subito dopo in automatico quello della classe padre.
    
    return 0;
}
