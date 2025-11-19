#include <iostream>
using namespace std;

/*
class X
{
public:
    void f() { cout << "X::f"; }
};
class Y : public X
{
public:
    void f() { cout << "Y::f"; }
};

int main()
{
    Y y;
    y.f(); // Y::f
    X x;
    X *p = &x;
    p->f(); // X::f
    X *p = &y;
    p->f(); // X::f
}*/

class X
{
public:
    virtual void f() { cout << "X::f"; }
};
class Y : public X
{
public:
    void f() { cout << "Y::f"; }
};

int main()
{
    Y y;
    y.f(); // Y::f
    X x;
    X *p = &x;
    p->f(); // X::f
    p = &y;
    p->f(); // Y::f
    X &a = y;
    a.f();
}