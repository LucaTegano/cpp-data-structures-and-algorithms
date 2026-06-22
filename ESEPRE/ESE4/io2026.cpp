/*Esercizio 4
Un regolo di Golomb è un particolare tipo di regolo in cui il numero di tacche
viene detto ordine, mentre la massima distanza tra due delle sue tacche viene
detta lunghezza. Le tacche di un regolo di Golomb rispettano i seguenti vincoli:
• non esiste alcuna coppia di tacche poste alla stessa distanza;
come per i regoli tradizionali, le sue tacche devono essere disposte in ordine
crescente; • la prima tacca si trova in posizione 0, mentre l'ultima in
posizione l, dove l è la lunghezza del regolo. Scrivere una funzione esercizio4
che, presi in input un unsigned o e un unsigned l componga un vector<unsigned›
regolo che rappresenti le tacche di un regolo di Golomb di ordine o e
lunghezza l. Se tale regolo esiste, la funzione deve stampare in output il
vettore regolo; altrimenti, deve stampare "IMPOSSIBILE". Esempio: il seguente è
un regolo di Golomb di ordine 4 e lunghezza 6. Si noti che la distanza tra ogni
coppia di tacche è sempre diversa. In questo caso, regolo = 10, 1, 4, 6). y0rd
Esempio: il seguente è un regolo di Golomb di ordine 4 e lunghezza 6. Si noti
che la distanza tra ogni coppia di tacche è sempre diversa. In questo caso,
regolo = (0, 1, 4, 6).
*/
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>
using namespace std;
// regolo, o, l, dists(bool),idx

/*
CASO BASE-> Se sono arrivato a idx == o -1 controllo dists[l-regolo[i]] se vanno
bene ho finito altrimenti devo ritoranare alla funzione ricorsiviva con un nuovo
regolo a idx = o -2 ,infatti se o -1 non va bene ,devo cambiare o -2 ,siccome
devo cambiare o - 2,tot volte mi serve sicuramente un ciclo ,questo ciclo va da
uno start fino a l ,inoltre ci vuole un ciclo interno perchè per ogni valore che
metto devo controllare se funziona prima di continuare con la chiamata
successiva start = regolo[idx-1]+1
vector<unsigned> n_dists
bool valido per verificare che sto inserendo un regolo giusto e le sue distanze
,questo vector di appoggio mi serve per poter aggiungere e rimuovere le distanze
dell'ultima aggiunta,infatti farò un for d: ndists dists[d] = true;

*/

bool solve(unsigned idx, unsigned o, unsigned l, vector<unsigned> &regolo,
           vector<bool> &dists) {
  if (idx == o - 1) {
    for (unsigned i = 0; i < idx; i++) {
      if (dists[l - regolo[i]])
        return false;
    }
    regolo[idx] = l;
    return true;
  }
  unsigned start = regolo[idx - 1] + 1;
  for (unsigned v = start; v < l; v++) {
    bool valido = true;
    vector<unsigned> n_dists;
    for (unsigned i = 0; i < idx; i++) {
      unsigned d = v - regolo[i];
      if (dists[d]) {
        valido = false;
        break;
      }
      n_dists.push_back(d);
    }
    if (valido) {
      regolo[idx] = v;
      for (unsigned d : n_dists) {
        dists[d] = true;
      }
      if (solve(idx + 1, o, l, regolo, dists)) {
        return true;
      }
      for (unsigned d : n_dists) {
        dists[d] = false;
      }
    }
  }
  return false;
}

void esercizio4(unsigned o, unsigned l) {
  if (o == 0) {
    cout << "IMPOSSIBILE";
    return;
  }
  vector<unsigned> regolo(o);
  vector<bool> dists(l + 1, false);
  if (solve(1, o, l, regolo, dists)) {
    for (unsigned i = 0; i < o; ++i) {
      cout << regolo[i];
    }
    cout << endl;
  } else {
    cout << "IMPOSSIBILE" << endl;
  }
  return;
}
