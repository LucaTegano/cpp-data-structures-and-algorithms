/*
ESERCIZIO: Gestione Pista di Decollo (Airport Runway Queue)

Si consideri la gestione dei decolli in un aeroporto. Ad ogni aereo in attesa viene 
attribuita una categoria di priorità: EMERGENZA, COMMERCIALE, PRIVATO.
Modellare un aereo nella classe Aereo, caratterizzato da:
  - codiceVolo: stringa univoca che identifica l'aereo.
  - categoria: una delle categorie (EMERGENZA, COMMERCIALE, PRIVATO).
  - ritardo: intero >= 0 che rappresenta i minuti di ritardo accumulati.

Implementare la classe CodaDecollo che gestisce la coda di decollo secondo i seguenti 
criteri di priorità:
  1. Categoria: EMERGENZA ha priorità su COMMERCIALE, che ha priorità su PRIVATO.
  2. Ritardo: a parità di categoria, ha priorità l'aereo con maggior ritardo accumulato.
  3. Ordine di arrivo: a parità di categoria e ritardo, viene inserito prima chi è arrivato 
     prima (ordine FIFO di inserimento).

La classe CodaDecollo deve fornire i seguenti metodi:
  1. bool inserisciAereo(Aereo* a): se non esiste già un aereo con lo stesso codiceVolo 
     nella coda, inserisce l'aereo nella posizione corretta e ritorna true; altrimenti 
     non altera la coda e ritorna false.
  2. Aereo* decollaProssimo(): estrae e restituisce l'aereo in testa alla coda (priorità massima). 
     Se la coda è vuota, restituisce nullptr.
  3. Aereo* prossimoAlDecollo() const: restituisce l'aereo in testa senza rimuoverlo. 
     Se la coda è vuota, restituisce nullptr.
  4. Ridefinizione dell'operator>: siano A e B due istanze di CodaDecollo. A > B se il numero 
     di aerei in EMERGENZA in A è maggiore di quello in B. A parità di EMERGENZA, si confronta 
     il numero di aerei COMMERCIALE. A parità di quest'ultimo, si confronta il numero di aerei PRIVATO.

Vincoli tecnici:
  - È vietato l'uso di strutture dati STL ad eccezione di std::vector e std::list.
*/

#include <iostream>
#include <list>
#include <string>
#include <cassert>

using namespace std;

enum Categoria { EMERGENZA, COMMERCIALE, PRIVATO };

class Aereo {
private:
    string codiceVolo;
    Categoria categoria;
    int ritardo;

public:
    Aereo(string codice, Categoria cat, int rit) 
        : codiceVolo(codice), categoria(cat), ritardo(rit) {}

    string getCodiceVolo() const { return codiceVolo; }
    Categoria getCategoria() const { return categoria; }
    int getRitardo() const { return ritardo; }
};

class CodaDecollo {
private:
    // TODO: Scegliere le strutture dati adatte (es. list o vector)
    // Suggerimento: analogamente a sim2.cpp, puoi usare 3 liste distinte per categoria
    
public:
    CodaDecollo() {
        // TODO: Inizializzazione se necessaria
    }

    bool inserisciAereo(Aereo* a) {
        // TODO: Inserisci l'aereo in coda rispettando le priorità. Ritorna false se l'aereo con lo stesso ID esiste già.
        return false; 
    }

    Aereo* decollaProssimo() {
        // TODO: Estrae e restituisce il prossimo aereo secondo le priorità
        return nullptr;
    }

    Aereo* prossimoAlDecollo() const {
        // TODO: Restituisce il prossimo aereo senza rimuoverlo
        return nullptr;
    }

    bool operator>(const CodaDecollo& altra) const {
        // TODO: Implementa il confronto tra carichi di lavoro delle code
        return false;
    }
};

// Funzione di test per guidarti nella verifica
int main() {
    cout << "--- Inizio Test CodaDecollo ---" << endl;

    CodaDecollo pista1;
    CodaDecollo pista2;

    Aereo* a1 = new Aereo("AZ123", COMMERCIALE, 15);
    Aereo* a2 = new Aereo("LH456", COMMERCIALE, 45); // Stessa cat di a1, ma più ritardo -> va prima di a1
    Aereo* a3 = new Aereo("EJ789", EMERGENZA, 5);    // Emergenza -> va prima di tutti
    Aereo* a4 = new Aereo("PR001", PRIVATO, 120);    // Privato -> in fondo
    Aereo* a5 = new Aereo("AZ123", EMERGENZA, 10);   // ID duplicato -> deve fallire l'inserimento
    Aereo* a6 = new Aereo("IB999", COMMERCIALE, 15); // Stessa cat e stesso ritardo di a1 -> deve andare DOPO a1 (FIFO)

    // Esegui inserimenti su pista1
    assert(pista1.inserisciAereo(a1) == true);
    assert(pista1.inserisciAereo(a2) == true);
    assert(pista1.inserisciAereo(a3) == true);
    assert(pista1.inserisciAereo(a4) == true);
    assert(pista1.inserisciAereo(a5) == false); // Duplicato AZ123
    assert(pista1.inserisciAereo(a6) == true);

    // Controlla prossimo al decollo (deve essere a3 - EMERGENZA)
    assert(pista1.prossimoAlDecollo() == a3);

    // Decollo degli aerei in sequenza e verifica ordine:
    // 1. a3 (Emergenza, ritardo 5)
    // 2. a2 (Commerciale, ritardo 45)
    // 3. a1 (Commerciale, ritardo 15 - arrivato prima di a6)
    // 4. a6 (Commerciale, ritardo 15 - arrivato dopo a1)
    // 5. a4 (Privato, ritardo 120)
    
    assert(pista1.decollaProssimo() == a3);
    assert(pista1.decollaProssimo() == a2);
    assert(pista1.decollaProssimo() == a1);
    assert(pista1.decollaProssimo() == a6);
    assert(pista1.decollaProssimo() == a4);
    assert(pista1.decollaProssimo() == nullptr); // Coda vuota

    // Test operator>
    // Aggiungiamo aerei a pista1 e pista2 per confrontarle
    pista1.inserisciAereo(new Aereo("X1", EMERGENZA, 10));
    pista1.inserisciAereo(new Aereo("X2", COMMERCIALE, 10));

    pista2.inserisciAereo(new Aereo("Y1", EMERGENZA, 10));
    pista2.inserisciAereo(new Aereo("Y2", COMMERCIALE, 20));
    pista2.inserisciAereo(new Aereo("Y3", COMMERCIALE, 30));

    // Entrambe hanno 1 EMERGENZA. pista2 ha 2 COMMERCIALE, pista1 ne ha 1. 
    // Quindi pista2 > pista1.
    assert(pista2 > pista1);
    assert(!(pista1 > pista2));

    cout << "TUTTI I TEST ESEGUITI CON SUCCESSO! L'implementazione e' corretta." << endl;

    // Pulizia memoria
    delete a1; delete a2; delete a3; delete a4; delete a5; delete a6;

    return 0;
}
