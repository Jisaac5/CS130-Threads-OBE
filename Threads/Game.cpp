#include <iostream>
#include <thread>
#include <windows.h>
#include "Header.h"

using namespace std;

int main()
{
	while (true)
	{
		cout << "Select your order" << endl;
		cout << "1) Tapsilog\n2) Bacsilog\n3) Hakdog\n4) Exit" << endl;

		int choice;
		cin >> choice;

		if (choice == 4)
		{
			break;
		}

		switch (choice)
		{
			case 1:
			{
				thread t1(&cookingGame::cookFood, "Tapsilog", 10);
				t1.detach();
				break;
			}

			case 2:
			{
				thread t2(&cookingGame::cookFood, "Bacsilog", 7);
				t2.detach();
				break;
			}

			case 3:
			{
				thread t3(&cookingGame::cookFood, "Hakdog", 3);
				t3.detach();
				break;
			}

		default:
			cout << "Invalid choice!" << endl;
		}
	}
}