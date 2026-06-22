/*
 * ============================================================================
 *  ESERCIZIO 6: RAPPORTO TRA PUNTATORI E REFERENCE
 *               *p = &x, int& r = *p, e tutte le combinazioni
 * ============================================================================
 *  Questo è l'esercizio PIÙ IMPORTANTE per capire la dualità ptr ↔ ref
 */

#include <iostream>
using namespace std;

void modificaPerRef(int& r) { r = 100; }
void modificaPerPtr(int* p) { *p = 200; }

int main() {

    // =====================================================================
    // PARTE A: Da variabile a puntatore a reference — la catena fondamentale
    // =====================================================================
    /*
     *  SCHEMA MENTALE:
     *
     *  int x = 5;       →  x è una variabile, vive in un indirizzo
     *  int* p = &x;     →  p è un puntatore che CONTIENE l'indirizzo di x
     *  int& r = x;      →  r è un reference, un ALIAS di x
     *
     *  ┌───────┐    &x     ┌───────┐
     *  │ x = 5 │ ←──────── │ p     │     p = &x
     *  └───────┘           └───────┘
     *      ↑↕                  │
     *      │                   │ *p = x
     *  ┌───────┐              │
     *  │r (=x) │ è alias ─────┘
     *  └───────┘
     *
     *  EQUIVALENZE:
     *    x  == *p  == r           (il VALORE)
     *    &x == p   == &r          (l'INDIRIZZO)
     */
    cout << "=== PARTE A: La catena x ↔ p ↔ r ===" << endl;

    int x = 5;
    int* p = &x;    // p punta a x
    int& r = x;     // r è alias di x

    cout << "x  = " << x << ", &x  = " << &x << endl;
    cout << "*p = " << *p << ", p   = " << p << endl;
    cout << "r  = " << r << ", &r  = " << &r << endl;
    cout << "Sono tutti uguali? " << ((&x == p && p == &r) ? "SÌ" : "NO") << endl;
    cout << endl;

    // Modifica attraverso il puntatore → si vede su x e r
    *p = 10;
    cout << "Dopo *p = 10:  x=" << x << ", *p=" << *p << ", r=" << r << endl;
    // x=10, *p=10, r=10 → TUTTI cambiano!

    // Modifica attraverso il reference → si vede su x e *p
    r = 20;
    cout << "Dopo r = 20:   x=" << x << ", *p=" << *p << ", r=" << r << endl;
    // x=20, *p=20, r=20 → TUTTI cambiano!

    // Modifica x direttamente → si vede su *p e r
    x = 30;
    cout << "Dopo x = 30:   x=" << x << ", *p=" << *p << ", r=" << r << endl;
    // TUTTI vedono 30

    // =====================================================================
    // PARTE B: Reference a dereferenziazione — int& ref = *p
    // =====================================================================
    /*
     * QUESTO È IL CASO PIÙ CONFUSO:
     *
     * int a = 7;
     * int* p = &a;       → p punta ad a
     * int& ref = *p;     → ref è un alias di *p, cioè un alias di a!
     *
     * Ora ref e a sono la stessa cosa.
     * Modificare ref modifica a (e viceversa).
     *
     * MA ATTENZIONE: se poi sposti p (p = &altroInt),
     * ref NON si sposta! ref resta legato ad a!
     * I reference sono IMMUTABILI nel binding.
     */
    cout << "\n=== PARTE B: int& ref = *p ===" << endl;

    int a = 7, b = 99;
    int* ptr = &a;
    int& ref = *ptr;  // ref è alias di a (tramite dereferenziazione di ptr)

    cout << "a=" << a << ", *ptr=" << *ptr << ", ref=" << ref << endl;  // 7,7,7

    ref = 42;
    cout << "Dopo ref=42: a=" << a << ", *ptr=" << *ptr << endl;  // 42,42

    // Ora cambiamo dove punta ptr
    ptr = &b;
    cout << "\nDopo ptr = &b:" << endl;
    cout << "  *ptr = " << *ptr << " (ora punta a b=99)" << endl;
    cout << "  ref  = " << ref << "  (ANCORA alias di a=42!)" << endl;
    cout << "  a    = " << a << endl;
    // ref è ANCORA legato ad a, NON segue ptr!

    // =====================================================================
    // PARTE C: Puntatore a reference — &ref == &originale
    // =====================================================================
    /*
     * Se ho:  int x = 5;
     *         int& ref = x;
     *
     * Allora: &ref è l'indirizzo di x (NON un "indirizzo del reference")
     *         I reference NON hanno un proprio indirizzo in memoria.
     *
     * Quindi: int* p = &ref → p punta a x!
     *         È come fare: int* p = &x
     */
    cout << "\n=== PARTE C: int* p = &ref ===" << endl;

    int val = 15;
    int& refVal = val;
    int* ptrVal = &refVal;  // equivale a &val

    cout << "val=" << val << ", refVal=" << refVal << ", *ptrVal=" << *ptrVal << endl;
    cout << "&val=" << &val << ", &refVal=" << &refVal << ", ptrVal=" << ptrVal << endl;
    cout << "Tutti lo stesso indirizzo? " << ((&val == &refVal && &refVal == ptrVal) ? "SÌ" : "NO") << endl;

    *ptrVal = 77;
    cout << "Dopo *ptrVal=77: val=" << val << ", refVal=" << refVal << endl;
    // val=77, refVal=77

    // =====================================================================
    // PARTE D: Passaggio a funzione — ref e puntatore sono intercambiabili?
    // =====================================================================
    /*
     * void modificaPerRef(int& r) { r = 100; }
     * void modificaPerPtr(int* p) { *p = 200; }
     *
     * Entrambe modificano l'originale, ma la SINTASSI di chiamata è diversa:
     *
     *   modificaPerRef(x);     ← passa x direttamente
     *   modificaPerRef(*p);    ← passa il VALORE PUNTATO (dereferenzia)
     *
     *   modificaPerPtr(&x);    ← passa l'INDIRIZZO di x
     *   modificaPerPtr(p);     ← passa il puntatore direttamente
     *
     * TUTTI e 4 i casi modificano la stessa variabile x.
     */
    cout << "\n=== PARTE D: Funzioni con ref vs puntatore ===" << endl;

    int z = 0;
    int* pz = &z;
    int& rz = z;

    cout << "z iniziale = " << z << endl;

    modificaPerRef(z);     cout << "modificaPerRef(z):   z=" << z << endl;   // 100
    modificaPerRef(*pz);   cout << "modificaPerRef(*pz): z=" << z << endl;   // 100 (stessa)
    modificaPerRef(rz);    cout << "modificaPerRef(rz):  z=" << z << endl;   // 100 (stessa)

    modificaPerPtr(&z);    cout << "modificaPerPtr(&z):  z=" << z << endl;   // 200
    modificaPerPtr(pz);    cout << "modificaPerPtr(pz):  z=" << z << endl;   // 200 (stessa)
    modificaPerPtr(&rz);   cout << "modificaPerPtr(&rz): z=" << z << endl;   // 200 (stessa)

    // =====================================================================
    // PARTE E: TRAPPOLA D'ESAME — Confondere *p = &y con p = &y
    // =====================================================================
    /*
     * CASO 1:  p = &y
     *   → Cambia DOVE punta p. Ora p punta a y.
     *   → Il vecchio oggetto puntato NON viene modificato.
     *
     * CASO 2:  *p = y    (o equivalente: *p = qualcosa)
     *   → Cambia il VALORE puntato da p. p continua a puntare allo stesso posto.
     *   → Il valore dove p punta diventa y.
     *
     * CASO 3:  *p = &y
     *   → Possibile SOLO se p è un int** (puntatore a puntatore)!
     *   → Se p è int*, allora *p è un int, e &y è un int* → TYPE MISMATCH!
     */
    cout << "\n=== PARTE E: p = &y vs *p = y ===" << endl;

    int m1 = 10, m2 = 20;
    int* pp = &m1;

    cout << "Iniziale: *pp=" << *pp << ", m1=" << m1 << ", m2=" << m2 << endl;

    // CASO 1: *pp = m2 → copia il VALORE di m2 in m1
    *pp = m2;
    cout << "Dopo *pp = m2:  m1=" << m1 << ", m2=" << m2 << ", *pp=" << *pp << endl;
    // m1=20, m2=20, *pp=20 (pp punta ANCORA a m1!)
    m2 = 99;
    cout << "  Poi m2=99:    m1=" << m1 << ", *pp=" << *pp << " (pp punta a m1!)" << endl;
    // m1=20, *pp=20 → conferma: pp punta ancora a m1

    m1 = 10;
    m2 = 20;
    pp = &m1;

    // CASO 2: pp = &m2 → pp ora punta a m2
    pp = &m2;
    cout << "\nDopo pp = &m2:  m1=" << m1 << ", m2=" << m2 << ", *pp=" << *pp << endl;
    // m1=10, m2=20, *pp=20 (pp ora punta a m2!)

    *pp = 777;
    cout << "  Dopo *pp=777: m1=" << m1 << ", m2=" << m2 << endl;
    // m1=10, m2=777 → conferma: pp punta a m2

    // =====================================================================
    // PARTE F: Reference a puntatore — int*& refP
    // =====================================================================
    /*
     * int*& refP = p;
     *   → refP è un ALIAS del PUNTATORE p (non del valore puntato!)
     *   → Modificare refP modifica dove punta p.
     *   → Modificare *refP modifica il valore puntato.
     *
     * UTILITÀ: serve per modificare un puntatore passato a una funzione.
     *   void alloca(int*& p) { p = new int(42); }
     *   → Modifica il puntatore originale, non una copia!
     */
    cout << "\n=== PARTE F: int*& (reference a puntatore) ===" << endl;

    int v1 = 10, v2 = 20;
    int* ptr2 = &v1;
    int*& refPtr = ptr2;  // refPtr è alias del PUNTATORE ptr2

    cout << "*ptr2 = " << *ptr2 << ", *refPtr = " << *refPtr << endl;  // 10, 10

    refPtr = &v2;  // modifica ptr2! Ora ptr2 punta a v2
    cout << "Dopo refPtr=&v2: *ptr2=" << *ptr2 << " (ptr2 ora punta a v2!)" << endl;

    *refPtr = 999;
    cout << "Dopo *refPtr=999: v2=" << v2 << endl;  // v2=999

    // =====================================================================
    // PARTE G: QUIZ RIEPILOGATIVO — Cosa stampa?
    // =====================================================================
    cout << "\n=== PARTE G: QUIZ RIEPILOGATIVO ===" << endl;

    int n1 = 3, n2 = 7;
    int* qp = &n1;
    int& qr = n1;
    int& qr2 = *qp;

    /*
     * ANALISI:
     *   qp punta a n1, qr è alias di n1, qr2 è alias di *qp = n1
     *   → qp, qr, qr2 fanno tutti riferimento a n1!
     *
     *   qr = n2;      → n1 = 7 (copia valore, qr è ancora alias di n1!)
     *   *qp += qr2;   → n1 = n1 + n1 = 7 + 7 = 14
     *   qp = &n2;     → qp ora punta a n2, ma qr e qr2 restano su n1!
     *   *qp = qr;     → n2 = n1 = 14
     *
     *   STAMPA: n1=14, n2=14, qr=14, qr2=14, *qp=14
     */
    qr = n2;
    *qp += qr2;
    qp = &n2;
    *qp = qr;

    cout << "n1=" << n1 << ", n2=" << n2 << endl;
    cout << "qr=" << qr << ", qr2=" << qr2 << ", *qp=" << *qp << endl;
    // Tutto 14!

    return 0;
}
