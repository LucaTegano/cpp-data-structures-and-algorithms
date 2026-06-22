#include "../../../../esami/prof/AlberoB.h"
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
bool esercizio1(...) che restituisce true se la somma dei nodi ai livelli pari è
maggiore della somma dei nodi ai livelli dispari.

bool esercizio1_1(...) che restituisce true se la somma dei nodi a ogni livello
pari è minore della somma dei nodi a ogni livello dispari.

int esercizio2(...) che restituisce il livello che contiene il massimo numero di
nodi. Se più livelli hanno lo stesso numero massimo, restituisci il più
piccolo.

bool esercizio3(...) che restituisce true se per ogni livello il valore massimo
è minore del valore massimo del livello successivo.

bool esercizio4(...) che restituisce true se per ogni nodo non foglia, i figli
(se esistono) hanno valore strettamente maggiore del padre.

int esercizio5(...) che conta quanti livelli hanno somma dei valori pari.

bool esercizio6(...) che restituisce true se per ogni nodo la differenza tra
numero di nodi del sottoalbero sinistro e destro è ≤ 1.

int esercizio7(...) che restituisce la somma massima lungo un percorso da radice
a foglia.

bool esercizio8(...) che restituisce true se per ogni livello i valori dei nodi
sono tutti crescenti da sinistra a destra.

int esercizio9(...) che restituisce il livello con il maggior numero di
foglie.

bool esercizio10(...) che restituisce true se tutte le foglie stanno allo stesso
livello.*/
/*
bool esercizio1(const AlberoB<int> &bt) {
  if (bt.nullo())
    return false;

  queue<AlberoB<int>> q;
  q.push(bt);

  int level = 0;
  int sum_pari = 0;
  int sum_dispari = 0;

  while (!q.empty()) {
    int level_size = q.size();

    for (int i = 0; i < level_size; ++i) {
      AlberoB<int> curr = q.front();
      q.pop();

      if (level % 2 == 0)
        sum_pari += curr.radice();
      else
        sum_dispari += curr.radice();

      if (!curr.figlio(SIN).nullo())
        q.push(curr.figlio(SIN));
      if (!curr.figlio(DES).nullo())
        q.push(curr.figlio(DES));
    }
    level++;
    }
    return sum_pari > sum_dispari;
  }
*/

/*
bool esercizio1_1(const AlberoB<int> &tree) {
  if (tree.nullo())
    return true;

  queue<AlberoB<int>> q;
  q.push(tree);

  vector<int> sommePari, sommeDispari;
  int level = 0;

  while (!q.empty()) {
    int n = q.size();
    int current_sum = 0;

    for (int i = 0; i < n; ++i) {
      AlberoB<int> curr = q.front();
      q.pop();
      current_sum += curr.radice();

      if (!curr.figlio(SIN).nullo())
        q.push(curr.figlio(SIN));
      if (!curr.figlio(DES).nullo())
        q.push(curr.figlio(DES));
    }

    if (level % 2 == 0)
      sommePari.push_back(current_sum);
    else
      sommeDispari.push_back(current_sum);

    level++;
  }

  if (sommeDispari.empty())
    return true; // Solo livello 0, condizione tecnicamente vera

  // Trova il massimo dei pari
  int maxPari = sommePari[0];
  for (int s : sommePari)
    if (s > maxPari)
      maxPari = s;

  // Trova il minimo dei dispari
  int minDispari = sommeDispari[0];
  for (int s : sommeDispari)
    if (s < minDispari)
      minDispari = s;

  return maxPari < minDispari;
}
*/
/*

int esercizio2(AlberoB<int> bt) {
  if (bt.nullo())
    return -1;

  queue<AlberoB<int>> q;
  q.push(bt);

  int max_nodes = 0;
  int sol_level = 0;
  int curr_level = 0;

  while (!q.empty()) {
    int level_size = q.size(); // Questo è già il numero di nodi del livello

    // Confronto: se trovo un livello con PIÙ nodi, aggiorno.
    // Se è uguale, il '>' non entra, mantenendo il sol_level più piccolo.
    if (level_size > max_nodes) {
      max_nodes = level_size;
      sol_level = curr_level;
    }

    // Svuoto il livello attuale e pusho i figli
    for (int i = 0; i < level_size; ++i) {
      AlberoB<int> current = q.front();
      q.pop();

      if (!current.figlio(SIN).nullo())
        q.push(current.figlio(SIN));
      if (!current.figlio(DES).nullo())
        q.push(current.figlio(DES));
    }

    curr_level++;
  }

  return sol_level;
}
*/

/*
bool esercizio3(AlberoB<int> &bt) {
  if (bt.nullo()) {
    return true;
  }
  queue<AlberoB<int>> q;
  q.push(bt);
  int prev_val = -10000;
  bool first_level = true;
  while (!q.empty()) {
    int node_size = q.size();
    int curr_val = -10000;
    for (int i = 0; i < node_size; ++i) {
      AlberoB<int> current = q.front();
      q.pop();
      if (current.radice() > curr_val) {
        curr_val = current.radice();
      }
      if (!current.figlio(SIN).nullo())
        q.push(current.figlio(SIN));
      if (!current.figlio(DES).nullo())
        q.push(current.figlio(DES));
    }
    if (!first_level && prev_val >= curr_val) {
      return false;
    }
    prev_val = curr_val;
    first_level = false;
  }
  return true;
}
*/