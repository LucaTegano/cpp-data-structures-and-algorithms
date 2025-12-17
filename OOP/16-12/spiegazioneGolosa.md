# Spiegazione Approccio Goloso (Greedy)

## L'Algoritmo

L'approccio "goloso" (o *Greedy*) per la ricerca di un cammino in un grafo consiste nel prendere, ad ogni passo, la decisione che appare migliore localmente, senza preoccuparsi delle conseguenze future.

Nel contesto della ricerca di un cammino da un nodo $S$ a un nodo $T$, la strategia più comune è quella del **Nearest Neighbor** (Vicino più prossimo):
1.  Partendo dal nodo corrente (inizialmente $S$).
2.  Si esaminano tutti gli archi uscenti verso nodi **non ancora visitati**.
3.  Si sceglie l'arco con il **peso minimo** (costo minore).
4.  Ci si sposta sul nuovo nodo e si ripete il processo finché non si raggiunge $T$.

### Perché non è ottimo?

Questo approccio **non garantisce** di trovare il cammino di costo minimo globale (shortest path). Scegliere l'arco più leggero subito potrebbe costringerci a percorrere archi molto pesanti in seguito, che avremmo potuto evitare facendo una scelta inizialmente più "costosa" ma strategicamente migliore.

---

## Esempio Step-by-Step (Controesempio)

Consideriamo il grafo implementato nel programma, dove l'approccio goloso fallisce.

### Dati dell'istanza
- **Nodi**: 0, 1, 2
- **Archi**:
  - `0 -> 1` con peso **1**
  - `0 -> 2` con peso **10**
  - `1 -> 2` con peso **100**
- **Obiettivo**: Trovare il cammino da **0** a **2**.

### Esecuzione dell'algoritmo Goloso

#### Passo 1: Analisi dal nodo 0
Siamo nel nodo **0**. Dobbiamo scegliere dove andare.
Opzioni disponibili verso nodi non visitati:
- Andare a **1**: costo arco = **1**
- Andare a **2**: costo arco = **10**

La scelta golosa è quella col costo minore.
> $1 < 10$, quindi l'algoritmo sceglie di andare al nodo **1**.

- **Cammino attuale**: `0 -> 1`
- **Costo parziale**: 1
- **Nodo corrente**: 1

#### Passo 2: Analisi dal nodo 1
Siamo nel nodo **1**.
Opzioni disponibili verso nodi non visitati:
- Andare a **2**: costo arco = **100**

C'è solo una scelta possibile (oltre a tornare indietro, ma qui assumiamo di proseguire verso la destinazione o nodi nuovi).
> L'algoritmo sceglie di andare al nodo **2**.

- **Cammino attuale**: `0 -> 1 -> 2`
- **Costo parziale**: $1 + 100 = 101$
- **Nodo corrente**: 2

#### Passo 3: Arrivo
Siamo arrivati al nodo destinazione **2**. L'algoritmo termina.

### Risultato Goloso
- **Cammino**: `0 -> 1 -> 2`
- **Costo Totale**: **101**

---

### Confronto con l'Ottimo

Se avessimo guardato "oltre" il primo passo, avremmo notato l'altra possibilità iniziale:
- Andare direttamente da **0** a **2**.
- **Costo dell'arco**: **10**.
- Siamo subito a destinazione.

### Risultato Ottimo
- **Cammino**: `0 -> 2`
- **Costo Totale**: **10**

### Conclusione
L'algoritmo goloso ha scelto `0 -> 1` per risparmiare **9** unità di costo inizialmente ($10 - 1$), ma questa scelta lo ha costretto a pagare **100** dopo. Il cammino trovato (101) è molto peggiore di quello ottimo (10).
