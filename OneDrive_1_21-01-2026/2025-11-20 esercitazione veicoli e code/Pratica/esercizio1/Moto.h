#ifndef MOTO_H
#define MOTO_H

#include "Veicolo.h"

using namespace std;


class Moto: public Veicolo {
    public:
        Moto(string t, float p, string c, string n): Veicolo(t, p, c, n) {}

        float getPrezzo() const {
            float p = Veicolo::getPrezzo();
            if (p<7000)
                return p-(p*0.03);
            if (p<15000)
                return p-(p*0.075);
            return p;
        }

        virtual Moto* clone() {
            return new Moto(*this);
        }
};

#endif