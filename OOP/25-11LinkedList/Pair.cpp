// TEMPLATE
#include <iostream>
template <typename T, typename U>

class Pair
{
private:
    T first;
    U second;

public:
    Pair(T a, U b) : first(a), second(b) {}
    T getFirst() { return first; }
    U getSecond() { return second; }
    void setFirst(T a) { first = a; }
    void setSecond(U a) { second = a; }
};

int main()
{
    Pair<int, int> P(2, 3);
    Pair<char, char> C('c', 't');
};