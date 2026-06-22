/*
Esercizio 3: Operazioni Avanzate e Utilizzo di Iteratori
Crea una lista di numeri interi casuali tra 1 e 100 (almeno 15 elementi). Stampa la lista, poi rimuovi i numeri inferiori a 50 e ristampala. Usare un iteratore per rimuovere i numeri inferiori a 50, successivamente calcola e stampa la media dei valori rimanenti.
*/

#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>
#include <numeric>

using namespace std;
int main() {
    list<int> numbers;
    srand(time(0));

    for (int i = 0; i < 15; ++i) {
        numbers.push_back(rand() % 100 + 1);
    }

    cout << "Lista originale: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    for (auto it = numbers.begin(); it != numbers.end(); ) {
        if (*it < 50) {
            it = numbers.erase(it);
        } else {
            ++it;
        }
    }

    cout << "Lista con valori >= 50: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // Calcolo della media dei valori rimanenti
    int somma = 0;
    for (int num : numbers) {
        somma += num;
    }
    double media = numbers.empty() ? 0 : static_cast<double>(somma) / numbers.size();

    cout << "Media dei valori rimanenti: " << media << endl;

    return 0;
}