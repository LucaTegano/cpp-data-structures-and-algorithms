//
// Created by admin on 17/12/2025.
//
#include <iostream>
#include <queue>

#include "AlberoB.h"
using namespace std;
AlberoB<float> recursive_spremi(const AlberoB<float>& alberoB, float c_value, float& quota) {
    if (alberoB.nullo()) {
        quota += c_value;
        return AlberoB<float>();
    }
    if (alberoB.foglia())
        return AlberoB<float>(alberoB.radice()+c_value);


    AlberoB<float> toReturn=AlberoB<float>(0);
    float cc_value = (alberoB.radice() + c_value) / 2;
    toReturn.insFiglio(SIN, recursive_spremi(alberoB.figlio(SIN),cc_value,quota));
    toReturn.insFiglio(DES, recursive_spremi(alberoB.figlio(DES),cc_value,quota));
    return toReturn;

}

void stampa(const AlberoB<float>& a, int livello = 0) {
    if (a.nullo()) return;

    // 1. Visita prima il figlio DESTRO (che apparirà in alto)
    stampa(a.figlio(DES), livello + 1);

    // 2. Stampa la radice attuale con l'indentazione giusta
    // Usiamo 4 spazi per ogni livello di profondità
    for (int i = 0; i < livello; i++) cout << "    ";

    cout << a.radice() << endl;

    // 3. Visita il figlio SINISTRO (che apparirà in basso)
    stampa(a.figlio(SIN), livello + 1);
}

float spremi(AlberoB<float>& alberoB) {
    float quota=0;
    AlberoB<float> newTree= recursive_spremi(alberoB,0,quota);
    cout<<"*********Albero dopo spremi*****"<<endl;
    stampa(newTree);
    return quota;
}


int main() {

    AlberoB<float> alberoB(4);
    AlberoB<float> alberoB2(6.4);
    AlberoB<float> alberoB3(0.6);
    alberoB.insFiglio(SIN, alberoB2);
    alberoB.insFiglio(DES, alberoB3);
    AlberoB<float> alberoB4(3);
    AlberoB<float> alberoB5(1.8);
    alberoB2.insFiglio(SIN, alberoB4);
    alberoB2.insFiglio(DES, alberoB5);
    AlberoB<float> alberoB6(0);
    AlberoB<float> alberoB7(4.2);
    alberoB3.insFiglio(SIN, alberoB6);
    alberoB3.insFiglio(DES, alberoB7);
    AlberoB<float> alberoB8(0.8);
    alberoB7.insFiglio(DES, alberoB8);
    AlberoB<float> alberoB9(2.3);
    alberoB5.insFiglio(SIN, alberoB9);
    stampa(alberoB);
    float totaleAcc=spremi(alberoB);
    cout << "Totale Acc "<<totaleAcc << endl;

    return 0;
}
