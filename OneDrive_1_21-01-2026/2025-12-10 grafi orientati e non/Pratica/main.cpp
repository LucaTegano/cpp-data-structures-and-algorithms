#include "GrafoNonOrientato.h"

#include <iostream>

#include <queue>
#include <climits>
using namespace std;
 
using CoppiaNodi = pair<int, int>;

void stampaGrafo(const Grafo& g);
int getNodoConGradoMassimo(const GrafoNonOrientato& g);
bool stessoNumeroNodiStessoGrado (const GrafoNonOrientato& g1, const GrafoNonOrientato& g2);
bool almenoUnNodoAdiacenteATutti(const GrafoNonOrientato& g);
CoppiaNodi getCoppiaConPiuAdiacenti(const GrafoNonOrientato& g);

bool connesso(const GrafoNonOrientato& g);
bool inUnCiclo(const Grafo& g, int nodo);
bool proprieta_1(const Grafo& g, int k);
bool proprieta_2(const Grafo& g, vector<int> pesi);
bool sotto_proprieta(int nodo, const Grafo& g, vector<int> pesi);

int main(){

	return 0;
}

//stampa le informazioni del grafo g
void stampaGrafo(const Grafo& g){

	cout << "Numero nodi: " << g.n() << endl;
	cout << "Numero archi: " << g.m() << endl;

	for (int i = 0; i < g.n(); i++)
		for (int j = 0; j < g.n(); j++)
			if (g(i,j))
				cout << "Arco: " << i << " -> " << j << endl;

}

//restituisce il nodo avente grado massimo all'interno di g
int getNodoConGradoMassimo(const GrafoNonOrientato& g){
	int grado_max = -1;
	int nodo_con_grado_max = -1;

	for (int nodo = 0; nodo < g.n(); nodo++)
	{
		int grado = 0;
		for (int i = 0; i < g.n(); i++)
			if (g(nodo,i) && i != nodo)
				grado++;

		if (grado > grado_max)
		{
			grado_max = grado;
			nodo_con_grado_max = nodo;
		}
	}

	return nodo_con_grado_max;
}

//restituisce true se e solo se per ogni 0<=i<=g.n()-1 vale che g1 e g2 hanno lo stesso numero di nodi aventi grado i
bool stessoNumeroNodiStessoGrado (const GrafoNonOrientato& g1, const GrafoNonOrientato& g2){
	if (g1.n() != g2.n()) return false;

	int num_nodi_per_grado[g1.n()] {0};

	//per ogni nodo v in g1, calcolo grado(v) ed eseguo num_nodi_per_grado[grado(v)] ++
	for (int nodo = 0; nodo < g1.n(); nodo++)
	{
		int count = 0;
		for (int j = 0; j < g1.n(); j++)
		{
			if (g1(nodo,j))
				count ++; 
		}

		num_nodi_per_grado[count] ++;
	}

	//per ogni nodo v in g2, calcolo grado(v) ed eseguo num_nodi_per_grado[grado(v)] --
	for (int nodo = 0; nodo < g2.n(); nodo++)
	{
		int count = 0;
		for (int j = 0; j < g2.n(); j++)
		{
			if (g2(nodo,j))
				count ++; 
		}

		num_nodi_per_grado[count] --;
	}

	// return true se e solo se num_nodi_per_grado = {0}
	for (int i = 0; i < g1.n(); i++)
		if (num_nodi_per_grado[i] != 0)
			return false;

	return true;
}

//restituisce true se e solo se esiste almeno un nodo in g che sia adiacente a tutti gli altri
bool almenoUnNodoAdiacenteATutti(const GrafoNonOrientato& g){
	for (int nodo = 0; nodo < g.n(); nodo++ ){
		
		bool adiacenteATutti = true;
		
		for (int i = 0; i < g.n() && adiacenteATutti; i++ )
			if (!g(nodo,i) && i != nodo )
				adiacenteATutti = false;
		

		if (adiacenteATutti)
			return true;
	}
	return false;
}

//restituisce la coppia di nodi (i,j) che abbiano più nodi adiacenti in comune nel grafo g
CoppiaNodi getCoppiaConPiuAdiacenti(const GrafoNonOrientato& g){

	CoppiaNodi coppiaPiuAdiacenti; 
	int max_num_adiacenti = -1;

	//per ogni coppia conto il numero di adiacenti e, se maggiore del massimo corrente, aggiorno il massimo e la coppia
	for (int nodo_1 = 0; nodo_1 < g.n() - 1; nodo_1++)	
		for (int nodo_2 = nodo_1 + 1; nodo_2 < g.n(); nodo_2++){
			
			int count_adiacenti = 0;

			for (int i = 0; i < g.n(); i++)
				if (i != nodo_1 && i != nodo_2 && g(nodo_1,i) && g(nodo_2,i))
					count_adiacenti++;

			if (count_adiacenti > max_num_adiacenti){
				max_num_adiacenti = count_adiacenti;
				coppiaPiuAdiacenti.first = nodo_1;
				coppiaPiuAdiacenti.second = nodo_2;
			}
		}
	return coppiaPiuAdiacenti;
	
}

//restituisce true se e solo se g è connesso (partendo da un qualsiasi nodo riesco a visitare tutti i restanti)
bool connesso(const GrafoNonOrientato& g){

	// visitati[i] == true se il nodo i è stato visitato a partire da s
    vector<bool> visitati(g.n(), false);

      
    // coda per la bfs
    queue<unsigned> q;
    
    // step 1: parto dal nodo 0 (va bene uno qualsiasi), lo inserisco nella coda e lo segno come visitato
    q.push(0);
    visitati[0] = true;
    int nodi_raggiunti = 1; // inizio avendo raggiunto solo il nodo di partenza

    // itero fin quando la coda non è vuota
    while (!q.empty()) {
        // step 2: estraggo il nodo in testa alla coda
        unsigned u = q.front();
        q.pop();

        // step 3: itero sui nodi adiacenti di u e inserisco nella 
		// coda quelli non visitati, contandone il numero
        for (unsigned v = 0; v < g.n(); ++v)
            if (g(u,v) && u != v && !visitati[v]) {
                q.push(v);
                visitati[v] = true;
                nodi_raggiunti++;
            }
    }

    //return true se e solo se raggiungo tutti i nodi
    return nodi_raggiunti == g.n();
}

//Controlla se il nodo "nodo" si trova all'interno di un ciclo in g
//Si noti che, rispetto alla BFS classica, il nodo di partenza non è etichettato come visitato in modo da non dover variare il primo if all'interno del for
bool inUnCiclo(const Grafo& g, int nodo){
	// visitati[i] == true se il nodo i è stato visitato a partire da s
    vector<bool> visitati(g.n(), false);

      
    // coda per la bfs
    queue<unsigned> q;
    
    // step 1: parto dal nodo 0, lo inserisco nella coda e lo segno come visitato
    q.push(nodo);

    // itero fin quando la coda non è vuota
    while (!q.empty()) {
        // step 2: estraggo il nodo in testa alla coda
        unsigned u = q.front();
        q.pop();

        // step 3: itero sui nodi adiacenti di u e inserisco nella 
		// coda quelli non visitati, contandone il numero
        for (unsigned v = 0; v < g.n(); ++v)
            if (g(u,v) && u != v && !visitati[v]) {
                q.push(v);
                visitati[v] = true;

                if(v == nodo)
                	return true;
            }
    }
    
    return false;
}

//Se, in un grafo orientato G(V,E), il numero di coppie di nodi <vi, vj> (con vi, vj ∈ V e vi ≠ vj) che hanno almeno un nodo adiacente in comune, 
//è maggiore o uguale ad un dato valore costante k (intero positivo), diciamo che G verifica la proprietà Adk.  
//Definire una funzione che, ricevuti in input un grafo G(V,E) ed un valore intero k,  restituisca true se G verifica la proprietà Adk, false altrimenti.
//Si noti che la coppia (i,j) e la coppia (j,i) vanno considerate uguali e dunque contate una sola volta
bool proprieta_1(const Grafo& g, int k){

	int num_coppie_valide = 0;
	for (int i = 0; i < g.n() - 1; i++)
		for (int j = i + 1; j < g.n(); j++){
			bool coppia_valida = false;
			for (int k = 0; k < g.n() && !coppia_valida; k++)
				if (k != i && k != j && g(i,k) && g(j,k))
					coppia_valida = true;

			
			if (coppia_valida)
				num_coppie_valide++;
		}
	return num_coppie_valide >= k; 
}
//X CASA
//Siano dati in input un grafo orientato G(V,E)  ed un vettore di interi positivi P di dimensione pari al numero di nodi di G. Supponendo che ad ogni nodo
//v ∈ V sia associato un peso dato da P[v], scrivere una funzione che verifichi se il grafo G soddisfa o meno la seguente proprietà: 
//per ogni nodo v ∈ V il peso di v moltiplicato per il numero di nodi adiacenti a v è maggiore o uguale alla somma dei pesi dei nodi adiacenti a v.

bool proprieta_2(const Grafo& g, vector<int> pesi)
{
	for (int nodo = 0; nodo < g.n(); nodo++)
		if (!sotto_proprieta(nodo, g, pesi))
			return false;
	return true;
}

bool sotto_proprieta(int nodo, const Grafo& g, vector<int> pesi)
{
	int num_adiacenti = 0;
	int somma_pesi = 0;

	for (int i = 0; i < g.n(); i++)
		if (i != nodo && g(nodo,i))
		{
			num_adiacenti++;
			somma_pesi += pesi[i];
		}
	return pesi[nodo] * num_adiacenti >= somma_pesi;	
}
