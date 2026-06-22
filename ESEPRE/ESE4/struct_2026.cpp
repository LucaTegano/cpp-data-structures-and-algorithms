#include <iostream>
#include <vector>

using namespace std;

/*
 * ESERCIZIO 4: Il Regolo di Golomb
 * 
 * Versione che utilizza una struct come contenitore dei dati, 
 * seguendo lo schema dell'esempio del dormitorio.
 */

struct DatiGolomb {
    unsigned o;              // Ordine (numero di tacche)
    unsigned l;              // Lunghezza (massima distanza)
    vector<unsigned> regolo; // Posizioni delle tacche
    vector<bool> dists;      // Supporto per il controllo delle distanze
};

// Funzione ricorsiva di backtracking che opera sulla struct
bool solve(unsigned idx, DatiGolomb& d) {
    // Caso base: posizionamento dell'ultima tacca (deve essere l)
    if (idx == d.o - 1) {
        for (unsigned i = 0; i < idx; ++i) {
            if (d.dists[d.l - d.regolo[i]]) return false;
        }
        d.regolo[idx] = d.l;
        return true;
    }

    // Ricerca delle posizioni valide per la tacca corrente
    unsigned start = d.regolo[idx - 1] + 1;
    for (unsigned v = start; v < d.l; ++v) {
        vector<unsigned> nuove_dist;
        bool valido = true;

        for (unsigned i = 0; i < idx; ++i) {
            unsigned dist = v - d.regolo[i];
            if (d.dists[dist]) {
                valido = false;
                break;
            }
            nuove_dist.push_back(dist);
        }

        if (valido) {
            d.regolo[idx] = v;
            for (unsigned ds : nuove_dist) d.dists[ds] = true;

            if (solve(idx + 1, d)) return true;

            // Backtracking
            for (unsigned ds : nuove_dist) d.dists[ds] = false;
        }
    }
    return false;
}

// Funzione principale che riceve la struct in input
bool esercizio4(DatiGolomb& d) {
    if (d.o == 0) return false;
    
    // Inizializzazione dei vettori interni alla struct
    d.regolo.assign(d.o, 0);
    d.dists.assign(d.l + 1, false);
    d.regolo[0] = 0;

    // Caso speciale ordine 1
    if (d.o == 1) {
        return (d.l == 0);
    }

    return solve(1, d);
}

// Esempio di utilizzo (opzionale, per chiarezza)
/*
int main() {
    DatiGolomb d = {4, 6, {}, {}};
    if (esercizio4(d)) {
        for (unsigned x : d.regolo) cout << x << " ";
        cout << endl;
    } else {
        cout << "IMPOSSIBILE" << endl;
    }
    return 0;
}
*/