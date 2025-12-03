#include <iostream>
#include <list>
#include <cassert>
using namespace std;

template <typename T>
class Queue
{
private:
    list<T> S;

public:
    void enqueue(T element) { S.push_back(element); }
    void dequeue()
    {
        assert(!S.empty());
        S.pop_front();
    }
    bool empty() { return S.empty(); }
    size_t size() { return S.size(); }
    T front() { return S.front(); }
};

template <typename T>
class QueueINHwithPriority : protected list<T>
{
public:
    void enqueue(T el) {
        // Priority Queue implementation: insert in order (descending)
        // Assuming T supports operator< or operator>
        // We want the largest element at the front.
        
        auto it = this->begin();
        while (it != this->end() && *it >= el) {
            ++it;
        }
        this->insert(it, el);
    }
    void dequeue()
    {
        assert(!this->empty());
        list<T>::pop_front();
    }
    using list<T>::empty;
    size_t size() { return list<T>::size(); }
    T front() { return list<T>::front(); }
};

int main()
{
    QueueINHwithPriority<int> pq;
    pq.enqueue(10);
    pq.enqueue(30);
    pq.enqueue(20);
    pq.enqueue(5);
    pq.enqueue(40);

    cout << "Priority Queue (Max at front):" << endl;
    while (!pq.empty()) {
        cout << pq.front() << " ";
        pq.dequeue();
    }
    cout << endl;

    return 0;
}