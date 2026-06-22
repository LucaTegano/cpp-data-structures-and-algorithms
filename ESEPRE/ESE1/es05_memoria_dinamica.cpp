/*
 * ============================================================================
 *  ESERCIZIO 5: MEMORIA DINAMICA — new/delete, array dinamici, matrici
 * ============================================================================
 *  Focus: allocazione/deallocazione, array 2D dinamici, regole new/delete
 */

#include <iostream>
using namespace std;

void stampaMatrice(int** mat, int righe, int colonne, const char* nome) {
    cout << nome << ":" << endl;
    for (int i = 0; i < righe; i++) {
        cout << "  [";
        for (int j = 0; j < colonne; j++) {
            if (j > 0) cout << ", ";
            cout << mat[i][j];
        }
        cout << "]" << endl;
    }
}

int main() {
    // =====================================================================
    // DOMANDA 1: Allocazione corretta di un array 2D dinamico (matrice)
    // =====================================================================
    /*
     * Per creare una matrice NxM dinamica servono DUE livelli di allocazione:
     *
     * STEP 1: Alloca un array di PUNTATORI (uno per riga)
     *         int** mat = new int*[N];
     *
     * STEP 2: Per ogni riga, alloca un array di int
     *         for (int i = 0; i < N; i++)
     *             mat[i] = new int[M];
     *
     * MEMORIA:
     *   mat ──→ [ptr0] [ptr1] [ptr2]    ← array di puntatori
     *             │      │      │
     *             ▼      ▼      ▼
     *           [0,1,2] [3,4,5] [6,7,8]  ← array di int (righe)
     *
     * DEALLOCAZIONE (ordine inverso!):
     *   STEP 1: Per ogni riga: delete[] mat[i];
     *   STEP 2: Poi: delete[] mat;
     *
     * ⚠️ Se fai solo delete[] mat → MEMORY LEAK sulle righe!
     * ⚠️ Se fai delete mat → UNDEFINED BEHAVIOR (manca [])
     */
    int N = 3, M = 4;
    int** mat = new int*[N];
    for (int i = 0; i < N; i++) {
        mat[i] = new int[M];
        for (int j = 0; j < M; j++)
            mat[i][j] = i * M + j;  // 0,1,2,...,11
    }

    cout << "=== DOMANDA 1: Matrice 2D dinamica ===" << endl;
    stampaMatrice(mat, N, M, "Matrice 3x4");

    // =====================================================================
    // DOMANDA 2: Quale deallocazione è corretta?
    // =====================================================================
    /*
     * a) delete[] mat;                          ← ❌ Memory leak righe!
     * b) delete mat;                            ← ❌ UB + memory leak!
     * c) for (int i=0; i<N; i++) delete mat[i]; 
     *    delete[] mat;                          ← ❌ Manca [] su mat[i]!
     * d) for (int i=0; i<N; i++) delete[] mat[i];
     *    delete[] mat;                          ← ✅ CORRETTA!
     * e) delete[][] mat;                        ← ❌ Non esiste delete[][]!
     *
     * REGOLA: Ogni new ha il suo delete. Ogni new[] ha il suo delete[].
     *   Abbiamo fatto 1 × new int*[N] + N × new int[M]
     *   Quindi servono N × delete[] + 1 × delete[]
     */
    cout << "\n=== DOMANDA 2: Deallocazione corretta ===" << endl;
    cout << "Risposta: d) prima delete[] su ogni riga, poi delete[] sulla matrice" << endl;
    
    for (int i = 0; i < N; i++) delete[] mat[i];
    delete[] mat;

    // =====================================================================
    // DOMANDA 3: Matrice "a righe di dimensione diversa" (ragged array)
    // =====================================================================
    /*
     * Con i puntatori, ogni riga può avere una dimensione DIVERSA!
     * Questo NON è possibile con un array 2D statico (int arr[3][4]).
     *
     * Esempio: triangolo di Pascal
     *   Riga 0: [1]          (1 elemento)
     *   Riga 1: [1, 1]       (2 elementi)
     *   Riga 2: [1, 2, 1]    (3 elementi)
     *   Riga 3: [1, 3, 3, 1] (4 elementi)
     */
    cout << "\n=== DOMANDA 3: Ragged array (righe diverse) ===" << endl;

    int numRighe = 4;
    int** triangolo = new int*[numRighe];
    int* lunghezze = new int[numRighe];

    for (int i = 0; i < numRighe; i++) {
        lunghezze[i] = i + 1;
        triangolo[i] = new int[lunghezze[i]];
        triangolo[i][0] = triangolo[i][i] = 1;
        for (int j = 1; j < i; j++)
            triangolo[i][j] = triangolo[i - 1][j - 1] + triangolo[i - 1][j];
    }

    for (int i = 0; i < numRighe; i++) {
        cout << "  Riga " << i << ": ";
        for (int j = 0; j < lunghezze[i]; j++)
            cout << triangolo[i][j] << " ";
        cout << endl;
    }

    // Deallocazione
    for (int i = 0; i < numRighe; i++) delete[] triangolo[i];
    delete[] triangolo;
    delete[] lunghezze;

    // =====================================================================
    // DOMANDA 4: Allocare singolo oggetto vs array — regole
    // =====================================================================
    /*
     *        Allocazione           Deallocazione         Cosa succede se sbagli
     * ┌────────────────────┬─────────────────────┬──────────────────────────────┐
     * │ int* p = new int;  │ delete p;           │ delete[] p → UB!            │
     * │                    │                     │ (tenta di deallocare array)  │
     * ├────────────────────┼─────────────────────┼──────────────────────────────┤
     * │ int* p = new int[5]│ delete[] p;         │ delete p → UB!              │
     * │                    │                     │ (dealloca solo il primo)     │
     * ├────────────────────┼─────────────────────┼──────────────────────────────┤
     * │ int* p = new int(5)│ delete p;           │ Nota: (5) è il VALORE       │
     * │                    │                     │ iniziale, non la dimensione! │
     * └────────────────────┴─────────────────────┴──────────────────────────────┘
     *
     * ATTENZIONE alla differenza:
     *   new int(5)  → alloca UN int con valore 5
     *   new int[5]  → alloca un ARRAY di 5 int
     */
    cout << "\n=== DOMANDA 4: new int(5) vs new int[5] ===" << endl;

    int* singolo = new int(42);  // UN int con valore 42
    int* array5 = new int[5]{10, 20, 30, 40, 50};

    cout << "new int(42):  *singolo = " << *singolo << endl;
    cout << "new int[5]:   ";
    for (int i = 0; i < 5; i++) cout << array5[i] << " ";
    cout << endl;

    delete singolo;    // delete per singolo
    delete[] array5;   // delete[] per array

    // =====================================================================
    // DOMANDA 5: Cosa stampa questo codice? (Trappola memory)
    // =====================================================================
    /*
     * int* a = new int(3);
     * int* b = new int(7);
     * int* c = a;       ← c è un ALIAS di a (puntano allo stesso int)
     * a = b;            ← a ora punta dove punta b
     *                      ⚠️ L'int(3) originale è ora PERSO!
     *                      Nessun puntatore ci punta più → MEMORY LEAK!
     * *a = 10;          ← modifica il valore puntato da a (e b): int(7) → 10
     * 
     * cout << *a → 10
     * cout << *b → 10  (a e b puntano allo stesso posto!)
     * cout << *c → 3   (c punta ancora al vecchio int(3))
     *
     * PROBLEMA: come deallocare?
     *   delete a; ← dealloca l'int che era 7 (ora 10)
     *   delete b; ← DOUBLE FREE! a e b puntano allo stesso blocco!
     *   delete c; ← dealloca l'int(3) → OK
     *
     * SOLUZIONE: delete c; delete a; (oppure delete b, ma NON entrambi!)
     */
    cout << "\n=== DOMANDA 5: Alias e memory leak ===" << endl;
    int* pA = new int(3);
    int* pB = new int(7);
    int* pC = pA;     // pC alias di pA
    pA = pB;          // ⚠️ memory leak se non salviamo il vecchio puntatore!
    *pA = 10;

    cout << "*pA = " << *pA << endl;  // 10
    cout << "*pB = " << *pB << endl;  // 10 (stesso blocco di pA!)
    cout << "*pC = " << *pC << endl;  // 3

    // Deallocazione corretta:
    delete pC;  // dealloca int(3)
    delete pA;  // dealloca int(10), NON fare anche delete pB!
    // delete pB;  ← DOUBLE FREE! pA e pB puntano allo stesso blocco!

    return 0;
}
