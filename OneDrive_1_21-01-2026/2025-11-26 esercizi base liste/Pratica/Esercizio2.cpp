/*
Esercizio 2: Manipolazione della Lista
Dato un elenco di nomi (ad esempio, "Anna", "Luca", "Giovanni", "Paola"), crea una lista di stringhe. Aggiungi un nome all'inizio, uno alla fine e rimuovi un nome specifico (suggerimento: trova nella documentazione come rimuovere un elemento specifico). Successivamente, ordina la lista alfabeticamente e stampa il risultato.
*/

#include <iostream>
#include <list>
#include <string>

using namespace std;
int main() {
    list<string> names = {"Anna", "Luca", "Giovanni", "Paola"};
    names.push_front("Marco");
    names.push_back("Elisa");

    names.remove("Luca");

    cout << "Lista dei nomi: ";
    for (const string& name : names) {
        cout << name << " ";
    }
    cout << endl;

    names.sort();

    cout << "Lista ordinata: ";
    for (const string& name : names) {
        cout << name << " ";
    }
    cout << endl;

    return 0;
}