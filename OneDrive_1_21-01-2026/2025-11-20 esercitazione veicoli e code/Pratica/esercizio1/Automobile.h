#ifndef AUTOMOBILE_H
#define AUTOMOBILE_H

#include "Veicolo.h"

using namespace std;


class Automobile: public Veicolo {
    public:
        Automobile(string t, float p, string c, string n): Veicolo(t, p, c, n) {}

        float getPrezzo() const {
            float p = Veicolo::getPrezzo();
            if (p<10000)
                return p-(p*0.05);
            if (p<20000)
                return p-(p*0.1);
            return p;
        }

        virtual Automobile* clone() {
            return new Automobile(*this);
        }
};

#endif