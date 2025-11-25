#include <iostream>
using namespace std;

template <typename T>
class ListT;

template <typename T>
class NodeT
{
    friend class ListT<T>;

private:
    T value;
    NodeT<T> *nextNode;

public:
    NodeT(T val) : value(val), nextNode(nullptr) {}
};

template <typename T>
class ListT
{
private:
    NodeT<T> *first;
    NodeT<T> *last;

public:
    ListT() : first(nullptr), last(nullptr) {}

    ~ListT()
    {
        while (!empty())
        {
            popFront();
        }
    }

    bool empty()
    {
        return first == nullptr;
    }

    void pushBack(T v)
    {
        NodeT<T> *newNode = new NodeT<T>(v);
        if (empty())
        {
            first = last = newNode;
        }
        else
        {
            last->nextNode = newNode;
            last = newNode;
        }
    }

    void pushFront(T v)
    {
        NodeT<T> *newNode = new NodeT<T>(v);
        if (empty())
        {
            first = last = newNode;
        }
        else
        {
            newNode->nextNode = first;
            first = newNode;
        }
    }

    bool popFront()
    {
        if (empty())
            return false;

        NodeT<T> *tmp = first;
        first = first->nextNode;
        delete tmp;

        if (first == nullptr)
            last = nullptr;

        return true;
    }

    bool popBack()
    {
        if (empty())
            return false;

        if (first == last)
        {
            delete first;
            first = last = nullptr;
            return true;
        }

        NodeT<T> *ptr = first;
        while (ptr->nextNode != last)
            ptr = ptr->nextNode;

        delete last;
        last = ptr;
        last->nextNode = nullptr;
        return true;
    }

    void print()
    {
        NodeT<T> *current = first;
        while (current != nullptr)
        {
            cout << current->value << " ";
            current = current->nextNode;
        }
        cout << endl;
    }
};

int main()
{
    cout << "--- Integer List ---" << endl;
    ListT<int> intList;
    intList.pushBack(10);
    intList.pushBack(20);
    intList.pushFront(5);
    intList.print();

    cout << "Pop Back..." << endl;
    intList.popBack();
    intList.print();

    cout << "\n--- Char List ---" << endl;
    ListT<char> charList;
    charList.pushBack('A');
    charList.pushBack('B');
    charList.pushFront('Z');
    charList.print();

    return 0;
}