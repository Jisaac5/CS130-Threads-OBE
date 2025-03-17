#pragma once
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace cookingGame
{
    void cookFood(std::string foodName, int cookTime);
    void addTask(const std::string& foodName, int cookTime, int foodCost);
    void workerThread();
    void startThreadPool(int numThreads);
    void stopThreadPool();
    void startGameTimer(int duration);
    void updateBalance(int amount);
    bool checkGameEnd();
    void deductRent();
    void displayTime();
}