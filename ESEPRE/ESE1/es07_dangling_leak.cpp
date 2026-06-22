/*
 * ============================================================================
 *  ESERCIZIO 7: DANGLING POINTERS, MEMORY LEAK, USE-AFTER-FREE
 *               Tutti gli errori di memoria che possono uscire all'esame
 * ============================================================================
 */

#include <iostream>
using namespace std;

// =====================================================================
// Funzione con DANGLING POINTER (ritorna puntatore a variabile locale)
// =====================================================================
int* funzionePericolosa() {
    int locale = 42;
    return &locale;  // ⚠️ locale viene distrutta → puntatore invalido!
}

// =====================================================================
// Funzione con DANGLING REFERENCE
// =====================================================================
int& refPericolosa() {
    int locale = 99;
    return locale;   // ⚠️ ritorna reference a variabile locale!
}

// =====================================================================
// Funzione CORRETTA (alloca in heap → sopravvive alla funzione)
// =====================================================================
int* funzioneCorretta() {
    int* p = new int(42);
    return p;  // ✅ OK! La memoria è nell'heap, sopravvive
}

int main() {

    // =====================================================================
    // DOMANDA 1: Quali di questi sono dangling pointer/reference?
    // =====================================================================
    /*
     * DANGLING POINTER: puntatore che punta a memoria NON più valida.
     * Cause principali:
     *
     * 1) Ritornare &variabile_locale
     *    int* f() { int x = 5; return &x; }    ← x muore, puntatore invalido!
     *
     * 2) Usare un puntatore DOPO delete
     *    int* p = new int(5);
     *    delete p;
     *    cout << *p;    ← USE AFTER FREE! p punta a memoria deallocata!
     *
     * 3) Puntatore a oggetto uscito dallo scope
     *    int* p;
     *    { int x = 5; p = &x; }   ← x muore alla }, p è dangling
     *    cout << *p;               ← DANGLING!
     *
     * MEMORY LEAK: memoria allocata ma MAI deallocata.
     * Cause principali:
     *
     * 1) Dimenticare delete
     *    int* p = new int(5);
     *    return 0;    ← p non viene mai deallocato!
     *
     * 2) Sovrascrivere il puntatore
     *    int* p = new int(5);
     *    p = new int(10);   ← il primo int(5) è perso! Memory leak!
     *
     * 3) Eccezione non gestita
     *    int* p = new int(5);
     *    funzione_che_lancia_eccezione();  ← se lancia, delete mai eseguito
     *    delete p;
     */
    cout << "=== DOMANDA 1: Tipi di errori di memoria ===" << endl;

    // Caso 1: Dangling pointer da funzione
    // int* dp = funzionePericolosa();  // ⚠️ dp è dangling!
    // cout << *dp;  // ← UNDEFINED BEHAVIOR
    cout << "funzionePericolosa() → DANGLING POINTER (variabile locale)" << endl;

    // Caso 2: Dangling reference
    // int& dr = refPericolosa();  // ⚠️ dr è dangling reference!
    // cout << dr;  // ← UNDEFINED BEHAVIOR
    cout << "refPericolosa()      → DANGLING REFERENCE (variabile locale)" << endl;

    // Caso 3: Corretto
    int* corretto = funzioneCorretta();
    cout << "funzioneCorretta()   → " << *corretto << " (OK, heap)" << endl;
    delete corretto;

    // =====================================================================
    // DOMANDA 2: Dove sono gli errori in questo codice?
    // =====================================================================
    /*
     * CODICE:
     *   int* a = new int(1);
     *   int* b = new int(2);
     *   int* c = new int(3);
     *   
     *   a = b;           // ← ERRORE 1: Memory Leak! int(1) perso!
     *   delete b;        // ← Dealloca int(2). Ma a punta allo stesso posto!
     *   cout << *a;      // ← ERRORE 2: USE AFTER FREE! a punta a memoria deallocata!
     *   delete a;        // ← ERRORE 3: DOUBLE FREE! a e b puntavano allo stesso blocco!
     *   *c = *a;         // ← ERRORE 4: a è già stato deallocato!
     *   delete c;        // ← Questa sarebbe ok di per sé
     *
     * ERRORI TOTALI:
     *   1. Memory leak di int(1)
     *   2. Use-after-free su *a
     *   3. Double free su a (già deallocato con b)
     *   4. Lettura di *a dopo double free
     */
    cout << "\n=== DOMANDA 2: Trova gli errori ===" << endl;
    cout << "Errore 1: a=b causa memory leak di int(1)" << endl;
    cout << "Errore 2: *a dopo delete b → use-after-free" << endl;
    cout << "Errore 3: delete a dopo delete b → double free" << endl;
    cout << "Errore 4: *a già invalidato" << endl;

    // =====================================================================
    // DOMANDA 3: Scope e dangling — cosa stampa?
    // =====================================================================
    /*
     * int* ptr;
     * {
     *     int x = 100;
     *     ptr = &x;
     *     cout << *ptr;   // ✅ OK: stampa 100 (x è ancora viva)
     * }
     * // qui x è stata distrutta!
     * cout << *ptr;       // ⚠️ DANGLING! x non esiste più
     *
     * NOTA: potrebbe SEMBRARE funzionare (stampare 100) perché la
     * memoria non viene subito sovrascritta. Ma è comunque UB!
     */
    cout << "\n=== DOMANDA 3: Scope e dangling ===" << endl;
    int* scopePtr;
    {
        int scopeVar = 100;
        scopePtr = &scopeVar;
        cout << "Dentro scope: *scopePtr = " << *scopePtr << " (OK)" << endl;
    }
    // cout << *scopePtr;  // ← DANGLING! Decommentare = UB
    cout << "Fuori scope: scopePtr è DANGLING (scopeVar distrutta)" << endl;

    // =====================================================================
    // DOMANDA 4: Come evitare il dangling dopo delete?
    // =====================================================================
    /*
     * BEST PRACTICE: dopo delete, metti il puntatore a nullptr.
     *
     *   int* p = new int(5);
     *   delete p;
     *   p = nullptr;      // ← previene use-after-free accidentale
     *
     *   if (p != nullptr)  // ← puoi controllare prima di usare
     *       cout << *p;
     *
     * NOTA: delete su nullptr è SICURO (non fa nulla).
     *   delete nullptr;  // ← OK, non crasha
     */
    cout << "\n=== DOMANDA 4: Buona pratica nullptr ===" << endl;
    int* sicuro = new int(5);
    cout << "*sicuro = " << *sicuro << endl;
    delete sicuro;
    sicuro = nullptr;  // ← BUONA PRATICA
    cout << "sicuro è nullptr? " << (sicuro == nullptr ? "SÌ" : "NO") << endl;
    // delete sicuro;  // ← OK! delete nullptr non fa nulla

    // =====================================================================
    // DOMANDA 5: Array — delete vs delete[]
    // =====================================================================
    /*
     * CASO SUBDOLO: cosa succede se usi delete invece di delete[]?
     *
     * int* arr = new int[5]{1,2,3,4,5};
     * delete arr;    ← ⚠️ UNDEFINED BEHAVIOR!
     *
     * Cosa succede in pratica:
     * - delete dealloca SOLO il primo elemento (o tenta di farlo)
     * - Il sistema non sa che era un array → potrebbe non chiamare
     *   i distruttori degli altri elementi (cruciale per oggetti)
     * - La memoria potrebbe non essere correttamente liberata
     * - Su sistemi moderni potrebbe funzionare per int, ma è SEMPRE UB
     *
     * Per tipi con distruttori (es. string), delete senza [] è DISASTROSO:
     *   string* arr = new string[3]{"a","b","c"};
     *   delete arr;  ← chiama il distruttore SOLO di arr[0]!
     *                   "b" e "c" hanno memory leak interno!
     */
    cout << "\n=== DOMANDA 5: Conseguenze di delete senza [] ===" << endl;
    cout << "new int[5]  → USARE delete[] (!!)" << endl;
    cout << "new int     → USARE delete" << endl;
    cout << "Usare quello sbagliato = UNDEFINED BEHAVIOR" << endl;

    int* arrOK = new int[5]{1, 2, 3, 4, 5};
    delete[] arrOK;  // ✅ CORRETTO

    // =====================================================================
    // DOMANDA 6: QUIZ — Quanti byte vengono persi (memory leak)?
    // =====================================================================
    /*
     * int* a = new int(1);    // 4 byte allocati              [blocco A]
     * int* b = new int(2);    // 4 byte allocati              [blocco B]
     * int* c = a;             // c punta a blocco A
     * a = new int(3);         // 4 byte allocati              [blocco C]
     *                         // ⚠️ blocco A perso? NO! c lo tiene!
     * b = a;                  // b punta a blocco C
     *                         // ⚠️ blocco B perso! Nessuno lo punta!
     * delete a;               // dealloca blocco C
     *                         // ⚠️ ma anche b puntava a C → b è dangling!
     * // delete b;            // ⚠️ DOUBLE FREE!
     * delete c;               // dealloca blocco A → OK
     *
     * MEMORY LEAK: blocco B (4 byte) — mai deallocato
     * DANGLING: b (dopo delete a)
     * DOUBLE FREE se si fa delete b
     *
     * Per sizeof(int) = 4 byte: PERSI 4 BYTE
     */
    cout << "\n=== DOMANDA 6: Quanti byte persi? ===" << endl;
    cout << "Risposta: 4 byte (blocco B = new int(2) mai deallocato)" << endl;
    cout << "Dangling: b dopo delete a" << endl;
    cout << "Corretto: delete a; delete c; (NON delete b!)" << endl;

    return 0;
}
