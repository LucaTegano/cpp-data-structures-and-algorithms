//
// Created by admin on 17/12/2025.
//

#ifndef SOLUZIONE20250613_GESTIONEDEBITI_H
#define SOLUZIONE20250613_GESTIONEDEBITI_H
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class GestioneDebiti {
public:
    GestioneDebiti(const vector<string> &amici);

    void anticipa(string x, string y, float k);
    float saldo(string x, string y) const;
    void paga (string x, string y, float k);

private:
    //assegno un ID di conto ad ogni amico
    unordered_map<string, unsigned> contoAmici;
    //una matrice di adiacenza contenenti i debiti
    // contiCompagnia[i][j] indica quandti soldi i deve dare a j, dove i e j sono gli ID definiti dalla struttura sopra
    // le righe sono debiti, le colonne sono crediti
    vector<vector<float> > contiCompagnia;
};


#endif //SOLUZIONE20250613_GESTIONEDEBITI_H
