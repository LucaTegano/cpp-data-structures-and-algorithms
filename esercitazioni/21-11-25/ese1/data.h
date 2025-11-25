#ifndef DATA_H
#define DATA_H

#include <iostream>

using namespace std;

class Data {
private:
    int giorno;
    int mese;
    int anno;

public:
    // Costruttori
    Data();
    Data(int g, int m, int a);

    // Setters
    void setGiorno(int g);
    void setMese(int m);
    void setAnno(int a);

    // Getters
    int getGiorno() const;
    int getMese() const;
    int getAnno() const;

    // Operatori di confronto
    bool operator<(const Data& other) const;
    bool operator==(const Data& other) const;

    // Input/Output
    friend ostream& operator<<(ostream& os, const Data& d);
    friend istream& operator>>(istream& is, Data& d);
};

#endif // DATA_H
