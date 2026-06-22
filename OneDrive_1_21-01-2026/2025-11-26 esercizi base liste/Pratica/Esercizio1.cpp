/*
Esercizio 1: Creazione e Operazioni di Base su std::list
Crea una lista di numeri interi e inserisci i numeri da 1 a 10. Stampa il contenuto della lista usando un ciclo for o un iteratore, rimuovi i numeri pari dalla lista e successivamente ristampa la lista.
*/

#include <iostream>
#include <list>

using namespace std;
int main() {
    list<int> numbers;
    for (int i = 1; i <= 10; ++i) {
        numbers.push_back(i);
    }

    cout << "Contenuto della lista: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // Rimuovi numeri pari
    for (auto it = numbers.begin(); it != numbers.end(); ) {
        if (*it % 2 == 0) {
            it = numbers.erase(it);
        } else {
            ++it;
        }
    }

    cout << "Lista senza numeri pari: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}