#include <iostream>
#include <vector>
using namespace std;

class FigGeo // BASE COMUNE ALLE FIGLIEª
{
public:
    virtual double area() = 0;      // VIRTUALE PURO
    virtual double perimetro() = 0; // VIRTUALE PURO
};

class Quadrato : public FigGeo
{
public:
    Quadrato(double a = 0.0) : lato(a) {};
    double lato;
    double perimetro() { return lato * 4; }
    double area()
    {
        cout << "Area Quadrato :";
        return lato * lato;
    }
};

class Cerchio : public FigGeo
{
public:
    Cerchio(double r = 0.0) : raggio(r) {};
    double raggio;
    double perimetro() { return 2 * 3.14 * raggio; }
    double area() { return 3.14 * raggio * raggio; }
};

class Rettangolo : public FigGeo
{
public:
    Rettangolo(double b = 0.0, double a = 0.0) : base(b), altezza(a) {};
    double base;
    double altezza;
    double perimetro() { return (base + altezza) * 2; }
    double area() { return base * altezza; }
};

int main()
{
    vector<FigGeo *> V;
    V.push_back(new Quadrato(4));
    V.push_back(new Cerchio(5));
    V.push_back(new Quadrato(2));
    V.push_back(new Rettangolo(2, 3));
    V.push_back(new Quadrato(7));

    // FigGeo F; // non possiamo istanziare una classe astratta
    for (auto it = V.begin(); it != V.end(); ++it)
    {
        cout << (*it)->perimetro() << endl;
        cout << (*it)->area() << endl;
    }
    for (unsigned i = 0; i < V.size(); i++)
        delete V[i];
    return 0;
}