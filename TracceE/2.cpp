#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class CalendarioRicevimenti {
private:
  // Rappresentazione dei dati:
  // Mappa esterna: giorno (stringa) -> Mappa interna: ora (int) -> studente
  // (stringa). Scelta della struttura dati: Usiamo una unordered_map nidificata
  // perché ci consente di accedere e modificare gli appuntamenti di un giorno
  // specifico in tempo medio O(1). Inoltre, per liberare un intero giorno,
  // basta fare un singolo erase sulla chiave del giorno, operazione che
  // richiede tempo medio O(1). Con un set dovremmo scorrere tutti gli elementi
  // O(N).
  unordered_map<string, unordered_map<int, string>> impegni;

  // 3) Metodo privato per controllare se il docente è libero
  // FIRMA RIVISTA:
  // - Passiamo 'giorno' come const string& per evitare copie inutili e
  // garantire const-correctness.
  // - Il metodo è contrassegnato come 'const' poiché si limita a leggere i dati
  // senza modificarli.
  bool isLibero(const string &giorno, int ora) const {
    auto it_giorno = impegni.find(giorno);
    // Se il giorno non è presente nella mappa, il docente è libero
    if (it_giorno == impegni.end()) {
      return true;
    }
    // Se il giorno esiste, verifichiamo se l'ora specifica è occupata
    auto it_ora = it_giorno->second.find(ora);
    return it_ora == it_giorno->second.end();
  }

  // Funzione helper per contare il numero totale di slot (giorno, ora)
  // occupati. Utile per rendere l'operator== estremamente efficiente.
  int contaSlotOccupati() const {
    int conteggio = 0;
    for (const auto &[giorno, orari] : impegni) {
      conteggio += orari.size();
    }
    return conteggio;
  }

public:
  // Costruttore di default
  CalendarioRicevimenti() = default;

  // Costruttore esplicito / tradizionale
  // Riceve una mappa con la stessa struttura di 'impegni' per inizializzare il calendario
  CalendarioRicevimenti(const unordered_map<string, unordered_map<int, string>>& iniziale)
      : impegni(iniziale) {}

  // Costruttore alternativo tramite vettore di coppie (giorno, sotto_mappa)
  CalendarioRicevimenti(const vector<pair<string, unordered_map<int, string>>> &lista)
      : impegni(lista.begin(), lista.end()) {}

  // 1) Richiedere un ricevimento
  // FIRMA RIVISTA:
  // - Passiamo 'studente' e 'giorno' per const string& per efficienza.
  // - Il metodo NON è const perché modifica lo stato dell'oggetto (inserisce
  // appuntamenti).
  bool chiediRicevimento(const string &studente, const string &giorno,
                         int ora) {
    // Controlliamo se lo slot è libero
    if (!isLibero(giorno, ora)) {
      return false;
    }
    // Assegniamo lo studente allo slot
    impegni[giorno][ora] = studente;
    return true;
  }

  // 2) Cancellare tutti i ricevimenti di un determinato giorno
  // FIRMA RIVISTA:
  // - Passiamo 'giorno' per const string& per permettere il passaggio di
  // costanti/rvalue.
  // - Il metodo NON è const perché modifica lo stato cancellando elementi.
  void libera(const string &giorno) {
    // Rimuove il giorno intero in tempo medio O(1)
    impegni.erase(giorno);
  }

  // 4) Confronto tra due CalendarioRicevimenti
  // Due calendari sono uguali se e solo se coincidono esattamente gli slot
  // occupati. FIRMA RIVISTA:
  // - Il parametro è passato per const&.
  // - Il metodo è const.
  // Efficienza:
  // 1. Controlliamo prima se hanno lo stesso numero di slot occupati in totale
  // (se differiscono, sono diversi).
  // 2. Scorriamo ogni slot del primo calendario e verifichiamo che esista anche
  // nel secondo. Poiché l'accesso agli elementi della unordered_map ha costo
  // medio O(1), il confronto ha costo medio proporzionale al numero di slot
  // occupati (ottimale).
  bool operator==(const CalendarioRicevimenti &altro) const {
    if (this->contaSlotOccupati() != altro.contaSlotOccupati()) {
      return false;
    }
    // Scorriamo gli impegni di questo calendario
    for (const auto &[giorno, orari] : impegni) {
      for (const auto &[ora, studente] : orari) {
        // Se lo slot (giorno, ora) in 'this' risulta libero in 'altro', i
        // calendari sono diversi
        if (altro.isLibero(giorno, ora)) {
          return false;
        }
      }
    }
    return true;
  }

  // PICCOLO BONUS) operator[]
  // Restituisce un vector contenente gli studenti impegnati in un dato giorno.
  // FIRMA RIVISTA:
  // - Restituisce per valore un vector<string>.
  // - Il parametro è passato come const string&.
  // - Il metodo è const perché non modifica la mappa (usiamo .find anziché
  // operator[]).
  vector<string> operator[](const string &giorno) const {
    vector<string> studenti_giorno;
    auto it_giorno = impegni.find(giorno);
    // Se il giorno esiste, raccogliamo gli studenti impegnati nelle varie ore
    if (it_giorno != impegni.end()) {
      for (const auto &[ora, studente] : it_giorno->second) {
        studenti_giorno.push_back(studente);
      }
    }
    return studenti_giorno;
  }
};

int main() {
  cout << "--- Test 0A: Costruttore da Mappa (Stessa struttura di 'impegni') ---" << endl;
  // Inizializzazione tramite mappa (costruttore 1)
  unordered_map<string, unordered_map<int, string>> dati_mappa = {
    {"15/03/2026", {{10, "Giovanni"}, {11, "Elena"}}},
    {"16/03/2026", {{14, "Alice"}}}
  };
  CalendarioRicevimenti c3(dati_mappa);
  cout << "Studenti impegnati il 15/03/2026 in c3 (da mappa):" << endl;
  for (const string &s : c3["15/03/2026"]) {
    cout << "- " << s << endl;
  }

  cout << "\n--- Test 0B: Costruttore da Vettore di Coppie ---" << endl;
  // Inizializzazione tramite vettore di coppie (costruttore 2)
  vector<pair<string, unordered_map<int, string>>> dati_vettore = {
    {"18/03/2026", {{9, "Roberto"}, {12, "Silvia"}}}
  };
  CalendarioRicevimenti c4(dati_vettore);
  cout << "Studenti impegnati il 18/03/2026 in c4 (da vettore):" << endl;
  for (const string &s : c4["18/03/2026"]) {
    cout << "- " << s << endl;
  }

  CalendarioRicevimenti c1;
  CalendarioRicevimenti c2;

  cout << "\n--- Test 1: Inserimento appuntamenti ---" << endl;
  // Prenotazioni in c1
  if (c1.chiediRicevimento("Luca", "20/02/2026", 10)) {
    cout << "Luca prenotato con successo per il 20/02/2026 alle ore 10."
         << endl;
  }
  // Tentativo di sovrapposizione
  if (!c1.chiediRicevimento("Marco", "20/02/2026", 10)) {
    cout << "Errore corretto: lo slot 20/02/2026 ore 10 e' gia' occupato!"
         << endl;
  }
  // Aggiungiamo altri appuntamenti in c1
  c1.chiediRicevimento("Anna", "20/02/2026", 11);
  c1.chiediRicevimento("Sofia", "21/02/2026", 15);

  // Prenotiamo gli stessi slot in c2 ma con studenti diversi
  c2.chiediRicevimento("Giacomo", "20/02/2026", 10);
  c2.chiediRicevimento("Beatrice", "20/02/2026", 11);
  c2.chiediRicevimento("Francesco", "21/02/2026", 15);

  cout << "\n--- Test 2: Uguaglianza (operator==) ---" << endl;
  // Poiche' gli slot occupati coincidono (indipendentemente dagli studenti), c1
  // == c2 deve essere true.
  if (c1 == c2) {
    cout << "SUCCESS: I due calendari sono considerati UGUALI (stessi slot "
            "occupati)."
         << endl;
  } else {
    cout << "FAILURE: I due calendari risultano diversi!" << endl;
  }

  // Modifichiamo c2 aggiungendo un appuntamento per renderli diversi
  c2.chiediRicevimento("Valeria", "21/02/2026", 16);
  if (!(c1 == c2)) {
    cout
        << "SUCCESS: Ora i due calendari sono DIVERSI (c2 ha uno slot in piu')."
        << endl;
  }

  cout << "\n--- Test 3: Rimozione (libera) ---" << endl;
  // Liberiamo il giorno 20/02/2026 in c1
  cout << "Liberiamo il giorno 20/02/2026 in c1..." << endl;
  c1.libera("20/02/2026");

  // Verifichiamo se lo slot e' tornato libero
  if (c1.chiediRicevimento("Matteo", "20/02/2026", 10)) {
    cout << "Matteo ha prenotato alle 10: slot liberato correttamente!" << endl;
  }

  cout << "\n--- Test 4: Accesso (operator[]) ---" << endl;
  // Testiamo l'operatore [] per ottenere gli studenti impegnati in un giorno
  c1.chiediRicevimento("Federico", "25/02/2026", 9);
  c1.chiediRicevimento("Chiara", "25/02/2026", 14);
  c1.chiediRicevimento("Alessandro", "25/02/2026", 18);

  cout << "Studenti impegnati il 25/02/2026 in c1:" << endl;
  vector<string> studenti = c1["25/02/2026"];
  for (const string &s : studenti) {
    cout << "- " << s << endl;
  }

  return 0;
}
