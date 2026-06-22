/*
ESERCIZIO: Gestione Coda Server di Stampa (Print Queue Manager)

Si consideri la gestione di una coda di stampa di rete per un'università. Ad ogni documento inviato 
viene associato il ruolo del proprietario: RETTORE, DOCENTE, STUDENTE.
Modellare un documento nella classe Documento, caratterizzato da:
  - id: intero univoco che identifica il documento.
  - proprietario: uno dei ruoli (RETTORE, DOCENTE, STUDENTE).
  - pagine: intero > 0 che rappresenta il numero di pagine del documento.

Implementare la classe ServerStampa che gestisce la coda di stampa secondo i seguenti 
criteri di priorità:
  1. Ruolo: RETTORE ha priorità su DOCENTE, che ha priorità su STUDENTE.
  2. Dimensione (Shortest Job First): a parità di ruolo, ha priorità il documento con MINOR numero di pagine.
  3. Ordine di arrivo: a parità di ruolo e pagine, viene stampato prima il documento inviato prima (ordine FIFO).

La classe ServerStampa deve fornire i seguenti metodi:
  1. bool inviaDocumento(Documento* d): se non esiste già un documento con lo stesso id 
     nella coda di stampa, lo inserisce nella posizione corretta secondo le priorità e ritorna true; 
     altrimenti non altera la coda e ritorna false.
  2. Documento* stampaProssimo(): estrae e restituisce il documento in testa alla coda (priorità massima). 
     Se la coda è vuota, restituisce nullptr.
  3. Documento* checkProssimo() const: restituisce il documento in testa alla coda senza rimuoverlo. 
     Se la coda è vuota, restituisce nullptr.
  4. Ridefinizione dell'operator>: siano A e B due istanze di ServerStampa. A > B se il numero 
     di documenti inviati da RETTORE in A è maggiore di quello in B. A parità di documenti del RETTORE, 
     si confronta il numero di documenti di tipo DOCENTE. A parità di quest'ultimo, si confronta il numero 
     di documenti di tipo STUDENTE.

Vincoli tecnici:
  - È vietato l'uso di strutture dati STL ad eccezione di std::vector e std::list.
*/

#include <iostream>
#include <list>
#include <string>
#include <cassert>

using namespace std;

enum Ruolo { RETTORE, DOCENTE, STUDENTE };

class Documento {
private:
    int id;
    Ruolo proprietario;
    int pagine;

public:
    Documento(int id, Ruolo prop, int pag) 
        : id(id), proprietario(prop), pagine(pag) {}

    int getId() const { return id; }
    Ruolo getProprietario() const { return proprietario; }
    int getPagine() const { return pagine; }
};

class ServerStampa {
private:
    // TODO: Scegliere le strutture dati adatte (es. list o vector)
    // Suggerimento: analogamente agli esercizi precedenti, puoi usare liste distinte per ogni ruolo
    
public:
    ServerStampa() {
        // TODO: Inizializzazione se necessaria
    }

    bool inviaDocumento(Documento* d) {
        // TODO: Inserisci il documento nella coda corretta rispettando le priorità. Ritorna false se l'ID esiste già.
        return false; 
    }

    Documento* stampaProssimo() {
        // TODO: Estrae e restituisce il prossimo documento secondo le priorità
        return nullptr;
    }

    Documento* checkProssimo() const {
        // TODO: Restituisce il prossimo documento senza rimuoverlo
        return nullptr;
    }

    bool operator>(const ServerStampa& altro) const {
        // TODO: Implementa il confronto tra i carichi di lavoro dei due server
        return false;
    }
};

// Funzione di test per verificare la correttezza dell'implementazione
int main() {
    cout << "--- Inizio Test ServerStampa ---" << endl;

    ServerStampa server1;
    ServerStampa server2;

    Documento* d1 = new Documento(101, DOCENTE, 20);
    Documento* d2 = new Documento(102, DOCENTE, 5);    // Stesso ruolo di d1 ma meno pagine -> va prima di d1 (SJF)
    Documento* d3 = new Documento(103, RETTORE, 50);   // Ruolo massimo -> va in testa
    Documento* d4 = new Documento(104, STUDENTE, 2);   // Ruolo minimo -> va in fondo
    Documento* d5 = new Documento(101, RETTORE, 10);   // ID duplicato -> deve fallire
    Documento* d6 = new Documento(105, DOCENTE, 20);   // Stesso ruolo e pagine di d1 -> deve andare DOPO d1 (FIFO)

    // Esegui inserimenti su server1
    assert(server1.inviaDocumento(d1) == true);
    assert(server1.inviaDocumento(d2) == true);
    assert(server1.inviaDocumento(d3) == true);
    assert(server1.inviaDocumento(d4) == true);
    assert(server1.inviaDocumento(d5) == false); // Duplicato ID 101
    assert(server1.inviaDocumento(d6) == true);

    // Controlla prossimo in stampa (deve essere d3 - RETTORE)
    assert(server1.checkProssimo() == d3);

    // Stampa dei documenti in sequenza e verifica ordine:
    // 1. d3 (Rettore, 50 pagine)
    // 2. d2 (Docente, 5 pagine - Shortest Job First rispetto a d1 e d6)
    // 3. d1 (Docente, 20 pagine - arrivato prima di d6)
    // 4. d6 (Docente, 20 pagine - arrivato dopo d1)
    // 5. d4 (Studente, 2 pagine)
    
    assert(server1.stampaProssimo() == d3);
    assert(server1.stampaProssimo() == d2);
    assert(server1.stampaProssimo() == d1);
    assert(server1.stampaProssimo() == d6);
    assert(server1.stampaProssimo() == d4);
    assert(server1.stampaProssimo() == nullptr); // Coda vuota

    // Test operator>
    // Inseriamo documenti in server1 e server2 per confrontarli
    server1.inviaDocumento(new Documento(201, RETTORE, 10));
    server1.inviaDocumento(new Documento(202, STUDENTE, 5));

    server2.inviaDocumento(new Documento(301, RETTORE, 10));
    server2.inviaDocumento(new Documento(302, DOCENTE, 10));
    server2.inviaDocumento(new Documento(303, STUDENTE, 10));

    // Entrambi hanno 1 documento di tipo RETTORE.
    // server2 ha 1 DOCENTE, server1 ha 0.
    // Quindi server2 > server1.
    assert(server2 > server1);
    assert(!(server1 > server2));

    cout << "TUTTI I TEST ESEGUITI CON SUCCESSO! L'implementazione e' corretta." << endl;

    // Pulizia memoria
    delete d1; delete d2; delete d3; delete d4; delete d5; delete d6;

    return 0;
}
