#include <iostream>
#include <iomanip>
#include <algorithm>
#include "input.h"

using namespace std;

void PatternOfAsterisksBlanks();
void printSpaces(int n);
void printStars(int n);
int pow2(int k);
void baseBlock(int indent);
void patternRec(int depth, int indent);

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


// Recursively prints n space characters.
void printSpaces(int n) {
    if (n <= 0) 
		return; // when n <= 0, it stops automatically

    cout << ' ';        // print one space
    printSpaces(n - 1); // call itself for remaining spaces
}

// Recursively prints n stars separated by spaces.
void printStars(int n) {
    if (n <= 0) 
		return;

    cout << "* ";         // print one star and a space
    printStars(n - 1);    // print the rest
}

// Recursively calculates 2^k (two raised to the power of k).
int pow2(int k)
{                  
    int result;
    if (k <= 0)
    {
        result = 1; // base case: 2^0 = 1
    }
    else
    {
        result = 2 * pow2(k - 1); // multiply by 2 each time
    }
    return result;
}

// Draws a small triangle(3 lines) that is the smallest pattern.
void baseBlock(int indent)
{
    // line 1: one star
    printSpaces(indent);
    printStars(1);
    cout << '\n';

    // line 2: two stars
    printSpaces(indent);
    printStars(2);
    cout << '\n';

    // line 3: one star again, but more indented
    printSpaces(indent + 2);
    printStars(1);
    cout << '\n';
}


void patternRec(int depth, int indent) {
    if (depth <= 0) return;      // nothing to print if depth is zero
    if (depth == 1) 
    {
        // smallest case: just draw a base block
        baseBlock(indent); 
        return;
    }

    //Draw the smaller pattern on the left
    patternRec(depth - 1, indent);
    //Draw the middle line with many stars
    printSpaces(indent);
    printStars(pow2(depth));
    cout << '\n';

    // Draw the smaller pattern on the right, shifted further to the right
    patternRec(depth - 1, indent + 4 * (depth - 1));
}

void PatternOfAsterisksBlanks() {
    cout << "\nPattern of Asterisks and Blanks (exact layout):\n\n";

    
    int depth = 3;   
    int indent = 8;  

    patternRec(depth, indent);
}
