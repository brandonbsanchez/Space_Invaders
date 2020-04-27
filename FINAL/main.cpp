// -----------------------------------------------------------------------------
// This is our main which controls the game.
// -----------------------------------------------------------------------------
int main()
{
    // create board object, initialize bool variable
    Board board;
    bool notLost = true;
    
    // start menu
    board.startMenu();
    
    // create the game board
    board.createBoard();

    // play Space Invaders; display board, get input, move enemies
    while(notLost)
    {
        system("clear");                // clear screen to display board again
        
        board.debug();                  // debug player
        
        if(board.getLaserStateP())      // if player laser is on the board
            board.movPlyrLas();
        
        // if the enemies are to move again; left, right, or down
        if(board.getSpeedTimer() == board.getEnemySpeed())
        {
            if(board.getDownState()){
                if (board.enemyStop()){
                    board.downStop();
                }else {
                    board.moveEnemiesD();
                }
            }
            board.moveEnemiesLR();
        }

        board.enemyLas();               // move enemy lasers
        
        board.debug();                  // debug player
        
        board.ldrBrd.getLeaderboard();  // leaderboard top
        board.dispBrd();                // game board 2D array
        board.ldrBrd.getBtmBoard();     // leaderboard bottom
        
        board.input();                  // player input
        
        board.speedTimer();             // increment speed timer
        board.eLasSpeedUp();            // increment enemy laser speed timer
        board.enemyTimer();             // increment enemy movement timer
        
        board.checkEnemies();           // checks number of enemies on board, lives
    }

    return 0;
}
