/*
 * ============================================================================
 *  ESERCIZIO 2 (ESEMPIO DATO): Reference, dangling reference, puntatori alias
 * ============================================================================
 *  Matricola esempio: {1, 2, 3, 4, 5, 6}
 */

#include <iostream>
using namespace std;

void f(int& a) {
    if (a % 2 == 0) a++;     // se pari → incrementa
    else a -= 2;              // se dispari → sottrai 2
}

int& g(int& a) {
    int b = a;    // b è una COPIA LOCALE di a
    return b;     // ⚠️ RITORNA REFERENCE A VARIABILE LOCALE!
    // b viene distrutta all'uscita di g → DANGLING REFERENCE
}

int main() {
    int* matricola = new int[6]{1, 2, 3, 4, 5, 6};

    // =====================================================================
    // DOMANDA 1: f(g(matricola[2])) e poi cout << matricola[2]
    //            È corretta? Cosa stampa?
    // =====================================================================
    /*
     * RISPOSTA: Il codice ha UNDEFINED BEHAVIOR.
     *
     * ANALISI STEP-BY-STEP:
     *
     * 1) g(matricola[2]) viene chiamata:
     *    - a è un reference a matricola[2] = 3
     *    - int b = a → b = 3 (COPIA locale)
     *    - return b → ritorna un REFERENCE a b
     *    - MA: b è una variabile LOCALE → viene distrutta qui!
     *    - Il reference ritornato punta a MEMORIA INVALIDA!
     *    → DANGLING REFERENCE!
     *
     * 2) f(g(matricola[2])):
     *    - f riceve un int& che punta a memoria invalidata
     *    - Qualsiasi operazione su quel reference è UNDEFINED BEHAVIOR
     *
     * 3) cout << matricola[2]:
     *    - matricola[2] NON è mai stato modificato (b era una copia!)
     *    - Se lo stampasse, stamperebbe ancora 3
     *    - MA il UB precedente potrebbe corrompere qualsiasi cosa
     *
     * NOTA ESAME: La risposta corretta è:
     *   "g() ritorna un dangling reference (reference a variabile locale).
     *    Il comportamento è indefinito."
     *
     * Il compilatore spesso dà un WARNING:
     *   "warning: reference to local variable 'b' returned"
     */
    // f(g(matricola[2]));  // ⚠️ UNDEFINED BEHAVIOR — decommentare a proprio rischio
    // cout << matricola[2] << endl;
    cout << "Domanda 1: UNDEFINED BEHAVIOR (dangling reference da g())" << endl;
    cout << "  matricola[2] = " << matricola[2] << " (non modificato, b era copia)" << endl;

    // =====================================================================
    // DOMANDA 2: Puntatori che diventano alias
    // =====================================================================
    /*
     * ANALISI STEP-BY-STEP:
     *
     * Stato iniziale: matricola = {1, 2, 3, 4, 5, 6}
     *                  indici:     0  1  2  3  4  5
     *
     * int* p = matricola + 4;   → p punta a matricola[4] = 5
     * int* q = matricola + 3;   → q punta a matricola[3] = 4
     *
     * p = q;   → p ora punta DOVE punta q → p punta a matricola[3]
     *            ⚠️ p NON punta più a matricola[4]!
     *
     * q = p;   → q = p → entrambi puntano a matricola[3]
     *            (questa istruzione non cambia nulla, p e q già puntano allo stesso posto)
     *
     * *p = 0;  → matricola[3] = 0   (p punta a matricola[3])
     * *q = 9;  → matricola[3] = 9   (q punta a matricola[3] — SOVRASCRIVE lo 0!)
     *
     * Stato finale: matricola = {1, 2, 3, 9, 5, 6}
     *
     * *(matricola+3) = matricola[3] = 9
     * *(matricola+4) = matricola[4] = 5  (MAI MODIFICATO!)
     *
     * STAMPA: 9 5
     *
     * CONCETTO CHIAVE: p = q copia l'INDIRIZZO, non il valore!
     *   Dopo p = q, sia p che q sono ALIAS dello stesso slot di memoria.
     */
    int* p = matricola + 4;
    int* q = matricola + 3;
    p = q;
    q = p;
    *p = 0;
    *q = 9;
    cout << "\nDomanda 2: " << *(matricola + 3) << " " << *(matricola + 4) << endl;
    // Stampa: 9 5

    // Reset per domanda 3
    matricola[3] = 4;  // ripristino

    // =====================================================================
    // DOMANDA 3: cout << matricola[matricola+2] — è corretta?
    // =====================================================================
    /*
     * RISPOSTA: NO, NON è corretta. ERRORE DI COMPILAZIONE.
     *
     * matricola[...] richiede un INDICE INTERO.
     * matricola + 2 è un int* (puntatore), NON un intero!
     *
     * Non si può usare un puntatore come indice di un array.
     *
     * Versioni corrette sarebbero:
     *   - matricola[2]           → accede alla terza posizione (= 3)
     *   - matricola[*(matricola+2)] → matricola[3] = 4 (usa il VALORE)
     *   - *(matricola + 2)       → equivale a matricola[2] = 3
     */
    cout << "\nDomanda 3: ERRORE DI COMPILAZIONE" << endl;
    cout << "  matricola + 2 è un int*, non un int!" << endl;
    cout << "  Versione corretta: matricola[*(matricola+2)] = " 
         << matricola[*(matricola + 2)] << endl;  // matricola[3] = 4

    // =====================================================================
    // DOMANDA 4: Quale operazione per deallocare?
    // =====================================================================
    /*
     * ANALISI di ogni opzione:
     *
     * a) delete[] matricola;    ← ✅ CORRETTA!
     *    Allocato con new int[6] → si dealloca con delete[]
     *
     * b) delete p;              ← ❌ SBAGLIATO!
     *    p punta a matricola[3], che è nel MEZZO dell'array.
     *    Non si può fare delete su un puntatore che non punta
     *    all'inizio di un blocco allocato con new.
     *    Inoltre, p punta dentro un array allocato con new[] →
     *    servirebbe delete[], non delete.
     *
     * c) for(...) delete matricola[i]; ← ❌ SBAGLIATO!
     *    matricola[i] è un int (valore), NON un puntatore!
     *    delete si usa solo su puntatori.
     *    Inoltre, i singoli elementi dell'array non sono stati
     *    allocati separatamente con new.
     *
     * d) delete matricola;      ← ❌ SBAGLIATO!
     *    Allocato con new[] → serve delete[], NON delete!
     *    (usando delete senza [] = UNDEFINED BEHAVIOR)
     *
     * e) delete q;              ← ❌ SBAGLIATO!
     *    Stessa ragione di b): q punta nel mezzo dell'array.
     *
     * RISPOSTA: Solo a) è corretta.
     */
    cout << "\nDomanda 4: Solo a) delete[] matricola; è corretta" << endl;

    delete[] matricola;
    return 0;
}
