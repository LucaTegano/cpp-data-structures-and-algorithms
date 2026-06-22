# Lezione: Ottimizzazione e Dinamica - Makespan e Palindromi

## Indice
1. [Introduzione](#1-introduzione)
2. [Problema del Makespan (Multiprocessor Scheduling)](#2-problema-del-makespan-multiprocessor-scheduling)
3. [Approccio Greedy: Euristica LPT](#3-approccio-greedy-euristica-lpt)
4. [Approccio Esatto: Backtracking](#4-approccio-esatto-backtracking)
5. [Longest Palindromic Subsequence (LPS) - Dinamica](#5-longest-palindromic-subsequence-lps---dinamica)
6. [Analisi delle Complessità](#6-analisi-delle-complessità)

---

## 1. Introduzione
Questa lezione affronta due temi centrali dell'informatica:
- **Scheduling di Risorse**: Come dividere il lavoro tra più agenti (macchine) per finire il prima possibile.
- **Analisi di Sequenze**: Come trovare pattern (palindromi) in modo efficiente usando la memoria dei sottoproblemi.

---

## 2. Problema del Makespan (Multiprocessor Scheduling)

### 2.1 Definizione
Dati $N$ lavori (jobs) con durata $t_1, t_2, \dots, t_n$ e $M$ macchine identiche, l'obiettivo è assegnare ogni lavoro a una macchina in modo da minimizzare il **makespan**.
- **Makespan**: Il tempo di completamento dell'ultima macchina che finisce il lavoro (il massimo carico tra le macchine).

### 2.2 Difficoltà
Il problema è **NP-difficile**. Non esiste un algoritmo polinomiale per trovare sempre la soluzione ottima. Si usano quindi:
- **Euristiche**: Veloci, ma approssimate.
- **Backtracking**: Trova l'ottimo, ma lento.

---

## 3. Approccio Greedy: Euristica LPT

### 3.1 Longest Processing Time (LPT) first
L'idea è semplice: i lavori più lunghi sono i più difficili da "incastrare" alla fine. Meglio assegnarli subito.

**Algoritmo:**
1. Ordina i lavori in ordine **decrescente** di durata.
2. Per ogni lavoro, assegnalo alla macchina che ha il **carico totale minimo** in quel momento.

### 3.2 Analisi dell'Esempio
Lavori: $\{5, 4, 3, 2, 1, 1\}$, Macchine: $M=2$.
- Ordine: $5, 4, 3, 2, 1, 1$.
1. Job 5 → Macchina 1 (carico: 5)
2. Job 4 → Macchina 2 (carico: 4)
3. Job 3 → Macchina 2 (carico: 4+3=7)
4. Job 2 → Macchina 1 (carico: 5+2=7)
5. Job 1 → Macchina 1 (carico: 7+1=8)
6. Job 1 → Macchina 2 (carico: 7+1=8)
**Makespan: 8**.

---

## 4. Approccio Esatto: Backtracking

### 4.1 Logica di Esplorazione
Il backtracking prova ogni possibile assegnamento:
- Il lavoro 1 può andare sulla macchina 1, 2, ..., M.
- Per ogni scelta, il lavoro 2 può andare sulla macchina 1, 2, ..., M.
- E così via...

### 4.2 Pruning (Potatura)
Per velocizzare la ricerca, si usa una variabile `best_makespan`. Se durante l'assegnamento parziale il carico di una macchina supera già `best_makespan`, si interrompe quel ramo (`canAdd` ritorna `false`).

---

## 5. Longest Palindromic Subsequence (LPS) - Dinamica

### 5.1 Definizione
Data una stringa $S$, trovare la lunghezza della più lunga sottosequenza che è un palindromo.
- **Sottosequenza**: Caratteri presi in ordine ma non necessariamente consecutivi.
- Esempio: "BBABCBCAB" → "BABCBAB" (LPS = 7).

### 5.2 Sottostruttura Ottima (Recurrence)
Sia $L(i, j)$ la lunghezza della LPS nella sottostringa $S[i \dots j]$:
1. **Se $i > j$**: $L = 0$.
2. **Se $i = j$**: $L = 1$ (un carattere è sempre palindromo).
3. **Se $S[i] == S[j]$**: $L = 2 + L(i+1, j-1)$ (i due estremi fanno parte del palindromo).
4. **Se $S[i] \neq S[j]$**: $L = \max(L(i+1, j), L(i, j-1))$ (proviamo a scartare uno dei due estremi).

### 5.3 Implementazione con Memoization
Si usa una matrice `dp[N][N]` inizializzata a -1. Prima di calcolare $L(i, j)$, si controlla se il valore è già in `dp`.

---

## 6. Analisi delle Complessità

| Problema | Algoritmo | Complessità Temporale | Spazio |
|----------|-----------|-----------------------|--------|
| Makespan | Greedy (LPT) | $O(N \log N + N \cdot M)$ | $O(N + M)$ |
| Makespan | Backtracking | $O(M^N)$ | $O(N)$ |
| LPS | Dinamica | $O(N^2)$ | $O(N^2)$ |

**Nota**: $N \cdot M$ nel greedy deriva dalla ricerca della macchina più scarica per ogni job. Può essere ridotto a $N \log M$ usando una min-priority-queue.
