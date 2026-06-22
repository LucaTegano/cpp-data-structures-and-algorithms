#include "../../../esami/prof/AlberoB.h"
#include <iostream>
#include <queue> // Necessario per la BFS
using namespace std;

// ============================================================
// ESERCIZIO 3 - Funzione "spremi"
// ============================================================
//
// L'esercizio richiede di distribuire il valore di un nodo ai suoi figli.
// Se un figlio manca, la quantità destinata a lui viene "accumulata".
//
// Si possono usare due approcci di visita:
// 1. DFS (Depth First Search) - Ricorsiva (quella vista prima)
// 2. BFS (Breadth First Search) - Iterativa (a livelli, con una Coda)
// ============================================================

// ------------------------------------------------------------
// APPROCCIO 1: DFS RICORSIVA (quella originale)
// ------------------------------------------------------------

// Funzione ausiliaria ricorsiva
float spremiAux_DFS(AlberoB<float> &tree, float ricevuto) {
  if (tree.nullo())
    return 0;

  // CASO BASE: foglia -> accumula il ricevuto e stop
  if (tree.foglia()) {
    tree.modRadice(tree.radice() + ricevuto);
    return 0;
  }

  // CASO NODO INTERNO
  float budget = tree.radice() + ricevuto;
  tree.modRadice(0); // Svuota il nodo corrente
  float meta = budget / 2.0f;

  float accumulato = 0;

  // Gestione Figlio Sinistro
  if (tree.figlio(SIN).nullo()) {
    accumulato += meta; // Figlio nullo -> recupera la metà
  } else {
    AlberoB<float> fs = tree.figlio(SIN);
    accumulato += spremiAux_DFS(fs, meta); // Passa la metà
  }

  // Gestione Figlio Destro
  if (tree.figlio(DES).nullo()) {
    accumulato += meta; // Figlio nullo -> recupera la metà
  } else {
    AlberoB<float> fd = tree.figlio(DES);
    accumulato += spremiAux_DFS(fd, meta); // Passa la metà
  }

  return accumulato;
}

float spremiDFS(AlberoB<float> &tree) {
  if (tree.nullo())
    return 0;
  return spremiAux_DFS(tree, 0);
}

// ------------------------------------------------------------
// APPROCCIO 2: BFS ITERATIVA (con coda)
// ------------------------------------------------------------

// Struttura di appoggio per la coda
struct Elemento {
  AlberoB<float> nodo; // Il sottoalbero (nodo corrente)
  float ricevuto;      // Quanto riceve dal padre
};

float spremiBFS(AlberoB<float> &tree) {
  if (tree.nullo())
    return 0;

  float totaleAccumulato = 0;
  queue<Elemento> q;

  // Inseriamo la radice nella coda con ricevuto = 0
  q.push({tree, 0});

  while (!q.empty()) {
    Elemento curr = q.front();
    q.pop();

    AlberoB<float> nodo = curr.nodo;
    float ricevuto = curr.ricevuto;

    // Se è una foglia: assorbe il valore e NON lo passa a nessuno
    if (nodo.foglia()) {
      nodo.modRadice(nodo.radice() + ricevuto);
      continue; // Passa al prossimo elemento in coda
    }

    // Se è un nodo interno: calcola, svuota e distribuisce
    float budget = nodo.radice() + ricevuto;
    nodo.modRadice(0); // Svuota
    float meta = budget / 2.0f;

    // Gestione Figlio Sinistro
    AlberoB<float> fs = nodo.figlio(SIN);
    if (fs.nullo()) {
      totaleAccumulato += meta; // Niente figlio -> accumulo subito
    } else {
      q.push({fs, meta}); // Metto in coda per visita futura
    }

    // Gestione Figlio Destro
    AlberoB<float> fd = nodo.figlio(DES);
    if (fd.nullo()) {
      totaleAccumulato += meta; // Niente figlio -> accumulo subito
    } else {
      q.push({fd, meta}); // Metto in coda per visita futura
    }
  }

  return totaleAccumulato;
}

// ============================================================
// MAIN DI TEST
// ============================================================

int main() {
  // Costruzione albero (copia 1 per DFS)
  AlberoB<float> n2(2);
  AlberoB<float> n1(1);

  AlberoB<float> n3(3);
  n3.insFiglio(SIN, n2);

  AlberoB<float> n4(4);
  n4.insFiglio(SIN, n1);

  AlberoB<float> treeDFS(5);
  treeDFS.insFiglio(SIN, n3);
  treeDFS.insFiglio(DES, n4);

  // Creiamo una copia esatta per la BFS (poiché spremi modifica l'albero!)
  // Usiamo il metodo copia()
  AlberoB<float> treeBFS = treeDFS.copia();

  cout << "--- TEST DFS (Ricorsiva) ---" << endl;
  cout << "Totale Accumulato: " << spremiDFS(treeDFS) << endl;
  // Verifica foglie:
  // treeDFS.figlio(SIN).figlio(SIN).radice() dovrebbe essere 4.75

  cout << "\n--- TEST BFS (Iterativa) ---" << endl;
  cout << "Totale Accumulato: " << spremiBFS(treeBFS) << endl;

  return 0;
}
