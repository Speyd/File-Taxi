#include "Task1.h"
#include "Task2.h"
#include <iostream>
#include <string>
using namespace std;

#pragma region Special_Abilities

void ClearScrean() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    cout << "\tTaxi" << endl;
}

void Enter() {
    string enter;
    cin.ignore();
    do {
        cout << "Press enter to continue: "; getline(cin, enter);
    } while (!enter.empty());
}

#pragma endregion

void choiceOut(int& choice)
{
    do
    {
        ClearScrean();
        cout << "Enter choice output\n[1] - Merge and sort files\n"
             << "[2] - Taxi simulator\n[0] - Exit" << endl;

        if (choice >= 0 && choice <= 2)cout << "Enter your choice: ";
        else cout << "There is no such choice! Enter your choice again: ";

        cin >> choice;

    } while (choice < 0 || choice > 2);
}

int main()
{
    int choice{ 0 };

    do
    {
        choiceOut(choice);

        ClearScrean();
        if (choice == 1)Task1();
        else if (choice == 2)Task2();

    } while (choice != 0);

    return 0;
}