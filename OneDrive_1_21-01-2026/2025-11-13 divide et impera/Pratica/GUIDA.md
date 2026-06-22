# Guida Pratica: Esercizi Divide et Impera

Questa guida ti aiuta a risolvere gli esercizi nel file `divideetimpera.pdf` con un approccio sistematico.

---

## Metodologia di Risoluzione

### Step 1: Identifica il Problema
Chiediti:
- Qual e l'input? (Array, matrice, numero...)
- Qual e l'output desiderato?
- Posso dividere il problema in sottoproblemi simili?

### Step 2: Definisci il Caso Base
- Qual e il problema piu piccolo che posso risolvere direttamente?
- Solitamente: array con 0, 1 o 2 elementi

### Step 3: Definisci la Ricorsione
- Come divido il problema?
- Quante chiamate ricorsive faccio?
- Come combino i risultati?

---

## Esercizi Tipo con Soluzioni Complete

### Esercizio 1: Somma di un Array

**Problema:** Calcolare la somma di tutti gli elementi di un array.

```cpp
// Caso base: array vuoto -> somma = 0
// Divide: dividi a meta
// Combina: somma delle due parti

int sommaArray(int arr[], int left, int right) {
    // Caso base: nessun elemento
    if (left > right) {
        return 0;
    }
    
    // Caso base: un solo elemento
    if (left == right) {
        return arr[left];
    }
    
    // DIVIDE
    int mid = (left + right) / 2;
    
    // IMPERA + COMBINA
    int sommaLeft = sommaArray(arr, left, mid);
    int sommaRight = sommaArray(arr, mid + 1, right);
    
    return sommaLeft + sommaRight;
}

// Utilizzo
int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = 8;
    
    int risultato = sommaArray(arr, 0, n - 1);
    cout << "Somma: " << risultato << endl;  // 36
    
    return 0;
}
```

**Complessita:**
$$T(n) = 2T(n/2) + O(1)$$
- Risultato: $O(n)$ (devi comunque visitare tutti gli elementi)

---

### Esercizio 2: Ricerca del Massimo

**Problema:** Trovare l'elemento massimo in un array.

```cpp
int trovaMax(int arr[], int left, int right) {
    // Caso base: un solo elemento
    if (left == right) {
        return arr[left];
    }
    
    // Caso base: due elementi
    if (right == left + 1) {
        return max(arr[left], arr[right]);
    }
    
    // DIVIDE
    int mid = (left + right) / 2;
    
    // IMPERA
    int maxLeft = trovaMax(arr, left, mid);
    int maxRight = trovaMax(arr, mid + 1, right);
    
    // COMBINA
    return max(maxLeft, maxRight);
}

// Utilizzo
int main() {
    int arr[] = {3, 7, 2, 9, 1, 5, 8, 4};
    int n = 8;
    
    int massimo = trovaMax(arr, 0, n - 1);
    cout << "Massimo: " << massimo << endl;  // 9
    
    return 0;
}
```

**Visualizzazione:**
```
         [3, 7, 2, 9, 1, 5, 8, 4]
                    |
         /                    \
    [3, 7, 2, 9]          [1, 5, 8, 4]
       |                       |
     /    \                  /    \
  [3,7]  [2,9]           [1,5]  [8,4]
   |       |               |       |
  max=7  max=9          max=5   max=8
     \   /                  \   /
     max=9                 max=8
          \               /
              max=9
```

---

### Esercizio 3: Contare le Occorrenze

**Problema:** Contare quante volte appare un elemento `x` in un array.

```cpp
int contaOccorrenze(int arr[], int left, int right, int x) {
    // Caso base: nessun elemento
    if (left > right) {
        return 0;
    }
    
    // Caso base: un solo elemento
    if (left == right) {
        return (arr[left] == x) ? 1 : 0;
    }
    
    // DIVIDE
    int mid = (left + right) / 2;
    
    // IMPERA + COMBINA
    int countLeft = contaOccorrenze(arr, left, mid, x);
    int countRight = contaOccorrenze(arr, mid + 1, right, x);
    
    return countLeft + countRight;
}

// Utilizzo
int main() {
    int arr[] = {5, 2, 5, 8, 5, 3, 5, 1};
    int n = 8;
    
    int occorrenze = contaOccorrenze(arr, 0, n - 1, 5);
    cout << "Occorrenze di 5: " << occorrenze << endl;  // 4
    
    return 0;
}
```

---

### Esercizio 4: Verifica se Array e Ordinato

**Problema:** Verificare se un array e ordinato in ordine crescente.

```cpp
bool isOrdinato(int arr[], int left, int right) {
    // Caso base: 0 o 1 elementi -> sempre ordinato
    if (left >= right) {
        return true;
    }
    
    // Caso base: due elementi
    if (right == left + 1) {
        return arr[left] <= arr[right];
    }
    
    // DIVIDE
    int mid = (left + right) / 2;
    
    // IMPERA: verifica le due meta
    bool leftSorted = isOrdinato(arr, left, mid);
    bool rightSorted = isOrdinato(arr, mid + 1, right);
    
    // COMBINA: entrambe ordinate E elemento di giunzione corretto
    return leftSorted && rightSorted && (arr[mid] <= arr[mid + 1]);
}

// Utilizzo
int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 3, 2, 4, 5};
    
    cout << "arr1 ordinato: " << (isOrdinato(arr1, 0, 4) ? "Si" : "No") << endl;  // Si
    cout << "arr2 ordinato: " << (isOrdinato(arr2, 0, 4) ? "Si" : "No") << endl;  // No
    
    return 0;
}
```

---

### Esercizio 5: Trovare un Picco

**Problema:** Trovare un elemento "picco" (maggiore dei vicini) in un array.

```cpp
int trovaPicco(int arr[], int left, int right, int n) {
    int mid = (left + right) / 2;
    
    // Controlla se mid e un picco
    bool leftOk = (mid == 0) || (arr[mid] >= arr[mid - 1]);
    bool rightOk = (mid == n - 1) || (arr[mid] >= arr[mid + 1]);
    
    if (leftOk && rightOk) {
        return mid;  // Trovato!
    }
    
    // Se il vicino sinistro e maggiore, cerca a sinistra
    if (mid > 0 && arr[mid - 1] > arr[mid]) {
        return trovaPicco(arr, left, mid - 1, n);
    }
    
    // Altrimenti cerca a destra
    return trovaPicco(arr, mid + 1, right, n);
}

// Utilizzo
int main() {
    int arr[] = {1, 3, 20, 4, 1, 0};
    int n = 6;
    
    int picco = trovaPicco(arr, 0, n - 1, n);
    cout << "Picco in posizione " << picco << " con valore " << arr[picco] << endl;
    // Output: Picco in posizione 2 con valore 20
    
    return 0;
}
```

**Complessita:** $O(\log n)$ (come Binary Search!)

---

### Esercizio 6: Ricerca in Array Ruotato

**Problema:** Cercare un elemento in un array ordinato ma ruotato (es: [4,5,6,7,0,1,2]).

```cpp
int cercaRuotato(int arr[], int left, int right, int x) {
    // Caso base: non trovato
    if (left > right) {
        return -1;
    }
    
    int mid = (left + right) / 2;
    
    // Trovato!
    if (arr[mid] == x) {
        return mid;
    }
    
    // Determina quale meta e ordinata
    if (arr[left] <= arr[mid]) {
        // Meta sinistra ordinata
        if (x >= arr[left] && x < arr[mid]) {
            return cercaRuotato(arr, left, mid - 1, x);
        }
        return cercaRuotato(arr, mid + 1, right, x);
    } else {
        // Meta destra ordinata
        if (x > arr[mid] && x <= arr[right]) {
            return cercaRuotato(arr, mid + 1, right, x);
        }
        return cercaRuotato(arr, left, mid - 1, x);
    }
}

// Utilizzo
int main() {
    int arr[] = {4, 5, 6, 7, 0, 1, 2};
    int n = 7;
    
    cout << "Posizione di 0: " << cercaRuotato(arr, 0, n-1, 0) << endl;  // 4
    cout << "Posizione di 3: " << cercaRuotato(arr, 0, n-1, 3) << endl;  // -1
    
    return 0;
}
```

---

### Esercizio 7: Merge Sort Completo

```cpp
#include <iostream>
using namespace std;

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Array temporanei
    int* L = new int[n1];
    int* R = new int[n2];
    
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    
    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void stampaArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = 7;
    
    cout << "Array originale: ";
    stampaArray(arr, n);
    
    mergeSort(arr, 0, n - 1);
    
    cout << "Array ordinato:  ";
    stampaArray(arr, n);
    
    return 0;
}

/* Output:
Array originale: 38 27 43 3 9 82 10 
Array ordinato:  3 9 10 27 38 43 82 
*/
```

---

### Esercizio 8: Quick Sort Completo

```cpp
#include <iostream>
using namespace std;

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = 6;
    
    quickSort(arr, 0, n - 1);
    
    cout << "Array ordinato: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    // Output: 1 5 7 8 9 10
    
    return 0;
}
```

---

## Tabella Riassuntiva Pattern

| Problema | Divide | Combina | Complessita |
|----------|--------|---------|-------------|
| Somma array | Meta | Somma | $O(n)$ |
| Max/Min | Meta | max()/min() | $O(n)$ |
| Conta occorrenze | Meta | Somma | $O(n)$ |
| Verifica ordinato | Meta | AND + controllo giunzione | $O(n)$ |
| Binary Search | Meta (una sola) | Nulla | $O(\log n)$ |
| Merge Sort | Meta | Merge $O(n)$ | $O(n \log n)$ |
| Quick Sort | Partition | Nulla | $O(n \log n)$ avg |
| Trova picco | Meta (una sola) | Nulla | $O(\log n)$ |

---

## Errori Comuni da Evitare

1. **Dimenticare il caso base**
   ```cpp
   // SBAGLIATO - ricorsione infinita!
   int somma(int arr[], int l, int r) {
       int mid = (l + r) / 2;
       return somma(arr, l, mid) + somma(arr, mid+1, r);
   }
   ```

2. **Caso base sbagliato**
   ```cpp
   // SBAGLIATO - cosa succede se l == r?
   if (l > r) return 0;  // Solo questo non basta!
   ```

3. **Calcolo errato del mid**
   ```cpp
   int mid = (l + r) / 2;          // Puo causare overflow per numeri grandi!
   int mid = l + (r - l) / 2;      // CORRETTO - evita overflow
   ```

4. **Indici sbagliati nelle chiamate ricorsive**
   ```cpp
   // SBAGLIATO - include mid due volte!
   func(arr, l, mid);
   func(arr, mid, r);    // Dovrebbe essere mid + 1
   ```

---

## Consigli per l'Esame

1. **Scrivi SEMPRE il caso base per primo** - E la cosa piu importante!

2. **Disegna l'albero delle chiamate** - Ti aiuta a visualizzare l'esecuzione

3. **Verifica manualmente** - Esegui a mano con un piccolo esempio (n=4 o n=8)

4. **Controlla i limiti degli indici** - `left <= right`, `mid`, `mid + 1`

5. **Pensa alla combinazione** - Spesso e la parte piu difficile da progettare
