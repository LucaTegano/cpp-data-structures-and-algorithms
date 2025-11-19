// POLIMORFISMO CON VETTORI DI PUNTATORI A CLASSI BASE e VIRTUALI
#include <iostream>
#include <vector>
using namespace std;

class Base
{
public:
    int a;
    virtual void print() { cout << "Base" << endl; }
    ~Base() { cout << "Distruttore Base" << endl; }
};

class Derivata : public Base
{
public:
    int b;
    void print() { cout << "Derivata" << endl; }
    ~Derivata() { cout << "Distruttore Derivata" << endl; }
};
class Derivata1 : public Derivata
{
public:
    int c;
    void print() { cout << "Derivata1" << endl; }
    ~Derivata1() { cout << "Distruttore Derivata1" << endl; }
};

int main()
{
    Base B;
    Derivata D1;
    Derivata D2;
    Base *pB = &B;
    Base *pD1 = &D1;
    Base *pD2 = &D2;

    vector<Base *> v;
    v.push_back(pB);
    v.push_back(pD1);
    v.push_back(pD2);
    for (unsigned int i = 0; i < v.size(); i++)
    {
        v[i]->print();
    }

    Derivata1 *pDD1 = new Derivata1();
    delete pDD1;
    return 0;
}
