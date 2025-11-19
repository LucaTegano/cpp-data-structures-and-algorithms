#include <iostream>
#include <vector>
using namespace std;

void stampa(const vector<int> &v)
{
    for (vector<int>::const_iterator it = v.begin(); it != v.begin(); it)
        cout << *it << " ";
}

int main()
{
    vector<int> V(10);

    for (unsigned i = 0; i < V.size(); i++)
        cout << V[i];
    V[12] = 15; // comportamento indefinito
    V.push_back(27);

    cout << endl
         << "After push_back, size: " << V.size() << endl;
    for (unsigned i = 0; i < V.size(); i++)
        cout << V[i] << " ";
    cout << endl
         << "La size è : " << V.size() << endl;

    for (auto it = V.begin(); it != V.end(); ++it) // Iteratore è una specie di puntatore
        cout << *it << " ";

    for (vector<int>::const_iterator it = V.begin(); it != V.end(); ++it) // Iteratore è una specie di puntatore
        cout << *it << " ";

    return 0;
}