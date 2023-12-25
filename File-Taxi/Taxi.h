#include "CircularQueue.h"
#include <iostream>
#include <string>
using namespace std;


template <typename T, typename T1>//T - тип  данных number | T1 - тип данных pathDistance
class Taxi
{
private:

    CircularQueue<T> number;
    CircularQueue<T1> pathDistance;
    int amountPassengers;

public:

    Taxi(const int size)
        :number{ CircularQueue<T>::CircularQueue(size) },
        pathDistance{ CircularQueue<T1>::CircularQueue(size) },
        amountPassengers{ 0 }
    { }

    template <typename T>
    void push(const T& value, const T1 distance)
    {
        number.push(value);
        pathDistance.push(distance);
    }

    int maxSize() const { return pathDistance.printMaxSize(); }

    T& backNumber() const { return number.back(); }
    T1& backDistance() const { return pathDistance.back(); }

    T& frontNumber() const { return number.front(); }
    T1& frontDistance() const { return pathDistance.front(); }

    void FrontToBackTaxi()
    {
        number.FrontToBack();
        pathDistance.FrontToBack();
    }

    int sizeNumber()const { return number.size(); }
    int sizeDistance()const { return pathDistance.size(); }

    void popNumDis()
    {
        number.pop();
        pathDistance.pop();
    }

    void swapNumDis()
    {

        swap(pathDistance.back(), pathDistance.front());
        swap(number.back(), number.front());

        number.FrontToBack();
        pathDistance.FrontToBack();



    }

    int& passengers()const { return amountPassengers; }
    int& passengers() { return amountPassengers; }

    int getAmountPassengers()const { return amountPassengers; }

};