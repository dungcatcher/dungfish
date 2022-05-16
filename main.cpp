#include <iostream>
#include <string>
#include "board.hpp"
#include "movegen.hpp"

// I am homosexual

int main()
{
    Board board;
    std::cout << board.prettyPrint();
    Move moveList[256];
    moveList = generateWPawnMoves(moveList, board.getWhitePawns(), ~board.getOccupied());
    for (auto i : moveList) {
        std::cout << i.start << " " << i.end << "\n";
    } // i am gay
    return 0;
}