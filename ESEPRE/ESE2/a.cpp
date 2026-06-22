#include <iostream>
#include <list>
#include <string>

using namespace std;

enum Priorita { EXPRESS, STANDARD, ECONOMIC };

class Spedizione {
private:
  int id;
  Priorita priorita;
  float peso;
  string destinazione;

public:
  Spedizione(int id, Priorita priorita, float peso, string destinazione)
      : id(id), priorita(priorita), peso(peso), destinazione(destinazione) {}

  int getId() const { return id; }
  Priorita getPriorita() const { return priorita; }
  float getPeso() const { return peso; }
  string getDestinazione() const { return destinazione; }
};

class GestoreSpedizioni {
private:
  list<Spedizione *> codaExpress;
  list<Spedizione *> codaStandard;
  list<Spedizione *> codaEconomic;

  // Helper per controllare se un ID esiste già
  bool idEsistente(int id) const {
    for (auto s : codaExpress)
      if (s->getId() == id)
        return true;
    for (auto s : codaStandard)
      if (s->getId() == id)
        return true;
    for (auto s : codaEconomic)
      if (s->getId() == id)
        return true;
    return false;
  }

  // Helper per svuotare una singola lista deallocando la memoria
  void svuotaLista(list<Spedizione *> &coda) {
    for (auto s : coda) {
      delete s; // <--- UTILE: Libera la memoria allocata dinamicamente
    }
    coda.clear();
  }

public:
  // Costruttore di default
  GestoreSpedizioni() = default;

  // Disabilitiamo il costruttore di copia e l'operatore di assegnamento
  // per prevenire la copia superficiale (shallow copy) di puntatori sullo heap.
  GestoreSpedizioni(const GestoreSpedizioni &altro) = delete;
  GestoreSpedizioni &operator=(const GestoreSpedizioni &altro) = delete;

  // 4. DISTRUTTORE: Fondamentale quando la classe possiede puntatori a dati
  // allocati con 'new'
  ~GestoreSpedizioni() {
    svuotaLista(codaExpress);
    svuotaLista(codaStandard);
    svuotaLista(codaEconomic);
  }

  // 1. Aggiungi Spedizione
  bool aggiungiSpedizione(int id, Priorita p, float peso, string dest) {
    if (idEsistente(id)) {
      return false; // Non allochiamo nulla se l'ID esiste già
    }

    // Creazione dinamica
    Spedizione *nuova = new Spedizione(id, p, peso, dest);

    list<Spedizione *> *codaTarget = nullptr;
    if (p == EXPRESS)
      codaTarget = &codaExpress;
    else if (p == STANDARD)
      codaTarget = &codaStandard;
    else
      codaTarget = &codaEconomic;

    // Inserimento ordinato decrescente per peso (peso maggiore prima)
    auto it = codaTarget->begin();
    while (it != codaTarget->end() && (*it)->getPeso() >= peso) {
      ++it;
    }
    codaTarget->insert(it, nuova);
    return true;
  }

  // 2. Evadi Prossima: elabora e DEALLOCA
  void evadiProssima() {
    Spedizione *daEvadere = nullptr;

    if (!codaExpress.empty()) {
      daEvadere = codaExpress.front();
      codaExpress.pop_front();
    } else if (!codaStandard.empty()) {
      daEvadere = codaStandard.front();
      codaStandard.pop_front();
    } else if (!codaEconomic.empty()) {
      daEvadere = codaEconomic.front();
      codaEconomic.pop_front();
    }

    if (daEvadere != nullptr) {
      cout << "Spedizione ID " << daEvadere->getId() << " inviata a "
           << daEvadere->getDestinazione() << endl;

      delete daEvadere; // <--- UTILE: Dobbiamo fare delete qui per evitare
                        // memory leak!
    }
  }

  // Helper per cercare e rimuovere da una specifica lista
  bool rimuoviEAnnullaDaLista(list<Spedizione *> &coda, int id) {
    for (auto it = coda.begin(); it != coda.end(); ++it) {
      if ((*it)->getId() == id) {
        Spedizione *daCancellare = *it;
        coda.erase(it);      // Rimuove il puntatore dalla lista STL
        delete daCancellare; // <--- UTILE: Libera effettivamente la memoria
        return true;
      }
    }
    return false;
  }

  // 3. Annulla Spedizione: cerca, rimuove e dealloca
  bool annullaSpedizione(int id) {
    if (rimuoviEAnnullaDaLista(codaExpress, id))
      return true;
    if (rimuoviEAnnullaDaLista(codaStandard, id))
      return true;
    if (rimuoviEAnnullaDaLista(codaEconomic, id))
      return true;
    return false; // Non trovata
  }
};
