#include <iostream>
#include <thread>
#include "Header.h"

using namespace std;

int main()
{
    cookingGame::startThreadPool(3); // Start a thread pool with 3 threads

    thread gameTimer(cookingGame::startGameTimer, 180); // Start game timer (3 minutes)
    thread rentThread(cookingGame::deductRent); // Start rent deduction

    while (true)
    {
        cout << "Select your order" << endl;
        cout << "1) Tapsilog (Cost: 5)\n2) Bacsilog (Cost: 3)\n3) Hakdog (Cost: 2)\n4) Exit" << endl;

        int choice;
        cin >> choice;

        if (choice == 4 || cookingGame::checkGameEnd())
        {
            break;
        }

        try
        {
            switch (choice)
            {
            case 1:
                cookingGame::addTask("Tapsilog", 10, 5);
                break;
            case 2:
                cookingGame::addTask("Bacsilog", 7, 3);
                break;
            case 3:
                cookingGame::addTask("Hakdog", 3, 2);
                break;
            default:
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
