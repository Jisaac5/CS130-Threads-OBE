#include <iostream>
#include <thread>
#include "Header.h"
#include <conio.h>
#include <windows.h>

using namespace std;

int main()
{
    cookingGame::startThreadPool(3); // Start a thread pool with 3 threads

    thread gameTimer(cookingGame::startGameTimer, 180); // Start game timer (3 minutes)
    thread rentThread(cookingGame::deductRent); // Start rent deduction

    cout << "[RENT GOAL: 200 (Get your balance above 200 and maintain it!)]" << endl;
    cout << "Select your order" << endl;
    cout << "1) Tapsilog (Cost: 5)\n2) Bacsilog (Cost: 3)\n3) Hakdog (Cost: 2)\n4) Exit" << endl;
    cout << "========================================================" << endl;

    char choice;

    while (true)
    {
        

        choice = _getch();
        if (choice == '4' || cookingGame::checkGameEnd())
        {
            Sleep(2000);
            return(0);
        }

        try
        {
            if (choice == '1') {
                cout << "Tapsilog order received..." << endl;
                cookingGame::addTask("Tapsilog", 10, 5, 1);
            }
            else if (choice == '2') {
                cout << "Bacsilog order received..." << endl;
                cookingGame::addTask("Bacsilog", 7, 3, 2);
            }
            else if (choice == '3') {
                cout << "Hakdog order received..." << endl;
                cookingGame::addTask("Hakdog", 3, 2, 3);
            }
            else {
                cout << "Invalid choice!" << endl;
            }
            cout << endl; // Add a blank line after the user makes a choice
        }
        catch (const exception& e)
        {
            cerr << "Error: " << e.what() << endl;
        }
    }

    gameTimer.join();
    rentThread.join();

    cookingGame::stopThreadPool(); // Stop the thread pool
    return 0;
}
