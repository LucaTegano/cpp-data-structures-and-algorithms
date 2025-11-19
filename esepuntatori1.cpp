#include <iostream>

using namespace std;

// Dimensione fissa dell'array: 10
const int DIMENSIONE = 10;
const int META = DIMENSIONE / 2;

/**
 * @brief Verifica se le due metà dell'array sono identiche usando l'aritmetica dei puntatori.
 * @param arr Puntatore all'inizio dell'array.
 * @return true se uguali, false altrimenti.
 */
bool verifica_meta_uguali(const int* arr) {
    // 1. Definiamo i puntatori
    const int* p_prima_meta = arr;          // Inizia all'indirizzo 0
    const int* p_seconda_meta = arr + META; // Inizia all'indirizzo META (es. 5)

    // 2. Iteriamo per la lunghezza di una metà (5 volte)
    for (int i = 0; i < META; ++i) {
        
        // Aritmetica dei puntatori per accedere agli elementi
        int val_prima = *(p_prima_meta + i);
        int val_seconda = *(p_seconda_meta + i);
        
        // Confronto
        if (val_prima != val_seconda) {
            return false; // Trovata una differenza
        }
    }
    
    return true; // Tutte le coppie sono uguali
}


int main() {
    int mio_array[DIMENSIONE];
    
    cout << "Inserisci 10 numeri interi." << endl;

    // --- INPUT UTILIZZANDO L'ARITMETICA DEI PUNTATORI ---
    for (int i = 0; i < DIMENSIONE; ++i) {
        cout << "Elemento " << i + 1 << ": ";
        // Uso di *(mio_array + i) invece di mio_array[i]
        cin >> *(mio_array + i); 
    }

    // --- ESECUZIONE DELLA VERIFICA ---
    bool sono_uguali = verifica_meta_uguali(mio_array);

    cout << "\n--- Risultato ---" << endl;
    
    // Stampa dell'array (opzionale, per verifica visiva)
    cout << "Array: [ ";
    for (int i = 0; i < DIMENSIONE; ++i) {
        cout << *(mio_array + i) << (i == DIMENSIONE - 1 ? "" : " ");
    }
    cout << " ]" << endl;

    // Stampa del risultato finale
    if (sono_uguali) {
        cout << "CONGRATULAZIONI: Le due metà sono identiche (Es. 12345 | 12345)." << endl;
    } else {
        cout << "VERIFICA FALLITA: Le due metà NON sono identiche." << endl;
    }

    return 0;
}
