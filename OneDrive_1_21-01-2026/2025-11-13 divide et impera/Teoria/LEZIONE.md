# Teoria Completa: Paradigma Divide et Impera

Questo documento fornisce una spiegazione approfondita del paradigma algoritmico **Divide et Impera** (Divide and Conquer), con esempi pratici e analisi della complessita.

---

## Indice
1. [Cos'e il Divide et Impera](#1-cose-il-divide-et-impera)
2. [Schema Generale](#2-schema-generale)
3. [Algoritmi Classici](#3-algoritmi-classici)
4. [Analisi della Complessita](#4-analisi-della-complessita)
5. [Quando Usarlo](#5-quando-usarlo)
6. [Esempi Avanzati](#6-esempi-avanzati)

---

## 1. Cos'e il Divide et Impera

Il **Divide et Impera** e una tecnica algoritmica che risolve un problema seguendo tre fasi:

1. **DIVIDE**: Suddividi il problema in sottoproblemi piu piccoli della stessa natura
2. **IMPERA (Conquista)**: Risolvi i sottoproblemi ricorsivamente
3. **COMBINA**: Unisci le soluzioni dei sottoproblemi per ottenere la soluzione finale

### Caratteristiche Fondamentali
- I sottoproblemi devono essere **indipendenti** tra loro
- La ricorsione termina quando si raggiunge un **caso base** (problema banale)
- L'efficienza dipende da come si **combinano** le soluzioni

### Differenza con Programmazione Dinamica
| Divide et Impera | Programmazione Dinamica |
|------------------|------------------------|
| Sottoproblemi indipendenti | Sottoproblemi sovrapposti |
| Non memorizza soluzioni | Memorizza soluzioni (memoization) |
| Top-down puro | Top-down o bottom-up |

---

## 2. Schema Generale

### Template Ricorsivo
```cpp
Soluzione divideEtImpera(Problema P) {
    // Caso base: problema abbastanza piccolo
    if (isBaseCase(P)) {
        return risolviDirettamente(P);
    }
    
    // DIVIDE: scomponi il problema
    Problema P1, P2, ..., Pk = divide(P);
    
    // IMPERA: risolvi ricorsivamente
    Soluzione S1 = divideEtImpera(P1);
    Soluzione S2 = divideEtImpera(P2);
    // ...
    Soluzione Sk = divideEtImpera(Pk);
    
    // COMBINA: unisci le soluzioni
    return combina(S1, S2, ..., Sk);
}
```

### Esempio Visivo: Binary Search
```
        Array[0...n-1]
             |
        /    |    \
   [0..n/2]  mid  [n/2..n]
       |           |
      ...         ...
       |           |
    [singolo]   [singolo]
```

---

## 3. Algoritmi Classici

### 3.1 Binary Search (Ricerca Binaria)

**Problema:** Trovare un elemento `x` in un array **ordinato**.

**Idea:** Confronta con l'elemento centrale e scarta meta array.

```cpp
// Versione Ricorsiva
int binarySearch(int arr[], int left, int right, int x) {
    // Caso base: elemento non trovato
    if (left > right) {
        return -1;
    }
    
    // DIVIDE: trova il punto medio
    int mid = left + (right - left) / 2;  // Evita overflow!
    
    // Caso base: elemento trovato
    if (arr[mid] == x) {
        return mid;
    }
    
    // IMPERA: cerca nella meta appropriata
    if (arr[mid] > x) {
        return binarySearch(arr, left, mid - 1, x);  // Cerca a sinistra
    } else {
        return binarySearch(arr, mid + 1, right, x); // Cerca a destra
    }
}

// Versione Iterativa (piu efficiente in pratica)
int binarySearchIterative(int arr[], int n, int x) {
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == x) return mid;
        if (arr[mid] > x) right = mid - 1;
        else left = mid + 1;
    }
    
    return -1;
}
```

**Complessita:**
- Tempo: $O(\log n)$
- Spazio: $O(\log n)$ ricorsiva, $O(1)$ iterativa

**Esempio d'uso:**
```cpp
int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
int n = sizeof(arr) / sizeof(arr[0]);

int pos = binarySearch(arr, 0, n-1, 23);
// pos = 5 (23 e in posizione 5)

pos = binarySearch(arr, 0, n-1, 10);
// pos = -1 (10 non presente)
```

---

### 3.2 Merge Sort

**Problema:** Ordinare un array.

**Idea:** 
1. Dividi l'array a meta
2. Ordina ricorsivamente le due meta
3. Fondi le due meta ordinate (merge)

```cpp
// Funzione di fusione (COMBINA)
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;  // Dimensione prima meta
    int n2 = right - mid;      // Dimensione seconda meta
    
    // Array temporanei
    int* L = new int[n1];
    int* R = new int[n2];
    
    // Copia i dati negli array temporanei
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // Fusione degli array temporanei
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copia elementi rimanenti di L[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copia elementi rimanenti di R[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    delete[] L;
    delete[] R;
}

// Funzione principale
void mergeSort(int arr[], int left, int right) {
    // Caso base: array con 0 o 1 elementi
    if (left >= right) {
        return;
    }
    
    // DIVIDE: trova il punto medio
    int mid = left + (right - left) / 2;
    
    // IMPERA: ordina le due meta
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    
    // COMBINA: fondi le due meta ordinate
    merge(arr, left, mid, right);
}
```

**Complessita:**
- Tempo: $O(n \log n)$ in **tutti** i casi
- Spazio: $O(n)$ per gli array temporanei

**Visualizzazione:**
```
      [38, 27, 43, 3, 9, 82, 10]
                 |
         /              \
    [38, 27, 43, 3]    [9, 82, 10]
        |                   |
     /     \            /       \
  [38,27] [43,3]    [9,82]    [10]
    |       |          |        |
   / \     / \        / \       |
 [38][27][43][3]   [9][82]    [10]
   \  /    \  /      \ /        |
  [27,38] [3,43]   [9,82]     [10]
     \      /         \        /
    [3,27,38,43]     [9,10,82]
          \            /
       [3, 9, 10, 27, 38, 43, 82]
```

---

### 3.3 Quick Sort

**Problema:** Ordinare un array.

**Idea:**
1. Scegli un elemento **pivot**
2. Partiziona l'array: elementi < pivot a sinistra, > pivot a destra
3. Ordina ricorsivamente le due parti

```cpp
// Funzione di partizionamento (DIVIDE + parziale COMBINA)
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // Pivot = ultimo elemento
    int i = low - 1;        // Indice dell'elemento piu piccolo
    
    for (int j = low; j < high; j++) {
        // Se elemento corrente < pivot
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    // Metti il pivot nella posizione corretta
    swap(arr[i + 1], arr[high]);
    return i + 1;  // Ritorna la posizione del pivot
}

// Funzione principale
void quickSort(int arr[], int low, int high) {
    // Caso base: array con 0 o 1 elementi
    if (low >= high) {
        return;
    }
    
    // DIVIDE: partiziona e ottieni posizione del pivot
    int pi = partition(arr, low, high);
    
    // IMPERA: ordina le due parti (pivot gia in posizione!)
    quickSort(arr, low, pi - 1);   // Elementi < pivot
    quickSort(arr, pi + 1, high);  // Elementi > pivot
    
    // COMBINA: nulla da fare! L'array e gia ordinato
}
```

**Complessita:**
- Tempo medio: $O(n \log n)$
- Tempo peggiore: $O(n^2)$ (quando l'array e gia ordinato e pivot = ultimo)
- Spazio: $O(\log n)$ per lo stack di ricorsione

---

### 3.4 Ricerca del Massimo e Minimo

**Problema:** Trovare max e min in un array con meno confronti possibili.

**Approccio Naive:** $2(n-1)$ confronti
```cpp
// Naive: 2n-2 confronti
int maxNaive = arr[0], minNaive = arr[0];
for (int i = 1; i < n; i++) {
    if (arr[i] > maxNaive) maxNaive = arr[i];
    if (arr[i] < minNaive) minNaive = arr[i];
}
```

**Approccio Divide et Impera:** $\frac{3n}{2} - 2$ confronti
```cpp
struct MinMax {
    int min, max;
};

MinMax findMinMax(int arr[], int low, int high) {
    MinMax result, left, right;
    
    // Caso base: un solo elemento
    if (low == high) {
        result.min = result.max = arr[low];
        return result;
    }
    
    // Caso base: due elementi
    if (high == low + 1) {
        if (arr[low] < arr[high]) {
            result.min = arr[low];
            result.max = arr[high];
        } else {
            result.min = arr[high];
            result.max = arr[low];
        }
        return result;
    }
    
    // DIVIDE
    int mid = (low + high) / 2;
    
    // IMPERA
    left = findMinMax(arr, low, mid);
    right = findMinMax(arr, mid + 1, high);
    
    // COMBINA
    result.min = min(left.min, right.min);
    result.max = max(left.max, right.max);
    
    return result;
}
```

---

## 4. Analisi della Complessita

### Master Theorem
Per ricorrenze della forma:
$$T(n) = aT\left(\frac{n}{b}\right) + f(n)$$

Dove:
- $a$ = numero di sottoproblemi
- $n/b$ = dimensione di ogni sottoproblema
- $f(n)$ = costo della divisione + combinazione

### Casi del Master Theorem

Sia $c_{crit} = \log_b a$

| Caso | Condizione | Risultato |
|------|------------|-----------|
| 1 | $f(n) = O(n^c)$ con $c < c_{crit}$ | $T(n) = \Theta(n^{c_{crit}})$ |
| 2 | $f(n) = \Theta(n^{c_{crit}})$ | $T(n) = \Theta(n^{c_{crit}} \log n)$ |
| 3 | $f(n) = \Omega(n^c)$ con $c > c_{crit}$ | $T(n) = \Theta(f(n))$ |

### Esempi Applicati

**Binary Search:**
$$T(n) = T(n/2) + O(1)$$
- $a=1, b=2, f(n)=O(1)$
- $c_{crit} = \log_2 1 = 0$
- Caso 2: $T(n) = O(\log n)$

**Merge Sort:**
$$T(n) = 2T(n/2) + O(n)$$
- $a=2, b=2, f(n)=O(n)$
- $c_{crit} = \log_2 2 = 1$
- Caso 2: $T(n) = O(n \log n)$

**Karatsuba (moltiplicazione veloce):**
$$T(n) = 3T(n/2) + O(n)$$
- $a=3, b=2, f(n)=O(n)$
- $c_{crit} = \log_2 3 \approx 1.585$
- Caso 1: $T(n) = O(n^{1.585})$ (meglio di $O(n^2)$!)

---

## 5. Quando Usarlo

### Usalo quando:
- Il problema puo essere scomposto in sottoproblemi **simili e indipendenti**
- La combinazione delle soluzioni e efficiente
- I sottoproblemi sono **bilanciati** (stessa dimensione approssimativa)

### NON usarlo quando:
- I sottoproblemi si **sovrappongono** (usa Programmazione Dinamica)
- Il costo di divisione/combinazione e troppo alto
- Esiste una soluzione iterativa piu semplice

---

## 6. Esempi Avanzati

### 6.1 Potenza in O(log n)

**Problema:** Calcolare $x^n$ velocemente.

```cpp
double potenza(double x, int n) {
    // Caso base
    if (n == 0) return 1;
    if (n < 0) return 1 / potenza(x, -n);
    
    // DIVIDE: calcola x^(n/2)
    double half = potenza(x, n / 2);
    
    // COMBINA
    if (n % 2 == 0) {
        return half * half;        // x^n = (x^(n/2))^2
    } else {
        return half * half * x;    // x^n = (x^(n/2))^2 * x
    }
}
```

**Complessita:** $O(\log n)$ invece di $O(n)$!

---

### 6.2 Moltiplicazione di Matrici (Strassen)

L'algoritmo di Strassen riduce la moltiplicazione di matrici $n \times n$ da $O(n^3)$ a $O(n^{2.81})$.

---

### 6.3 Contare le Inversioni

**Problema:** Contare le coppie $(i, j)$ con $i < j$ e $arr[i] > arr[j]$.

```cpp
int mergeCount(int arr[], int temp[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    int invCount = 0;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            invCount += (mid - i + 1);  // Tutte le inversioni!
        }
    }
    
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    
    for (i = left; i <= right; i++)
        arr[i] = temp[i];
    
    return invCount;
}

int countInversions(int arr[], int temp[], int left, int right) {
    int count = 0;
    if (left < right) {
        int mid = (left + right) / 2;
        count += countInversions(arr, temp, left, mid);
        count += countInversions(arr, temp, mid + 1, right);
        count += mergeCount(arr, temp, left, mid, right);
    }
    return count;
}
```

**Complessita:** $O(n \log n)$ invece di $O(n^2)$!

---

## Riepilogo

| Algoritmo | Divide | Impera | Combina | Complessita |
|-----------|--------|--------|---------|-------------|
| Binary Search | Meta array | 1 chiamata | Nulla | $O(\log n)$ |
| Merge Sort | 2 meta | 2 chiamate | Merge $O(n)$ | $O(n \log n)$ |
| Quick Sort | Partiziona | 2 chiamate | Nulla | $O(n \log n)$ avg |
| Potenza | $n/2$ | 1 chiamata | Moltiplicazione | $O(\log n)$ |
| Strassen | Sottomatrici | 7 chiamate | Somme | $O(n^{2.81})$ |
