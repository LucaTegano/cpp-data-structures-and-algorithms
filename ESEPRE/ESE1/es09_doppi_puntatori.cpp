/*
 * ============================================================================
 *  ESERCIZIO 9: DOPPI PUNTATORI (int**) e PUNTATORI A PUNTATORI
 *               Allocazione, passaggio a funzioni, matrici
 * ============================================================================
 */

#include <iostream>
using namespace std;

// Funzione che alloca tramite puntatore a puntatore
void allocaArray(int** p, int n) {
    *p = new int[n];  // modifica il puntatore originale!
    for (int i = 0; i < n; i++) (*p)[i] = i * 10;
}

// Funzione che alloca tramite reference a puntatore (equivalente, più pulito)
void allocaArrayRef(int*& p, int n) {
    p = new int[n];
    for (int i = 0; i < n; i++) p[i] = i * 100;
}

// ⚠️ Funzione SBAGLIATA: passaggio puntatore per valore
void allocaErrata(int* p, int n) {
    p = new int[n];  // modifica la COPIA locale del puntatore!
    for (int i = 0; i < n; i++) p[i] = i;
    // Memory leak: la memoria allocata qui è persa!
}

int main() {

    // =====================================================================
    // DOMANDA 1: SCHEMA MENTALE — cosa sono **, ***, ecc.?
    // =====================================================================
    /*
     * LIVELLI DI INDIREZIONE:
     *
     *  int x = 5;        → x è un valore
     *  int* p = &x;      → p è un puntatore a x        (1 livello)
     *  int** pp = &p;    → pp è un puntatore a p        (2 livelli)
     *  int*** ppp = &pp; → ppp è un puntatore a pp      (3 livelli)
     *
     *  Per accedere al valore:
     *    x      = 5
     *    *p     = 5   (dereferenzia 1 volta)
     *    **pp   = 5   (dereferenzia 2 volte)
     *    ***ppp = 5   (dereferenzia 3 volte)
     *
     *  MEMORIA:
     *    ppp ──→ pp ──→ p ──→ x(5)
     *
     *  Per cambiare DOVE punta p, serve passare &p (cioè int**)
     */
    cout << "=== DOMANDA 1: Livelli di indirezione ===" << endl;

    int x = 5;
    int* p = &x;
    int** pp = &p;
    int*** ppp = &pp;

    cout << "x       = " << x << endl;
    cout << "*p      = " << *p << endl;
    cout << "**pp    = " << **pp << endl;
    cout << "***ppp  = " << ***ppp << endl;
    cout << endl;

    // Modifica attraverso i vari livelli
    ***ppp = 99;
    cout << "Dopo ***ppp=99: x=" << x << endl;  // x=99!

    // =====================================================================
    // DOMANDA 2: Perché serve int** per allocare in una funzione?
    // =====================================================================
    /*
     * Se passi int* a una funzione:
     *   void f(int* p) { p = new int(5); }
     *   → p è una COPIA del puntatore. La modifica NON si propaga!
     *   → MEMORY LEAK + il puntatore originale resta NULL.
     *
     * Se passi int**:
     *   void f(int** p) { *p = new int(5); }
     *   → p punta AL puntatore originale. *p modifica l'originale!
     *
     * Alternativa C++: int*& (reference a puntatore)
     *   void f(int*& p) { p = new int(5); }
     *   → Più pulito, stesso effetto di int**
     */
    cout << "\n=== DOMANDA 2: Allocare tramite funzione ===" << endl;

    int* arr1 = nullptr;
    allocaArray(&arr1, 5);  // passa &arr1 (int**)
    cout << "allocaArray (int**):   ";
    for (int i = 0; i < 5; i++) cout << arr1[i] << " ";
    cout << endl;

    int* arr2 = nullptr;
    allocaArrayRef(arr2, 5);  // passa arr2 per reference
    cout << "allocaArrayRef (int*&): ";
    for (int i = 0; i < 5; i++) cout << arr2[i] << " ";
    cout << endl;

    int* arr3 = nullptr;
    allocaErrata(arr3, 5);  // ⚠️ arr3 resta nullptr!
    cout << "allocaErrata (int*):    arr3 è " 
         << (arr3 == nullptr ? "NULLPTR (non funziona!)" : "valido") << endl;

    delete[] arr1;
    delete[] arr2;
    // arr3 non va deallocato (è nullptr), ma la memoria allocata dentro
    // allocaErrata è un MEMORY LEAK!

    // =====================================================================
    // DOMANDA 3: int** come matrice — analisi passo passo
    // =====================================================================
    /*
     * int** mat = new int*[3];     → array di 3 puntatori
     * mat[0] = new int[2]{1,2};    → prima riga
     * mat[1] = new int[2]{3,4};    → seconda riga
     * mat[2] = new int[2]{5,6};    → terza riga
     *
     * DOMANDA: cosa stampa mat[1][0]?
     *
     *   mat[1] è un int*, punta alla seconda riga
     *   mat[1][0] = 3
     *
     * DOMANDA: cosa stampa *mat[1]?
     *   Equivale a *(mat[1]) = mat[1][0] = 3
     *
     * DOMANDA: cosa stampa **mat?
     *   *mat = mat[0]        (primo puntatore nell'array di puntatori)
     *   **mat = *mat[0] = mat[0][0] = 1
     *
     * DOMANDA: cosa stampa *(*(mat+1)+1)?
     *   mat+1 = &mat[1]     (indirizzo del secondo puntatore)
     *   *(mat+1) = mat[1]   (secondo puntatore = riga 1)
     *   *(mat+1)+1 = mat[1]+1 (secondo elemento della riga 1)
     *   *(*(mat+1)+1) = mat[1][1] = 4
     *
     * EQUIVALENZE:
     *   mat[i][j] == *(mat[i]+j) == *(*(mat+i)+j)
     */
    cout << "\n=== DOMANDA 3: int** come matrice ===" << endl;

    int** mat = new int*[3];
    mat[0] = new int[2]{1, 2};
    mat[1] = new int[2]{3, 4};
    mat[2] = new int[2]{5, 6};

    cout << "mat[1][0]         = " << mat[1][0] << endl;          // 3
    cout << "*mat[1]           = " << *mat[1] << endl;            // 3
    cout << "**mat             = " << **mat << endl;              // 1
    cout << "*(*(mat+1)+1)     = " << *(*(mat + 1) + 1) << endl; // 4
    cout << "mat[2][1]         = " << mat[2][1] << endl;          // 6
    cout << "*(mat[2]+1)       = " << *(mat[2] + 1) << endl;     // 6

    for (int i = 0; i < 3; i++) delete[] mat[i];
    delete[] mat;

    // =====================================================================
    // DOMANDA 4: Scambio di puntatori tramite int**
    // =====================================================================
    /*
     * void scambia(int** a, int** b) {
     *     int* temp = *a;
     *     *a = *b;
     *     *b = temp;
     * }
     *
     * Questo scambia DOVE puntano i puntatori originali!
     * (Non i valori, ma gli indirizzi stessi)
     *
     * Dopo: p1 punterà dove puntava p2 e viceversa.
     */
    cout << "\n=== DOMANDA 4: Scambio puntatori con int** ===" << endl;

    int v1 = 111, v2 = 222;
    int* p1 = &v1;
    int* p2 = &v2;

    cout << "Prima:  *p1=" << *p1 << ", *p2=" << *p2 << endl;

    // Scambio tramite doppio puntatore
    int* temp = p1;
    p1 = p2;
    p2 = temp;

    cout << "Dopo:   *p1=" << *p1 << ", *p2=" << *p2 << endl;
    // *p1=222, *p2=111 (scambiati i puntatori, non i valori!)
    cout << "v1=" << v1 << ", v2=" << v2 << " (i valori NON cambiano!)" << endl;

    // =====================================================================
    // DOMANDA 5: QUIZ — Cosa stampa?
    // =====================================================================
    cout << "\n=== DOMANDA 5: QUIZ ===" << endl;

    int a = 1, b = 2, c = 3;
    int* pa = &a;
    int* pb = &b;
    int** qq = &pa;

    /*
     * STEP-BY-STEP:
     * 
     * **qq = 10;     → *pa = 10 → a = 10
     * *qq = pb;      → pa = pb → pa ora punta a b!
     * **qq = 20;     → *pa = 20 → b = 20 (pa punta a b!)
     * qq = &pb;      → qq ora punta a pb (non più a pa)
     *                   Ma pa è ancora puntato a b!
     *
     * Stato finale:
     *   a = 10   (modificato da **qq = 10)
     *   b = 20   (modificato da **qq = 20 dopo *qq = pb)
     *   c = 3    (mai toccato)
     *   pa → b   (spostato da *qq = pb)
     *   pb → b   (invariato)
     *   qq → pb  (spostato da qq = &pb)
     */
    **qq = 10;
    *qq = pb;
    **qq = 20;

    cout << "a=" << a << " (era 1, ora 10)" << endl;
    cout << "b=" << b << " (era 2, ora 20)" << endl;
    cout << "c=" << c << " (invariato = 3)" << endl;
    cout << "*pa=" << *pa << " (pa ora punta a b)" << endl;

    return 0;
}
