#include <iostream>
#include <list>
using namespace std;

template <typename T, typename T1>
class PriorityQueue
{
private:

    list<T> value;
    list<T1> priority;

public:

    PriorityQueue() = default;

    void push_front(const T valueP, const T1 priorityP)
    {
        value.push_front(valueP);
        priority.push_front(priorityP);
    }

    void push_back(const T valueP, const T1 priorityP)
    {
        value.push_back(valueP);
        priority.push_back(priorityP);
    }

    void pop_back()
    {
        value.pop_back();
        priority.pop_back();
    }

    void pop_front()
    {
        value.pop_front();
        priority.pop_front();
    }

    int size() const
    {
        return priority.size();
    }

    bool empty() const
    {
        return value.empty() && priority.empty() ? true : false;
    }

    T print_frontValue()const { return value.front(); }

    T print_backValue()const { return value.back(); }

    T1 print_frontPriority()const { return priority.front(); }

    T1 print_backPriority()const { return priority.back(); }

    void OutInfoFilePriorityQueue(const char* text1, const char* text2, PriorityQueue<T, T1>& resultPriority);

    void Sort(PriorityQueue<T, T1>& resultPriority, string& tempText, string& findPriority);

};