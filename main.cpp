#include <iostream>
#include <string>
#include "board.cpp"
#include "movegen.cpp"

int main()
{
    Board board;
    std::cout << board.prettyPrint();
    generateWPawnMoves(board.getWhitePawns(), ~board.getOccupied());
    return 0;
}