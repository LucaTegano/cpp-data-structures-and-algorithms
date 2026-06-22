/*
Esercizio 6: Invertire l'Ordine di una Lista
Crea una lista di nomi e inverti l'ordine degli elementi. La lista iniziale può essere, ad esempio, { "Anna", "Luca", "Giovanni", "Paola" }. Stampa la lista invertita.
*/

#include <iostream>
#include <list>
#include <string>

using namespace std;

int main() {
    list<string> names = {"Anna", "Luca", "Giovanni", "Paola"};

    names.reverse();

    cout << "Lista invertita: ";
    for (const string& name : names) {
        cout << name << " ";
    }
    cout << endl;

    return 0;
}