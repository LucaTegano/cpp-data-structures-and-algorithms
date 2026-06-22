#include<iostream>
using namespace std;
#include "GrafoNonOrientato.h"
const unsigned MAX_VAL =4;
const unsigned MIN_VAL = 0;
using Solution = vector<unsigned>;

bool isComplete(Solution& sol, unsigned k) {
    return sol.size() == k;
}

void add(unsigned node, Solution& sol) {
    sol.push_back(node);
}

bool canAdd(unsigned node, Solution& sol, const GrafoNonOrientato& Map) {
    cout << "provo con il nodo " << node << endl;
    unsigned size = sol.size();
    //esamino i nodi in sol
    for (unsigned i = 0; i < size; i++)
        // e verifico che siano collgati con node, altrimenti return false
        if (!Map(sol[i], node))
            return false;
    return true;
}

unsigned next(unsigned node) {
    return node + 1;
}

bool isEmpty(const Solution& sol) {
    return sol.empty();
}

void remove(unsigned& node, Solution& sol) {
    node = sol.back();
    sol.pop_back();
    cout << "rimuovo " << node << endl;
}

bool solve(Solution& sol, const GrafoNonOrientato& Map, unsigned k) {
    unsigned x = MIN_VAL;
    bool stop = false, existsSolution = false;
    while (!stop) {
        if (x <= MAX_VAL)
            if (canAdd(x, sol, Map)) {
                cout << "aggiungo " << x << "alla solzione" << endl;
                add(x, sol); // aggiungi x in coda a sol
                if (isComplete(sol, k)) {
                    existsSolution = true;
                    stop = true;
                } else x = MIN_VAL;
            } else x = next(x);
        else {
            if (isEmpty(sol)) {
                existsSolution = false;
                stop = true;
            } else {
                remove(x, sol);
                x = next(x); //backtrack
            }
        }
    }
    return existsSolution;
}

/*VERSIONE RICORSIVA
List sol = {};*/
bool solverec(Solution& sol, const GrafoNonOrientato& Map, unsigned k) {
    unsigned x = MIN_VAL;
    while (x <= MAX_VAL)
        if (canAdd(x, sol, Map)) {
            add(x, sol); //aggiungi x in coda a sol
            if (isComplete(sol, k)) return true;
            else if (solve(sol, Map, k)) return true;
            remove(x, sol);
            x = next(x); //backtrack
        } else
            x = next(x);
    return false;
}


int main() {
    /*//3-colorable
       GrafoNonOrientato Map(6);
       Map(0,1,true);
       Map(0,5,true);
       Map(1,2,true);
       Map(1,5,true);
       Map(5,4,true);
       Map(2,4,true);
       Map(2,3,true);
       Map(4,3,true);
*/
    /*//Non 3-colorable
    GrafoNonOrientato Map(7);
    Map(0, 1, true);
    Map(0, 2, true);
    Map(2, 3, true);

    Map(3, 4, true);
    Map(4, 6, true);
    Map(6, 3, true);
    Map(5, 3, true);
    Map(5, 4, true);
    Map(5, 6, true);
*/

    GrafoNonOrientato Map(5);
    Map(0,1,true);
    Map(0,2,true);
    Map(1,2,true);
    Map(2,3,true);
    Map(3,4,true);
    Solution sol;
    if (solve(sol, Map, 2)) {
        cout << "cricca di dimensione " << sol.size() << " composta dai nodi:" << endl;
        for (int i = 0; i < sol.size(); i++)
            cout << sol[i] << " ";
        cout << endl;
    } else cout << "non esiste una cricca della dimensione richiesta " << endl;

    cout<<"****************"<<endl;
    Solution solrec;
    if (solve(solrec, Map, 4)) {
        cout << "cricca di dimensione " << solrec.size() << " composta dai nodi:" << endl;
        for (int i = 0; i < solrec.size(); i++)
            cout << solrec[i] << " ";
        cout << endl;
    } else cout << "non esiste una cricca della dimensione richiesta " << endl;
}
