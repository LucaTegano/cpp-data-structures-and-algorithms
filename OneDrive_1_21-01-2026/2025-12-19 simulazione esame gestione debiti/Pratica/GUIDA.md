# Guida Pratica: Simulazione d'Esame - Risoluzione Esercizi

## Indice
1. [Analisi Esercizio 2: GestioneDebiti](#1-analisi-esercizio-2-gestionedebiti)
2. [Analisi Esercizio 3: Algoritmo Spremi (Ricorsione)](#2-analisi-esercizio-3-algoritmo-spremi-ricorsione)
3. [Analisi Esercizio 4: Ciclo Hamiltoniano (Backtracking)](#3-analisi-esercizio-4-ciclo-hamiltoniano-backtracking)
4. [Trace di Esecuzione Hamilton](#4-trace-di-esecuzione-hamilton)

---

## 1. Analisi Esercizio 2: GestioneDebiti

### 1.1 Mappa e Matrice
La classe usa una mappa per tradurre nomi in indici. 
```cpp
contoAmici[amici[i]] = i; 
```
Se la compagnia è `{"Luca", "Anna", "Marco"}`, la mappa sarà:
- `Luca` → 0
- `Anna` → 1
- `Marco` → 2

La matrice `contiCompagnia` sarà $3 \times 3$.

### 1.2 Anticipo di Gruppo (`y == "*"`)
Quando un amico paga per tutti, il debito viene diviso. 
Esempio: Marco paga 30€ per il gruppo.
- `quota = 30 / 3 = 10€`
- La riga di Luca, Anna e Marco riceve `+10` nella colonna di Marco (ID 2).
- `contiCompagnia[0][2] += 10`, `contiCompagnia[1][2] += 10`, `contiCompagnia[2][2] += 10`.

---

## 2. Analisi Esercizio 3: Algoritmo Spremi (Ricorsione)

### 2.1 Logica del `cc_value`
Il nodo corrente "si svuota". Tutto il suo valore fluisce verso il basso.
```cpp
float cc_value = (alberoB.radice() + c_value) / 2;
```
Se un nodo ha valore 4 e riceve 6 dal padre, il valore totale da distribuire è 10. Ogni figlio riceverà 5.

### 2.2 Casi Particolari
- **Nodo Nullo**: Se un valore arriva a un figlio che non esiste, viene aggiunto alla `quota` esterna. Questo simula la perdita di valore nei "rami secchi".
- **Foglia**: La foglia è un "serbatoio finale". Somma il suo valore a quello ricevuto e non distribuisce più nulla.

---

## 3. Analisi Esercizio 4: Ciclo Hamiltoniano (Backtracking)

### 3.1 Funzione `canAdd`
Controlla due condizioni fondamentali:
1. **Esistenza Arco**: Deve esserci un collegamento tra l'ultimo nodo inserito e il candidato.
2. **Unicità**: Il candidato non deve essere già stato visitato.

```cpp
bool canAdd(int nodo, Soluzione &soluzione) {
    return (find(soluzione.ciclo.begin(), soluzione.ciclo.end(), nodo) == soluzione.ciclo.end() && 
            soluzione.g(soluzione.ciclo.back(), nodo));
}
```

### 3.2 Funzione `isComplete`
Il cammino è Hamiltoniano se:
1. Contiene tutti i nodi (`size == g.n()`).
2. Si può chiudere il ciclo (arco dall'ultimo al primo).

---

## 4. Trace di Esecuzione Hamilton

Consideriamo il **Test 4** del `main.cpp`:
Grafo con 4 nodi: 0, 1, 2, 3.
Archi: 0→1, 0→2, 1→2, 2→3, 3→0.

**Esecuzione:**
1.  **Partenza**: `ciclo = [0]`
2.  **Prova Nodo 1**: `canAdd(1)`? Arco 0→1 esiste? Sì. 1 già in ciclo? No.
    -   `ciclo = [0, 1]`
    -   **Sotto-chiamata solve**:
        -   Prova Nodo 2: `canAdd(2)`? Arco 1→2 esiste? Sì. 2 in ciclo? No.
            -   `ciclo = [0, 1, 2]`
            -   **Sotto-chiamata solve**:
                -   Prova Nodo 3: `canAdd(3)`? Arco 2→3 esiste? Sì. 3 in ciclo? No.
                    -   `ciclo = [0, 1, 2, 3]`
                    -   `isComplete`? `size=4 == n=4`? Sì. Arco 3→0 esiste? Sì.
                    -   **Ritorna TRUE**.
3.  **Risultato**: `0 1 2 3`.

**Cosa succede se proviamo prima il nodo 2 da 0?**
1.  `ciclo = [0, 2]`
2.  Prova Nodo 3: `canAdd(3)`? Sì (Arco 2→3).
    -   `ciclo = [0, 2, 3]`
3.  Prova nodi rimanenti:
    -   Nodo 1? `canAdd(1)`? Arco 3→1 esiste? **NO**.
    -   Nessun altro nodo disponibile.
4.  **Backtrack**: Rimuovi 3, prova altri da 2... (nessuno)
5.  **Backtrack**: Rimuovi 2, prova prossimo da 0 (che è 1)... e si torna al caso di successo.
