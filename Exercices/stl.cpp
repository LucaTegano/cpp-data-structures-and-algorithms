#include <iostream>
using namespace std;
class VectorOfInt
{
private:
    int *array;
    unsigned size;
    unsigned capacity;
    // aray = new int[10] CAPACITY DEL VECTOR,DI QUANTO HO ALLOCATO
    // Size quanti elementi ho inserito
    // 2 dim CAPACITY ,e SIZE .SIZE <= CAPACITY ALTRIMENTI SI AUMENTARE LA CAPACITY
public:
    VectorOfInt() : array(nullptr), capacity(0), size(0) {}
    VectorOfInt(unsigned c) : array(new int[c]), capacity(c), size(0) // posso preimostarlo a 100 unsigned c = 100
    {
        cout << "Costruttore che riceve la capacity" << endl;
    }
    ~VectorOfInt()
    {
        cout << "Distruttore" << endl;
        delete[] array;
    }

    VectorOfInt(const VectorOfInt &other) : array(new int[other.capacity]), size(other.size), capacity(other.capacity)
    {
        cout << "Copy constructor" << endl;
        for (unsigned i = 0; i < size; i++)
            array[i] = other.array[i];
    }

    VectorOfInt &operator=(const VectorOfInt &other)
    {
        cout << "Assignment operator" << endl;
        if (this != &other)
        {
            delete[] array;
            array = new int[other.capacity];
            size = other.size;
            capacity = other.capacity;
            for (unsigned i = 0; i < size; i++)
                array[i] = other.array[i];
        }
        return *this;
    }

    void push_back(int el)
    {
        if (size == capacity)
        {
            if (capacity == 0)
            {
                cout << "Chiama resize, capacity a 10" << endl;
                resize(10);
            }
            else
                resize(capacity * 2);
        }
        array[size++] = el; // array[size] = el; size += 1
    }

    void resize(unsigned C)
    {
        if (C == capacity)
            return;

        int *temp = new int[C];
        unsigned newSize = (C < size) ? C : size;
        for (unsigned i = 0; i < newSize; i++)
            temp[i] = array[i];

        delete[] array;
        array = temp;
        capacity = C;
        size = newSize;
    }
    unsigned getSize() const { return size; }
    unsigned getCapacity() const { return capacity; }

    int &operator[](unsigned i) { return array[i]; }
    const int &operator[](unsigned i) const { return array[i]; }

    void stampaMaggioriDi(VectorOfInt V, int x)
    {
        for (unsigned i = 0; i < V.getSize(); i++)
        {
            if (V[i] > x)
                cout << V[i] << " ";
        }
    }

    // VectorOfInt(const VecotrofInt &C); IMPLEMENTARE
    // operator = IMPLEMENTARE
};

int main()
{
    VectorOfInt V;
    V.push_back(5);
    V.push_back(2);
    for (unsigned i = 0; i < V.getSize(); i++)
        cout << V[i] << endl;
}