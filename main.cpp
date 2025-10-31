#include <iostream>
#include <iomanip>
#include <algorithm>
#include "input.h"
#include "TowerOfHanoi.h"

using namespace std;

void PatternOfAsterisksBlanks();
void printSpaces(int n);
void printStars(int n);
int pow2(int k);
void baseBlock(int indent);
void patternRec(int depth, int indent);

int guess(int low, int high, int& count);
void GuessNumber();

bool hasConflict(int board[], int newRow, int newCol);
bool solveNQueensRec(int board[], int n, int row);
void solveNQueens(int n, int firstCol);


int main()
{
    TowerOfHanoi game;
   
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
        switch (inputInteger("\t\t  Option: ", 0, 4))
        {
        case 0: exit(1);
        case 1: PatternOfAsterisksBlanks();  break;
        case 2: GuessNumber(); break;
        case 3: game.autoSolve(); break;
        case 4:
        {
            system("cls");
            cout << "\n\t 4> n-Queens Problem";
            cout << "\n\t" << string(100, char(205));

            int queen = inputInteger("\n\tEnter a number(1..100) of queens: ", 1, 100);
            int column = inputInteger("\n\tEnter the column(1.." + to_string(queen) + ") to place the first queen: ", 1, queen);
            cout << "\n\n\t" << queen << " -Queens solution";
            solveNQueens(queen, column);
        }
        break;
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

void PatternOfAsterisksBlanks()
{
    system("cls");
    cout << "\nPattern of Asterisks and Blanks (exact layout):\n\n";


    int depth = 3;
    int indent = 8;

    patternRec(depth, indent);
}

///////////////////////////============2============/////////////////////////
// Recursive function definition
int guess(int low, int high, int& count) {
    // Base case: only one number left
    if (low == high) {
        count++;
        cout << "\n\tIt must be " << low << "!\n";
        cout << "\n\tYay! I guessed your number.\n";
        return low;
    }

    // Smart case: only one number between low and high
    if (high - low == 2) {
        int mid = (low + high) / 2;
        cout << "\n\tIt must be " << mid << "! (only one number fits)\n";
        count++;
        cout << "\n\tYay! I guessed your number.\n";
        return mid;
    }

    // For adjacent numbers (only 2 left), check directly
    if (high - low == 1) {
        count++;
        char answer = inputChar("Is your number " + to_string(low) + "? (y/n): ");
        if (answer == 'y' || answer == 'Y') {
            cout << "\n\tYay! I guessed your number.\n";
            return low;
        }
        count++;
        cout << "\n\tThen it must be " << high << "!\n";
        cout << "\n\tYay! I guessed your number.\n";
        return high;
    }

    //Recursive midpoint logic
    int mid = (low + high) / 2;
    count++;

    char response = inputChar("Is your number " + to_string(mid) + "? (y/n): ");
    if (response == 'y' || response == 'Y') {
        cout << "\n\tGreat! I found it!\n";
        return mid;
    }

    response = inputChar("Is your number larger than " + to_string(mid) + "? (y/n): ");
    if (response == 'y' || response == 'Y')
        return guess(mid + 1, high, count);
    else
        return guess(low, mid - 1, count);
}

void GuessNumber()
{
    system("cls");
    cout << "\n\t2> Guess a number";
    cout << "\n\t" << string(90,char(196));
    cout << "\n\tThink of a number between 1 and 1,000,000.\n";
    cout << "\n\tI will try to guess it using yes/no questions.\n";
    cout << "\n\tPlease answer with 'y' for yes and 'n' for no.\n";
    cout << "\n\t" << string(90, char(196)) << "\n\n";

    srand(static_cast<unsigned>(time(0))); // seed random number generator
    int firstGuess = rand() % 1000 + 1; // random number between 1 and 1,000,000

    int count = 1;
    char response = inputChar("Is your number " + to_string(firstGuess) + "? (y/n): ");
    if (response == 'y' || response == 'Y') {
        cout << "\n\n\tYay! I guessed your number on the first try!\n";
    }
    else {
        response = inputChar("Is your number larger than " + to_string(firstGuess) + "? (y/n): ");
        if (response == 'y' || response == 'Y')
            guess(firstGuess + 1, 1000, count);
        else
            guess(1, firstGuess - 1, count);
    }

    cout << "\n\tI guessed your number in " << count << " attempts.\n";
    cout << "\n\t" << string(90, char(196)) << "\n\n";
}

// ==================================================
// Check if placing a queen at (row, col) is safe
// ==================================================
bool hasConflict(int board[], int newRow, int newCol) {
    for (int r = 0; r < newRow; r++) {
        int c = board[r];
        if (c == newCol) return true;                         // same column
        if (abs(r - newRow) == abs(c - newCol)) return true;  // same diagonal
    }
    return false;
}

// ==================================================
// Recursive function to place queens
// ==================================================
bool solveNQueensRec(int board[], int n, int row) {
    if (row == n) return true; 

    for (int col = 1; col <= n; col++) {
        if (!hasConflict(board, row, col)) {
            board[row] = col;              // place queen
            if (solveNQueensRec(board, n, row + 1))
                return true;               // found solution
        }
    }
    return false; // ❌ no valid placement in this row
}

// ==================================================
// Wrapper function to start recursion and display board
// ==================================================
void solveNQueens(int n, int firstCol)
{
    int board[100] = { 0 };

    // Place the first queen manually (row 0)
    board[0] = firstCol;

    bool success = solveNQueensRec(board, n, 1);

    //==================== DISPLAY RESULT ====================
    if (success) {
        char display[100][100];
        for (int r = 0; r < n; r++)
            for (int c = 0; c < n; c++)
                display[r][c] = '_';

        for (int r = 0; r < n; r++)
            display[r][board[r] - 1] = 'Q';

        // Draw board using ASCII lines
        cout << "\n\t";
        cout << char(0xC9); // top-left
        for (int i = 0; i < n; i++) {
            cout << "\xCD\xCD\xCD";
            if (i < n - 1) cout << char(0xCB);
        }
        cout << char(0xBB);

        for (int r = 0; r < n; r++) {
            cout << "\n\t" << char(0xBA);
            for (int c = 0; c < n; c++) {
                cout << " " << display[r][c] << " ";
                if (c < n - 1) cout << char(0xBA);
            }
            cout << char(0xBA);

            if (r < n - 1) {
                cout << "\n\t" << char(0xCC);
                for (int i = 0; i < n; i++) {
                    cout << "\xCD\xCD\xCD";
                    if (i < n - 1) cout << char(0xCE);
                }
                cout << char(0xB9);
            }
        }

        cout << "\n\t" << char(0xC8);
        for (int i = 0; i < n; i++) {
            cout << "\xCD\xCD\xCD";
            if (i < n - 1) cout << char(0xCA);
        }
        cout << char(0xBC) << endl;
    }
    else {
        cout << "\n\tNo solution found for " << n
            << "-Queens with first queen in column " << firstCol << ".\n";
    }
}
