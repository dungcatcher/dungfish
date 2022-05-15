#include <iostream>
#include <string>
#include "board.hpp"
#include "movegen.hpp"

int main()
{
    Board board;
    std::cout << board.prettyPrint();
    generateWPawnMoves(board.getWhitePawns(), ~board.getOccupied());
    
    return 0;
}