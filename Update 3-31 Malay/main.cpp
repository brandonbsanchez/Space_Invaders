// header.h ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <windows.h> // for getasynkeystate function

using namespace std;

// board.h ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Board
{
private:
    int row;
    int col;
    char **board;
    bool gameOver;
    
    char emptyChar = '-';
    
    // player data
    char plyrChar = 'P';
    int plyrX, plyrY;       // x and y of the player in the 2D array
    
    // enemy data
    char enemyChar = 'E';
    int count = 0;          // counter for movement
    int enemyX = 0, enemyY = 1;     // x and y of the player in the 2D array
    
    // shield data
    char shield4 = '4';
    char shield3 = '3';
    char shield2 = '2';
    char shield1 = '1';
    
    // laserData
    char lasChar = '|';
    int lasX, lasY;         // x and y of the player's laser, vertically bound
    bool lasState;          // state of laser, if its on board or not
    
public:
    // constructor to set size of game board, initialize dynamic 2D array
    Board()
    {
        row = 12;                       // height of board
        col = 16;                       // width of board
        board = new char*[row];
        for(int i=0; i<row; i++)
            board[i] = new char[col];
            
        gameOver = false;
        lasState = false;
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
//    void setGameState() { gameOver = false; }
    bool getGameState() { return gameOver; }
    void input();
//    void setLaserState() { lasState = false; }
    bool getLaserState() { return lasState; }
    void plyrLas();
    void movPlyrLas();
    /////Enemy movement////////////////////////////////////////////////////////
    void ShiftRows();    
    void ShiftRowsR(/*char enemy[enemyX][enemyY]*/);
    void ShiftRowsL(/*char enemy[enemyX][enemyY]*/);
    void ShiftRowsD(/*char enemy[enemyX][enemyY]*/);
};

// this functions sets up the initial conditions of the gameboard with:
// player, side barriers, enemies, blockades, empty space
void Board::createBoard()
{
    for(int i=0; i < row; i++){
        for(int j=0; j < col; j++){
            if(i == 11 && j == 8)
            {
                board[i][j] = plyrChar;
                plyrX = i;
                plyrY = j;
            }
            else if(i == 8 && j == 3)
            {
                board[i][j] = shield4;
            }
            else if(i == 8 && j == 6)
            {
                board[i][j] = shield4;
            }
            else if(i == 8 && j == 9)
            {
                board[i][j] = shield4;
            }
            else if(i == 8 && j == 12)
            {
                board[i][j] = shield4;
            }
            else if(j==0 || j==col-1)
            {
                board[i][j] = '#';
            }
            /////Enemy Spawning //////////////////////////////
            else if((i >= 0) && (i < 5) && (j > 1) && (j < 14)){
                board[i][j] = enemyChar;
            }
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
            /////////////////
            else
            {
                board[i][j] = '-';
            }
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
        board[plyrX][plyrY] = emptyChar;
        board[plyrX][plyrY-1] = plyrChar;
        plyrY--;
    }
    else if(GetAsyncKeyState(0x44) && (board[plyrX][plyrY+1] != '#')){ // 'd'
        board[plyrX][plyrY] = emptyChar;
        board[plyrX][plyrY+1] = plyrChar;
        plyrY++;
    }
    // laser stuff to be completed below
    else if(GetAsyncKeyState(0x20) && lasState == false){ // 'SPACEBAR'
        plyrLas();
    }
}

void Board::plyrLas()
{
    lasState = true;
    
    if(board[plyrX][plyrY] == plyrChar)
    {
        lasX = plyrX;
        lasY = plyrY;
    }
}

void Board::movPlyrLas()
{
    if(lasX-1 < 0)
    {
        board[lasX][lasY] = emptyChar;
        lasState = false;
    }
    else if(board[lasX-1][lasY] == emptyChar)
    {
        if(board[lasX][lasY] == plyrChar)
            board[lasX-1][lasY] = lasChar;
        else
        {
            board[lasX][lasY] = emptyChar;
            board[lasX-1][lasY] = lasChar;
        }
        
        lasX -= 1;
    }
   else if(board[lasX-1][lasY] == shield4 || board[lasX-1][lasY] == shield3 ||
           board[lasX-1][lasY] == shield2 || board[lasX-1][lasY] == shield1)
   {
       switch(board[lasX-1][lasY])
       {
           case '4':
               board[lasX-1][lasY] = shield3;
               board[lasX][lasY] = emptyChar;
               break;
           case '3':
               board[lasX-1][lasY] = shield2;
               board[lasX][lasY] = emptyChar;
               break;
           case '2':
               board[lasX-1][lasY] = shield1;
               board[lasX][lasY] = emptyChar;
               break;
           case '1':
               board[lasX-1][lasY] = emptyChar;
               board[lasX][lasY] = emptyChar;
               break;
       }
       lasState = false;
   }
   else if(board[lasX-1][lasY] == enemyChar){
       board[lasX][lasY] = emptyChar;
       board[lasX-1][lasY] = emptyChar;
       lasState = false;
   }
    else
        lasState = false;
}
//     Enemy Movement////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void Board::ShiftRows(){
    if ((board[enemyX][enemyY+1] != '#') && (count % 2 == 0)){
        Board::ShiftRowsR();
    } else if ((board[enemyX][enemyY-1] != '#') && (count % 2 != 0)){
        Board::ShiftRowsL();
    } else if((board[enemyX][enemyY+1] == '#') || (board[enemyX][enemyY-1] == '#')){
        count++;
        Board::ShiftRowsD();
    }
}
void Board::ShiftRowsR(){
//    for (int i = enemyX; i < row-1; i++){
//        for (int j = enemyY; j < col-2; j++){
//            if (board[enemyX][enemyY-1] == enemyChar){
//                board[enemyX][enemyY-1] = emptyChar;
//                board[enemyX][enemyY] = enemyChar;
//                enemyY++;
//            } else if (board[enemyX][enemyY-1] == emptyChar){
//                board[enemyX][enemyY] = emptyChar;
//                board[enemyX][enemyY+1] = enemyChar;
//                enemyY++;
//            }
//            char t = board[enemyX][enemyY];
//            board[enemyX][enemyY] = board[enemyX][enemyY+1];
//            board[enemyX][enemyY+1] = t;
//            enemyY++;
//        }
//    }
        board[enemyX][enemyY] = emptyChar;
        board[enemyX][enemyY+1] = enemyChar;
        enemyY++;
}
void Board::ShiftRowsL(){
//    for (int i = enemyX; i < row-1; i++){
//        for(int j = enemyY; j > 1; j--){
//            char first = board[enemyX][enemyY];               
//            board[enemyX][enemyY] = board[enemyX][enemyY-1];
//            board[enemyX][enemyY-1] = first;
//            enemyY--;
//        }
//    }
        board[enemyX][enemyY] = emptyChar;
        board[enemyX][enemyY-1] = enemyChar;
        enemyY--;
}
void Board::ShiftRowsD(/*char enemy[enemyX][enemyY]*/){
//    for (int i = enemyX; i < row-1; i++){
//        for (int j = enemyY; j < col-1; j++){
//            char p = board[enemyX][enemyY];
//            board[enemyX][enemyY] = board[enemyX+1][enemyY];
//            board[enemyX+1][enemyY] = p;
//        }
//    }
    board[enemyX][enemyY] = emptyChar;
    board[enemyX+1][enemyY] = enemyChar;
    enemyX++;
}
// leaderboard.h //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
// enemy.h //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class Enemy : public Board
//{
//private:
//    int length;
//    int height;
//    int enemyX;
//    int enemyY;
//    char** enemy;
//    
//public:
//    Enemy(){
//        length = 7;
//        height = 3;
//        enemy = new char*[length];
//        for(int i = 0; i < length; i++) {
//            enemy[i] = new char[height];
//        }
//    }
//    ~Enemy()
//    {
//        for(int i=0; i < length; i++){
//            delete[] enemy[i];   
//        }
//        delete[] enemy;
//    }
//    void ShowRows(char enemy[length][height]);
//    void ShowFull (char enemy[length][height]);
//    void ShiftRowsR(/*char enemy[enemyX][enemyY]*/);
//    void ShiftRowsL(/*char enemy[enemyX][enemyY]*/);
//    void ShiftRowsD(/*char enemy[enemyX][enemyY]*/);
//};
//void Enemy::ShowRows(char enemy[length][height]){
//    for (int i = 0; i < length; i++){
//     std::cout << enemy[i][height];
//    }
//    std::cout << '\n';
//}
//
//
//void Enemy::ShowFull (char enemy[length][height]){
//    for (int i = 0; i < height; i++){
//        for(int j = 0; j < length; j++){
//            ShowRows(enemy);        
//        }
//        std::cout << '\n';
//    }
//    std::cout << '\n';
//}

//void Enemy::ShiftRowsR(/*char enemy[enemyX][enemyY]*/){
//    char last = enemy[enemyX-1][enemyY];
//    for (int i = length; i > 0; i--){
//        enemy[i][enemyY] = enemy[i-1][enemyY];
//        enemy[0][enemyY]=last;
//    }
//}
//void Enemy::ShiftRowsL(/*char enemy[enemyX][enemyY]*/){
//    char first = enemy[0][enemyY];
//    for (int i = 0; i < length; i++){
//        enemy[i-1][enemyY] = enemy[i][enemyY];
//        enemy[enemyX-1][enemyY] = first;
//    }
//}
//void Enemy::ShiftRowsD(/*char enemy[enemyX][enemyY]*/){
//    for (int i = 0; i < length; i++){
//        for (int j = 0; j < height; i++){
//            enemy[j][enemyY] = enemy[j+1][enemyY];
//        }
//    }
//    std::cout << '\n' << '\n';
//}

// main.cpp ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    // create objects from classes
    Board board;
    Leaderboard ldrBrd;
    
    // create the game board
    board.createBoard();
    
    // play Space Invaders; display board, get input
    while(board.getGameState() != true)
    {
        system("clear");
        
        if(board.getLaserState())
            board.movPlyrLas();
        
        ldrBrd.getLeaderboard();
        board.dispBrd();
        ldrBrd.getBtmBoard();
        
        board.input();
        board.ShiftRows();
    }

    return 0;
}
