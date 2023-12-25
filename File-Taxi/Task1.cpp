#include "PriorityQueue.h"
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
using namespace std;

extern void Enter();

template <typename T, typename T1>
void PriorityQueue<T, T1>::Sort(PriorityQueue<T, T1>& resultPriority,
    string& tempText, string& findPriority)
{
    for (size_t i{ 0 }; i < resultPriority.size(); i++)
    {
        if (resultPriority.print_frontPriority() >= findPriority && !findPriority.empty())
        {
            resultPriority.push_front(tempText, findPriority);
            --i;
            findPriority = "";
        }
        else if (resultPriority.print_frontPriority() < findPriority || findPriority.empty())
        {
            string textFront[2]{ resultPriority.print_frontValue(), resultPriority.print_frontPriority() };
            resultPriority.pop_front();
            resultPriority.push_back(textFront[0], textFront[1]);
        }
    }
    if (!findPriority.empty())resultPriority.push_back(tempText, findPriority);

}

void Sort(deque<string>& resultText, string& tempText)
{
    for (size_t i{ 0 }; i < resultText.size(); i++)
    {
        if (resultText.front() >= tempText && !tempText.empty())
        {
            resultText.push_front(tempText);
            --i;
            tempText = "";
        }
        else if (resultText.front() < tempText || tempText.empty())
        {
            string textFront{ resultText.front() };
            resultText.pop_front();
            resultText.push_back(textFront);
        }
    }
    if (!tempText.empty())resultText.push_back(tempText);

}

void OutInfoFileQueue(const char* text1, const char* text2, deque<string>& resultText)
{
    ifstream file1(text1);
    string tempText{};

    while (!file1.eof())
    {
        getline(file1, tempText);
        if (tempText.empty())throw runtime_error("Found empty string!");
        Sort(resultText, tempText);
    }

    ifstream file2(text2);

    while (!file2.eof())
    {
        getline(file2, tempText);
        if (tempText.empty())throw runtime_error("Found empty string!");
        Sort(resultText, tempText);
    }

    file1.close(); file2.close();
}

template <typename T, typename T1>
void PriorityQueue<T, T1>::OutInfoFilePriorityQueue
(const char* text1, const char* text2, PriorityQueue<T, T1>& resultPriority)
{
    ifstream file1(text1);
    string tempText{};

    while (!file1.eof())
    {
        getline(file1, tempText);
        string findPriority{ "0" };

        if (tempText.find_last_of('(') == string::npos || tempText.find_last_of(')') == string::npos)
        {
            throw runtime_error("No bracket find");
        }
        findPriority.insert(0, tempText, tempText.find_last_of('('), tempText.find_last_of(')'));

        Sort(resultPriority, tempText, findPriority);
    }



    ifstream file2(text2);
    while (!file2.eof())
    {
        getline(file2, tempText);
        string findPriority{ "0" };

        if (tempText.find_last_of('(') == string::npos || tempText.find_last_of(')') == string::npos)
        {
            throw runtime_error("No bracket find");
        }
        findPriority.insert(0, tempText, tempText.find_last_of('('), tempText.find_last_of(')'));

        Sort(resultPriority, tempText, findPriority);
    }


    file1.close(); file2.close();
}


template <typename T, typename T1>
void InputInfoFile(const char* text1, const char* text2,
    deque<string>& resultText, PriorityQueue<T, T1>& resultPriority)
{
    ofstream file1(text1);

    while (!resultText.empty())
    {
        file1 << resultText.front() << endl;
        resultText.pop_front();
    }


    ofstream file2(text2);

    while (!resultPriority.empty())
    {
        file2 << resultPriority.print_frontValue() << endl;
        resultPriority.pop_front();
    }

    file1.close(); file2.close();

}

int Task1()
{
    deque<string> resultText{};
    PriorityQueue<string, string> resultPriority{};

    try
    {
        OutInfoFileQueue("text1.txt", "text2.txt", resultText);
        resultPriority.OutInfoFilePriorityQueue("text1.txt", "text2.txt", resultPriority);
        InputInfoFile("resultQueue.txt", "resultPriority.txt", resultText, resultPriority);

        cout << "Check the folder 'resultQueue.txt' and 'resultPriority.txt'!" << endl;

        while (!resultPriority.empty())
        {
            cout << resultPriority.print_frontValue() << endl;
            resultPriority.pop_front();
        }
    }
    catch (runtime_error error)
    {
        cout << error.what() << endl;
    }

    Enter();

    return 0;
}