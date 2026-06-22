/*Esercizio 4
Un regolo di Golomb è un particolare tipo di regolo in cui il numero di tacche
viene detto ordine, mentre la massima distanza tra due delle sue tacche viene
detta lunghezza. Le tacche di un regolo di Golomb rispettano i seguenti vincoli:
• non esiste alcuna coppia di tacche poste alla stessa distanza;
come per i regoli tradizionali, le sue tacche devono essere disposte in ordine
crescente; • la prima tacca si trova in posizione 0, mentre l'ultima in
posizione 1, dove 1 è la lunghezza del regolo. Scrivere una funzione esercizio4
che, presi in input un unsigned o e un unsigned ] componga un vector<unsigned›
regolo che rappresenti le tacche di un regolo di Golomb di ordine o e
lunghezza 1. Se tale regolo esiste, la funzione deve stampare in output il
vettore regolo; altrimenti, deve stampare "IMPOSSIBILE". Esempio: il seguente è
un regolo di Golomb di ordine 4 e lunghezza 6. Si noti che la distanza tra ogni
coppia di tacche è sempre diversa. In questo caso, regolo = 10, 1, 4, 6). y0rd
Esempio: il seguente è un regolo di Golomb di ordine 4 e lunghezza 6. Si noti
che la distanza tra ogni coppia di tacche è sempre diversa. In questo caso,
regolo = (0, 1, 4, 6).*/

/*
 * ESERCIZIO 4: Il Regolo di Golomb
 *
 * Un regolo di Golomb è un insieme di tacche poste a distanze intere lungo un
 * righello. Si definiscono:
 *  - ORDINE (o): Il numero totale di tacche presenti.
 *  - LUNGHEZZA (l): La posizione dell'ultima tacca (la massima distanza
 * possibile).
 *
 * Un regolo di Golomb deve rispettare i seguenti vincoli:
 *  1. DISTANZE UNICHE: La distanza tra ogni possibile coppia di tacche deve
 * essere diversa da quella di ogni altra coppia (non esistono due coppie di
 * tacche con la stessa distanza).
 *  2. ORDINAMENTO: Le tacche devono essere disposte in ordine strettamente
 * crescente.
 *  3. POSIZIONI FISSE: La prima tacca è sempre in posizione 0, l'ultima in
 * posizione 'l'.
 *
 * RICHIESTA:
 * Scrivere una funzione 'esercizio4' che riceva in input:
 *  - unsigned o (l'ordine desiderato)
 *  - unsigned l (la lunghezza desiderata)
 *
 * La funzione deve cercare un vector<unsigned> che rappresenti le tacche del
 * regolo.
 *  - Se il regolo esiste: stampare i valori del vettore.
 *  - Se non esiste: stampare "IMPOSSIBILE".
 *
 * ESEMPIO:
 * Ordine = 4, Lunghezza = 6
 * Regolo valido: {0, 1, 4, 6}
 * Verifica distanze:
 *  |1-0|=1, |4-0|=4, |6-0|=6, |4-1|=3, |6-1|=5, |6-4|=2
 * Tutte le distanze {1, 2, 3, 4, 5, 6} sono uniche.
 */

#include <iostream>
#include <vector>
using namespace std;

// Funzione ricorsiva di backtracking
bool solve(unsigned idx, unsigned o, unsigned l, vector<unsigned> &regolo,
           vector<bool> &dists) {
  // Caso base: ultima tacca. Deve necessariamente essere 'l'.
  if (idx == o - 1) {
    for (unsigned i = 0; i < idx; ++i) {
      if (dists[l - regolo[i]])
        return false; // Distanza già presente
    }
    regolo[idx] = l;
    return true;
  }

  // Prova a piazzare la tacca in tutte le posizioni valide tra la precedente e
  // 'l'
  unsigned start = regolo[idx - 1] + 1;
  for (unsigned v = start; v < l; ++v) {
    vector<unsigned> nuove_dist;
    bool valido = true;

    // Controlla le distanze con le tacche già posizionate
    for (unsigned i = 0; i < idx; ++i) {
      unsigned d = v - regolo[i];
      if (dists[d]) {
        valido = false;
        break;
      }
      nuove_dist.push_back(d);
    }

    if (valido) {
      regolo[idx] = v;
      for (unsigned d : nuove_dist)
        dists[d] = true; // Segna le distanze come usate

      if (solve(idx + 1, o, l, regolo, dists))
        return true;

      for (unsigned d : nuove_dist)
        dists[d] = false; // Backtrack: libera le distanze
    }
  }
  return false;
}

void esercizio4(unsigned o, unsigned l) {
  // Controllo preventivo: la lunghezza deve poter contenere tutte le distanze
  // univoche
  if (o == 0) { //|| (o > 1 && l < (o * (o - 1)) / 2)
    cout << "IMPOSSIBILE\n";
    return;
  }
  if (o == 1 && l == 0) {
    cout << "(0)\n";
    return;
  }

  vector<unsigned> regolo(o);
  vector<bool> dists(l + 1, false); // Vettore di lookup veloce per le distanze
  regolo[0] = 0;

  if (solve(1, o, l, regolo, dists)) {
    cout << "(";
    for (unsigned i = 0; i < o; ++i) {
      cout << regolo[i];
    }
    cout << ")\n";
  } else {
    cout << "IMPOSSIBILE\n";
  }
}