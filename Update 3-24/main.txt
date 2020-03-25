// header.h ////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <windows.h> // for getasynkeystate function

using namespace std;

// board.h //////////////////////////////////////////////////////////////////////

class Board
{
private:
    int row;
    int col;
    char **board;
    bool gameOver;
    
    // player data
    int plyrX, plyrY;
    
    // enemy data
    
    
public:
    // constructor to set size of game board, initialize dynamic 2D array
    Board()
    {
        row = 12;
        col = 17;
        board = new char*[row];
        for(int i=0; i<row; i++)
            board[i] = new char[col];
    }
    
    // destructor to delete dynamic memory from 2D array
    ~Board()
    {
        for(int i=0; i < row; i++)
            delete [] board[i];
        delete [] board;
    }
    
    // class functions
    void createBoard();
    void dispBrd();
    void setGameState() { gameOver = false; }
    bool getGameState() { return gameOver; }
    void input();
};

// this functions sets up the initial conditions of the gameboard with:
// player, side barriers, enemies, blockades, empty space
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

// this function simply outputs the current state of the board, or the 2D array
// at the end it clears the screen just to display itself again
void Board::dispBrd()
{
    for(int i=0; i < row; i++){
        for(int j=0; j < col; j++){
            cout << board[i][j] << "  ";
        }
        cout << endl;
    }
    
    //system("clear");
}

// this function looks for input from the player to move Left and Right, and
// shoot lazers; it has boundary check and laser delay
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
    // laser stuff to be completed below
    
}

// leaderboard.h ////////////////////////////////////////////////////////////////////////////////

class Leaderboard{
    private:
        int scoreOne;           //Player One's score.
        int hiScore;            //High Score.
        //int scoreTwo;         //Player Two's score. To be implemented later.
        int lives;              //The number of lives the player has.
        int credit;             //Credits player has.
    public:
        Leaderboard();          //Default constructor.
        void addScore(int);     //Add score for kills.
        void setHiScore();      //Set Hi-Score.
        int getScore(){         //Display Player One's score.
            return scoreOne;
        }
        int getHiScore(){       //Display Hi-Score.
            return hiScore;
        }
        //int getScoreTwo();    //Display Player Two's score.
        void getLeaderboard();  //Display scores neatly.
        void getBtmBoard();     //Display lives & credits
        void displayLives();    //Determine how many lives to display.
};

Leaderboard::Leaderboard(){                 //Default constructor.
    scoreOne=0;
    hiScore=0;
    lives=3;
    credit=0;
}

void Leaderboard::addScore(int score){      //Accepts score for the kill and
    scoreOne+=score;                        //Adds score to scoreOne.
}

void Leaderboard::setHiScore(){
    hiScore=scoreOne;
}

void Leaderboard::getLeaderboard(){         //Display the top UI.
    cout<<"SCORE<1>"<<"\tHI-SCORE\n";
    cout<<setw(4)<<scoreOne<<"\t\t"<<setw(4)<<hiScore<<endl<<endl;
}

void Leaderboard::getBtmBoard(){            //Display lives & credits below
    cout<<endl<<lives;                            //game board.
    displayLives();     //Call separate function to display lives
    cout<<"\t\tCREDIT "<<credit<<endl;
}

void Leaderboard::displayLives(){
    switch(lives){                          //Determine how many lives to
        case 3: cout<<" PP";                //display based on lives left
                break;                      //in Space Invaders Theme.
        case 2: cout<<" P";
                break;
        case 1: cout<<" ";
                break;
    }
}

// main.cpp ////////////////////////////////////////////////////////////////////////

int main()
{
    // create objects from classes
    Board board;
    Leaderboard ldrBrd;
    
    // create the game board
    board.createBoard();
    
//    ldrBrd.getLeaderboard();
//    board.dispBrd();
//    ldrBrd.getBtmBoard();
    
    // play Space Invaders; display board, get input
    while(board.getGameState() != true)
    {
        system("clear");
        ldrBrd.getLeaderboard();
        board.dispBrd();
        ldrBrd.getBtmBoard();
        board.input();
    }

    return 0;
}
