#include <iostream>

int main() { 
    int numero;
    int familyCardinality = 0; // Quesito 1: numero di insiemi nella famiglia
    int currentSetSize = 0;    // Dimensione dell'insieme corrente
    int maxSetSize = 0;        // Quesito 2: cardinalità massima trovata finora

    std::cout << "Inserisci la sequenza di interi (terminata da -1, con 0 come separatore):" << std::endl;

    // Legge i numeri in un ciclo finché non incontra -1
    while (std::cin >> numero && numero != -1) {
        
        if (numero == 0) {
            // Lo '0' agisce da separatore, quindi un insieme è terminato.
            
            // 1. Incrementiamo il contatore della famiglia.
            familyCardinality++;

            // 2. Controlliamo se l'insieme appena concluso è il più grande trovato finora.
            if (currentSetSize > maxSetSize) {
                maxSetSize = currentSetSize;
            }

            // 3. Azzzeriamo il contatore per il prossimo insieme.
            currentSetSize = 0;

        } else {
            // Se il numero non è '0', è un elemento dell'insieme corrente.
            // Incrementiamo la dimensione dell'insieme corrente.
            currentSetSize++;
        }
    }

    // --- Stampa dei risultati ---
    
    std::cout << "\n--- Risultati ---" << std::endl;
    std::cout << "1. Cardinalita' della famiglia: " << familyCardinality << std::endl;
    std::cout << "2. Cardinalita' massima degli insiemi: " << maxSetSize << std::endl;

    return 0;
}
