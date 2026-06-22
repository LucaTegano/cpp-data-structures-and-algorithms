#include <iostream>
#include <vector>
using namespace std;

// KISS = Keep It Simple, S...

// sol = array di indici dei valori in S
// esempio: S = [4, 12, 3, 88, 192], W = 207
// la sol sarà un array contenenti gli indici, es: sol = [1,2,4] => somma(S[1], S[2], S[4])

//ottimizzazioni da discutere: 
//1. evitare il ricalcolo della somma corrente, 
//2. passare alla solve l'indice x di partenza invece di ripartire da 0 (chiamando la solve dal main con x=0 e chiamando la sole ricorsivamente con x=x+1)

struct Soluzione {
    vector<int> sol; // soluzione
    vector<int> elementi;   // vector dato in input
    int somma_target;           // costante data in input

    Soluzione(vector<int>& el, int st) : elementi(el), somma_target(st) {}
};

void add(int x, Soluzione& soluzione) {
    soluzione.sol.push_back(x);
}
void remove(int x, Soluzione& soluzione) {
    // in alcuni casi potrebbe servire sapere la ultima x inserita
    soluzione.sol.pop_back();
}
bool isComplete(Soluzione& soluzione) {
    int sum = 0;
    for (auto i: soluzione.sol)
        sum += soluzione.elementi[i];
    return sum == soluzione.somma_target;
}

bool canAdd(int x, Soluzione& soluzione) {
    // se x è stato già inserito, non posso inserirlo, return false
    for (auto y: soluzione.sol)
        if (x == y)
            return false;
    // se la somma di sol + x > W --> ho sforato, non ha senso continuare ad inserire
    // quindi return false
    int sum = 0;
    for (auto i: soluzione.sol)
        sum += soluzione.elementi[i];
    if (sum + soluzione.elementi[x] > soluzione.somma_target)
        return false;
    
    // se arrivo qui indica che (1) x non è dentro sol e (2) la somma aggiundendo S[x] non sfora
    return true;
}

bool solve(Soluzione& soluzione) {
    int x = 0; //rimuoverlo per ottimizzare e passare x come parametro alla solve
    while (x < soluzione.elementi.size()) {
        if (canAdd(x, soluzione)) {
            add(x, soluzione);
            
            if (isComplete(soluzione))
                return true;
            else if (solve(soluzione)) //solve(soluzione, x+1)
                return true;
            
            remove(x, soluzione);
            x++;
        } else
            x++;
    }
  return false;
}

int main() {
    vector<int> elementi;
    cout << "Inserisci elementi:" << endl;
    int elem; cin >> elem;

    while(elem != -1)
    {
        elementi.push_back(elem);
        cin >> elem;
    }

    cout << "Inserisci target:" << endl;
    int somma_target; cin >> somma_target;

    Soluzione s(elementi, somma_target);
    
    if(solve(s))
        for(auto x: s.sol)
            cout << s.elementi[x] << " ";
    return 0;
}