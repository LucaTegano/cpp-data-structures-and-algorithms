/*
ESERCIZIO: Gestore Spedizioni E-commerce (E-commerce Delivery Queue Manager)

Si desidera modellare un sistema avanzato per la gestione dei flussi di spedizione di un e-commerce.
Il sistema gestisce diversi ordini suddivisi per categoria merceologica.

Modellare la classe Ordine, che contiene:
  - id: stringa univoca che identifica l'ordine.
  - categoria: stringa (es. "Elettronica", "Libri", "Abbigliamento").
  - importo: double (valore economico dell'ordine).
  - urgente: boolean (indica se la spedizione ha carattere d'urgenza).

Implementare la classe GestoreOrdini che gestisce le code di spedizione. 
La classe deve utilizzare internamente le seguenti strutture dati:
  1. Una mappa `std::map<string, std::list<Ordine*>> codeSpedizione` che associa ogni categoria alla lista degli ordini in attesa.
  2. Una mappa `std::map<string, Ordine*> mappaOrdini` che associa l'ID dell'ordine al puntatore dell'ordine per ricerche e cancellazioni veloci.

Criteri di ordinamento all'interno della lista di ciascuna categoria:
  1. Gli ordini con urgente == true hanno priorità su quelli con urgente == false.
  2. A parità di urgenza, gli ordini con IMPORTO MAGGIORE hanno la priorità.
  3. A parità di urgenza ed importo, si segue l'ordine FIFO di inserimento.

La classe GestoreOrdini deve fornire i seguenti metodi:
  1. bool inserisciOrdine(Ordine* o): inserisce l'ordine nella categoria corretta rispettando le priorità sopra indicate,
     e lo memorizza nella mappa globale mappaOrdini. Ritorna true se inserito con successo, false se esiste già un ordine con lo stesso id.
  2. Ordine* spedisciProssimo(string categoria): estrae (rimuovendolo sia dalla lista che dalla mappa) il prossimo ordine da spedire 
     per la categoria indicata. Ritorna nullptr se la categoria non esiste o è vuota.
  3. bool annullaOrdine(string id): cancella l'ordine avente l'ID fornito, rimuovendolo sia dalla mappa globale che dalla lista 
     della categoria corrispondente. Sfruttare la mappa per verificare in tempo efficiente O(log N) se l'ordine esiste prima di cercarlo nella lista.
     Ritorna true se rimosso con successo, false altrimenti.
  4. double calcolaValoreTotale(string categoria) const: calcola e restituisce la somma degli importi degli ordini in attesa per la categoria indicata.
     Se la categoria non esiste, ritorna 0.0.
  5. Ridefinizione dell'operator>: confronta due istanze A e B di GestoreOrdini. A > B se la somma totale degli importi di tutti 
     gli ordini presenti in A (di qualsiasi categoria) è maggiore della somma totale di B.

Vincoli tecnici:
  - È consentito l'uso di std::vector, std::list, std::map e std::pair.
*/

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <cassert>

using namespace std;

class Ordine {
private:
    string id;
    string categoria;
    double importo;
    bool urgente;

public:
    Ordine(string id, string cat, double imp, bool urg)
        : id(id), categoria(cat), importo(imp), urgente(urg) {}

    string getId() const { return id; }
    string getCategoria() const { return categoria; }
    double getImporto() const { return importo; }
    bool isUrgente() const { return urgente; }
};

class GestoreOrdini {
private:
    map<string, list<Ordine*>> codeSpedizione;
    map<string, Ordine*> mappaOrdini;

public:
    GestoreOrdini() {}

    bool inserisciOrdine(Ordine* o) {
        // TODO: Implementare l'inserimento con priorità
        // Ricordarsi di aggiornare sia codeSpedizione che mappaOrdini.
        // Criteri di priorità nella lista della categoria di o:
        // 1. Urgente (true prima di false)
        // 2. Importo maggiore prima di importo minore
        // 3. FIFO in caso di parità
        return false;
    }

    Ordine* spedisciProssimo(string categoria) {
        // TODO: Estrarre e rimuovere il primo ordine per la categoria data.
        // Rimuovere sia dalla lista in codeSpedizione che da mappaOrdini.
        return nullptr;
    }

    bool annullaOrdine(string id) {
        // TODO: Annullare l'ordine identificato da id.
        // Utilizzare mappaOrdini per verificare l'esistenza a costo O(log N).
        // Rimuovere sia da mappaOrdini che dalla lista specifica all'interno di codeSpedizione.
        return false;
    }

    double calcolaValoreTotale(string categoria) const {
        // TODO: Calcolare la somma degli importi degli ordini in una data categoria.
        return 0.0;
    }

    double calcolaValoreGlobale() const {
        // Metodo helper opzionale per sommare gli importi di tutti gli ordini presenti nel gestore
        double totale = 0.0;
        // TODO
        return totale;
    }

    bool operator>(const GestoreOrdini& altro) const {
        // TODO: Confrontare i valori globali di due gestori
        return false;
    }
};

// Funzione di test per verificare la tua soluzione
int main() {
    cout << "--- Inizio Test GestoreOrdini (Misto Map/List) ---" << endl;

    GestoreOrdini gestore;

    Ordine* o1 = new Ordine("O1", "Elettronica", 150.0, false);
    Ordine* o2 = new Ordine("O2", "Elettronica", 300.0, false); // Stessa categoria, importo maggiore -> va prima di o1
    Ordine* o3 = new Ordine("O3", "Elettronica", 50.0, true);   // Urgente -> va in testa assoluta
    Ordine* o4 = new Ordine("O4", "Libri", 20.0, false);
    Ordine* o5 = new Ordine("O5", "Elettronica", 150.0, false); // Stesso importo e urgenza di o1 -> va dopo o1 (FIFO)
    
    // Test Inserimenti
    assert(gestore.inserisciOrdine(o1) == true);
    assert(gestore.inserisciOrdine(o2) == true);
    assert(gestore.inserisciOrdine(o3) == true);
    assert(gestore.inserisciOrdine(o4) == true);
    assert(gestore.inserisciOrdine(o5) == true);
    
    // Test Duplicato (ID già presente)
    Ordine* o_dupl = new Ordine("O1", "Abbigliamento", 10.0, true);
    assert(gestore.inserisciOrdine(o_dupl) == false);
    delete o_dupl;

    // Test Valore Totale per Categoria
    // Elettronica ha: o1 (150), o2 (300), o3 (50), o5 (150) -> Totale = 650.0
    // Libri ha: o4 (20) -> Totale = 20.0
    assert(gestore.calcolaValoreTotale("Elettronica") == 650.0);
    assert(gestore.calcolaValoreTotale("Libri") == 20.0);
    assert(gestore.calcolaValoreTotale("Inesistente") == 0.0);

    // Test Spedizioni (Ordine di priorità Elettronica):
    // 1. o3 (Urgente)
    // 2. o2 (Non urgente, importo 300)
    // 3. o1 (Non urgente, importo 150 - arrivato prima di o5)
    // 4. o5 (Non urgente, importo 150 - arrivato dopo o1)
    assert(gestore.spedisciProssimo("Elettronica") == o3);
    assert(gestore.spedisciProssimo("Elettronica") == o2);

    // Rimangono o1 e o5 in Elettronica. Proviamo ad annullare o1
    assert(gestore.annullaOrdine("O1") == true);
    assert(gestore.annullaOrdine("O1") == false); // Già rimosso

    // Ora in Elettronica deve esserci solo o5
    assert(gestore.spedisciProssimo("Elettronica") == o5);
    assert(gestore.spedisciProssimo("Elettronica") == nullptr); // Finita

    // Test Annullamento con ID inesistente
    assert(gestore.annullaOrdine("NON_ESISTE") == false);

    // Libri ha ancora o4
    assert(gestore.spedisciProssimo("Libri") == o4);
    assert(gestore.spedisciProssimo("Libri") == nullptr);

    // Test operator>
    GestoreOrdini gA;
    GestoreOrdini gB;

    gA.inserisciOrdine(new Ordine("A1", "Elettronica", 100.0, false));
    gA.inserisciOrdine(new Ordine("A2", "Libri", 50.0, false)); // Totale gA = 150.0

    gB.inserisciOrdine(new Ordine("B1", "Elettronica", 80.0, false));
    gB.inserisciOrdine(new Ordine("B2", "Abbigliamento", 60.0, false)); // Totale gB = 140.0

    assert(gA > gB);
    assert(!(gB > gA));

    cout << "TUTTI I TEST ESEGUITI CON SUCCESSO! L'implementazione e' corretta." << endl;

    // Pulizia
    delete o1; delete o2; delete o3; delete o4; delete o5;
    return 0;
}
