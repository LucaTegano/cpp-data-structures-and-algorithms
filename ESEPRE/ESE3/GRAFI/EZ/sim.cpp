/*
Dato in input un albero binario tree, implementato tramite la classe
AlberoB<int> tree, implementare una funzione esercizio3(...) che restituisca
true se e solo se, per ogni livello, la somma dei valori di quel livello è
minore della somma dei valori del livello successivo (se esiste). In caso
contrario, la funzione deve restituire false. Si assuma che la radice si trovi
al livello 0. La classe AlberoB<T> mette a disposizione la seguente interfaccia
pubblica di metodi costanti (tree istanza di AlberoB<T>): • tree. radice ()
restituisce il valore informativo di tree (di tipo T) • tree. figlio (DIR)
restituisce il sottoalbero sinistro (DIR=S IN) e destro (DIR=DES) di tree •
tree.nullo() restituisce true se tree è un albero nullo e false altrimenti •
tree. foglia () restituisce true se tree è una foglia e false altrimenti
*/
#include "../../../../esami/prof/AlberoB.h"
#include <iostream>
#include <queue>
using namespace std;

bool esercizio3(const AlberoB<int> &tree) {
  if (tree.nullo())
    return true;

  queue<AlberoB<int>> q;
  q.push(tree);

  int prev_sum = 0;
  bool first_level = true;

  while (!q.empty()) {
    int level_nodes = q.size();
    int current_sum = 0;

    for (int i = 0; i < level_nodes; ++i) {
      AlberoB<int> current = q.front();
      q.pop();

      current_sum += current.radice();

      if (!current.figlio(SIN).nullo()) {
        q.push(current.figlio(SIN));
      }
      if (!current.figlio(DES).nullo()) {
        q.push(current.figlio(DES));
      }
    }

    if (!first_level) {
      if (prev_sum >= current_sum) {
        return false;
      }
    }

    prev_sum = current_sum;
    first_level = false;
  }

  return true;
}

int main() {
  // Test Case 1: True
  //      1
  //     / \
  //    2   3
  // Sums: L0=1, L1=5. 1 < 5. Expected: True
  AlberoB<int> t1(1);
  t1.insFiglio(SIN, AlberoB<int>(2));
  t1.insFiglio(DES, AlberoB<int>(3));
  cout << "Test 1: " << (esercizio3(t1) ? "PASSED" : "FAILED") << endl;

  // Test Case 2: False
  //      10
  //     /  \
  //    2    3
  // Sums: L0=10, L1=5. 10 > 5. Expected: False
  AlberoB<int> t2(10);
  t2.insFiglio(SIN, AlberoB<int>(2));
  t2.insFiglio(DES, AlberoB<int>(3));
  cout << "Test 2: " << (!esercizio3(t2) ? "PASSED" : "FAILED") << endl;

  // Test Case 3: Multiple levels
  //      1
  //     / \
  //    2   3
  //   / \
  //  4   5
  // Sums: L0=1, L1=5, L2=9. 1 < 5 < 9. Expected: True
  AlberoB<int> t3(1);
  AlberoB<int> n2(2);
  n2.insFiglio(SIN, AlberoB<int>(4));
  n2.insFiglio(DES, AlberoB<int>(5));
  t3.insFiglio(SIN, n2);
  t3.insFiglio(DES, AlberoB<int>(3));
  cout << "Test 3: " << (esercizio3(t3) ? "PASSED" : "FAILED") << endl;

  return 0;
}