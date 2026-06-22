# Guida Pratica: Makespan e Palindromi

## Indice
1. [Analisi Makespan: Approccio Greedy](#1-analisi-makespan-approccio-greedy)
2. [Analisi Makespan: Approccio Backtracking](#2-analisi-makespan-approccio-backtracking)
3. [Analisi Palindromi: Programmazione Dinamica](#3-analisi-palindromi-programmazione-dinamica)
4. [Trace di Esecuzione LPS](#4-trace-di-esecuzione-lps)

---

## 1. Analisi Makespan: Approccio Greedy

### 1.1 Funzione `getMacchinaPiuScarica`
Questa funzione è il cuore della scelta golosa:
```cpp
int getMacchinaPiuScarica(vector<int>& lavoro_macchina, int num_macchine){
    int macchina_piu_scarica = 0;
    for(int i = 1; i < num_macchine; i++){
        if(lavoro_macchina[i] < lavoro_macchina[macchina_piu_scarica]){
            macchina_piu_scarica = i;
        }
    }
    return macchina_piu_scarica;
}
```
**Perché funziona?** Minimizza l'incremento del makespan ad ogni passo.

### 1.2 Importanza del Sort
Se non ordinassimo i job in modo decrescente, il risultato sarebbe pessimo. 
- **Esempio**: Job {1, 1, 1, 1, 5}, 2 macchine.
- **Senza Sort**: M1={1,1,5}=7, M2={1,1}=2. Makespan = 7.
- **Con Sort**: M1={5}=5, M2={1,1,1,1}=4. Makespan = 5.

---

## 2. Analisi Makespan: Approccio Backtracking

### 2.1 La struttura `Soluzione`
Contiene lo stato globale:
- `loadMacchine`: carico attuale di ogni macchina.
- `solution`: il miglior makespan trovato finora (inizializzato a `INT_MAX`).

### 2.2 Pruning Strategico
```cpp
bool canAdd(unsigned job_idx, int macchina, const Soluzione& soluzione) {
    unsigned newMakespan = soluzione.loadMacchine[macchina] + soluzione.jobs[job_idx];
    if (newMakespan >= soluzione.solution) {
        return false; // Inutile continuare, abbiamo già superato l'ottimo corrente
    }
    return true;
}
```

---

## 3. Analisi Palindromi: Programmazione Dinamica

### 3.1 Differenza tra Sottostringa e Sottosequenza
- **Sottostringa**: Caratteri consecutivi (es. "ABC").
- **Sottosequenza**: Caratteri in ordine ma sparsi (es. "ACE" in "ABCDE").
- L'algoritmo implementato trova la **sottosequenza**.

### 3.2 Memoization Table
In `main.cpp`, la matrice `dp[SIZE][SIZE]` evita ricalcoli. Senza di essa, la complessità sarebbe $O(2^N)$ a causa delle biforcazioni `max(L(i+1,j), L(i,j-1))`. Con la tabella, ogni cella viene calcolata una sola volta: $O(N^2)$.

---

## 4. Trace di Esecuzione LPS

Stringa $S = "BBABC"$. Cerco $L(0, 4)$.

1.  **Chiamata $L(0, 4)$**: $S[0]='B', S[4]='C'$. Diversi.
    -   $\max(L(1, 4), L(0, 3))$
2.  **Sotto-chiamata $L(1, 4)$**: $S[1]='B', S[4]='C'$. Diversi.
    -   $\max(L(2, 4), L(1, 3))$
3.  **Sotto-chiamata $L(0, 3)$**: $S[0]='B', S[3]='B'$. UGUALI!
    -   $2 + L(1, 2)$
4.  **Sotto-chiamata $L(1, 2)$**: $S[1]='B', S[2]='A'$. Diversi.
    -   $\max(L(2, 2), L(1, 1))$
5.  **Casi Base**:
    -   $L(2, 2) = 1$ (un solo carattere 'A')
    -   $L(1, 1) = 1$ (un solo carattere 'B')
6.  **Risalita**:
    -   $L(1, 2) = \max(1, 1) = 1$
    -   $L(0, 3) = 2 + 1 = 3$
    -   ... e così via ...

**Risultato finale**: LPS = 3 (es. "BBB" o "BAB").
