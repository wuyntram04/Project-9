#include <iostream>
#include <iomanip>
#include <algorithm>
#include "input.h"

using namespace std;


int main()
{
	do
	{
		system("cls");
		cout << "\n\t\t CMPR131 Chapter 9: Recursive Applications by Khang Quach, Thi Ho, Thi Pham";
		cout << "\n\t\t" << string(70, char(205));
		cout << "\n\t\t1> Pattern of astricks and blanks";
		cout << "\n\t\t2> Guess a number";
		cout << "\n\t\t3> Solve Tower of Hanoi";
		cout << "\n\t\t4> Solve n-Queens";
		cout << "\n\t\t" << string(70, char(196));
		cout << "\n\t\t0> Exit";
		cout << "\n\t\t" << string(70, char(205)) << '\n';
		switch (inputInteger("\t\t  Option: ", 0, 3))
		{
		case 0: exit(1);
		case 1: PatternOfAsterisksBlanks();  break;
		case 2: break;
			//			case 3: option3(); break;
		default: cout << "\n\tERROR: invalud option.\n";
		}

		cout << '\n';
		system("pause");

	} while (true);

	return 0;
}
