#include <iostream>
using namespace std;
class A
{
protected:
    int x;
    char c;

public:
    A() = default;
    A(int x1, char c1) : x(x1), c(c1) {}
    int getX() const { return x; }
    int getC() const { return c; }
};

class B : public A
{
    float f;

public:
    B(float f1) : f(f1) {};
    void stampa() { cout << f << endl; }
};
int main()
{
    B b(3);
    b.stampa();
    cout << b.getX() << endl;
}