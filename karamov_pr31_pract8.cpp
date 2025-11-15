
#include <iostream>
#include <Windows.h>
#define TURTLES_AMOUNT 5
#define MAP_LENGHT 50

int positions[TURTLES_AMOUNT];
int win;

DWORD WINAPI Move(LPVOID turtleNumber)
{
    srand(time(NULL) + (int)turtleNumber);
    while (positions[(int)turtleNumber] < MAP_LENGHT)
    {
        Sleep(rand() % 200 + 100);
        positions[(int)turtleNumber] += rand() % 3;
    }
    positions[(int)turtleNumber] = MAP_LENGHT-1;
    CloseHandle(GetCurrentThread());
    return 0;
}
DWORD WINAPI UpdateMap(LPVOID a)
{
    int count = 0;
    bool winner = false;
    while (count != TURTLES_AMOUNT)
    {
        count = 0;
        for (int i = 0; i < TURTLES_AMOUNT; i++)
        {
            if (positions[i] == MAP_LENGHT - 1)
            {
                count++;
                if (!winner)
                {
                    winner = true;
                    win = i+1;
                }
            }
        }
        system("cls");
        for (int i = 0; i < MAP_LENGHT; i++)
        {
            bool taken = false;
            for (int j = 0; j < TURTLES_AMOUNT; j++)
            {
                if (positions[j] == i)
                {
                    taken = true;
                    break;
                }
            }
            if (taken)
            {
                std::cout << '*';
            }
            else
            {
                std::cout << '-';
            }
        }
        /*std::cout << std::endl;
        for (int i = 0; i < MAP_LENGHT; i++)
        {
            if (positions[i] != 0)
            {
                std::cout << i;
            }
            else
            {
                std::cout << '+';
            }
        }*/
        Sleep(250);
    }
    return 0;
}

int main()
{
    DWORD idThread;
    HANDLE UpdateThread = CreateThread(NULL, 0, UpdateMap, NULL, 0, &idThread);
    for (int i = 0; i < TURTLES_AMOUNT; i++)
    {
        DWORD idThread;
        HANDLE newThread = CreateThread(NULL, 0, Move, (void*)i, 0, &idThread);
    }
    WaitForSingleObject(UpdateThread, INFINITE);
    CloseHandle(UpdateThread);
    std::cout << "winner: " << win;
    return 0;
}