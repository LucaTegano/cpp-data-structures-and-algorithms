#include <iostream>
using namespace std;
class X
{
public:
    void f() { cout << "X::f" << endl; }
    int a;
};

class Y : public X
{
public:
    void f() { cout << "Y::f" << endl; }
    int a;
};

int main()
{
    X x;
    x.a = 20;
    x.f();               // X::f
    cout << x.a << endl; // 20
    Y y;
    y.a = 40;
    y.X::a = 60;
    y.f();                  // Y::f
    y.X::f();               // X::f
    cout << y.a << endl;    // 40
    cout << y.X::a << endl; // 60
    X z = y;
    cout << z.a << endl; // 60
    return 0;
}
