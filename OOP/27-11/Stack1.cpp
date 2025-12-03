#include <iostream>
#include <list>
#include <cassert>
using namespace std;

template <typename T>
class Stack
{
private:
    list<T> S;

public:
    void push(T element) { S.push_back(element); }
    void pop()
    {
        assert(!S.empty());
        S.pop_back();
    }
    bool empty() { return S.empty(); }
    size_t size() { return S.size(); }
    T top() { return S.back(); }
};

int main()
{
    Stack<int> H;
    if (!H.empty())
        H.pop();
}