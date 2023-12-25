#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Queue
{
private:
    T* queuePtr;               // queue pointer
    const int maxSize;         // maximum items amount
    int first;                 // first item number
    int next;                  // first empty item number
    bool over;                 // refill tag
public:
    Queue(const int size);     // default queue size
    ~Queue();                  // destructor
    void push(const T& value); // push item to queue back
    void pop();                // remove item from queue front
    T& front() const;          // return queue front item
    T& back() const;           // return queue back item
    bool empty() const;        // if queue is empty
    bool full() const;         // if queue is full
    int size() const;          // queue size
    int printMaxSize() const;
    int getFirst() const { return first; }
    int getNext() const { return next; }
    void setFirst(int value) { first = value; }
    void setNext(int value) { next = value; }
    void swap();

};

#pragma region MethodsQueue

template <typename T>
Queue<T>::Queue(const int size) : maxSize(size)
{
    queuePtr = new T[maxSize];
    first = 0;
    next = 0;
    over = false;
}

template <typename T>
Queue<T>::~Queue()
{
    delete[] queuePtr;
}

template <typename T>
void Queue<T>::push(const T& value)
{
    if (full())
    {
        throw exception("Queue is full");
    }
    queuePtr[next++] = value;
    if (next == maxSize)
    {
        over = true;
        next = 0;
    }
}

template <typename T>
void Queue<T>::pop()
{
    if (empty())
    {
        throw exception("Queue is empty");
    }
    first++;
    if (first == maxSize)
    {
        over = false;
        first = 0;
    }
}

template <class T>
T& Queue<T>::front() const
{
    if (empty())
    {
        throw exception("Queue is empty");
    }
    return queuePtr[first];
}

template <class T>
T& Queue<T>::back() const
{
    if (empty())
    {
        throw exception("Queue is empty");
    }
    if (next == 0 && over)
    {
        return queuePtr[maxSize - 1];
    }
    return queuePtr[next - 1];
}

template <typename T>
bool Queue<T>::empty() const
{
    return size() == 0;
}

template <typename T>
bool Queue<T>::full() const
{
    return size() == maxSize;
}

template <typename T>
int Queue<T>::size() const
{
    return next > first ? next - first :
        first > next ? maxSize - (first - next) :
        over ? maxSize : 0;
}

template <typename T>
int Queue<T>::printMaxSize() const
{
    return maxSize;
}

template <typename T>
void Queue<T>::swap()
{
    if (this->empty()) return;

    T item = this->front();
    this->pop();
    this->push(item);

    // ƒополнительный код дл€ кругового сдвига
    int oldFirst = this->getFirst();
    int oldNext = this->getNext();

    if (oldFirst == 0 && oldNext == 0) return;  // Ќе нужно сдвигать, если оба индекса наход€тс€ в начале

    // —двиг индексов по кругу
    this->setFirst((oldFirst - 1) % this->maxSize);
    this->setNext((oldNext - 1) % this->maxSize);
}

#pragma endregion