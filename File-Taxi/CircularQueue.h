#include "Queue.h"
#include <iostream>
#include <string>
using namespace std;

template <typename T>
class CircularQueue : public Queue<T> {

public:

    CircularQueue(const int size) : Queue<T>::Queue(size) {}

    void FrontToBack()
    {
        if (this->empty()) return;

        T item = this->front();
        this->pop();
        this->push(item);
    }

};