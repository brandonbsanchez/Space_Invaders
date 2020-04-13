/*
Notes of what to do:
1. Put player and enemy variables/functions into their own class
2. Fix bug with down then Left or Right not having a pause, [main.cpp]
3. Clean up the temp and holder variables in board.h member functions
4. Enemy Lazers; scan columns from bottom until first enemy, assign X Y variables, randomize shooting pattern
5. Multiple enemy speeds
6. Incorporate scores for hitting enemies with leaderboard class
7. Reset condition if player hit by laser/aliens, need to use a numEnemies variable to build the board instead of hard coding them in
8. comment the functions
9. Add a library to stop the blinking, need to research more
*/

// header.h ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <windows.h> // for getasynkeystate function

using namespace std;

// player.h ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// enemy.h ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// leaderboard.h //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Leaderboard
{
private:
    int scoreOne;                       //Player One's score.
    int hiScore;                        //High Score.
    //int scoreTwo;                     //Player Two's score. To be implemented later.
    int lives;                          //The number of lives the player has.
    int credit;                         //Credits player has.
public:
    Leaderboard();                      //Default constructor.
    void addScore(int);                 //Add score for kills.
    void setHiScore();                  //Set Hi-Score.
    int getScore(){ return scoreOne; }  //Display Player One's score.
    int getHiScore(){ return hiScore; } //Display Hi-Score.
    //int getScoreTwo();                //Display Player Two's score.
    void getLeaderboard();              //Display scores neatly.
    void getBtmBoard();                 //Display lives & credits
    void displayLives();                //Determine how many lives to display.
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

// board.h ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Board
{
private:
    int row;
    int col;
    char **board;
    bool gameOver;
    
    char emptyChar = '-';
    char boundaryChar = '#';
    
    // player data
    char plyrChar = 'P';
    int plyrX, plyrY;       // x and y of the player in the 2D array
    
    // enemy data
    char enemyChar = 'E';
    char destroyedEnemyChar = 'x';
    int numEnemies;
    int moveR;
    int moveL;
    int enemySpeed;
    int speedTime;
    bool downState;
    int enemyDead;
    
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
        
        //
        numEnemies = 20;
        moveR = 2;
        moveL = 0;
        enemySpeed = 12;
        speedTime = 0;
        downState = false;
    }
    
    // destructor to delete dynamic memory from 2D array
    ~Board()
    {
        for(int i=0; i < row; i++)
            delete [] board[i];
        delete [] board;
    }
    
    // start menu
    void start_menu();
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
    
    // enemy functions
    void moveEnemiesLR();
    void moveEnemiesD();
    void speedTimer() { speedTime++; }
    int getSpeedTimer() { return speedTime; }
    int getEnemySpeed() { return enemySpeed; }
    bool checkRow(int, char);
    bool checkCol(int);
    void checkSide(char);
    bool getDownState() { return downState; }
    void enemyTimer();
};

// start menu 
void start_menu() {            
    //display welcome banner
    cout<<"****************************************************"<<endl;
    cout<<"    * * *   * * *      * *           * * *  * * * *    "<<endl;
    cout<<"   *     *  *    *    *   *        *        *          "<<endl;
    cout<<"  *         *    *   *     *     *          *          "<<endl;
    cout<<"   *        * * *   * * * * *    *          * * *      "<<endl;
    cout<<"    *       *      *         *   *          *          "<<endl;
    cout<<"*     *     *     *           *    *        *          "<<endl;
    cout<<" * * *      *    *             *     * * *  * * * *    "<<endl;
    cout<<"                                       "<<endl; //
    cout<<"* * * * *  * *           *   * *       * *      * * * *  * * *        * * *  "<<endl; 
    cout<<"    *      *  *         *   *   *      *    *   *        *    *      *     * "<<endl; 
    cout<<"    *      *   *       *   *     *     *      * *        *    *     *        "<<endl;
    cout<<"    *      *    *     *   * * * * *    *      * * * *    * * *       *       "<<endl;
    cout<<"    *      *     *   *   *         *   *      * *        *    *       *      "<<endl;
    cout<<"    *      *      * *   *           *  *    *   *        *     *  *     *    "<<endl;
    cout<<"* * * * *  *       *   *             * * *      * * * *  *      *  * * *     "<<endl;
    cout<<"*****************************************************************************"<<endl;
            
    int ans;    //store user input
    cout<<"Select:"<<endl;
    cout<<"1: Start"<<endl; // menu to start or exit
    cout<<"0: Exit"<<endl;
    cin>>ans;
    
    while (cin.fail() || ans>1 || ans<0) {  // validate user input, must be integer, 1 or 0      
        cout<<"Please select a valid option 1 or 0\n";
        cin.clear();
        cin.ignore(256,'\n');
        cin>>ans;      
    }    
    switch(ans){
        case 1: //start menu
            break;
        case 0: //exit -> finish program
            cout<<"\n\nExiting . . . Goodbye\n";     
            exit(0);
    }    
}

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
                board[i][j] = boundaryChar;
            }
            else if(i == 1 && j > 2 && j < 13)
                board[i][j] = enemyChar;
            else if(i == 2 && j > 2 && j < 13)
                board[i][j] = enemyChar;
            else if(i == 3 && j > 2 && j < 13)
                board[i][j] = enemyChar;
            else if(i == 4 && j > 2 && j < 13)
                board[i][j] = enemyChar;
            else if(i == 5 && j > 2 && j < 13)
                board[i][j] = enemyChar;
            else
            {
                board[i][j] = emptyChar;
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
    Leaderboard l;
    
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
    else if(board[lasX-1][lasY] == enemyChar)
    {
        board[lasX-1][lasY] = destroyedEnemyChar;
        board[lasX][lasY] = emptyChar;
        // add delay function
        board[lasX-1][lasY] = emptyChar;
        ////////////////////////////////////////////////////////////////////////
        l.addScore(100);
        lasState = false;
        enemyDead++;
    }
    else
        lasState = false;
}

void Board::moveEnemiesLR()
{
    if(moveR > 0)
    {
        for(int i = 0; i < row; i++)
        {
            if(checkRow(i, 'R'))
            {
                int temp = board[i][col-2];
                for(int j = col-2; j > 0; --j)
                {
                    board[i][j] = board [i][j-1];
                }
                board [i][1] = temp;
            }
        }
        
        if(moveR == 1)
            checkSide('R');
        
        if(moveR == 1)
        {
            moveR = 0;
            moveL = 4;
            downState = true;
        } 
        else if(moveR > 1)
            moveR--;
    }
    else if(moveL > 0)
    {
        for(int i = 0; i < row; i++)
        {
            if(checkRow(i, 'L'))
            {
                int temp = board[i][1];
                for(int j = 1; j < col-2; j++)
                {
                    board[i][j] = board [i][j+1];
                }
                board [i][col-2] = temp;
            }
        }
        
        if(moveL == 1)
            checkSide('L');
        
        if(moveL == 1)
        {
            moveR = 4;
            moveL = 0;
            downState = true;
        } 
        else if(moveL > 1)
            moveL--;
    }

    speedTime = 0;
}

bool Board::checkRow(int row, char direction)
{
    bool state = false;
    int enemy = 0;
    
    if(direction == 'R')
    {
        for(int i = 1; i < col-2; i++)
        {
            if(board[row][i] == enemyChar)
                enemy++;
            else if(board[row][i] == lasChar)
                board[row][i] = emptyChar;
            else if((board[row][i] == shield4 || board[row][i] == shield3 ||
                    board[row][i] == shield2 || board[row][i] == shield1) &&
                    enemy > 0)
            {
                if(board[row][i-1] == enemyChar)
                    board[row][i] = emptyChar;
                else
                {
                    board[row][i-1] = board[row][i];
                    board[row][i] = emptyChar;
                }
            }
//            if(board[row][i] == plyrChar)
                // condition for restart game, lose life
        }
    }
    else if (direction == 'L')
    {
        for(int i = col-2; i > 1; --i)
        {
            if(board[row][i] == enemyChar)
                enemy++;
            else if(board[row][i] == lasChar)
                board[row][i] = emptyChar;
            else if((board[row][i] == shield4 || board[row][i] == shield3 ||
                    board[row][i] == shield2 || board[row][i] == shield1) &&
                    enemy > 0)
            {
                if(board[row][i+1] == enemyChar)
                    board[row][i] = emptyChar;
                else
                {
                    board[row][i+1] = board[row][i];
                    board[row][i] = emptyChar;
                }
                enemy++;
            }
//            if(board[row][i] == plyrChar)
                // condition for restart game, lose life
        }        
    }
    
    if(enemy > 0)
        state = true;
    
    return state;
}

void Board::checkSide(char direction)
{
    int enemy = 0;
    
    if(direction == 'R')
    {
        for(int i = 0; i < row; i++)
        {
            if(board[i][col-2] == enemyChar)
            {
                enemy++;
            }
        }
        if(enemy == 0)
            moveR++;
    }
    else if(direction == 'L')
    {
       for(int i = 0; i < row; i++)
        {
            if(board[i][1] == enemyChar)
            {
                enemy++;
            }
        } 
        if(enemy == 0)
            moveL++;
    }   
}

void Board::moveEnemiesD()
{
    int temp;
    
    for(int i = 1; i < col-1; i++)
    {
        if(checkCol(i))
        {
            temp = board[row-1][i];
            for(int j = row-1; j > 0; --j)
            {
                // add in enemy hitting player condition
                board[j][i] = board[j-1][i];
            }
            board [0][i] = temp;
        }
    }
    
    downState = false;
}

bool Board::checkCol(int col)
{
    bool state = false;
    int enemy = 0;
    
    for(int i = 0; i < row; i++)
    {
        if(board[i][col] == enemyChar)
        {
            enemy++;
        }
        else if(board[i][col] == plyrChar)
        {
            // add condition to lose a life
            board[i][col] = emptyChar;
            board[i-1][col] = plyrChar;
        }
        else if((board[i][col] == shield4 || board[i][col] == shield3 ||
                board[i][col] == shield2 || board[i][col] == shield1)
                && enemy > 0)
        {
            if(board[i-1][col] == enemyChar)
                board[i][col] = emptyChar;
            else
            {
                board[i-1][col] = board[i][col];
                board[i][col] = emptyChar;
            }
        }
    }
    
    if(enemy > 0)
        state = true;
    
    return state;
}

void Board::enemyTimer(){
    if (enemyDead > 1){
        enemySpeed++;
        enemyDead = 0;
    }
}

// main.cpp ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    // create objects from classes
    Board board;
    Leaderboard ldrBrd;
    
    //start menu
    start_menu();
    
    // create the game board
    board.createBoard();
    
    // play Space Invaders; display board, get input
    while(board.getGameState() != true)
    {
        system("clear");
        
        if(board.getLaserState())
            board.movPlyrLas();
        
        if(board.getSpeedTimer() == board.getEnemySpeed())
        {
            if(board.getDownState())
                board.moveEnemiesD();
//            else
                board.moveEnemiesLR();
        }

        ldrBrd.getLeaderboard();
        board.dispBrd();
        ldrBrd.getBtmBoard();
        
        board.input();
        
        board.speedTimer();
        board.enemyTimer();
    }

    return 0;
}