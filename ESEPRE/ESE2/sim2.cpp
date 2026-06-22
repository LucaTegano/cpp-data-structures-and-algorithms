/*
Si consideri un Pronto Soccorso semplificato, in cui ad ogni paziente viene
attribuito uno tra i seguenti codici di gravità: ROSSO, GIALLO, VERDE. Modellare
opportunamente un paziente nella classe Paziente, tenendo conto che un paziente
è caratterizzato da: un ID univoco che lo identifica, un codice di gravita
(ROSSO, GIALLO, VERDE), la sua eta. Implementare inoltre una classe
CodaProntosoccorso che tenga traccia dell'ordine in cui visitare i pazienti in
sala d'attesa secondo i seguenti criteri di priorita: • I pazienti con codice
ROSSO hanno priorità su quelli di codice GIALLO, che hanno priorità su quelli di
codice VERDE; • a parità di codice, viene visitato prima il paziente più
anziano; • a parità di età, viene visitato prima chi è arrivato prima, secondo
l'ordine di inserimento nella coda. La classe CodaProntosoccorso deve fornire i
seguenti metodi: I bool arrivo (Paziente* p): se non esiste alcun paziente con
lo stesso ID di p già nella sala d'attesa, inserisce il paziente p secondo le
priorità e ritorna true; altrimenti, non altera la sala d'attesa e ritorna
false;
2. Paziente* visitaProssimo () : restituisce il prossimo paziente, eliminandolo
dalla sala d'attesa. Se quest'ultima è vuota, restituisce nullptr.
3. Paziente* checkProssimo() const: restituisce il prossimo paziente, senza
eliminarlo dalla sala d'attesa. Se quest'ultima è vuota, restituisce nullptr;
4. la ridefinizione di operator>: siano a e b due istanze di CodaProntoSoccorso.
a>b se il numero di pazienti con codice ROSSO di a > di numero di pazienti con
codice ROSSO di b. A parità di pazienti con codice ROSSO, si confronta sui
pazienti con codice GIALLO. A parità di pazienti con codice GIALLO, si confronta
sui pazienti con codice VERDE. Si può assumere che gli input siano sempre
corretti, che il codice di gravità sia sempre uno tra ROSSO, GIALLO, VERDE e che
il tempo di attesa sia un intero >= 0. Ai fini dell'esercizio, non è consentito
l'uso di strutture dati STL ad eccezione di vector e list. Criteri che
influenzeranno la valutazione dell'esercizio sono anche: la scelta delle
strutture dati utilizzate per rappresentare il problema e l'efficienza dei
metodi implementati.*/

#include <list>
using namespace std;

enum Gravita { ROSSO, GIALLO, VERDE };

class Paziente {
private:
  int id;
  Gravita codice;
  int eta;

public:
  Paziente(int id, Gravita codice, int eta)
      : id(id), codice(codice), eta(eta) {}

  int getId() const { return id; }
  Gravita getCodice() const { return codice; }
  int getEta() const { return eta; }
};

class CodaProntosoccorso {
private:
  // Utilizziamo 3 liste separate per gestire facilmente le priorità dei codici
  // e per poter inserire ed eliminare efficientemente in mezzo/testa.
  list<Paziente *> codaRosso;
  list<Paziente *> codaGiallo;
  list<Paziente *> codaVerde;

  bool idEsistente(int id) const {
    for (const auto &p : codaRosso) {
      if (p->getId() == id)
        return true;
    }
    for (const auto &p : codaGiallo) {
      if (p->getId() == id)
        return true;
    }
    for (const auto &p : codaVerde) {
      if (p->getId() == id)
        return true;
    }
    return false;
  }

public:
  // Inserisce il paziente p nella coda corretta secondo le priorità di età.
  bool arrivo(Paziente *p) {
    if (!p)
      return false;

    // Verifica se l'ID esiste già (costo O(N))
    if (idEsistente(p->getId())) {
      return false;
    }

    list<Paziente *> *codaTarget = nullptr;
    switch (p->getCodice()) {
    case ROSSO:
      codaTarget = &codaRosso;
      break;
    case GIALLO:
      codaTarget = &codaGiallo;
      break;
    case VERDE:
      codaTarget = &codaVerde;
      break;
    }

    // Inserimento ordinato per età: viene visitato prima il paziente più
    // anziano. A parità di età: si visita chi è arrivato prima. Scorrendo la
    // lista dall'inizio e fermandoci al primo paziente STRETTAMENTE più giovane
    // per l'inserimento, inseriremo il nuovo paziente DOPO tutti i pazienti con
    // età >= alla sua, rispettando l'ordine di arrivo in caso di parità di età.
    auto it = codaTarget->begin();
    while (it != codaTarget->end() && (*it)->getEta() >= p->getEta()) {
      ++it;
    }
    codaTarget->insert(it, p);

    return true;
  }

  Paziente *visitaProssimo() {
    Paziente *prossimo = nullptr;
    if (!codaRosso.empty()) {
      prossimo = codaRosso.front();
      codaRosso.pop_front();
    } else if (!codaGiallo.empty()) {
      prossimo = codaGiallo.front();
      codaGiallo.pop_front();
    } else if (!codaVerde.empty()) {
      prossimo = codaVerde.front();
      codaVerde.pop_front();
    }
    return prossimo;
  }

  Paziente *checkProssimo() const {
    if (!codaRosso.empty()) {
      return codaRosso.front();
    } else if (!codaGiallo.empty()) {
      return codaGiallo.front();
    } else if (!codaVerde.empty()) {
      return codaVerde.front();
    }
    return nullptr;
  }

  bool operator>(const CodaProntosoccorso &b) const {
    if (codaRosso.size() != b.codaRosso.size()) {
      return codaRosso.size() > b.codaRosso.size();
    }
    if (codaGiallo.size() != b.codaGiallo.size()) {
      return codaGiallo.size() > b.codaGiallo.size();
    }
    return codaVerde.size() > b.codaVerde.size();
  }
};