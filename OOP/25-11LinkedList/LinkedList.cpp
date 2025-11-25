#include <iostream>
using namespace std;

class NodeInt
{
    friend class ListInt;

private:
    int value;
    NodeInt *nextNode;
    NodeInt(int val) : value(val), nextNode(nullptr) {}
};

class ListInt
{
    NodeInt *first;
    NodeInt *last;

public:
    ListInt() : first(nullptr), last(nullptr) {};
    void pushBack(int v)
    {
        NodeInt *newNode = new NodeInt(v);
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

    bool empty()
    {
        return first == nullptr;
    };

    bool popFront()
    {
        if (empty())
            return false;
        else
        {
            NodeInt *tmp = first;
            first = first->nextNode;
            delete tmp;
        }
        if (first == nullptr)
            last = nullptr;
        return true;
    }

    bool popBack()
    {
        if (empty())
            return false;
        NodeInt *ptr = first;
        while (ptr->nextNode != last)
            ptr = ptr->nextNode;
        delete last;
        last = ptr;
        return true;
    }

    void print()
    {
        NodeInt *current = first;
        while (current != nullptr)
        {
            cout << current->value << " ";
            current = current->nextNode;
        }
    }
    void pushFront(int v)
    {
        NodeInt *newNode = new NodeInt(v);
        if (empty())
            first = last = newNode;
        else
        {
            newNode->nextNode = first;
            first = newNode;
        }
    }

    /*~distruttoreNodeInt()
    {
        while (!empty())
        {
            popFront();
        }
    }*/
};

int main()
{
    ListInt T;
    T.pushBack(3);
    T.pushBack(2);
    T.pushBack(4);
    T.print();
    cout << endl;
    T.popFront();
    T.print();
    cout << endl;
    T.popFront();
    T.print();
    T.pushFront(9);
    T.print();
}