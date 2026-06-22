//
// Created by admin on 17/12/2025.
//

#include "GestioneDebiti.h"

#include <iostream>

GestioneDebiti::GestioneDebiti(const vector<string> &amici) {
    for (unsigned i = 0; i < amici.size(); i++) {
        contoAmici[amici[i]] = i; //assegno un conto ad ogni amico
        contiCompagnia.push_back(vector<float>(amici.size(), 0));
    }
}

void GestioneDebiti::anticipa(string x, string y, float k) {
    if (k <= 0.0)
        return;
    unsigned contoCreditore = contoAmici[x];
    if (y == "*") {
        float quota = k / contiCompagnia.size();
        for (unsigned i = 0; i < contiCompagnia.size(); i++) {
            contiCompagnia[i][contoCreditore] += quota;
        }
    } else {
        unsigned contoDebitore = contoAmici[y];
        contiCompagnia[contoDebitore][contoCreditore] += k;
    }
}

float GestioneDebiti::saldo(string x, string y) const {
	if(!contoAmici.contains(x)||!contoAmici.contains(y)){
		cout<<"Gli amici specificati non sono validi";
		return 0;
	}
    unsigned contoDebitore = contoAmici.at(x);
    unsigned contoCreditore = contoAmici.at(y); //at è const [] non è const
	float somma=contiCompagnia[contoDebitore][contoCreditore] - contiCompagnia[contoCreditore][contoDebitore];
    return somma>=0.0 ? somma : 0;
}

void GestioneDebiti::paga(string x, string y, float k) {
	if(!contoAmici.contains(x)||!contoAmici.contains(y)){
		cout<<"Gli amici specificati non sono validi";
		return;
	}
    float saldoCorrente = saldo(x, y);
    unsigned contoDebitore = contoAmici.at(x);
    unsigned contoCreditore = contoAmici.at(y); //at è const [] non è const
    if (saldoCorrente > 0 && k <= saldoCorrente) {
        contiCompagnia[contoDebitore][contoCreditore] = saldoCorrente - k;
        contiCompagnia[contoCreditore][contoDebitore] = 0;
    } else
        cout << "la somma inserita è superiore al debito presente fra x e y";
}
