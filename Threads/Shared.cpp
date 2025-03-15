#include <iostream>
#include <windows.h>

using namespace std;

namespace cookingGame
{
	void cookFood(string foodName, int cookTime)
	{
		cout << "Cooking " << foodName << " for " << cookTime << " seconds" << endl;
		Sleep(1000 * cookTime);
		cout << foodName << " is ready!" << endl;
	}
}