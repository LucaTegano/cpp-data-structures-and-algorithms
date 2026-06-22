#include<iostream>
#include<vector>
#include<cstdlib>
using namespace std;
const unsigned regine = 4;
const unsigned MAX_VAL = regine - 1;
const unsigned MIN_VAL = 0;
// La mia soluzione è rappresentata dall'insieme delle colonne su cui posiziono le regine
// in questa soluzione, la corrispondenza fra regina e riga è implicita la regina I verrà posizionata sempre sulla riga I-esima.
// l'indice I del vettore Solution corrisoponde alla regina I posizionata sulla riga Iesima, mentre il valore Solution[I] corrisponde alla
// colonna C sulla quale la regina I è posizionata.
// es: Solution[3]=5, indica che la regina numero 3 è posizionata alla riga 3, colonna 5.
using Solution = vector<unsigned>;


bool isComplete(const Solution& sol) {
    cout << "Verifico se la soluzione è completa:" << (sol.size() == regine) << endl;
    return sol.size() == regine;
}

void add(unsigned colonna, Solution& sol) {
    cout << "Aggiorno la soluzione corrente. Aggiungo la regina "<<sol.size()<<" alla colonna: "<<colonna<<endl;
    sol.push_back(colonna);
}

bool canAdd(unsigned colonna, const Solution& sol) {
    unsigned rigaDaRiempire = sol.size();

    cout << "nella riga " << rigaDaRiempire << " provo con la regina in colonna" << colonna << endl;
    //verifico che non si attacchi con le altre
    for (unsigned i = 0; i < rigaDaRiempire; i++) {
        //se nelle righe precedenti ho già messo una regina su quella colonna allora
        if (sol[i] == colonna) {
            cout<<"non posso procedere perchè c'è già la regina"<<i<<" su questa colonna"<<endl;
            //due regine nella stessa colonna
            return false;
        }
        if (std::abs(static_cast<int>(i) - static_cast<int>(rigaDaRiempire))
            == std::abs(static_cast<int>(sol[i]) - static_cast<int>(colonna))) {
            //due regine in diagonale
            cout<<"non posso procedere perchè c'è già la regina"<<i<<" su questa diagonale"<<endl;
            return false;
        }
    }
    cout<<"ok, posso aggiungerla"<<endl;
    return true;
}

unsigned next(unsigned colonna) {
    cout<<"provo con la colonna "<<colonna+1<<endl;
    return colonna + 1;
}

bool isEmpty(const Solution& sol) {
    return sol.empty();
}

void remove(unsigned& colonna, Solution& sol) {
    colonna = sol.back();
    sol.pop_back();
    cout << "rimuovo la regina nella colonna " << colonna << " della riga " << sol.size() << endl;
}

bool solve(Solution& sol) {
    unsigned x = MIN_VAL; //uso x per iterare sulle colonne
    bool stop = false, existsSolution = false;
    while (!stop) {
        if (x <= MAX_VAL)
            if (canAdd(x, sol)) {
                cout << "aggiungo la regina nella colonna" << x << "della riga" << sol.size() << endl;
                add(x, sol); // aggiungi x in coda a sol
                if (isComplete(sol)) {
                    existsSolution = true;
                    stop = true;
                } else x = MIN_VAL;
                //azzero la colonna per ripartire dalla 0 e sfruttare qualche colonna che non ho potuto usare in precedenza
            } else x = next(x); //se non posso aggiungerla provo con una nuova colonna
        else {
            // se non ho più colonne disponibili allora non ho trovato una soluzione oppure ho percorso un ramo sbagliato
            if (isEmpty(sol)) {
                //se la soluzione è vuota vuol dire che le ho provate tutte e nessuna andava bene
                existsSolution = false;
                stop = true;
            } else {
                remove(x, sol); //rimuovo l'ultima colonna inserita e torno indietro
                x = next(x); //backtrack
            }
        }
    }
    return existsSolution;
}

//VERSIONE RICORSIVA
// List sol = {};
//
bool solverec(Solution& sol) {
    unsigned x = MIN_VAL;
    while (x <= MAX_VAL)
        if (canAdd(x, sol)) {
            add(x, sol); //aggiungi x in coda a sol
            if (isComplete(sol)) return true;
            else if (solve(sol))
                return true;
            remove(x, sol);
            x = next(x); //backtrack
        } else
            x = next(x);
    return false;
}


int main() {
    //Non 3-colorable

    Solution sol;
    if (solve(sol)) {
        cout << "regine in posizione: " << endl;
        for (int i = 0; i < sol.size(); i++)
            cout << i << " , " << sol[i] << endl;
    } else cout << "non ho trovato una soluzione " << endl;


    cout << "*****************" << endl;
    Solution solrec;
    if (solverec(solrec)) {
        cout << "regine in posizione: " << endl;
        for (int i = 0; i < sol.size(); i++)
            cout << i << " , " << sol[i] << endl;
    } else cout << "non ho trovato una soluzione " << endl;
}
