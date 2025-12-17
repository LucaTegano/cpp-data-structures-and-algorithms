#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

// Funzione ricorsiva per trovare il sottoinsieme
bool solve(const vector<int>& elements, int index, int currentSum, int target, vector<int>& subset) {
    // Caso base: somma trovata
    if (currentSum == target) {
        return true;
    }
    
    // Caso base: somma ecceduta o fine elementi
    if (currentSum > target || index == elements.size()) {
        return false;
    }

    // Opzione 1: Includi elements[index] nel sottoinsieme corrente
    // Proviamo a prendere il numero e vediamo se porta alla soluzione
    subset.push_back(elements[index]);
    // Chiamata ricorsiva: passiamo al prossimo indice (index + 1) 
    // e aggiorniamo la somma corrente (currentSum + elements[index])
    if (solve(elements, index + 1, currentSum + elements[index], target, subset)) {
        return true; // Se questa strada ha portato al target, ritorniamo true
    }
    
    // BACKTRACKING:
    // Se siamo qui, significa che includere elements[index] non ha portato a una soluzione.
    // Quindi dobbiamo "tornare indietro": rimuoviamo l'elemento dal subset
    // per poter provare l'altra strada (non includerlo).
    subset.pop_back(); 

    // Opzione 2: Non includere elements[index]
    // Proviamo a saltare il numero corrente e cerchiamo di raggiungere il target
    // con i numeri rimanenti.
    if (solve(elements, index + 1, currentSum, target, subset)) {
        return true;
    }

    // Se nessuna delle due opzioni (prenderlo o lasciarlo) ha funzionato, 
    // allora da questo punto non c'è soluzione.
    return false;
}

int main() {
    vector<int> elements;
    int val;

    cout << "Input elementi (termina con -1): ";
    while (cin >> val && val != -1) {
        if (val >= 0) {
            elements.push_back(val);
        }
    }

    int target;
    cout << "Somma target: ";
    if (!(cin >> target)) {
        cout << "Input target non valido." << endl;
        return 0;
    }

    vector<int> subset;
    if (solve(elements, 0, 0, target, subset)) {
        cout << "Sottoinsieme trovato: [";
        for (size_t i = 0; i < subset.size(); ++i) {
            cout << subset[i] << (i < subset.size() - 1 ? ", " : "");
        }
        cout << "]" << endl;
    } else {
        cout << "nessuna soluzione" << endl;
    }

    return 0;
}
