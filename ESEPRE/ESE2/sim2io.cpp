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
metodi implementati.


Esercizio: Gestione Priorità Pronto Soccorso
1. Obiettivo
Progettare un sistema per la gestione di una sala d'attesa di un Pronto
Soccorso. Il sistema deve dare precedenza ai casi più gravi e, a parità di
gravità, ai pazienti più anziani.
2. La Classe Paziente
Ogni paziente è definito da:
•	ID univoco (stringa o intero).
•	Codice Gravità: ROSSO (massima), GIALLO, VERDE (minima).
•	Età: intero positivo.
3. La Classe CodaProntoSoccorso
La classe deve gestire la collezione di pazienti in attesa.
Logica di Ordinamento (Priority)
Il prossimo paziente da visitare è determinato secondo questi criteri
gerarchici: 1.	Gravità: ROSSO > GIALLO > VERDE. 2.	Età: A parità di codice,
viene visitato prima il paziente più anziano. 3.	Ordine di arrivo: A
parità di gravità ed età, vale l'ordine FIFO (First-In, First-Out).
Metodi Obbligatori
•	bool arrivo(Paziente* p): Inserisce il paziente nella
posizione corretta. Vincolo: Se l'ID è già presente, l'inserimento fallisce
(ritorna false).
•	Paziente* visitaProssimo(): Estrae e restituisce il
paziente in testa. Restituisce nullptr se la coda è vuota.
•	Paziente* checkProssimo() const: Restituisce il puntatore al prossimo
paziente senza rimuoverlo.
•	Overloading operator>: Confronta due diverse
istanze di CodaProntoSoccorso (es. A > B). Il confronto avviene sul carico di
lavoro: • Vince chi ha più codici ROSSI. •	In caso di parità, chi ha più
codici GIALLI. •	In ultima istanza, chi ha più codici VERDI.
4. Vincoli Tecnici
[!IMPORTANT]
Limitazioni: È vietato l'uso di qualsiasi struttura dati STL ad eccezione di
std::vector o std::list. Efficienza: La scelta del contenitore e l'algoritmo di
inserimento influenzeranno la valutazione. Considera bene se mantenere la lista
sempre ordinata o ordinare al momento dell'estrazione. Perché questa versione è
migliore? •	Separazione delle responsabilità: Divide chiaramente i dati
(Paziente) dalla logica (Coda). •	Gerarchia dei criteri: I punti elenco
per la priorità eliminano le ambiguità del testo discorsivo. •	Enfasi sui
vincoli: Il box "Vincoli Tecnici" impedisce allo studente di usare
std::priority_queue o std::set, costringendolo a ragionare sulla complessità
computazionale di vector vs list.*/

#include <cstddef>
#include <list>
using namespace std;

enum Gravita { ROSSO, GIALLO, VERDE };
class Paziente {
private:
  int id;
  int eta;
  Gravita codice;

public:
  Paziente(int id, int eta, Gravita codice)
      : id(id), eta(eta), codice(codice) {}

  int getId() const { return id; }
  int getEta() const { return eta; }
  Gravita getCodice() const { return codice; }
};
class ProntoSoccorso {
private:
  list<Paziente *> codaRossa;
  list<Paziente *> codaGialla;
  list<Paziente *> codaVerde;

  bool idEsistente(int id) const {
    for (const auto &p : codaRossa) {
      if (p->getId() == id) {
        return true;
      }
    }
    for (const auto &p : codaGialla) {
      if (p->getId() == id) {
        return true;
      }
    }
    for (const auto &p : codaVerde) {
      if (p->getId() == id) {
        return true;
      }
    }
    return false;
  }

public:
  bool arrivo(Paziente *p) {
    if (!p || idEsistente(p->getId())) {
      return false;
    }
    list<Paziente *> *codaTarget = nullptr;
    switch (p->getCodice()) {
    case ROSSO:
      codaTarget = &codaRossa;
      break;
    case GIALLO:
      codaTarget = &codaGialla;
      break;
    case VERDE:
      codaTarget = &codaVerde;
      break;
    }
    auto it = codaTarget->begin();
    while (it != codaTarget->end() && (*it)->getEta() > p->getEta()) {
      it++;
    }
    codaTarget->insert(it, p);
    return true;
  }

  Paziente *visitaProssimo() {
    Paziente *prossimo = nullptr;
    if (!codaRossa.empty()) {
      prossimo = codaRossa.front();
      codaRossa.pop_front();
    } else if (!codaGialla.empty()) {
      prossimo = codaRossa.front();
      codaRossa.pop_front();
    } else if (!codaVerde.empty()) {
      prossimo = codaRossa.front();
      codaRossa.pop_front();
    }
    return prossimo;
  }

  Paziente *checkProssimo() const {
    if (!codaRossa.empty()) {
      return codaRossa.front();
    } else if (!codaGialla.empty()) {
      return codaGialla.front();
    } else if (!codaVerde.empty()) {
      return codaVerde.front();
    }
    return nullptr;
  }
  bool operator>(const ProntoSoccorso &b) const {
    if (codaRossa.size() != b.codaRossa.size()) {
      return codaRossa.size() > b.codaRossa.size();
    }
    if (codaGialla.size() != b.codaGialla.size()) {
      return codaGialla.size() > b.codaGialla.size();
    }
    if (codaVerde.size() != b.codaVerde.size()) {
      return codaVerde.size() > b.codaVerde.size();
    }
  }
};
