#include <iostream>
#include <string>
#include <vector>

#include "board.hpp"
#include "movegen.hpp"

int main()
{
    Board board;
    std::cout << board.prettyPrint();
    std::vector<Move> moveList;
    generatePawnMoves(moveList, true, board.getWhitePawns(), ~board.getOccupied());

    return 0;
}