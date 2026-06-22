/*
Esercizio 5: Unisci Due Liste e Ordina
Dati due elenchi ordinati di numeri interi, uniscili in una singola lista ordinata. Le due liste di partenza possono essere, ad esempio, {1, 3, 5, 7} e {8, 2, 4, 6}. La lista finale deve essere ordinata senza utilizzare std::sort direttamente sulla lista unita.
*/

#include <iostream>
#include <list>

using namespace std;

void bubbleSortList(list<int>& lst) {
    bool swapped;
    do {
        swapped = false;
        for (auto it1 = lst.begin(); it1 != lst.end(); ++it1) {
            auto it2 = it1;
            ++it2;  // Avanza al successivo manualmente
            
            // Controlla se it2 è valido (fine della lista)
            if (it2 != lst.end() && *it1 > *it2) {
                int temp = *it1;
                *it1 = *it2;
                *it2 = temp;
                swapped = true;
            }
        }
    } while (swapped);  // Continua finché ci sono scambi
}

int main() {
    list<int> list1 = {1, 3, 5, 7};
    list<int> list2 = {8, 2, 4, 6};

    list1.merge(list2);
    bubbleSortList(list1);
    cout << "Lista unita ";
    for (int num : list1) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}