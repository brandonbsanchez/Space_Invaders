#include <iostream>
#include <cstdlib>
#include <windows.h> // for getasynkeystate function

using namespace std;

////////////////////////////////////////////////////////////////////////

class Board
{
private:
    int row;
    int col;
    char **board;
    bool gameOver;
    
    // player data
    int plyrX, plyrY;
    
public:
    Board()
    {
        row = 12;
        col = 17;
        board = new char*[row];
        for(int i=0; i<row; i++)
            board[i] = new char[col];
    }
    
    ~Board()
    {
        for(int i=0; i < row; i++)
            delete [] board[i];
        delete [] board;
    }
    
    void createBoard();
    void dispBrd();
    void setGameState() { gameOver = false; }
    bool getGameState() { return gameOver; }
    void input();
};

void Board::createBoard()
{
    for(int i=0; i < row; i++){
        for(int j=0; j < col; j++){
            if(i == 10 && j > 6 && j < 8)
            {
                board[i][j] = 'P';
                plyrX = i;
                plyrY = j;
            }
            else if(j==0 || j==col-1)
                board[i][j] = '#';
//            if(i == 2 && j > 2 && j < 14)
//                board[i][j] = 'E';
//            else if(i == 3 && j > 2 && j < 14)
//                board[i][j] = 'E';
//            else if(i == 4 && j > 2 && j < 14)
//                board[i][j] = 'E';
//            else if(i == 5 && j > 2 && j < 14)
//                board[i][j] = 'E';
//            else if(i == 6 && j > 2 && j < 14)
//                board[i][j] = 'E';
//            if(i == 0 || i == row - 1)
//                board[i][j] = '#';
//            else if(j == 0 || j == row - 1)
//                board[i][j] = '#';
            else
                board[i][j] = '-';
        }
    }
}

void Board::dispBrd()
{
    for(int i=0; i < row; i++){
        for(int j=0; j < col; j++){
            cout << board[i][j] << "  ";
        }
        cout << endl;
    }
    
    system("clear");
}

void Board::input()
{
    if(GetAsyncKeyState(0x41) && (board[plyrX][plyrY-1] != '#')){ // 'a'
        board[plyrX][plyrY] = '-';
        board[plyrX][plyrY-1] = 'P';
        plyrY--;
    }
    else if(GetAsyncKeyState(0x44) && (board[plyrX][plyrY+1] != '#')){ // 'd'
        board[plyrX][plyrY] = '-';
        board[plyrX][plyrY+1] = 'P';
        plyrY++;
    }
}

///////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Board board;
    
    board.createBoard();
    
    while(board.getGameState() != true)
    {
        board.dispBrd();
        board.input();
    }

    return 0;
}
