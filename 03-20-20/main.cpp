#include "header.h"
#include "board.h"

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
