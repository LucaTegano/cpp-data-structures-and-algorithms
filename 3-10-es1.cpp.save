#include <iostream>

// Funzione ausiliaria per verificare se un valore è presente in una porzione di array
// Parametri:
//   arr: l'array in cui cercare
//   valore: il numero da cercare
//   lunghezza: la dimensione della porzione di array da esaminare (da indice 0 a lunghezza-1)
// Ritorna:
//   true se il valore è presente, false altrimenti
bool contiene(const int arr[], int valore, int lunghezza) {
    for (int i = 0; i < lunghezza; ++i) {
        if (arr[i] == valore) {
            return true; // Trovato!
        }
    }
    return false; // Non trovato
}

int main() {
    const int MAX_SIZE = 100;
    int array[MAX_SIZE];
    int lunghezza_originale = 0;
    int numero;

    // 1. Lettura e memorizzazione della sequenza
    std::cout << "Input utente:" << std::endl;
    while (lunghezza_originale < MAX_SIZE && std::cin >> numero && numero != -1) {
        array[lunghezza_originale] = numero;
        lunghezza_originale++;
    }

    // 2. Compattazione dell'array
    int nuova_lunghezza = 0;
    
    // Scorre ogni elemento dell'array originale
    for (int i = 0; i < lunghezza_originale; ++i) {
        // Controlla se l'elemento corrente (array[i]) è già stato aggiunto
        // alla parte compattata dell'array (che va da 0 a nuova_lunghezza-1)
        if (!contiene(array, array[i], nuova_lunghezza)) {
            // Se non è presente, è un elemento unico (il primo che incontriamo)
            // Lo aggiungiamo alla fine della parte compattata
            array[nuova_lunghezza] = array[i];
            nuova_lunghezza++;
        }
    }

    // 3. Stampa dei risultati
    std::cout << "\nL'array compattato e':" << std::endl;
    for (int i = 0; i < nuova_lunghezza; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "La nuova lunghezza dell'array e': " << nuova_lunghezza << std::endl;

    return 0;
}
