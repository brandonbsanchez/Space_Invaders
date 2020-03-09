/* 
 * File: main.cpp
 * Author: Brandon Sanchez
 * Created on March 5, 2020, 9:56 AM
 */

#include <cstdlib>
#include <iostream>
#include <windows.h> //For getasynkeystate function
using namespace std;

const int width = 100, height = 28; //Width/Height of Board

void printBoard(int, int);
void input(int&, int&);

int main()
{
    bool gameOver = false; //Will eventually switch to false once dead
    int x = (width - 10)/ 2, y = height - 5;
    
    while(!gameOver) //Loop to refresh the board
    {
        printBoard(x, y); //Prints the board
        input(x, y);
    }
        
    return 0;
}

void input(int &x, int &y)
{
    
    if(GetAsyncKeyState(0x57)) //"W" key
        y--;
    else if(GetAsyncKeyState(0x41)) //"A" key
        x -= 3;
    else if(GetAsyncKeyState(0x53)) // "S" key
        y++;
    else if(GetAsyncKeyState(0x44)) // "D" key
        x += 3;
    
    if(y <= 0)
        y = 1;
    else if(x <= 0)
        x = 1;
    else if(y >= height - 1)
        y = height - 2;
    else if(x >= width - 1)
        x = width - 2;
}
void printBoard(int x, int y)
{
    for(int i = 0 ; i < height ; i++)
    {
        for(int j = 0 ; j < width ; j++)
        {
            if(i == y && j == x)
                cout << "X";
            else if(i == 0 || i == height - 1)
                cout << "#";
            else if(j == 0 || j == width - 1)
                cout << "#";
            else
                cout << " ";
        }
        cout << endl;
    }
    
    system("clear");
}
