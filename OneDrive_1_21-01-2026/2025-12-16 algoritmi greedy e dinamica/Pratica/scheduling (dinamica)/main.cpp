#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct Attivita {
    int inizio;  
    int fine;  
    int valore;  

    Attivita(int i, int f, int v): inizio(i), fine(f), valore(v) {}

    bool operator<(const Attivita other) {
        return fine < other.fine;
    }
};


int schedule(const vector<Attivita>& attivita) {
    // NB: attivita deve essere già ordinato per fine crescente

    // 1. calcolo P (precedenti compatibili)
    // p[i] = j significa che il job j è il compatibile più vicino (recente) al job i
    vector<int> p(attivita.size(), -1);
    for (int i=1; i<attivita.size(); ++i)
        for (int j=i-1; j>=0; --j) 
            // appena trovo un'attività precedente (j) che non 
            // si sovrappone a quella corrente (i), ho trovato P(j)
            if (attivita[j].fine <= attivita[i].inizio) {
                p[i] = j;
                break;
            } 

    for (int i=0; i<p.size(); ++i)
        cout << "p(" << i << ") = " << p[i] << endl; 

    // 2. risolvo da 1 a tutti i job
    vector<int> M(attivita.size());  // M[i] = valore max delle prime i macchine compatibili (i.e., non sovrapposte)
    M[0] = attivita[0].valore;  // la prima macchina la prendo da sola
    for (int i=1; i<attivita.size(); ++i) {
        if (p[i] == -1)   // se non c'è uno scheduling precedente ottimo (i.e., un ottimo con meno macchine)
            M[i] = max(attivita[i].valore,  // max tra: singola macchina
                       M[i-1]);             // e sol ottima al passo precedente (con i-1 macchine)
        else {
            M[i] = max(M[p[i]]+attivita[i].valore,  // max tra: sol ottima della macchina comptatibile precedente + valore della macchina corrente
                       M[i-1]);                     // e sol ottima al passo precedente (con i-1 macchine)
        }  
    }
    return M[M.size()-1];
}


int main() {
    vector<Attivita> attivita;
    attivita.push_back(Attivita(3,8,5));
    attivita.push_back(Attivita(7,11,8));
    attivita.push_back(Attivita(0,6,3)); 

    attivita.push_back(Attivita(1,4,1)); 
    attivita.push_back(Attivita(3,5,2)); 
    attivita.push_back(Attivita(4,7,4)); 
    attivita.push_back(Attivita(5,9,6)); 
    attivita.push_back(Attivita(6,10,7));
    
    // ordiniamo per fine attività (crescente)
    sort(attivita.begin(), attivita.end()); 

    cout << "Valore max: " << schedule(attivita) << endl;

    return 0;
}