#include <iostream>
using namespace std;
// COMPOSIZIONE ,risponde alla domanda ha 1
class Punto
{
private:
    float x, y;

public:
    Punto() : x(0), y(0) { cout << "Costuttore senza parametri di Punto" << endl; }

    Punto(float x1, float y1) : x(x1), y(y1) { cout << "Costuttore a 2 parametri di Punto" << endl; }

    float getX() { return x; }
    float getY() { return y; }
    void setX(float x1) { x = x1; }
    void setY(float y1) { y = y1; }

    friend istream &operator>>(istream &, Punto &);
    friend ostream &operator<<(ostream &, const Punto &);
};

istream &operator>>(istream &i, Punto &p)
{
    i >> p.x >> p.y;
    return i;
}

ostream &operator<<(ostream &o, const Punto &p)
{
    o << "(" << p.x << "," << p.y << ")";
    return o;
}

class Cerchio
{
private:
    float raggio;
    Punto centro;

public:
    Cerchio() : raggio(5), centro(3, 3) { cout << "Costuttore senza parametri di Cerchio" << endl; };
    Cerchio(float r, float x, float y) : raggio(r), centro(x, y) { cout << "Costuttore con 3 parametri di Cerchio" << endl; };
    Cerchio(float r, const Punto &c) : raggio(r), centro(c) // centro(c) Costruttore per copia chiamo
    {
        // centro = c;
        cout << "Costuttore con 2 paramentri raggio e Punto parametri di Cerchio" << endl;
    };

    friend istream &operator>>(istream &i, Cerchio &C)
    {
        i >> C.centro >> C.raggio; // chiamo l'operatore input di Punto  friend istream &operator>>(istream &, Punto);
        return i;
    }

    friend ostream &operator<<(ostream &o, const Cerchio &C)
    {
        o << "Cerchio con centro in " << C.centro << " e raggio " << C.raggio;
        return o;
    }

    Cerchio &operator=(const Cerchio &c)
    {
        if (&c != this)
        {
            centro = c.centro;
            raggio = c.raggio;
        }
        return *this;
    }
    float getRaggio() { return raggio; }
};

int main()
{
    Punto P;
    cin >> P; // equivale a operator <<(cin,P)

    Punto P2(2, 3);

    Cerchio C;

    Cerchio C2(2, P2);

    Cerchio Array[3];

    for (unsigned i = 0; i < 3; i++)
        cin >> Array[i];

    unsigned posMax = 0;

    for (unsigned i = 1; i < 3; i++)
    {
        if (Array[i].getRaggio() > Array[posMax].getRaggio())
            posMax = i;
    }
    cout << Array[posMax];
}
// ESERCIZIO STAMPARE IL CERCHIO CON IL RAGGIO PIù GRANDE