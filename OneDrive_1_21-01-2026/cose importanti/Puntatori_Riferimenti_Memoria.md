# Cheat Sheet Completo: Puntatori, Riferimenti e Memoria

La guida definitiva per risolvere gli esercizi d'esame sui casi limite del C++.

## 1. Operatori Fondamentali

| Operatore | Nome | Significato |
| :--- | :--- | :--- |
| `int* p` | **Dichiarazione** | `p` è una variabile che contiene un indirizzo di memoria. |
| `&x` | **Indirizzo di** | Ritorna l'indirizzo di memoria della variabile `x`. |
| `*p` | **Dereferenziazione** | Accede al **valore** memorizzato all'indirizzo `p`. |
| `p = nullptr` | **Null** | Il puntatore non punta a nulla (sicurezza). |

---

## 2. Puntatori vs Riferimenti

### 2.1 Differenze
- **Puntatore**: Può essere cambiato (`p = &y`), può essere nullo, ha bisogno di `*` per il valore.
- **Riferimento**: È un alias costante. Deve essere inizializzato subito e non può cambiare bersaglio. Si usa come una variabile normale.

### 2.2 Passaggio Parametri
- **Per Valore**: `void f(int x)` -> Copia l'intero (lento per oggetti grandi, non modifica originale).
- **Per Puntatore**: `void f(int* x)` -> Passa indirizzo (modifica originale, usa `*x`).
- **Per Riferimento**: `void f(int& x)` -> Passa alias (modifica originale, sintassi pulita). **Migliore scelta per efficienza**.

---

## 3. Aritmetica dei Puntatori (IL PERICOLO!)

### 3.1 Gli Array sono Puntatori
Il nome di un array è un puntatore al suo primo elemento.
`int a[5];` -> `a` è uguale a `&a[0]`.

### 3.2 Priorità Operatori e Parentesi
Sia `a` un array che inizia con i valori `{10, 20, 30, 40}`:

| Sintassi | Significato | Risultato |
| :--- | :--- | :--- |
| `*a + 3` | `(*a) + 3` -> Prendi il primo valore (10) e aggiungi 3. | **13** |
| `*(a + 3)` | Spostati avanti di 3 posti (`a[3]`), poi prendi il valore. | **40** |
| `*a++` | Prendi il valore attuale, poi sposta il puntatore avanti. | **10** (poi `a` punta a 20) |
| `++*a` | Incrementa il **valore** del primo elemento. | **11** |

---

## 4. Memoria Dinamica: New e Delete

### 4.1 Ciclo di vita
Ogni `new` deve avere un `delete` corrispondente.

| Allocazione | Deallocazione Corretta | Errore Comune |
| :--- | :--- | :--- |
| `int* p = new int;` | `delete p;` | `delete[] p;` ❌ |
| `int* a = new int[10];` | `delete[] a;` | `delete a;` ❌ |

### 4.2 Deallocazione di Sotto-Puntatori
Se `p = matricola + 4`, **NON puoi** fare `delete p;`. Devi sempre deallocare il puntatore originale restituito da `new`.

---

## 5. Analisi degli Esercizi "Trappola"

### 5.1 Esempio 1: f(int* a)
```cpp
void f (int* a) { 
    int b = (*a+3); 
    int c = *(a+3); 
    cout << b << " " << c << endl; 
}
```
- **f(matricola)**: `a` punta all'inizio. `b = m[0]+3`, `c = m[3]`.
- **f(matricola+3)**: `a` punta all'indice 3. 
  - `*a` è `m[3]`. Quindi `b = m[3]+3`.
  - `*(a+3)` è `m[3+3] = m[6]`. **ATTENZIONE**: se l'array è di 6 elementi (0..5), `m[6]` è **fuori dai limiti**! Crash o spazzatura.

### 5.2 Esempio 2: Metodi su Puntatori Grezzi
```cpp
int* matricola = new int[6];
while (!matricola.empty()) ... ❌ ERRORE!
```
**Perché?** `int*` è un puntatore grezzo (indirizzo). Non è un oggetto `std::vector`. Non ha funzioni membro come `.empty()`, `.size()`, `.pop_back()`.

### 5.3 Esempio 3: Riferimenti a Variabili Locali
```cpp
int& g(int& a) {
    int b = a; 
    return b; 
} ❌ ERRORE CRITICO!
```
`b` viene allocata nello stack di `g()`. Quando `g()` finisce, lo stack viene pulito e `b` scompare. Il chiamante riceve un riferimento a un'area di memoria non più valida (**Dangling Reference**).

### 5.4 Esempio 4: Indici e Indirizzi
```cpp
cout << matricola[matricola + 2] << endl; ❌ ERRORE!
```
L'operatore `[]` vuole un numero intero (indice). `matricola + 2` è un indirizzo di memoria. Non puoi usare un indirizzo come indice.
**Corretto**: `matricola[2]` oppure `*(matricola + 2)`.

### 5.5 Esempio 5: Assegnamento Puntatori
```cpp
int* p = m + 4;  // p -> m[4]
int* q = m + 3;  // q -> m[3]
p = q;           // Ora p punta dove punta q (m[3])
q = p;           // Inutile, q puntava già lì
*p = 0;          // m[3] diventa 0
*q = 9;          // m[3] diventa 9 (sovrascrive 0)
```
Alla fine: `m[3] = 9`, `m[4]` è invariato.

---

## 6. Checklist Finale (Vero o Falso?)
1. **Un puntatore può puntare a un altro puntatore?** Sì (`int** pp`).
2. **`delete[]` pulisce anche i valori puntati da un array di puntatori?** No, pulisce solo l'array di puntatori. Se ogni puntatore punta a memoria dinamica, devi fare un loop e cancellarli uno ad uno.
3. **Sottrarre due puntatori è legale?** Sì, ritorna la distanza (numero di elementi) tra i due.
4. **Sommare due puntatori è legale?** No, non ha senso matematico in memoria.
5. **`unsigned` overflow**: `unsigned x = 0; x--;` -> `x` diventa il numero più grande possibile (es. 4 miliardi), NON -1.
