#include "GestoreComputers.h"
#include <iostream>

#include "Computer.h"

using namespace std;


int main() {
    GestoreComputers gestore;

    gestore.aggiungi(Computer("Computer1", "Produttore1", 1000, Tipo::ULTRABOOK));
    gestore.aggiungi(Computer("Computer2", "Produttore2", 800, Tipo::NETBOOK));
    gestore.aggiungi(Computer("Computer3", "Produttore3", 700, Tipo::NOTEBOOK));
    gestore.aggiungi(Computer("Computer4", "Produttore4", 700, Tipo::ULTRABOOK));
    gestore.aggiungi(Computer("Computer5", "Produttore5", 900, Tipo::NOTEBOOK));
    gestore.aggiungi(Computer("Computer6", "Produttore6", 900, Tipo::NETBOOK));
    gestore.aggiungi(Computer("Computer7", "Produttore7", 1100, Tipo::ULTRABOOK));

    int medianaPrezzo = gestore.metodo2();
    if (medianaPrezzo != -1) {
        cout << "Il prezzo della mediana dei computer è: " << medianaPrezzo << endl;
    } else {
        cout << "Non ci sono computer nel gestore" << endl;
    }

    return 0;
}