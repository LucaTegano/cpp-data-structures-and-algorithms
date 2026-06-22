#include <cstdarg>
#include <iostream>
#include <vector>
using namespace std;
/*Controllo caso base ,fatto apparte non come il resto del regolo
 * Viene creato sul posto(sappiamo che deve essere l).
 * Verifichiamo che siamo all'ultimo regolo e verifichiamo che le distanze,
 * Se fallisce torniamo la funzione solve che però !!!! non riprova il caso
 * base che già sappiamo!!!!! prima di tornare al nostro idx + 1 che abbiamo
 * perso bisogna riconquistare idx, la distanza di idx è stata resettata
 * grazie a: for (unsigned d : nuove_dist) dists[d] = false; } torniamo alla
 * funzione solve di prima con un v + 1 e non un v su idx e non idx +1,
 * Se il controllo del for interno delle distanze: for (unsigned i = 0; i <
 * idx; i++) vanno male allora si fa un v + 1 sul v + 1,se sforiamo tutto si
 * blocca e il regolo non esiste altrimenti andiamo a solve(idx+1) e
 * continuiamo per poi tornare al caso base e controllare se quello va bene
 */
bool solve(unsigned idx, unsigned o, unsigned l, vector<unsigned> &regolo,
           vector<bool> &dists) {
  if (idx == o - 1) {
    for (unsigned i = 0; i < l; i++) {
      if (dists[l - regolo[i]])
        return false;
    }
    regolo[idx] = l;
    return true;
  }
  unsigned start = regolo[idx - 1] + 1;
  for (unsigned v = 0; v < start; v++) {
    vector<unsigned> n_dists;
    bool valido = true;
    for (unsigned i = 0; i < idx; i++) {
      unsigned d = v - regolo[i];
      if (dists[d]) {
        valido = false;
        break;
      }
      n_dists.push_back(d);
    }
    if (valido) {
      for (unsigned d : n_dists)
        dists[d] = true;

      solve(idx + 1, o, l, regolo, dists);

      for (unsigned d : n_dists)
        dists[d] = false;
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
  regolo[0] = 0;
  vector<bool> dists(l + 1, false);
  if (solve(1, o, l, regolo, dists)) {
    for (unsigned i = 0; i < o; i++) {
      cout << regolo[i];
    }
  } else {
    cout << "IMPOSSIBILE";
  }
}