#include "Taxi.h"
#include <iostream>
#include <string>
#include <list>
#include <Windows.h>
using namespace std;
constexpr auto FIRST_BIG_LETTER = 65;//Первая капс буква в ASCII
constexpr auto LAST_BIG_LETTER = 90;//Последняя капс буква в ASCII

const int minWaitingPassenger{ 1 }, maxWaitingPassenger{ 4 };
const int minAmountgPassenger{ 1 }, maxAmountgPassenger{ 5 };
const int minTripLength{ 500 }, maxTripLength{ 3000 };
const int amountTaxi{ 5 }, amountTaxiDepartures{ amountTaxi * 2 };

#pragma region Special_Abilities

extern void ClearScrean();

extern void Enter();

#pragma endregion

string randomNumber()
{
    string result{};
    result += char(rand() % (LAST_BIG_LETTER - FIRST_BIG_LETTER + 1) + FIRST_BIG_LETTER);
    result += char(rand() % (LAST_BIG_LETTER - FIRST_BIG_LETTER + 1) + FIRST_BIG_LETTER);
    result += " " + to_string(rand() % (9 - 0 + 1) + 0) + to_string(rand() % (9 - 0 + 1) + 0);
    result += to_string(rand() % (9 - 0 + 1) + 0) + to_string(rand() % (9 - 0 + 1) + 0);
    result += " ";
    result += char(rand() % (LAST_BIG_LETTER - FIRST_BIG_LETTER + 1) + FIRST_BIG_LETTER);
    result += char(rand() % (LAST_BIG_LETTER - FIRST_BIG_LETTER + 1) + FIRST_BIG_LETTER);

    return result;
}

template <typename T, typename T1>
void generatorNumbers(Taxi<T, T1>& taxi)
{
    for (size_t i{ 0 }; i != taxi.maxSize(); i++)
    {
        taxi.push(randomNumber(), 0);
    }
}

template <typename T, typename T1, typename T2>
void downtime(list<T>& timeExpectations, list<T>& timeSleep, Taxi<T1, T2>& taxi)
{
    int sum{ 0 };
    if (timeExpectations.size() != 0 && timeExpectations.size() % 6 == 0)timeExpectations.push_back(0);
    list<int> tempList = timeExpectations;
    for (size_t i{ 0 }; i < taxi.sizeNumber() && i < timeExpectations.size(); i++)
    {
        sum += tempList.back();
        tempList.pop_back();
    }

    timeSleep.push_back(sum);

}

template <typename T, typename T1, typename T2>
void comparisonTaxi(list<T>& firstGo, Taxi<T1, T2>& taxi)//Сравнивает время и дистанцию и вставка
{

    if (firstGo.size() >= 2 && taxi.sizeDistance() >= 2)
    {
        list<int> secondGo = firstGo;
        firstGo.pop_back();

        if (firstGo.back() > secondGo.back() && taxi.backDistance() > taxi.frontDistance())
        {
            taxi.swapNumDis();

            firstGo.pop_back();
            firstGo.push_back(secondGo.back());
            secondGo.pop_back();
            firstGo.push_back(secondGo.back());

        }

        else if (firstGo.back() > secondGo.back() && taxi.backDistance() < taxi.frontDistance() ||
            firstGo.back() < secondGo.back() && taxi.backDistance() > taxi.frontDistance())
        {
            if (taxi.frontDistance() + secondGo.back() >= taxi.backDistance() + firstGo.back())
            {

                taxi.FrontToBackTaxi();
                firstGo.push_back(secondGo.back());
            }
            else
            {
                taxi.swapNumDis();

                firstGo.pop_back();
                firstGo.push_back(secondGo.back());
                secondGo.pop_back();
                firstGo.push_back(secondGo.back());
            }
        }


        else if (firstGo.back() < secondGo.back() && taxi.backDistance() < taxi.frontDistance() ||
            firstGo.back() == secondGo.back() && taxi.backDistance() == taxi.frontDistance())
        {
            taxi.FrontToBackTaxi();
            firstGo.push_back(secondGo.back());
        }


        else if (firstGo.back() == secondGo.back() && taxi.backDistance() < taxi.frontDistance() ||
            firstGo.back() < secondGo.back() && taxi.backDistance() == taxi.frontDistance())
        {
            taxi.FrontToBackTaxi();
            firstGo.push_back(secondGo.back());
        }


        else if (firstGo.back() == secondGo.back() && taxi.backDistance() > taxi.frontDistance() ||
            firstGo.back() > secondGo.back() && taxi.backDistance() == taxi.frontDistance())
        {
            taxi.swapNumDis();

            firstGo.pop_back();
            firstGo.push_back(secondGo.back());
            secondGo.pop_back();
            firstGo.push_back(secondGo.back());
        }
    }
}

int choiceOut()
{
    int choice{ 1 };

    do
    {
        ClearScrean();
        cout << "Enter choice output\n[1] - Detailed output\n[2] - Compressed output" << endl;

        if (choice >= 1 && choice <= 2)cout << "Enter your choice: ";
        else cout << "There is no such choice! Enter your choice again: ";

        cin >> choice;

    } while (choice < 1 || choice > 2);

    return choice;
}

template <typename T, typename T1, typename T2>
void outputInfo(const int& choice, Taxi<T, T1>& taxi,
    const list<T2>& timeSleep, const T2& amountPasseng)
{
    if (choice == 1)
    {
        cout << "Taxi with numbers '" << taxi.frontNumber() << "' leaves!" << endl;
        cout << "He is carrying " << amountPasseng << " people" << endl;
        cout << "He needs to drive " << taxi.frontDistance() << " meters!" << endl;
        cout << "And stood idle this taxi " << timeSleep.back() << " minutes" << endl << endl;
    }
    else if (choice == 2)
    {
        for (size_t i{ 0 }; i < taxi.sizeNumber(); i++)
        {
            cout << taxi.frontNumber() << " | " << taxi.frontDistance() << " metres" << endl;
            taxi.FrontToBackTaxi();
        }
        cout << endl;
    }
}

int averageWaiting(const list<int>& time)
{
    int sum{ 0 };
    for (int value : time)
    {
        sum += value;
    }

    return sum / time.size();
}

int Task2()
{
    srand(time(nullptr));

    int choice{ choiceOut() }, tempAmountTaxiDepar{ 1 };

    list<int> timeExpectations{ }, timeSleep{ };
    Taxi<string, int> taxi{ amountTaxi };
    generatorNumbers(taxi);

    ClearScrean();

    while (tempAmountTaxiDepar <= amountTaxiDepartures)
    {
        int minutes{ rand() % (maxWaitingPassenger - minWaitingPassenger + 1) + minWaitingPassenger };
        timeExpectations.push_back(minutes);
        downtime(timeExpectations, timeSleep, taxi);

        int amountPasseng{ rand() % (maxAmountgPassenger - minAmountgPassenger + 1) + minAmountgPassenger };
        taxi.frontDistance() = rand() % (maxTripLength - minTripLength + 1) + minTripLength;
        taxi.passengers() += amountPasseng;

        outputInfo(choice, taxi, timeSleep, amountPasseng);

        /* if (tempAmountTaxiDepar == 1) { taxi.FrontToBackTaxi(); }
         else comparisonTaxi(timeSleep, taxi);*/
        if (tempAmountTaxiDepar % 2 != 0) { taxi.FrontToBackTaxi(); }
        else if (tempAmountTaxiDepar % 2 == 0)comparisonTaxi(timeSleep, taxi);

        if (tempAmountTaxiDepar % 5 == 0)cout << "\nTaxi circle completed\n" << string(20, '-') << endl;
        tempAmountTaxiDepar++;
    }

    cout << endl << endl;
    cout << "Anount of passengers carried: " << taxi.getAmountPassengers() << endl;
    cout << "Average waiting time for passengers: " << averageWaiting(timeExpectations) << " minutes" << endl;
    cout << "Average taxi dwell time: " << averageWaiting(timeSleep) <<  "minutes" << endl;

    Enter();

    return 0;
}