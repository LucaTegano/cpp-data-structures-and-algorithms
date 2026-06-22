#include "grafoPesato.hpp"
#include <iostream>
#include <vector>

using namespace std;


int sceltaGolosa(const GrafoPesato& g, int nodo_corrente, const vector<bool>& visitati) {
    int costo_min = INT16_MAX;
    int nodo_min = -1;

    // tra i nodi adiacenti a nodo_corrente, 
    // prendo quello il cui arco ha costo minimo
    for (int i=0; i<g.n(); ++i) {
        if (!visitati[i] && g(nodo_corrente, i) && g.w(nodo_corrente, i) < costo_min) {
            costo_min = g.w(nodo_corrente, i);
            nodo_min = i;
        }
    }

    return nodo_min;
}


vector<int> calcolaCammino(const GrafoPesato& g, int i, int j) {
    vector<int> cammino = {i};

    // per evitare cicli
    vector<bool> visitati(g.n(), false);
    visitati[i] = true;

    int nodo_corrente = i;
    int prossimo_nodo;
    while (nodo_corrente != j) {
        prossimo_nodo = sceltaGolosa(g, nodo_corrente, visitati); 
        
        // se non è stato trovato alcun cammino
        if (prossimo_nodo == -1)
            return vector<int>();   
        
        // altrimenti, aggiorno il cammino e proseguo
        cammino.push_back(prossimo_nodo);
        visitati[prossimo_nodo] = true;
        nodo_corrente = prossimo_nodo;
    }

    return cammino;
}


int main() {
    //NON GARANTISCE SOLUZIONE OTTIMA
    //NON GARANTISCE NEMMENO UNA SOLUZIONE AMMISSIBILE
    //NON E' POSSIBILE FARE UN ORDINAMENTO A PRIORI PERCHE' I COSTI VARIANO IN BASE ALLE SCELTE PRECEDENTI

    /*ESEMPIO IN CUI NON TROVA L'OTTIMO
    GrafoPesato g(4);
    g(0,1,true,7);
    g(0,2,true,3);
    g(2,3,true,10);
    g(1,3,true,2);
    cammino 0->3
    */

    /* ESEMPIO IN CUI TROVA L'OTTIMO
    GrafoPesato g(4);
	g(0,1,true,7);
	g(0,2,true,3);
	g(1,3,true,4);
	g(2,3,true,9);
    cammino 0->3
    */

    /*ESEMPIO IN CUI NON TROVA UNA SOL AMMISSIBILE
    GrafoPesato g(4);
    g(0,1,true,7);
    g(0,2,true,3);
    g(1,3,true,2);
    cammino 0->3
    */

    GrafoPesato g(4);
	g(0,1,true,7);
	g(0,2,true,3);
	g(1,3,true,4);
	g(2,3,true,9);

	int i, j; 
	cout << "DA: "; cin >> i;
	cout << "A: "; cin >> j;

    vector<int> cammino = calcolaCammino(g, i, j);

    if (cammino.empty())
        cout << "Non è stato possibile trovare un cammino" << endl;
    else {
        // stampo il cammino e il suo costo
        int costo=0;
        for (int k=0; k<g.n()-1; ++k) {
            cout << cammino[k] << ' ';
            costo += g.w(cammino[k], cammino[k+1]);
        }
        cout << endl << "Costo: " << costo << endl;
    }

    return 0;
}