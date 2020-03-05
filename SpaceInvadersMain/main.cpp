/* 
 * File: main.cpp
 * Author: Brandon Sanchez
 * Created on March 5, 2020, 9:56 AM
 */

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
using namespace std;

const int width = 100, height = 28; //Width/Height of Board

void printBoard();

int main()
{
    bool gameOver = false; //Will eventually switch to false once dead
    
    while(!gameOver) //Loop to refresh the board
    {
        printBoard(); //Prints the board
    }
        
    return 0;
}

void printBoard()
{
    for(int i = 0 ; i < height ; i++)
    {
        for(int j = 0 ; j < width ; j++)
        {
            if(i == 0 || i == height - 1)
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
