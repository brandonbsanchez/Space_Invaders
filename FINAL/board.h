// -----------------------------------------------------------------------------
// This class holds everything that goes on the game board itself like the
// player, enemies, lasers, shields, and boundaries. The board is able to be
// printed based on how fast the computer running it can handle. 
// -----------------------------------------------------------------------------
#include "header.h"
#include "leaderboard.h"

class Board
{
private:
    // board data
    int row;                    // row size of 2D array
    int col;                    // col size of 2D array
    char **board;               // dynamic 2D array for game board
    bool gameState;              // bool to determine if the game is over
    char emptyChar;             // char for empty spaces on the game board
    char boundaryChar;          // char for boundaries on the sides of the board
    
    // player data
    char plyrChar;              // char for the player on the board
    int plyrX, plyrY;           // x and y of the player in the 2D array
    
    // enemy data
    char enemyChar;             // char for enemy on the board  
    char destroyedEnemyChar;    // char for when the enemy is destroyed
    int enemyPoints;            // point value per enemy
    int numEnemies;             // total number of enemies on board
    int moveR;                  // number of times the enemies need to move right
    int moveL;                  // number of times the enemies need to move left
    int enemySpeed;             // how quickly the enemies move, higher = slower
    int speedTime;              // variable to control enemy speed, increments
    bool downState;             // bool if the enemies need to move down or not
                                // X Y position for the two enemy lasers
    int lasX1, lasX2, lasX3, lasX4, lasX5, lasX6, lasX7, lasX8, lasX9, lasX10;
    int lasY1, lasY2, lasY3, lasY4, lasY5, lasY6, lasY7, lasY8, lasY9, lasY10;
    int netLR;                  // the net enemy movement, used for enemy lasers
    int numEnemyLas;            // number of enemy lasers on board at once, max 2
    int eLas1X, eLas1Y;         // enemy las 1's X Y position in 2D array
    int eLas2X, eLas2Y;         // enemy las 2's X Y position in 2D array
    bool eLas1State, eLas2State;// bool for if las 1 or 2 is on the board
    int eLasSpeed;              // speed for the lasers
    
    // shield data
    char shield1;               // char for the first  shield on the board
    char shield2;               // char for the second shield on the board
    char shield3;               // char for the third  shield on the board
    char shield4;               // char for the fourth shield on the board
    char sHlth4;                // shield health of '4'
    char sHlth3;                // shield health of '3'
    char sHlth2;                // shield health of '2'
    char sHlth1;                // shield health of '1'
    
    // laserData        
    char lasChar;               // char for any laser in the 2D array
    int lasX, lasY;             // x and y of the player's laser, vertically bound
    bool lasStateP;             // state of laser, if its on board or not
    
    // loseGame
    int choice;              // variable to hold choice
    
public:
    Board();                    // constructor
    ~Board();                   // destructor
    
    // create object for the Leaderboard class in the board class
    Leaderboard ldrBrd;
    
    // class functions
    void startMenu();                           // menu to introduce game
    void createBoard();                         // starting board conditions
    void dispBrd();                             // output the board itself
    bool getGameState() { return gameState; }    // return if game is over or not
    
    // player functions
    void input();                               // keyboard input of player
    bool getLaserStateP() { return lasStateP; } // if player laser is on the board
    void plyrLas();                             // set X Y of laser from the player X Y
    void movPlyrLas();                          // move the player laser
    
    // enemy functions
    void moveEnemiesLR();                       // move enemies Left or Right
    void moveEnemiesD();                        // move enemies Down
    void speedTimer() { speedTime++; }          // increment speed timer
    int getSpeedTimer() { return speedTime; }   // get speed timer for main
    int getEnemySpeed() { return enemySpeed; }  // get enemy speed for main
    bool checkRow(int, char);                   // check if row has enemies in it
    bool checkCol(int);                         // check if column has enemies
    void checkSide(char);                       // check if sides have enemies
    bool getDownState() { return downState; }   // get down state for main
    void setEnemyLasers();                      // set up all the enemy lasers X Y
    void enemyTimer();                          // how fast enemies are based on how many are left
    void enemyLas();                            // randomize which enemies shoot a laser
    void moveEnemyLas1(int, int);               // move enemy laser 1
    void moveEnemyLas2(int, int);               // move enemy laser 
    void eLasSpeedUp() { eLasSpeed++; }         // keeps track of enemy laser speed
    void checkEnemies();                        // double check how many enemies left
    bool enemyStop();                           // stop enemies on row before shields
    void downStop() { downState = false; }      // stop enemes from moving down
    
    // game functions
    void loseLife();                            // lose a life
    void winGame();                             // you win the game
    void loseGame();                            // you lose the game
    
    // debug function
    void debug();                               // housekeeping for the player icon with row movement
};

// constructor to set size of game board, initialize dynamic 2D array
Board::Board()
{
    // board variables
    row = 14;                           // height of board
    col = 18;                           // width of board
    
    // initialize dynamic 2D array
    board = new char*[row];
    for(int i=0; i<row; i++)
        board[i] = new char[col];
        
    // player variables
    plyrX = plyrY = 0;
        
    // character variables for the board
    emptyChar = '-';
    boundaryChar = '#';
    plyrChar = 'P';
    lasChar = '|';
    enemyChar = 'E';
    destroyedEnemyChar = 'x';

    // shield variables
    shield1 = shield2 = shield3 = shield4 = '4';    // starting health for shield
    sHlth4 = '4';
    sHlth3 = '3';
    sHlth2 = '2';
    sHlth1 = '1';

    // enemy variables
    numEnemies = 1;
    enemyPoints = 100;
    moveR = 3;
    moveL = 0;
    enemySpeed = 15;
    speedTime = 0;
    downState = false;
    netLR = 0;
    lasX1 = lasX2 = lasX3 = lasX4 = lasX5 = lasX6 = lasX7 = lasX8 = lasX9 = lasX10 = 0;
    lasY1 = lasY2 = lasY3 = lasY4 = lasY5 = lasY6 = lasY7 = lasY8 = lasY9 = lasY10 = 0;

    // laser variables
    lasX = lasY = 0;
    lasStateP = false;
    numEnemyLas = 0;
    eLas1X = eLas1Y = eLas2X = eLas2Y = 0;
    eLas1State = eLas2State = false;
    eLasSpeed = 0;
    
    // game variables
    gameState = true;
    
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

// this function outputs a start menu and ascii graphic for the game
// it includes instructions and points along with the initial leaderboard
// and highscore
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

// this functions sets up the initial conditions of the game board with:
// player, side barriers, enemies, blockades, empty space
void Board::createBoard()
{
    int e = numEnemies;                     // to dynamically place in enemies
    
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
    setEnemyLasers();                       // initial enemy laser positions
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

// this function sets the X Y position for the player laser to the player's
// current position
void Board::plyrLas()
{
    lasStateP = true;
    
    if(board[plyrX][plyrY] == plyrChar)
    {
        lasX = plyrX;
        lasY = plyrY;
    }
}

// this function moves the player laser, vertically bound
// it considers every type of character that could be above it
void Board::movPlyrLas()
{
    // if outside of the board, stop laser, set empty char
    if(lasX-1 < 0)
    {
        board[lasX][lasY] = emptyChar;
        lasX = lasY = 0;
        lasStateP = false;
    }
    // if empty, move laser up one, put empty space where it was
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
    // if a shield, decrement the enemy shield, keep track of each shield 
    // position X Y
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
        lasX = lasY = 0;
    }
    // if its an enemy, replace las and enemy with empty char, add score, stop 
    // laser on board, decrement number of enemies on board, reset enemy
    // laser position to enemy above it using net movement
    else if(board[lasX-1][lasY] == enemyChar)
    {
        board[lasX-1][lasY] = destroyedEnemyChar;
        board[lasX][lasY] = emptyChar;
        board[lasX-1][lasY] = emptyChar;
        
        ldrBrd.addScore(enemyPoints);
        lasX = lasY = 0;
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
    // if its a laser they cancel out, both empty spots
    else if(board[lasX-1][lasY] == lasChar)
    {
        if(lasX-1 == eLas1X && lasY == eLas1Y)
        {
            board[lasX-1][lasY] = emptyChar;
            eLas1X = eLas1Y = 0;
            eLas1State = false;
        }
        else if(lasX-1 == eLas2X && lasY == eLas2Y)
        {
            board[lasX-1][lasY] = emptyChar;
            eLas2X = eLas2Y = 0;
            eLas2State = false;
        }
        board[lasX-1][lasY] = emptyChar;
        board[lasX][lasY] = emptyChar;
        lasX = lasY = 0;
        lasStateP = false;
    }
    // otherwise stop the laser
    else
    {
        lasX = lasY = 0;
        lasStateP = false;
    }
}

// this function moves the group of enemies left or right one spot at a time
// using the timer, it check if each row even has an enemy otherwise it wont
// move the row, it also uses a temp variables to hold the end array spot
// so it can rotate the whole role, it also adjusts the enemy laser positions,
// it also check the side to see if the enemies can move left or right more
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

// this function check the row to see if there is an enemy or other thing in the
// row so it can move it, it corrects if there is a laser character
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
                    if(board[row][i-1] == enemyChar)
                    {
                        board[row][i] = emptyChar;
                        lasStateP = false;
                    }
                    else if(board[row][i-1] == emptyChar)
                    {
                        board[row][i-1] == lasChar;
                        board[row][i] == enemyChar;
                    }
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
                    if(board[row][i+1] == enemyChar)
                    {
                        board[row][i] = emptyChar;
                        lasStateP = false;
                    }
                    else if(board[row][i+1] == emptyChar)
                    {
                        board[row][i+1] == lasChar;
                        board[row][i] == enemyChar;
                    }
                }
            }
        }        
    }

    if(enemy > 0)
        state = true;
    
    return state;
}

// this board check the sides next to the boundaries to see if there are enemies
// so the moveLR function knows if it can move the enemies another spot left
// or right
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

// this function moves the enemies down, adjusts the enemy laser position,
// and checks each column to adjust everything
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
                board[j][i] = board[j-1][i];
            }
            board [0][i] = temp;
        }
    }
    
    ++lasX1, ++lasX2, ++lasX3, ++lasX4, ++lasX5, ++lasX6, ++lasX7, ++lasX8, ++lasX9, ++lasX10;
    
    downState = false;
}

// this function checks the columns that enemies are in so they can move down,
// it accounts for player, laser, and shield characters so they dont get
// displaced
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

// this function determines how quick the enemies move as a function of how many
// enemies are still on the board, the high the number the slower they move
// since it they remove a that many frames essentially
void Board::enemyTimer()
{
    if(numEnemies <= 10)
        enemySpeed = 10;
    else if(numEnemies <= 30)
        enemySpeed = 12;
    else if(numEnemies <= 50)
        enemySpeed = 15;
}

// this function search the initial columns the enemies are in to set the X Y
// position of each of the enemy lasers X Y positions
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

// this function randomizes which of the enemies shoot a laser, makes sure they
// cant be the same enemy shooting the laser, used random numbers
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

// this function moves one of the enemy lasers, makes sure it check for each of
// the possible characters it could encounter and adjusts like the player laser
// function did
void Board::moveEnemyLas1(int x, int y)
{
    if(x+1 > row-1)
    {
        board[x][y] = emptyChar;
        --numEnemyLas;
        eLas1X = eLas1Y = 0;
        eLas1State = false;
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
        eLas1X = eLas1Y = 0;
    }
    else if(board[x+1][y] == enemyChar)
    {
        board[x][y] = emptyChar;
        board[x+1][y] = emptyChar;
        --numEnemyLas;     
        eLas1State = false;
        eLas1X = eLas1Y = 0;
    }
    else if(board[x+1][y] == lasChar)
    {
        board[x+1][y] = emptyChar;
        board[x][y] = emptyChar;
        --numEnemyLas;
        eLas1State = false;
        eLas1X = eLas1Y = 0;
    }
    else if(board[x+1][y] == plyrChar)
    {
        ldrBrd.lostLife();
        --numEnemyLas;
        eLas1State = false;
        eLas1X = eLas1Y = 0;
        loseLife();
    }
    else
    {
        --numEnemyLas;
        eLas1State = false;
        eLas1X = eLas1Y = 0;
    }
}

// this function moves one of the enemy lasers, makes sure it check for each of
// the possible characters it could encounter and adjusts like the player laser
// function did
void Board::moveEnemyLas2(int x, int y)
{
    if(x+1 > row-1)
    {
        board[x][y] = emptyChar;
        --numEnemyLas;
        eLas2State = false;
        eLas2X = eLas2Y = 0;
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
        eLas2X = eLas2Y = 0;
    }
    else if(board[x+1][y] == enemyChar)
    {
        board[x][y] = emptyChar;
        board[x+1][y] = emptyChar;
        --numEnemyLas;  
        eLas2State = false;
        eLas2X = eLas2Y = 0;
    }
    else if(board[x+1][y] == lasChar)
    {
        board[x+1][y] = emptyChar;
        board[x][y] = emptyChar;
        --numEnemyLas;
        eLas2State = false;
        eLas2X = eLas2Y = 0;
    }
    else if(board[x+1][y] == plyrChar)
    {
        ldrBrd.lostLife();
        --numEnemyLas;
        eLas2State = false;
        eLas2X = eLas2Y = 0;
        loseLife();
    }
    else
    {
        --numEnemyLas;
        eLas2State = false;
        eLas2X = eLas2Y = 0;
    }
}

// this function happens when the player loses a life by being hit by an enemy 
// laser, it resets the conditions so the board can be recreated again
void Board::loseLife()
{
    Sleep(500);
    
    system("clear");
    
    cout << " _               _     _     _  __       _ "          << endl;
    cout << "| |             | |   | |   (_)/ _|     | |    "      << endl;  
    cout << "| |     ___  ___| |_  | |    _| |_ ___  | |    "      << endl;
    cout << "| |    / _ \\/ __| __| | |   | |  _/ _ \\ | |    "    << endl;
    cout << "| |___| (_) \\__ \\ |_  | |___| | ||  __/ |_|    "    << endl;
    cout << "\\_____/\\___/|___/\\__| \\_____/_|_| \\___| (_)    " << endl;
    
    cout << "\nPress [ENTER] to continue...";

    cin.ignore();
    
    system("clear");
    
    // reset some conditions
    plyrX = plyrY = 0;
    moveR = 3;
    moveL = 0;
    enemySpeed = 15;
    speedTime = 0;
    downState = false;
    netLR = 0;
    numEnemyLas = 0;
    lasX1 = lasX2 = lasX3 = lasX4 = lasX5 = lasX6 = lasX7 = lasX8 = lasX9 = lasX10 = 0;
    lasY1 = lasY2 = lasY3 = lasY4 = lasY5 = lasY6 = lasY7 = lasY8 = lasY9 = lasY10 = 0;
    lasX = lasY = 0;
    lasStateP = false;
    numEnemyLas = 0;
    eLas1X = eLas1Y = eLas2X = eLas2Y = 0;
    eLas1State = eLas2State = false;
    eLasSpeed = 0;
    
    if(ldrBrd.getLives() == 0)
        loseGame();
    else
    {
        enemyTimer();                   // determine enemy speed again
        createBoard();                  // recreate the board
    }
}

// this function double checks if the enemies are all gone so the player can
// either win the game or if the player has any lives left so they can lose
// the game
void Board::checkEnemies()
{
    int enemiesLeft = 0;                    // how many enemies are left
    
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
        gameState = false;
        winGame();              // you win
    }
    
    if(ldrBrd.lives <= 0 )
    {
        gameState = false;
        loseGame();             // you lose
    }
}

// this function is when the player defeats all the enemies and wins the game,
// it gives the player the option to play again and enter a highscore if the
// player got higher than the current highscore
void Board::winGame()
{
    Sleep(500);
    int choice = 0;
    
    system("clear");
    
    cout << " _    _ _                         _    "    << endl;
    cout << "| |  | (_)                       | |  "     << endl;
    cout << "| |  | |_ _ __  _ __   ___ _ __  | |  "     << endl;
    cout << "| |/\\| | | '_ \\| '_ \\ / _ \\ '__| | |  " << endl;
    cout << "\\  /\\  / | | | | | | |  __/ |    |_|  "   << endl;
    cout << " \\/  \\/|_|_| |_|_| |_|\\___|_|    (_)  "  << endl;       
    
    cout << " \nPress 1 to PLAY AGAIN\nPress 2 to EXIT\n[ENTER YOUR CHOICE]: ";
    cin >> choice;
    
    switch(choice)
    {
        case 1: break;
        case 2: exit(0); break;
    }
    
    // reset conditions in the constructor
    ldrBrd.lives = 3;
    ldrBrd.setScoreOne(0);
    plyrX = plyrY = 0;
    shield1 = shield2 = shield3 = shield4 = '4';
    numEnemies = 50;
    moveR = 3;
    moveL = 0;
    enemySpeed = 15;
    speedTime = 0;
    downState = false;
    netLR = 0;
    lasX1 = lasX2 = lasX3 = lasX4 = lasX5 = lasX6 = lasX7 = lasX8 = lasX9 = lasX10 = 0;
    lasY1 = lasY2 = lasY3 = lasY4 = lasY5 = lasY6 = lasY7 = lasY8 = lasY9 = lasY10 = 0;
    lasX = lasY = 0;
    lasStateP = false;
    numEnemyLas = 0;
    eLas1X = eLas1Y = eLas2X = eLas2Y = 0;
    eLas1State = eLas2State = false;
    eLasSpeed = 0;
    gameState = true;
    
    system("clear");
    
    startMenu();
    createBoard();
}

// this function is when the player loses all their lives before defeating all
// of the enemies, gives the player the option to play again
void Board::loseGame() 
{
    Sleep(500);
    int choice = 0;
    
    system("clear");
    
    cin.clear();
    
    cout << "_____                        _____                        "<<endl;    
    cout << "|  __ \\                      |  _  |                     "<<endl;  
    cout << "| |  \\/ __ _ _ __ ___   ___  | | | |_   _____ _ __       "<<endl;
    cout << "| | __ / _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__|  "<<endl;
    cout << "| |_\\ \\ (_| | | | | | |  __/ \\ \\_/ /\\ V /  __/ |     "<<endl;
    cout << "\\____/\\__,_|_| |_| |_|\\___|  \\___/  \\_/ \\___|_|     "<<endl;
    
    cout << " \nPress 1 to PLAY AGAIN\nPress 2 to EXIT\n[ENTER YOUR CHOICE]: ";
    cin >> choice;
    
    switch(choice)
    {
        case 1: break;
        case 2: exit(0); break;
    }         
    
    // reset conditions in the constructor
    ldrBrd.lives = 3;
    ldrBrd.setScoreOne(0);
    plyrX = plyrY = 0;
    shield1 = shield2 = shield3 = shield4 = '4';
    numEnemies = 50;
    moveR = 3;
    moveL = 0;
    enemySpeed = 15;
    speedTime = 0;
    downState = false;
    netLR = 0;
    lasX1 = lasX2 = lasX3 = lasX4 = lasX5 = lasX6 = lasX7 = lasX8 = lasX9 = lasX10 = 0;
    lasY1 = lasY2 = lasY3 = lasY4 = lasY5 = lasY6 = lasY7 = lasY8 = lasY9 = lasY10 = 0;
    lasX = lasY = 0;
    lasStateP = false;
    numEnemyLas = 0;
    eLas1X = eLas1Y = eLas2X = eLas2Y = 0;
    eLas1State = eLas2State = false;
    eLasSpeed = 0;
    gameState = true;
    
    system("clear");
    
    startMenu();
    createBoard();
}

// this function stops the enemies from moving down on the row before the shields
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

// this is a debug function to make sure there are no extra player characters 
// that pop up on the board, or lasers
void Board::debug()
{
    for(int i = 1; i < 13; i++)
    {
        for(int j = 1 ; j < col ; j++)
        {
            if(board[i][j] == plyrChar)
                board[i][j] = emptyChar;
            if(lasStateP && board[i][j] == lasChar)
            {
                if(eLas1X != i && eLas1Y != j)
                {
                    if(eLas2X != i && eLas2Y != j)
                    {
                        if(lasX != i && lasY != j)
                        {
                            board[i][j] = emptyChar;
                            lasX = lasY = 0;
                            lasStateP = false;
                        }
                    }
                }
            }
        }
    }
}
