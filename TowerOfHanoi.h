#include <stack>
#include <iomanip>
#include <thread>
#include <chrono>
#include "input.h"

#pragma once
using namespace std;

class TowerOfHanoi
{
private:
    int rings = 0;
    stack<int> towerA, towerB, towerC;
    int totalMoves = 0;

public:
    // ================================
    // Display Towers (Your Original)
    // ================================
    void displayTower()
    {

        stack<int> tempA = towerA, tempB = towerB, tempC = towerC;

        if (rings == 3 || rings > 9)
            cout << "\n\t   \xBA       \xBA       \xBA\n";
        else
            cout << "\n\t" << string(rings, ' ') << "\xBA" << string(rings * 2 + 5, ' ')
            << "\xBA" << string(rings * 2 + 5, ' ') << "\xBA     \n";

        if (rings <= 9)
        {
            for (int i = rings; i > 0; i--)
            {
                cout << "\t";
                printPeg(tempA, i);
                printPeg(tempB, i);
                printPeg(tempC, i);
                cout << "\n";
            }
        }
        else
        {
            for (int i = rings; i > 0; i--)
            {
                cout << "\t";
                printPegNumber(tempA, i);
                printPegNumber(tempB, i);
                printPegNumber(tempC, i);
                cout << "\n";
            }
        }

        int standLength;

        if (rings > 9)
        {
            standLength = 3;   // fixed width for 10 or more rings
        }
        else
        {
            standLength = rings;   // same width as number of rings for small towers
        }

        cout << "\t";
        for (int i = 0; i < 3; i++)
        {
            for (int k = 0; k < standLength; k++) cout << "\xCD";
            cout << "\xCA";
            for (int k = 0; k < standLength; k++) cout << "\xCD";
            cout << ((standLength == 3) ? " " : "     ");
        }

        cout << "\n\t";
        for (int i = 0; i < 3; i++)
        {
            for (int k = 0; k < standLength; k++) cout << " ";
            cout << char(65 + i);
            for (int k = 0; k < standLength; k++) cout << " ";
            cout << ((standLength == 3) ? " " : "     ");
        }
        cout << "\n";
    }

    void printPeg(stack<int>& peg, int i)
    {
        if (i <= peg.size() && !peg.empty())
        {
            int top = peg.top(); peg.pop();
            for (int s = 0; s < rings - top; s++) cout << " ";
            for (int j = 1; j <= top; j++) cout << "\xFE";
            cout << top;
            for (int j = 1; j <= top; j++) cout << "\xFE";
            for (int s = 0; s < rings - top; s++) cout << " ";
            cout << ((rings == 3) ? " " : "     ");
        }
        else
        {
            cout << setw(rings + 1) << "\xBA";
            cout << ((rings == 3) ? string(rings + 1, ' ') : string(rings + 5, ' '));
        }
    }

    void printPegNumber(stack<int>& peg, int i)
    {
        if (i <= peg.size() && !peg.empty())
        {
            cout << "   " << setw(4) << left << peg.top();
            peg.pop();
        }
        else
            cout << "   " << setw(4) << left << "\xBA";
    }

    // ===============================
    // Initialization / Reset Section
    // ===============================
    void setRings(int r)
    {
        rings = r;
        for (int i = r; i > 0; --i)
            towerA.push(i);
    }

    void restartGame()
    {
        rings = 0;
        totalMoves = 0;
        stack<int> empty;
        towerA = towerB = towerC = empty;
    }

    int getCurrentMoves() const { return totalMoves; }

    // ================================
    // Move Logic (Reusable)
    // ================================
    void moveDisk(char from, char to)
    {
        switch (toupper(from))
        {
        case 'A': if (toupper(to) == 'B') moveAtoB(); else if (toupper(to) == 'C') moveAtoC(); break;
        case 'B': if (toupper(to) == 'A') moveBtoA(); else if (toupper(to) == 'C') moveBtoC(); break;
        case 'C': if (toupper(to) == 'A') moveCtoA(); else if (toupper(to) == 'B') moveCtoB(); break;
        }
    }

    void moveAtoB() { moveHelper(towerA, towerB, 'A', 'B'); }
    void moveAtoC() { moveHelper(towerA, towerC, 'A', 'C'); }
    void moveBtoA() { moveHelper(towerB, towerA, 'B', 'A'); }
    void moveBtoC() { moveHelper(towerB, towerC, 'B', 'C'); }
    void moveCtoA() { moveHelper(towerC, towerA, 'C', 'A'); }
    void moveCtoB() { moveHelper(towerC, towerB, 'C', 'B'); }

    void moveHelper(stack<int>& from, stack<int>& to, char f, char t)
    {
        if (from.empty()) return;
        if (!to.empty() && from.top() > to.top()) return;

        to.push(from.top());
        from.pop();
        totalMoves++;

        system("cls"); // clear screen for animation
        cout << "\n\tMove " << setw(4) << totalMoves << "\n\t";
        displayTower();
        this_thread::sleep_for(chrono::milliseconds(1000)); // small pause
    }

    // ===============================
    // Recursive Solver Implementation
    // ===============================
    void solveRecursively(int n, char from, char to, char aux)
    {
        if (n <= 0) return; // safety stop for invalid cases

        if (n == 1)
        {
            moveDisk(from, to);
            return;
        }

        solveRecursively(n - 1, from, aux, to);
        moveDisk(from, to);
        solveRecursively(n - 1, aux, to, from);
    }

    void autoSolve()
    {
        system("cls");
        restartGame();
        int num = inputInteger("\n\tEnter number of rings (1..64 for clarity): ", 1, 64);
        setRings(num);
        rings = num;
        totalMoves = 0;

        cout << "\n\tSolving Tower of Hanoi recursively...\n";
        displayTower();
        this_thread::sleep_for(chrono::milliseconds(1000));

        solveRecursively(rings, 'A', 'C', 'B');

        cout << "\n\n\tCompleted! Solved recursively in "
            << totalMoves << " moves.\n";
    }

    // ===============================
    // Destructor
    // ===============================
    ~TowerOfHanoi() { restartGame(); }
};

