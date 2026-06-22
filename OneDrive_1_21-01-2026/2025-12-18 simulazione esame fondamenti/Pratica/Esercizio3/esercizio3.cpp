#include "Grafo.h"
#include <vector>

using namespace std;


bool f(const Grafo& g) {
    vector<int> grado_uscente(g.n());
    vector<int> grado_entrante(g.n());

    int count_archi=0;

    for (int i=0; i<g.n(); ++i)
        for (int j=0; j<g.n(); ++j) {
            if (g(i, j)) {  
                if (i==j) return false; // CODIZIONE 3: g NON ha autoarchi
                grado_entrante[j]++;    // punto 1
                grado_uscente[i]++;     // punto 1
                count_archi++;          // punto 2
            }
        }
    

    // CONDIZIONE 2. Il numero totale di archi di g è pari
    if (count_archi%2!=0)
        return false;


    // CONDIZIONE 1. il grado uscente di ogni nodo di g è minore del numero di nodi di g che hanno al più un arco entrante
    // conto nodi con al più un arco entrante
    int count_max_uno_entrante=0;
    for (int i=0; i<g.n(); ++i)
        if (grado_entrante[i]<=1)
            count_max_uno_entrante++;
    // controllo che non esista nodo con grado uscente > # nodi con max 1 entrante
    for (int i=0; i<g.n(); ++i)
        if (grado_uscente[i] > count_max_uno_entrante)
            return false;


    return true;      
}

