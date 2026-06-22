/*
Esercizio 4: Rimuovere Duplicati da una Lista
Dato un elenco di numeri interi, alcuni dei quali duplicati, crea una lista e rimuovi tutti i duplicati in modo che ogni numero appaia solo una volta. La lista iniziale può essere, ad esempio, {1, 2, 3, 2, 4, 1, 5, 3, 6}.
*/

#include <iostream>
#include <list>

using namespace std;
int main() {
    list<int> numbers = {1, 2, 3, 2, 4, 1, 5, 3, 6};

    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        auto it_inner = it;
        ++it_inner;  // Avanziamo l'iteratore interno di una posizione per confrontare solo gli elementi successivi

        while (it_inner != numbers.end()) {
            if (*it == *it_inner) {
                it_inner = numbers.erase(it_inner);  // Rimuovi l'elemento duplicato e avanza l'iteratore
            } else {
                ++it_inner;
            }
        }
    }

    // Stampa della lista senza duplicati
    cout << "Lista senza duplicati: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}