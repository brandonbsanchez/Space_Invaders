// header.h ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <windows.h> // for getasynkeystate function

using namespace std;

// board.h ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// leaderboard.h //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Leaderboard
{
private:
    int scoreOne;                       //Player One's score.
    int hiScore;                        //High Score.
    //int scoreTwo;                     //Player Two's score. To be implemented later.
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
    int lives;                          //The number of lives the player has.
    
    void lostLife() { --lives; }
    int getLives() { return lives; }
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
    cout<<"SCORE<1>"<<"\tHI-SCORE\n  ";
    cout<<setw(4)<<setfill('0')<<scoreOne<<"\t\t "<<setw(4)<<setfill('0')<<hiScore<<endl<<endl;
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

class Board
{
private:
    int row;
    int col;
    char **board;
    bool gameOver;
    
    char emptyChar;
    char boundaryChar;
    
    // player data
    char plyrChar;
    int plyrX, plyrY;       // x and y of the player in the 2D array
    
    // enemy data
    char enemyChar;
    char destroyedEnemyChar;
    int enemyPoints;
    int numEnemies;
    int moveR;
    int moveL;
    int enemySpeed;
    int speedTime;
    bool downState;
    int lasX1, lasX2, lasX3, lasX4, lasX5, lasX6, lasX7, lasX8, lasX9, lasX10;
    int lasY1, lasY2, lasY3, lasY4, lasY5, lasY6, lasY7, lasY8, lasY9, lasY10;
    int netLR;
    int numEnemyLas;
    int eLas1X, eLas1Y;
    int eLas2X, eLas2Y;
    bool eLas1State, eLas2State;
    int eLasSpeed;
    
    // shield data
    char shield1;
    char shield2;
    char shield3;
    char shield4;
    char sHlth4;
    char sHlth3;
    char sHlth2;
    char sHlth1;
    
    // laserData
    char lasChar;
    int lasX, lasY;         // x and y of the player's laser, vertically bound
    bool lasStateP;          // state of laser, if its on board or not
    
public:
    Board();
    ~Board();
    
    // create object for the Leaderboard class in the board class
    Leaderboard ldrBrd;
    
    // class functions
    void startMenu();
    void createBoard();
    void dispBrd();
    bool getGameState() { return gameOver; }
    
    // player functions
    void input();
    bool getLaserStateP() { return lasStateP; }
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
    void setEnemyLasers();
    void enemyTimer();
    void enemyLas();
    void moveEnemyLas1(int, int);
    void moveEnemyLas2(int, int);
    void eLasSpeedUp() { eLasSpeed++; }
    bool checkEnemies();
    bool enemyStop();
    void downStop() { downState = false; }
    
    void loseLife();
    void winGame();
    void loseGame();
    
    void debug();
};

// constructor to set size of game board, initialize dynamic 2D array
Board::Board()
{
    row = 14;                       // height of board
    col = 18;                       // width of board
    
    board = new char*[row];
    for(int i=0; i<row; i++)
        board[i] = new char[col];
        
    emptyChar = '-';
    boundaryChar = '#';
        
    plyrChar = 'P';

    lasChar = '|';

    gameOver = false;
    lasStateP = false;
    
    shield1 = shield2 = shield3 = shield4 = '4';
    sHlth4 = '4';
    sHlth3 = '3';
    sHlth2 = '2';
    sHlth1 = '1';

    enemyChar = 'E';
    destroyedEnemyChar = 'x';
    numEnemies = 50;
    enemyPoints = 100;
    moveR = 3;
    moveL = 0;
    enemySpeed = 15;
    speedTime = 0;
    downState = false;
    netLR = 0;
    numEnemyLas = 0;
    eLas1X = eLas1Y = eLas2X = eLas2Y = 0;
    eLas1State = eLas2State = false;
    eLasSpeed = 0;
    
    // set the random number seed
    srand(static_cast<unsigned int>(time(0)));
}

// destructor to delete dynamic memory from 2D array
Board::~Board()
{
    for(int i=0; i < row; i++)
        delete [] board[i];
    delete [] board;    
}

void Board::startMenu()
{
    ldrBrd.getLeaderboard();
    
    cout << "  ____                         ___                     _                       \n";
    cout << " / ___| _ __   __ _  ___ ___  |_ _|_ ____   ____ _  __| | ___ _ __ ___         \n";
    cout << " \\___ \\| '_ \\ / _` |/ __/ _ \\  | || '_ \\ \\ / / _` |/ _` |/ _ \\ '__/ __| \n";
    cout << "  ___) | |_) | (_| | (_|  __/  | || | | \\ V / (_| | (_| |  __/ |  \\__ \\     \n";
    cout << " |____/| .__/ \\__,_|\\___\\___| |___|_| |_|\\_/ \\__,_|\\__,_|\\___|_|  |___/ \n";
    cout << "       |_|                                                                   \n\n";
    
    cout << " 'A' to move LEFT\n";
    cout << " 'D' to move RIGHT\n";
    cout << " 'SPACEBAR' to shoot laser\n\n";

    cout << " * SCORE ADVANCE TABLE *\n";
    cout << "     " << enemyChar << " = " << enemyPoints << " POINTS\n\n";
    cout << "Press [ENTER] to continue...";

    cin.ignore();
}

// this functions sets up the initial conditions of the gameboard with:
// player, side barriers, enemies, blockades, empty space
void Board::createBoard()
{
    int e = numEnemies;
    
    for(int i=0; i < row; i++){
        for(int j=0; j < col; j++){
            if(i == 13 && j == 8)
            {
                board[i][j] = plyrChar;
                plyrX = i;
                plyrY = j;
                lasX = plyrX;
                lasY = plyrY;
            }
            else if(i == 11 && j == 4)
            {
                board[i][j] = shield1;
            }
            else if(i == 11 && j == 7)
            {
                board[i][j] = shield2;
            }
            else if(i == 11 && j == 10)
            {
                board[i][j] = shield3;
            }
            else if(i == 11 && j == 13)
            {
                board[i][j] = shield4;
            }
            else if (i > 0 && i < 6 && j > 3 && j < 14 && e > 0)
            {
                board[i][j] = enemyChar;
                --e;
            }
            else if(j==0 || j==col-1)
            {
                board[i][j] = boundaryChar;
            }
            else
            {
                board[i][j] = emptyChar;
            }
        }
    }
    setEnemyLasers();
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
}

// this function looks for input from the player to move Left and Right, and
// shoot lasers; it has boundary check and laser delay
void Board::input()
{
    if(board[plyrX][plyrY] != plyrChar)
        board[plyrX][plyrY] = plyrChar;
    
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
    else if(GetAsyncKeyState(0x20) && lasStateP == false){ // 'SPACEBAR'
        plyrLas();
    }
}

void Board::plyrLas()
{
    lasStateP = true;
    
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
        lasStateP = false;
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
    else if(board[lasX-1][lasY] == shield1 || board[lasX-1][lasY] == shield2 ||
            board[lasX-1][lasY] == shield3 || board[lasX-1][lasY] == shield4)
    {
        if(board[lasX-1][lasY] == shield1)
        {
            switch(board[lasX-1][lasY])
            {
                case '4':
                    board[lasX-1][lasY] = shield1 = sHlth3;
                    board[lasX][lasY] = emptyChar;
                    break;
                case '3':
                    board[lasX-1][lasY] = shield1 = sHlth2;
                    board[lasX][lasY] = emptyChar;
                    break;
                case '2':
                    board[lasX-1][lasY] = shield1 = sHlth1;
                    board[lasX][lasY] = emptyChar;
                    break;
                case '1':
                    board[lasX-1][lasY] = shield1 = emptyChar;
                    board[lasX][lasY] = emptyChar;
                    break;
            }
        }
        else if(board[lasX-1][lasY] == shield2)
        {
            switch(board[lasX-1][lasY])
            {
                case '4':
                    board[lasX-1][lasY] = shield2 = sHlth3;
                    board[lasX][lasY] = emptyChar;
                    break;
                case '3':
                    board[lasX-1][lasY] = shield2 = sHlth2;
                    board[lasX][lasY] = emptyChar;
                    break;
                case '2':
                    board[lasX-1][lasY] = shield2 = sHlth1;
                    board[lasX][lasY] = emptyChar;
                    break;
                case '1':
                    board[lasX-1][lasY] = shield2 = emptyChar;
                    board[lasX][lasY] = emptyChar;
                    break;
            }
        }
        else if(board[lasX-1][lasY] == shield3)
        {
            switch(board[lasX-1][lasY])
            {
                case '4':
                    board[lasX-1][lasY] = shield3 = sHlth3;
                    board[lasX][lasY] = emptyChar;
                    break;
                case '3':
                    board[lasX-1][lasY] = shield3 = sHlth2;
                    board[lasX][lasY] = emptyChar;
                    break;
                case '2':
                    board[lasX-1][lasY] = shield3 = sHlth1;
                    board[lasX][lasY] = emptyChar;
                    break;
                case '1':
                    board[lasX-1][lasY] = shield3 = emptyChar;
                    board[lasX][lasY] = emptyChar;
                    break;
            }
        }
        else if(board[lasX-1][lasY] == shield4)
        {
            switch(board[lasX-1][lasY])
            {
                case '4':
                    board[lasX-1][lasY] = shield4 = sHlth3;
                    board[lasX][lasY] = emptyChar;
                    break;
                case '3':
                    board[lasX-1][lasY] = shield4 = sHlth2;
                    board[lasX][lasY] = emptyChar;
                    break;
                case '2':
                    board[lasX-1][lasY] = shield4 = sHlth1;
                    board[lasX][lasY] = emptyChar;
                    break;
                case '1':
                    board[lasX-1][lasY] = shield4 = emptyChar;
                    board[lasX][lasY] = emptyChar;
                    break;
            }
        }
        lasStateP = false;
    }
    else if(board[lasX-1][lasY] == enemyChar)
    {
        board[lasX-1][lasY] = destroyedEnemyChar;
        board[lasX][lasY] = emptyChar;
        board[lasX-1][lasY] = emptyChar;
        
        ldrBrd.addScore(enemyPoints);
        lasStateP = false;
        
        --numEnemies;
        
        switch(lasY - 3 + (-1*netLR))
        {
            case 1:
                --lasX1;
                break;
            case 2:
                --lasX2;
                break;
            case 3:
                --lasX3;
                break;
            case 4:
                --lasX4;
                break;
            case 5:
                --lasX5;
                break;
            case 6:
                --lasX6;
                break;
            case 7:
                --lasX7;
                break;
            case 8:
                --lasX8;
                break;
            case 9:
                --lasX9;
                break;
            case 10:
                --lasX10;
                break;
        }        
    }
    else if(board[lasX-1][lasY] == lasChar)
    {
        board[lasX-1][lasY] = emptyChar;
        board[lasX][lasY] = emptyChar;
        lasStateP = false;
    }
    else
        lasStateP = false;
}

void Board::moveEnemiesLR()
{
    if(moveR > 0)
    {
        for(int i = 0; i < row-3; i++)
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
        
        ++lasY1, ++lasY2, ++lasY3, ++lasY4, ++lasY5, ++lasY6, ++lasY7, ++lasY8, ++lasY9, ++lasY10;
        
        if(moveR == 1)
            checkSide('R');
        
        if(moveR == 1)
        {
            moveR = 0;
            moveL = 5;
            downState = true;
        } 
        else if(moveR > 1)
            moveR--;
        
        netLR++;
    }
    else if(moveL > 0)
    {
        for(int i = 0; i < row-3; i++)
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
        
        --lasY1, --lasY2, --lasY3, --lasY4, --lasY5, --lasY6, --lasY7, --lasY8, --lasY9, --lasY10;
        
        if(moveL == 1)
            checkSide('L');
        
        if(moveL == 1)
        {
            moveR = 5;
            moveL = 0;
            downState = true;
        } 
        else if(moveL > 1)
            moveL--;
        
        netLR--;
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
            else if((board[row][i] == shield1 || board[row][i] == shield2 ||
                    board[row][i] == shield3 || board[row][i] == shield4) &&
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
        }
        if(enemy > 0)
        {
            for(int i = 1; i < col-2; i++)
            {
                if(board[row][i] == lasChar)
                {
                    board[row][i] = emptyChar;
                    lasStateP = false;
                }
            }
        }
    }
    else if (direction == 'L')
    {
        for(int i = col-2; i > 1; --i)
        {
            if(board[row][i] == enemyChar)
                enemy++;
            else if(board[row][i] == lasChar)
            {
                board[row][i] = emptyChar;
                //
                lasStateP = false;
            }
            else if((board[row][i] == shield1 || board[row][i] == shield2 ||
                    board[row][i] == shield3 || board[row][i] == shield4) &&
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
        }
        if(enemy > 0)
        {
            for(int i = 1; i < col-2; i++)
            {
                if(board[row][i] == lasChar)
                {
                    board[row][i] = emptyChar;
                    lasStateP = false;
                }
            }
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
    
    ++lasX1, ++lasX2, ++lasX3, ++lasX4, ++lasX5, ++lasX6, ++lasX7, ++lasX8, ++lasX9, ++lasX10;
    
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
            
            if(board[i-1][col-1] == plyrChar)
                board[i-1][col-1] == emptyChar;
            if(board[i][col-1] == plyrChar)
                board[i][col-1] == emptyChar;
            if(board[i-1][col+1] == plyrChar)
                board[i-1][col+1] == emptyChar;
            if(board[i][col+1] == plyrChar)
                board[i][col+1] == emptyChar;
        }
        else if((board[i][col] == shield1 || board[i][col] == shield2 ||
                board[i][col] == shield3 || board[i][col] == shield4)
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

void Board::enemyTimer()
{
    if(numEnemies <= 10)
        enemySpeed = 10;
    else if(numEnemies <= 30)
        enemySpeed = 12;
    else if(numEnemies <= 50)
        enemySpeed = 15;
}

void Board::setEnemyLasers()
{
    bool boolVar;
    
    // column 4 through 13
    for(int i = 4; i < 14; i++)
    {
        boolVar = true;
        for(int j = row-1; j > 0; --j)
        {
            if(board[j][i] == enemyChar && boolVar)
            {
                boolVar = false;
                switch(i)
                {
                    case 4:
                        lasX1 = j;
                        lasY1 = i;
                        break;
                    case 5:
                        lasX2 = j;
                        lasY2 = i;
                        break;
                    case 6:
                        lasX3 = j;
                        lasY3 = i;
                        break;
                    case 7:
                        lasX4 = j;
                        lasY4 = i;
                        break;
                    case 8:
                        lasX5 = j;
                        lasY5 = i;
                        break;
                    case 9:
                        lasX6 = j;
                        lasY6 = i;
                        break;
                    case 10:
                        lasX7 = j;
                        lasY7 = i;
                        break;
                    case 11:
                        lasX8 = j;
                        lasY8 = i;
                        break;
                    case 12:
                        lasX9 = j;
                        lasY9 = i;
                        break;
                    case 13:
                        lasX10 = j;
                        lasY10 = i;
                        break;
                }
            }
        }
    }    
}

void Board::enemyLas()
{
    int randNum, x, y;
    
    if(numEnemyLas == 0 || numEnemyLas == 1)
        ++numEnemyLas;
    
    if((numEnemyLas == 1 || numEnemyLas == 2) && ((eLasSpeed == 20)))
    {
        randNum = rand() % 10 + 1;      // in range 1 to 10
        
        switch(randNum)
        {
            case 1:
                x = lasX1;
                y = lasY1;
                break;
            case 2:
                x = lasX2;
                y = lasY2;
                break;
            case 3:
                x = lasX3;
                y = lasY3;
                break;
            case 4:
                x = lasX4;
                y = lasY4;
                break;
            case 5:
                x = lasX5;
                y = lasY5;
                break;
            case 6:
                x = lasX6;
                y = lasY6;
                break;
            case 7:
                x = lasX7;
                y = lasY7;
                break;
            case 8:
                x = lasX8;
                y = lasY8;
                break;
            case 9:
                x = lasX9;
                y = lasY9;
                break;
            case 10:
                x = lasX10;
                y = lasY10;
                break;      
        }
        
        if(!eLas1State)
        {
            eLas1X = x;
            eLas1Y = y;
            eLas1State = true;
        }
        
        if(!eLas2State)
        {
            eLas2X = x;
            eLas2Y = y;
            if((eLas2X == eLas1X) && (eLas2Y == eLas1Y))
                enemyLas();
            eLas2State = true;
        }
        
        eLasSpeed = 0;
    }
    
    if(numEnemyLas == 1 || numEnemyLas == 2)
    {
        if(eLas1State && eLas1X > 0)
            moveEnemyLas1(eLas1X, eLas1Y);
        
        if(eLas2State && eLas2X > 0)
            moveEnemyLas2(eLas2X, eLas2Y);
    }
}

void Board::moveEnemyLas1(int x, int y)
{
    if(x+1 > row-1)
    {
        board[x][y] = emptyChar;
        --numEnemyLas;
        eLas1State = false;
        eLas1X = 0;
    }
    else if(board[x+1][y] == emptyChar)
    {
        if(board[x][y] == enemyChar)
            board[x+1][y] = lasChar;
        else
        {
            board[x][y] = emptyChar;
            board[x+1][y] = lasChar;
        }
        
        ++eLas1X;
    }
    else if(board[x+1][y] == shield1 || board[x+1][y] == shield2 ||
            board[x+1][y] == shield3 || board[x+1][y] == shield4)
    {
        if(board[x+1][y] == shield1)
        {
            switch(board[x+1][y])
            {
                case '4':
                    board[x+1][y] = shield1 = sHlth3;
                    board[x][y] = emptyChar;
                    break;
                case '3':
                    board[x+1][y] = shield1 = sHlth2;
                    board[x][y] = emptyChar;
                    break;
                case '2':
                    board[x+1][y] = shield1 = sHlth1;
                    board[x][y] = emptyChar;
                    break;
                case '1':
                    board[x+1][y] = shield1 = emptyChar;
                    board[x][y] = emptyChar;
                    break;
            }
        }
        else if(board[x+1][y] == shield2)
        {
            switch(board[x+1][y])
            {
                case '4':
                    board[x+1][y] = shield2 = sHlth3;
                    board[x][y] = emptyChar;
                    break;
                case '3':
                    board[x+1][y] = shield2 = sHlth2;
                    board[x][y] = emptyChar;
                    break;
                case '2':
                    board[x+1][y] = shield2 = sHlth1;
                    board[x][y] = emptyChar;
                    break;
                case '1':
                    board[x+1][y] = shield2 = emptyChar;
                    board[x][y] = emptyChar;
                    break;
            }
        }
        else if(board[x+1][y] == shield3)
        {
            switch(board[x+1][y])
            {
                case '4':
                    board[x+1][y] = shield3 = sHlth3;
                    board[x][y] = emptyChar;
                    break;
                case '3':
                    board[x+1][y] = shield3 = sHlth2;
                    board[x][y] = emptyChar;
                    break;
                case '2':
                    board[x+1][y] = shield3 = sHlth1;
                    board[x][y] = emptyChar;
                    break;
                case '1':
                    board[x+1][y] = shield3 = emptyChar;
                    board[x][y] = emptyChar;
                    break;
            }
        }
        else if(board[x+1][y] == shield4)
        {
            switch(board[x+1][y])
            {
                case '4':
                    board[x+1][y] = shield4 = sHlth3;
                    board[x][y] = emptyChar;
                    break;
                case '3':
                    board[x+1][y] = shield4 = sHlth2;
                    board[x][y] = emptyChar;
                    break;
                case '2':
                    board[x+1][y] = shield4 = sHlth1;
                    board[x][y] = emptyChar;
                    break;
                case '1':
                    board[x+1][y] = shield4 = emptyChar;
                    board[x][y] = emptyChar;
                    break;
            }
        }
        --numEnemyLas;
        eLas1State = false;
        eLas1X = 0;
    }
    else if(board[x+1][y] == enemyChar)
    {
        board[x][y] = emptyChar;
        board[x+1][y] = emptyChar;
        --numEnemyLas;     
        eLas1State = false;
        eLas1X = 0;
    }
    else if(board[x+1][y] == lasChar)
    {
        board[x+1][y] = emptyChar;
        board[x][y] = emptyChar;
        --numEnemyLas;
        eLas1State = false;
        eLas1X = 0;
    }
    else if(board[x+1][y] == plyrChar)
    {
        ldrBrd.lostLife();
        --numEnemyLas;
        eLas1State = false;
        eLas1X = 0;
        eLas1Y = 0;
        loseLife();
    }
    else
    {
        --numEnemyLas;
        eLas1State = false;
        eLas1X = 0;
    }
}

void Board::moveEnemyLas2(int x, int y)
{
    if(x+1 > row-1)
    {
        board[x][y] = emptyChar;
        --numEnemyLas;
        eLas2State = false;
        eLas2X = 0;
    }
    else if(board[x+1][y] == emptyChar)
    {
        if(board[x][y] == enemyChar)
            board[x+1][y] = lasChar;
        else
        {
            board[x][y] = emptyChar;
            board[x+1][y] = lasChar;
        }
        
        ++eLas2X;
    }
    else if(board[x+1][y] == shield1 || board[x+1][y] == shield2 ||
            board[x+1][y] == shield3 || board[x+1][y] == shield4)
    {
        if(board[x+1][y] == shield1)
        {
            switch(board[x+1][y])
            {
                case '4':
                    board[x+1][y] = shield1 = sHlth3;
                    board[x][y] = emptyChar;
                    break;
                case '3':
                    board[x+1][y] = shield1 = sHlth2;
                    board[x][y] = emptyChar;
                    break;
                case '2':
                    board[x+1][y] = shield1 = sHlth1;
                    board[x][y] = emptyChar;
                    break;
                case '1':
                    board[x+1][y] = shield1 = emptyChar;
                    board[x][y] = emptyChar;
                    break;
            }
        }
        else if(board[x+1][y] == shield2)
        {
            switch(board[x+1][y])
            {
                case '4':
                    board[x+1][y] = shield2 = sHlth3;
                    board[x][y] = emptyChar;
                    break;
                case '3':
                    board[x+1][y] = shield2 = sHlth2;
                    board[x][y] = emptyChar;
                    break;
                case '2':
                    board[x+1][y] = shield2 = sHlth1;
                    board[x][y] = emptyChar;
                    break;
                case '1':
                    board[x+1][y] = shield2 = emptyChar;
                    board[x][y] = emptyChar;
                    break;
            }
        }
        else if(board[x+1][y] == shield3)
        {
            switch(board[x+1][y])
            {
                case '4':
                    board[x+1][y] = shield3 = sHlth3;
                    board[x][y] = emptyChar;
                    break;
                case '3':
                    board[x+1][y] = shield3 = sHlth2;
                    board[x][y] = emptyChar;
                    break;
                case '2':
                    board[x+1][y] = shield3 = sHlth1;
                    board[x][y] = emptyChar;
                    break;
                case '1':
                    board[x+1][y] = shield3 = emptyChar;
                    board[x][y] = emptyChar;
                    break;
            }
        }
        else if(board[x+1][y] == shield4)
        {
            switch(board[x+1][y])
            {
                case '4':
                    board[x+1][y] = shield4 = sHlth3;
                    board[x][y] = emptyChar;
                    break;
                case '3':
                    board[x+1][y] = shield4 = sHlth2;
                    board[x][y] = emptyChar;
                    break;
                case '2':
                    board[x+1][y] = shield4 = sHlth1;
                    board[x][y] = emptyChar;
                    break;
                case '1':
                    board[x+1][y] = shield4 = emptyChar;
                    board[x][y] = emptyChar;
                    break;
            }
        }
        --numEnemyLas;
        eLas2State = false;
        eLas2X = 0;
    }
    else if(board[x+1][y] == enemyChar)
    {
        board[x][y] = emptyChar;
        board[x+1][y] = emptyChar;
        --numEnemyLas;  
        eLas2State = false;
        eLas2X = 0;
    }
    else if(board[x+1][y] == lasChar)
    {
        board[x+1][y] = emptyChar;
        board[x][y] = emptyChar;
        --numEnemyLas;
        eLas2State = false;
        eLas2X = 0;
    }
    else if(board[x+1][y] == plyrChar)
    {
        ldrBrd.lostLife();
        --numEnemyLas;
        eLas2State = false;
        eLas2X = 0;
        eLas2Y = 0;
        loseLife();
    }
    else
    {
        --numEnemyLas;
        eLas2State = false;
        eLas2X = 0;
    }
}

void Board::loseLife()
{
cout<<" _               _     _     _  __       _ "<<endl;
cout<<"| |             | |   | |   (_)/ _|     | |    "<<endl;  
cout<<"| |     ___  ___| |_  | |    _| |_ ___  | |    "<<endl;
cout<<"| |    / _ \\/ __| __| | |   | |  _/ _ \\ | |    "<<endl;
cout<<"| |___| (_) \\__ \\ |_  | |___| | ||  __/ |_|    "<<endl;
cout<<"\\_____/\\___/|___/\\__| \\_____/_|_| \\___| (_)    "<<endl;
cout<<endl<<"\t"<<"Lives Remaining: "<<ldrBrd.getLives()<<endl;    
    Sleep(2000);
    
    
    // reset some conditions
    moveR = 3;
    moveL = 0;
    enemySpeed = 15;
    speedTime = 0;
    downState = false;
    netLR = 0;
    numEnemyLas = 0;
    eLas1X = eLas1Y = eLas2X = eLas2Y = 0;
    eLas1State = eLas2State = false;
    eLasSpeed = 0;
    
//    if(ldrBrd.getLives() == 0){
//        loseGame();
//    }else
//    {
//        createBoard();
//    }
}

bool Board::checkEnemies()
{
    int enemiesLeft = 0;
    
    for(int i = 0 ; i < row ; i++)
    {
        for(int j = 0 ; j < col ; j++)
        {
            if(board[i][j] == enemyChar)
            {
                enemiesLeft++;
            }
        }
    }
    if(enemiesLeft == 0)
    {
        winGame();          // you win
        
        return false;
    }
    if(ldrBrd.lives <= 0 )
    {
        loseGame();
        
        return false;
    }
    
    return true;
}

void Board::winGame()
{
    numEnemies = 50;
    ldrBrd.lives = 3;
    system("clear");    
    cout<<" _    _ _                         _    "<<endl;
    cout<<"| |  | (_)                       | |  "<<endl;
    cout<<"| |  | |_ _ __  _ __   ___ _ __  | |  "<<endl;
    cout<<"| |/\\| | | '_ \\| '_ \\ / _ \\ '__| | |  "<<endl;
    cout<<"\\  /\\  / | | | | | | |  __/ |    |_|  "<<endl;
    cout<<" \\/  \\/|_|_| |_|_| |_|\\___|_|    (_)  "<<endl;                               
    Sleep(2000);    
    system("clear"); 
}

void Board::loseGame() {
    numEnemies = 50;
    ldrBrd.lives = 3;
    system("clear");    
    cout<<"_____                        _____                        "<<endl;    
    cout<<"|  __ \\                      |  _  |                     "<<endl;  
    cout<<"| |  \\/ __ _ _ __ ___   ___  | | | |_   _____ _ __       "<<endl;
    cout<<"| | __ / _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__|  "<<endl;
    cout<<"| |_\\ \\ (_| | | | | | |  __/ \\ \\_/ /\\ V /  __/ |     "<<endl;
    cout<<"\\____/\\__,_|_| |_| |_|\\___|  \\___/  \\_/ \\___|_|     "<<endl;
//    cin.clear();
    Sleep(2000);      
    system("clear"); 
}

bool Board::enemyStop(){
    bool state = false;
    int enemy = 0;
    for (int i = 0; i < col-1; i++){
        if (board[10][i] == enemyChar){
            enemy++;
        }
    }
    if (enemy > 0){
        state = true;
    }
    
    return state;
}

void Board::debug()
{
    for(int i = 0 ; i < 13; i++)
    {
        for(int j = 0 ; j < col ; j++)
        {
            if(board[i][j] == plyrChar)
                board[i][j] = emptyChar;
        }
    }
}

// main.cpp ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    
    do{
    // create board object
    Board board;

    // start menu
    board.startMenu();
    
    // create the game board
    board.createBoard();
    bool notLost = true;
    
    // play Space Invaders; display board, get input, move enemies
    while(notLost)
    {
        system("clear");
        
        board.debug();
        
        if(board.getLaserStateP())
            board.movPlyrLas();
        
        if(board.getSpeedTimer() == board.getEnemySpeed())
        {
            if(board.getDownState()){
                if (board.enemyStop()){
                    board.downStop();
                }else {
                    board.moveEnemiesD();
//                  Sleep(1000);          // find a better function
                }
            }
//            else
                board.moveEnemiesLR();
        }

        board.enemyLas();
        board.ldrBrd.getLeaderboard();
        board.dispBrd();
        board.ldrBrd.getBtmBoard();
        
        board.input();
        
        board.speedTimer();
        board.eLasSpeedUp();
        
        board.enemyTimer();
        
        notLost = board.checkEnemies();
    }
}while(true);
    // end the game, credits
    
    return 0;
}
