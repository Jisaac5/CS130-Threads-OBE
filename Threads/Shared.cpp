#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include "Header.h"

using namespace std;

namespace cookingGame
{
    struct Task
    {
        std::string foodName;
        int cookTime;
        int foodCost;
    };

    std::queue<Task> taskQueue;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop = false;
    int balance = 100; // Starting balance
    int rentGoal = 200; // Rent goal
    int gameTime = 180; // Game time in seconds (3 minutes)

    void cookFood(string foodName, int cookTime)
    {
        cout << "Cooking " << foodName << " for " << cookTime << " seconds" << endl;
        Sleep(1000 * cookTime);
        cout << "$$$$$$$$ " << foodName << " is ready! Selling for " << cookTime * 2 << " units $$$$$$$$" << endl;
        updateBalance(cookTime * 2); // Earn double the cook time as earnings
        cout << endl; // Add a blank line after the cooking message
    }

    void addTask(const std::string& foodName, int cookTime, int foodCost)
    {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            taskQueue.push({ foodName, cookTime, foodCost });
        }
        condition.notify_one();
    }

    void workerThread()
    {
        while (true)
        {
            Task task;
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                condition.wait(lock, [] { return !taskQueue.empty() || stop; });

                if (stop && taskQueue.empty())
                    return;

                task = taskQueue.front();
                taskQueue.pop();
            }
            updateBalance(-task.foodCost); // Deduct food cost
            cookFood(task.foodName, task.cookTime);
        }
    }

    std::vector<std::thread> threadPool;

    void startThreadPool(int numThreads)
    {
        for (int i = 0; i < numThreads; ++i)
        {
            threadPool.emplace_back(workerThread);
        }
    }

    void stopThreadPool()
    {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread& thread : threadPool)
        {
            if (thread.joinable())
                thread.join();
        }
    }

    void startGameTimer(int duration)
    {
        gameTime = duration;
        while (gameTime > 0)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            gameTime--;
            if (gameTime % 5 == 0)
            {
                displayTime();
            }
            if (checkGameEnd())
                break;
        }
        stopThreadPool();
        cout << "Game Over! Final Balance: " << balance << endl;
    }

    void updateBalance(int amount)
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        balance += amount;
        cout << "Current Balance: " << balance << endl;
    }

    bool checkGameEnd()
    {
        return gameTime <= 0 || balance <= 0;
    }

    void deductRent()
    {
        while (gameTime > 0)
        {
            std::this_thread::sleep_for(std::chrono::seconds(10));
            updateBalance(-10); // Deduct rent
            if (checkGameEnd())
                break;
        }
    }

    void displayTime()
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        cout << "Time remaining: " << gameTime << " seconds" << endl;
    }
}
