#include "GestoreProdottiAlimentari.h"
#include "Prodotto.h"
#include "ProdottoFresco.h"
#include "ProdottoConservato.h"


int main() {

    GestoreProdottiAlimentari g;

    // =========================================
    // USO CORRETTO
    // =========================================

    g.aggiungi(new ProdottoFresco("Latte", 1.50));
    g.aggiungi(new ProdottoConservato("Pasta", 0.90));

    cout << "--- Elenco prodotti ---\n";
    g.stampa();

    cout << "\nTotale: " << g.totale() << " €\n";

    // Ricerca
    Prodotto* trovato = g.cerca("Latte");
    if (trovato)
        cout << "\nTrovato: " << trovato->getNome() << "\n";


    // =========================================
    // USO SBAGLIATO
    // =========================================

    // NO 1. Object slicing
    ProdottoFresco pf("Carne", 5.0);
    // Prodotto p = pf;   // slicing (PERDITA dati)

    // NO 2. Downcast pericoloso
    Prodotto* base = new ProdottoConservato("Tonno", 3.5);
    ProdottoFresco* wrong = static_cast<ProdottoFresco*>(base);  
    // RUN-TIME: comportamento indefinito

    // NO 3. Memory leak se non si cancella base
    // delete base;  // qui andrebbe cancellato

    return 0;
}